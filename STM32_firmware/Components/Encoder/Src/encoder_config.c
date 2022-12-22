/**
  ******************************************************************************
  * @file		: encoder_config.c
  * @author  	: Krzysztof Witkowski
  * @version 	: 1.10.1
  * @date    	: Dec 20, 2022
  * @brief   	: Encoder configuration source code file
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include "encoder_config.h"
#include "main.h"

/* Public variables ----------------------------------------------------------*/

ENC_HandleTypeDef henc1 = {
  .CH1_Port = ENC_CH1_GPIO_Port,
  .CH1_Pin = ENC_CH1_Pin,
  .CH2_Port  = ENC_CH2_GPIO_Port,
  .CH2_Pin  = ENC_CH2_Pin,
  .BTN_Port = ENC_BTN_GPIO_Port,
  .BTN_Pin = ENC_BTN_Pin,
  .Counter  = 0,
  .CounterMax = 400,
  .CounterMin = -400,
  .Step = 20
};
