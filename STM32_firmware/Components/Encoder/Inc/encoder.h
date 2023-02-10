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


/**
 * @defgroup Encoder Encoder module
 * @brief    Encoder struct and functions
 * @{
 */

/**
 * @addtogroup Encoder
 * @{
 */

/* Define --------------------------------------------------------------------*/

/**
 * @brief encoder type defines
 */
#define ENC_PortType GPIO_TypeDef*
#define ENC_PinType uint16_t

/* Typedef -------------------------------------------------------------------*/

/**
 * @brief encoder structure definition
 */
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
  uint16_t Step;
} ENC_HandleTypeDef;

/* Public function prototypes ------------------------------------------------*/

/**
 * @brief:      Encoder update counter function
 * @param[in]   *henc point to a encoder handle
 * @param[in]   pin is a pin type 
 * @return:     counter value
 */
int16_t ENC_UpdateCounter(ENC_HandleTypeDef* henc, ENC_PinType pin);

/**
 * @brief:      Encoder on button press function
 * @param[in]   *henc points to a enoder handle
 * @param[in]   pin is a pin type
 * @return:     pin type
 *              - true encoder button
 *              - false not encoder button
 */
bool ENC_OnButtonPress(ENC_HandleTypeDef* henc, ENC_PinType pin);

/**
 * @}
 */

/**
 * @}
 */

#endif /* INC_ENCODER_H_ */
