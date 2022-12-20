/**
  ******************************************************************************
  * @file		: drv8825_config.c
  * @author  	: Krzysztof Witkowski
  * @date    	: Dec 17, 2022
  * @brief   	: DRV8825 step motor driver configuration source code file
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include "drv8825_config.h"

/* Public variables ----------------------------------------------------------*/

DRV8825_HandleTypeDef hdrv8825_1 = {
  .Tim = &htim2,
  .TimChannel = TIM_CHANNEL_1,
  .Speed = 0,
  .DirPort = DRV8825_DIR_GPIO_Port,
  .DirPin = DRV8825_DIR_Pin,
  .EnblPort = DRV8825_ENABLE_GPIO_Port,
  .EnblPin = DRV8825_ENABLE_Pin
};
