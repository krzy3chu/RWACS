/**
  ******************************************************************************
 * @file		: encoder.c
  * @author  	: Krzysztof Witkowski
  * @version 	: 1.10.1
  * @date    	: Dec 20, 2022
  * @brief   	: Encoder source code file
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include "encoder.h"

/* Public function -----------------------------------------------------------*/

/**
 * @brief:      Encoder update counter function
 * @param[in]   *henc point to a encoder handle
 * @param[in]   pin is a pin type 
 * @return:     counter value
 */
int16_t ENC_UpdateCounter(ENC_HandleTypeDef* henc, ENC_PinType pin)
{
	if(pin == henc->CH1_Pin){
		if(HAL_GPIO_ReadPin(henc->CH2_Port, henc->CH2_Pin)){
			henc->Counter = (henc->Counter >= henc->CounterMax) ? henc->CounterMax : henc->Counter + henc->Step;
		}else{
			henc->Counter = (henc->Counter <= henc->CounterMin) ? henc->CounterMin : henc->Counter - henc->Step;
		}
	}
	return henc->Counter;
}

/**
 * @brief:      Encoder on button press function
 * @param[in]   *henc points to a enoder handle
 * @param[in]   pin is a pin type
 * @return:     pin type
 *              - true encoder button
 *              - false not encoder button
 */
bool ENC_OnButtonPress(ENC_HandleTypeDef* henc, ENC_PinType pin){
	return pin == henc->BTN_Pin;
}
