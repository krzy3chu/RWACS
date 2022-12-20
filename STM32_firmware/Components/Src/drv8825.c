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
	 HAL_TIM_PWM_Start_IT(hdrv8825->Tim, hdrv8825->TimChannel);
	 return HAL_OK;
}

HAL_StatusTypeDef DRV8825_SetSpeed(DRV8825_HandleTypeDef* hdrv8825, DRV8825_SpeedType speed){
	return HAL_OK;
}
