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
	if(speed > DRV8825_MaxSpeed || speed < -DRV8825_MaxSpeed){
		return HAL_ERROR;
	}
	hdrv8825->Speed = speed;
	if(speed > 0){
		HAL_GPIO_WritePin(hdrv8825->DirPort, hdrv8825->DirPin, GPIO_PIN_SET);
	}else if(speed < 0){
		HAL_GPIO_WritePin(hdrv8825->DirPort, hdrv8825->DirPin, GPIO_PIN_RESET);
		speed *= -1;
	}else{
		__HAL_TIM_SET_AUTORELOAD(hdrv8825->Tim, 0xFFFFFFFF);  // if speed is set to 0, set ARR and CCR to maximum value
		__HAL_TIM_SET_COMPARE(hdrv8825->Tim, hdrv8825->TimChannel, 0xFFFFFFFF);
		return HAL_OK;
	}
	if(__HAL_TIM_GET_COUNTER(hdrv8825->Tim) > DRV8825_TimArrSpeed){ // protect from setting to ARR lower value than current counter value
		__HAL_TIM_SET_COUNTER(hdrv8825->Tim, 0);
	}
	__HAL_TIM_SET_AUTORELOAD(hdrv8825->Tim, DRV8825_TimArrSpeed);
	__HAL_TIM_SET_COMPARE(hdrv8825->Tim, hdrv8825->TimChannel, DRV8825_TimArrSpeed / 2);
	return HAL_OK;
}
