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


/**
 * @brief uart communication codes enumeration definition
 */
typedef enum {
	PROPORTIONAL_GAIN,
	INTEGRAL_GAIN,
	DERIVATIVE_GAIN,
	SETPOINT
} RWACS_ControllerIDs;

/**
 * @brief current uart handle configuration definition
 */
#define CURRENT_UART_HANDLE &huart3

/**
 * @brief     Uart parse data function
 * @note      parse received data and assign it to the pid handle
 */
void RWACS_Parse_Data();


/**
 * @brief     	Uart print controller state function
 * @param[in]	*sepoint points to a setpoint buffer
 * @param[in]	*output points to a output buffer
 * @param[in]	*filtered_setpoint points to a filtered setpoint buffer
 * @param[in]	*controller_output points to a controller output buffer
 * @return    	status code
 * @note      	return code uses HAL_StatusTypeDef
 */
HAL_StatusTypeDef RWACS_Print_Controller_State(float* setpoint , float* output,
											   float* filtered_setpoint, float* controller_output);


/**
 * @brief     	Uart assign pid handle function
 * @param[in]	*hpid points to a pid handle buffer
 */
void RWACS_UART_Init(PID_HandleTypeDef* hpid);

/**
 * @brief     	Uart print controller state function
 * @param[in]	*fmt specifies a message format
 * @param[in]	... are varg values to send
 * @return    	status code
 * @note      	return code uses HAL_StatusTypeDef
 */
HAL_StatusTypeDef RWACS_Print(const char *fmt, ...);

/**
 * @brief     	Uart dma receive function
 * @return    	status code
 * @note      	return code uses HAL_StatusTypeDef
 */
HAL_StatusTypeDef RWACS_Receive();

#endif /* INC_RWACS_H_ */
