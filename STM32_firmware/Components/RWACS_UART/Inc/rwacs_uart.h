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

typedef struct {
	uint32_t kp;
	uint32_t ki;
	uint32_t kd;
	uint32_t ref;
} Controller_HandleTypeDef;

typedef enum {
	KP,
	KI,
	KD,
	REF
} RWACS_ReceiveCodes;

/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

#define CURRENT_UART_HANDLE &huart3

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

void RWACS_UART_Init(Controller_HandleTypeDef* hcntrl);

HAL_StatusTypeDef RWACS_Print(const char *fmt, ...);

HAL_StatusTypeDef RWACS_Receive();

#endif /* INC_RWACS_H_ */
