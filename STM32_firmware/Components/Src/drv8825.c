/**
  ******************************************************************************
  * @file		: drv8825.c
  * @author  	: Krzysztof Witkowski
  * @date    	: Dec 17, 2022
  * @brief   	: DRV8825 step motor driver source code file
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include "drv8825.h"

/* Public function -----------------------------------------------------------*/

HAL_StatusTypeDef DRV8825_Start(DRV8825_HandleTypeDef* hdrv8825){
	 return HAL_TIM_PWM_Start(hdrv8825->Tim, hdrv8825->TimChannel);
}

HAL_StatusTypeDef DRV8825_SetSpeed(DRV8825_HandleTypeDef* hdrv8825, DRV8825_SpeedType speed){

	// Protect from setting speed higher than maximum
	if(speed > hdrv8825->MaxSpeed || speed < (-1 * hdrv8825->MaxSpeed) ){
		return HAL_ERROR;
	}

	// Skip rest of function body if speed is already set to target speed
	if(speed == hdrv8825->Speed)
		return HAL_OK;
	hdrv8825->Speed = speed;

	// Operate direction pin, transform speed to absolute value, handle zero speed exception
	if(speed > 0){
		HAL_GPIO_WritePin(hdrv8825->DirPort, hdrv8825->DirPin, GPIO_PIN_SET);
	}else if(speed < 0){
		HAL_GPIO_WritePin(hdrv8825->DirPort, hdrv8825->DirPin, GPIO_PIN_RESET);
		speed *= -1;
	}else{
		HAL_GPIO_WritePin(hdrv8825->EnblPort, hdrv8825->EnblPin, GPIO_PIN_SET);
		__HAL_TIM_SET_AUTORELOAD(hdrv8825->Tim, 0xFFFFFFFF);
		__HAL_TIM_SET_COMPARE(hdrv8825->Tim, hdrv8825->TimChannel, 0xFFFFFFFF);
		return HAL_OK;
	}
	HAL_GPIO_WritePin(hdrv8825->EnblPort, hdrv8825->EnblPin, GPIO_PIN_RESET);

	// Calculate counter frequency, set proper values to ARR and CCR timer registers
	uint32_t Counter_freq = HAL_RCC_GetPCLK2Freq() / (hdrv8825->Tim->Instance->PSC + 1);
	uint32_t ARR_value = DRV8825_TimArrSpeed(Counter_freq, hdrv8825->StepsPerRev, speed);
	uint32_t CCR_value = ARR_value - DRV8825_PulseWidthCycles(Counter_freq, hdrv8825->PulseWidthUs);
	__HAL_TIM_SET_AUTORELOAD(hdrv8825->Tim, ARR_value);
	__HAL_TIM_SET_COMPARE(hdrv8825->Tim, hdrv8825->TimChannel, CCR_value);

	// Protect from setting to ARR lower value than current counter value
	if(__HAL_TIM_GET_COUNTER(hdrv8825->Tim) > ARR_value){
		__HAL_TIM_SET_COUNTER(hdrv8825->Tim, 0);
	}

	return HAL_OK;
}
