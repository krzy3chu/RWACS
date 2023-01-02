/**
  ****************************************************************************
  * @file		: bh1750.cpp
  * @author  	: Mateusz Koza
  * @date    	: Nov 16, 2022
  * @brief   	: bh1750 source code file
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
    	free(msg);
    	return HAL_ERROR;
   	}

    va_start(args, fmt);
    msg_size = vsnprintf(msg, msg_size + 1, fmt, args);
    va_end(args);
    if(msg_size < 0){
    	free(msg);
    	return HAL_ERROR;
    }

    if(HAL_UART_Transmit(CURRENT_UART_HANDLE, (uint8_t*)msg, msg_size, HAL_MAX_DELAY) != HAL_OK){
    	free(msg);
    	return HAL_ERROR;
    }

    free(msg);
    return HAL_OK;
}


HAL_StatusTypeDef RWACS_receive(uint8_t* pData, uint16_t Size)
{
	return HAL_UART_Receive(CURRENT_UART_HANDLE, pData, Size, HAL_MAX_DELAY);
}
