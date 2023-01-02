/**
  ****************************************************************************
  * @file		: bh1750.h
  * @author  	: Mateusz Koza
  * @date    	: Nov 16, 2022
  * @brief   	: bh1750 configuration header file
  *
  ****************************************************************************
  */

#ifndef INC_RWACS_H_
#define INC_RWACS_H_

/* Config --------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/

#include "stm32f746xx.h"
#include "usart.h"

/* Typedef -------------------------------------------------------------------*/

/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

#define CURRENT_UART_HANDLE &huart3

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

HAL_StatusTypeDef RWACS_print(const char *fmt, ...);

HAL_StatusTypeDef RWACS_receive(uint32_t* receiver, uint32_t* data);

#endif /* INC_RWACS_H_ */
