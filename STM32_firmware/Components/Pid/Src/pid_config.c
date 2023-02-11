/**
  ******************************************************************************
  * @file		: pid_config.c
  * @author  	: Krzysztof Witkowski
  * @date    	: Jan 27, 2023
  * @brief   	: Pid controller configuration source code file
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include "pid.h"

/* Public variables ----------------------------------------------------------*/

/**
 * @brief pid handle definition
 */
PID_HandleTypeDef hpid1 = {
		.Kp = 70,
		.Ki = 0,
		.Kd = 500
};
