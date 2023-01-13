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


/* Typedef -------------------------------------------------------------------*/

/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

static uint32_t msg[2];

static Controller_HandleTypeDef* hcntrl1;

/* Public variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private function ----------------------------------------------------------*/

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	uint32_t id = msg[0];
	uint32_t data = msg[1];

	switch(id)
	{
		case KP:
			hcntrl1->kp = data;
			RWACS_Print("kp changed\n");
			break;

		case KI:
			hcntrl1->ki = data;
			RWACS_Print("ki changed\n");
			break;

		case KD:
			hcntrl1->kd = data;
			RWACS_Print("kd changed\n");
			break;

		case REF:
			hcntrl1->ref = data;
			RWACS_Print("ref changed\n");
			break;

		default:
			RWACS_Print("invalid id\n");
			break;
	}

	RWACS_Receive();
}

/* Public function -----------------------------------------------------------*/

void RWACS_UART_Init(Controller_HandleTypeDef* hcntrl)
{
	hcntrl1 = hcntrl;
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

    if(HAL_UART_Transmit_DMA(CURRENT_UART_HANDLE, (uint8_t*)msg, msg_size)!= HAL_OK){
    	free(msg);
    	return HAL_ERROR;
    }

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
