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

/**
 * @brief		 Start Tim timer in PWM mode
 * @param[in]	 *hdrv8825 DRV8825 handler
 * @retval		 HAL_status from PWM start function
 */
HAL_StatusTypeDef DRV8825_Init(DRV8825_HandleTypeDef* hdrv8825){
	 return HAL_TIM_PWM_Start(hdrv8825->Tim, hdrv8825->TimChannel);
}

/**
 * @brief		Set timer, Dir and Enbl pins properly according to target speed
 * @param[in]	*hdrv8825 DRV8825 handler
 * @param[in]	*speed target motor rotational speed
 * @retval		HAL_OK speed is setup properly
 * @retval	  	HAL_ERROR absolute value of target speed is higher than maximum motor rotational speed
 */
HAL_StatusTypeDef DRV8825_SetSpeed(DRV8825_HandleTypeDef* hdrv8825, DRV8825_SpeedType* speed){

	// Protect from setting speed higher than maximum
	if(*speed > hdrv8825->MaxSpeed || *speed < (-1 * hdrv8825->MaxSpeed) ){
		return HAL_ERROR;
	}

	// Skip rest of function body if speed is already set to target speed
	if(*speed == hdrv8825->Speed)
		return HAL_OK;
	hdrv8825->Speed = *speed;

	// Operate direction pin, transform speed to absolute value, handle zero speed exception
	if(*speed > 1){
		HAL_GPIO_WritePin(hdrv8825->DirPort, hdrv8825->DirPin, GPIO_PIN_SET);
	}else if(*speed < 1){
		HAL_GPIO_WritePin(hdrv8825->DirPort, hdrv8825->DirPin, GPIO_PIN_RESET);
		*speed *= -1;
	}else{
		HAL_GPIO_WritePin(hdrv8825->EnblPort, hdrv8825->EnblPin, GPIO_PIN_SET);
		__HAL_TIM_SET_AUTORELOAD(hdrv8825->Tim, 0xFFFFFFFF);
		__HAL_TIM_SET_COMPARE(hdrv8825->Tim, hdrv8825->TimChannel, 0xFFFFFFFF);
		return HAL_OK;
	}
	HAL_GPIO_WritePin(hdrv8825->EnblPort, hdrv8825->EnblPin, GPIO_PIN_RESET);

	// Calculate counter frequency, set proper values to ARR and CCR timer registers
	uint32_t Counter_freq = HAL_RCC_GetPCLK2Freq() / (hdrv8825->Tim->Instance->PSC + 1);
	uint32_t ARR_value = DRV8825_TimArrSpeed(Counter_freq, hdrv8825->StepsPerRev, *speed);
	uint32_t CCR_value = ARR_value - DRV8825_PulseWidthCycles(Counter_freq, hdrv8825->PulseWidthUs);
	__HAL_TIM_SET_AUTORELOAD(hdrv8825->Tim, ARR_value);
	__HAL_TIM_SET_COMPARE(hdrv8825->Tim, hdrv8825->TimChannel, CCR_value);

	// Protect from setting to ARR lower value than current counter value
	if(__HAL_TIM_GET_COUNTER(hdrv8825->Tim) > ARR_value){
		__HAL_TIM_SET_COUNTER(hdrv8825->Tim, 0);
	}
	return HAL_OK;
}

/**
 * @brief 		Set motor speed according to desired acceleration
 * @param[in]	*hdrv8825 DRV8825 handler
 * @param[in]	*acceleration desired acceleration, expressed in degrees per second squared
 * @retval 		HAL_OK speed is setup properly
 * @retval		HAL_ERROR absolute value of target speed is higher than maximum motor rotational speed set in DRV8825_MaxSpeed definition
 */
HAL_StatusTypeDef DRV8825_SetAcceleration(DRV8825_HandleTypeDef* hdrv8825, DRV8825_AccelerationType* acceleration){
	float acc_speed;
	if(*acceleration > hdrv8825->MaxAcceleration){
		*acceleration = hdrv8825->MaxAcceleration;
	}else if(*acceleration < -hdrv8825->MaxAcceleration){
		*acceleration = -hdrv8825->MaxAcceleration;
	}
	acc_speed = hdrv8825->Speed + (*acceleration) * (hdrv8825->SamplingTime);
	return DRV8825_SetSpeed(hdrv8825, &acc_speed);
}
