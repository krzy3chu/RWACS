/**
  ****************************************************************************
  * @file		: rwacs_uart.c
  * @author  	: Mateusz Koza
  * @date    	: Jan 5, 2023
  * @brief   	: rwacs_uart source code file
  *
  ****************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include "rwacs_uart.h"
#include "stm32f7xx.h"
#include "usart.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arm_math.h>


/* Typedef -------------------------------------------------------------------*/

/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

static int32_t msg[2];

static PID_HandleTypeDef* _hpid;

/* Public variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private function ----------------------------------------------------------*/

/* Public function -----------------------------------------------------------*/


void RWACS_Parse_Data()
{
	int32_t id = msg[0];
	float32_t data = (float32_t)msg[1];
	switch(id)
	{
		case PROPORTIONAL_GAIN:
			_hpid->Kp = data;
			break;

		case INTEGRAL_GAIN:
			_hpid->Ki = data;
			break;

		case DERIVATIVE_GAIN:
			_hpid->Kd = data;
			break;

		case SETPOINT:
			_hpid->Setpoint = data;
			break;
	}
	RWACS_Receive();
}

HAL_StatusTypeDef RWACS_Print_Controller_State(float* setpoint, float* output,
											   float* filtered_setpoint, float* controller_output)
{
	return RWACS_Print("%0.1f, %0.1f, %0.1f, %0.1f\n", *setpoint, *output, *filtered_setpoint, *controller_output);
}

void RWACS_UART_Init(PID_HandleTypeDef* hpid)
{
	_hpid = hpid;
}

HAL_StatusTypeDef RWACS_Print(const char* fmt, ...)
{
    va_list args;
    char* msg;
    int msg_size;

    va_start(args, fmt);
    msg_size = vsnprintf(NULL, 0, fmt, args);
    va_end(args);
    if(msg_size < 0){
    	return HAL_ERROR;
    }

    msg = malloc(msg_size + 1);
    if(msg == NULL){
    	return HAL_ERROR;
   	}

    va_start(args, fmt);
    msg_size = vsnprintf(msg, msg_size + 1, fmt, args);
    va_end(args);
    if(msg_size < 0){
    	free(msg);
    	return HAL_ERROR;
    }

    if(HAL_UART_Transmit(CURRENT_UART_HANDLE, (uint8_t*)msg, msg_size, HAL_MAX_DELAY)!= HAL_OK){
    	free(msg);
    	return HAL_ERROR;
    }

//    if(HAL_UART_Transmit_IT(CURRENT_UART_HANDLE, (uint8_t*)msg, msg_size)!= HAL_OK){
//        free(msg);
//        return HAL_ERROR;
//    }


    free(msg);
    return HAL_OK;
}


HAL_StatusTypeDef RWACS_Receive()
{
	if(HAL_UART_Receive_DMA(CURRENT_UART_HANDLE, (uint8_t*)msg, sizeof(msg)) != HAL_OK){
		return HAL_ERROR;
	}
	return HAL_OK;
}
