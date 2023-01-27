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

PID_HandleTypeDef hpid1 = {
		.Kp = 0.1,
		.Ki = 0.1,
		.Kd = 0.1
};
