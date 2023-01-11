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

/* Public variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private function ----------------------------------------------------------*/

/* Public function -----------------------------------------------------------*/

HAL_StatusTypeDef RWACS_print(const char* fmt, ...)
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


HAL_StatusTypeDef RWACS_receive(uint32_t* receiver, uint32_t* data)
{
	uint32_t msg[2];
	if(HAL_UART_Receive(CURRENT_UART_HANDLE, (uint8_t*)msg, sizeof(msg), HAL_MAX_DELAY) != HAL_OK){
		return HAL_ERROR;
	}
	*receiver = msg[0];
	*data = msg[1];
	return HAL_OK;
}
