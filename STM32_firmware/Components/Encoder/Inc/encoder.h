/**
  ******************************************************************************
  * @file		: encoder.h
  * @author  	: Krzysztof Witkowski
  * @version 	: 1.10.1
  * @date    	: Dec 20, 2022
  * @brief   	: Encoder header file
  *
  ******************************************************************************
  */

#ifndef INC_ENCODER_H_
#define INC_ENCODER_H_

/* Includes ------------------------------------------------------------------*/

#include "stm32f7xx_hal.h"
#include <stdbool.h>

/* Define --------------------------------------------------------------------*/

#define ENC_PortType GPIO_TypeDef*
#define ENC_PinType uint16_t

/* Typedef -------------------------------------------------------------------*/

typedef struct {
  ENC_PortType CH1_Port;
  ENC_PinType  CH1_Pin;
  ENC_PortType CH2_Port;
  ENC_PinType  CH2_Pin;
  ENC_PortType BTN_Port;
  ENC_PinType  BTN_Pin;
  int16_t Counter;
  int16_t CounterMax;
  int16_t CounterMin;
  uint8_t Step;
} ENC_HandleTypeDef;

/* Public function prototypes ------------------------------------------------*/

/**
 * @brief Increment or decrement encoder counter, based on a CH2_Pin state
 * @param[in] henc: Encoder handler
 * @param[in] pin: GPIO external interrupt callback pin
 * @return Current counter value
 */
int16_t ENC_UpdateCounter(ENC_HandleTypeDef* henc, ENC_PinType pin);

/**
 * @brief Checks if encoder button was pressed
 * @param[in] henc: Encoder handler
 * @param[in] pin: GPIO external interrupt callback pin
 * @return true if callback came from encoder button pin, false if not
 */
bool ENC_OnButtonPress(ENC_HandleTypeDef* henc, ENC_PinType pin);


#endif /* INC_ENCODER_H_ */
