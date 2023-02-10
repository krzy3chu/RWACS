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

static int32_t msg[2]; /**< uart message buffer */


static PID_HandleTypeDef* _hpid; /**< pid  handle */

/* Public variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private function ----------------------------------------------------------*/

/* Public function -----------------------------------------------------------*/

/**
 * @brief     Uart parse data function
 * @note      parse received data and assign it to the pid handle
 */
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

/**
 * @brief     	Uart print controller state function
 * @param[in]	*sepoint points to a setpoint buffer
 * @param[in]	*output points to a output buffer
 * @param[in]	*filtered_setpoint points to a filtered setpoint buffer
 * @param[in]	*controller_output points to a controller output buffer
 * @return    	status code
 * @note      	return code uses HAL_StatusTypeDef
 */
HAL_StatusTypeDef RWACS_Print_Controller_State(float* setpoint, float* output,
											   float* filtered_setpoint, float* controller_output)
{
	return RWACS_Print("%0.1f, %0.1f, %0.1f, %0.1f\n", *setpoint, *output, *filtered_setpoint, *controller_output);
}

/**
 * @brief     	Uart assign pid handle function
 * @param[in]	*hpid points to a pid handle buffer
 */
void RWACS_UART_Init(PID_HandleTypeDef* hpid)
{
	_hpid = hpid;
}

/**
 * @brief     	Uart print controller state function
 * @param[in]	*fmt specifies a message format
 * @param[in]	... are varg values to send
 * @return    	status code
 * @note      	return code uses HAL_StatusTypeDef
 */
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

    free(msg);
    return HAL_OK;
}

/**
 * @brief     	Uart dma receive function
 * @return    	status code
 * @note      	return code uses HAL_StatusTypeDef
 */
HAL_StatusTypeDef RWACS_Receive()
{
	return HAL_UART_Receive_DMA(CURRENT_UART_HANDLE, (uint8_t*)msg, sizeof(msg));
}
