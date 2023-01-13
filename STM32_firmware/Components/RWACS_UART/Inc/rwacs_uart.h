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
	uint32_t proportional_gain;
	uint32_t integral_gain;
	uint32_t derivative_gain;
	uint32_t setpoint;
} Controller_HandleTypeDef;

typedef enum {
	PROPORTIONAL_GAIN,
	INTEGRAL_GAIN,
	DERIVATIVE_GAIN,
	SETPOINT
} RWACS_ControllerIDs;

typedef enum {
	CONTROLLER_STATE,
	LOG,
} RWACS_MessageType;

/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

#define CURRENT_UART_HANDLE &huart3

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

HAL_StatusTypeDef RWACS_Print_Controller_State(int16_t* setpoint , int16_t* output, int16_t* filtered_setpoint, int16_t* controller_output);

void RWACS_UART_Init(Controller_HandleTypeDef* hcntrl);

HAL_StatusTypeDef RWACS_Print(const char *fmt, ...);

HAL_StatusTypeDef RWACS_Receive();

#endif /* INC_RWACS_H_ */
