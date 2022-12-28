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


/* Typedef -------------------------------------------------------------------*/

/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private function ----------------------------------------------------------*/

PUTCHAR_PROTOTYPE
{
  HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
  return ch;
}

/* Public function -----------------------------------------------------------*/

HAL_StatusTypeDef RWACS_print(const char *fmt, ...)
{
	HAL_DMA_StateTypeDef status;
    va_list args;
    va_start(args, fmt);
    if(vprintf(fmt, args)>0)
    {
    	status = HAL_OK;
    }
    else status = HAL_ERROR;

    va_end(args);

    return status;
}

    HAL_StatusTypeDef RWACS_read(uint8_t* pData, uint16_t Size)
{
	return HAL_UART_Receive(CURRENT_UART_HANDLE, pData, Size, HAL_MAX_DELAY);
}
