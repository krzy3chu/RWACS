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
#include "pid.h"

/* Typedef -------------------------------------------------------------------*/

typedef enum {
	PROPORTIONAL_GAIN,
	INTEGRAL_GAIN,
	DERIVATIVE_GAIN,
	SETPOINT
} RWACS_ControllerIDs;

/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

#define CURRENT_UART_HANDLE &huart3

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

void RWACS_Parse_Data();

HAL_StatusTypeDef RWACS_Print_Controller_State(float* setpoint , float* output,
											   float* filtered_setpoint, float* controller_output);

void RWACS_UART_Init(PID_HandleTypeDef* hpid);

HAL_StatusTypeDef RWACS_Print(const char *fmt, ...);

HAL_StatusTypeDef RWACS_Receive();

#endif /* INC_RWACS_H_ */
