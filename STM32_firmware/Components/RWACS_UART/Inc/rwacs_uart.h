/**
  ****************************************************************************
  * @file		: rwacs_uart.h
  * @author  	: Mateusz Koza
  * @date    	: Jan 5, 2022
  * @brief   	: rwacs_uart configuration header file
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
