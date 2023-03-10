/**
  ******************************************************************************
  * @file		: pid_config.h
  * @author  	: Krzysztof Witkowski
  * @date    	: Jan 27, 2023
  * @brief   	: Pid controller configuration header file
  *
  ******************************************************************************
  */

#ifndef PID_INC_PID_CONFIG_H_
#define PID_INC_PID_CONFIG_H_

/* Includes ------------------------------------------------------------------*/

#include "pid.h"

/* Public variables ----------------------------------------------------------*/

/**
 * @addtogroup Pid
 * @{
 */

extern PID_HandleTypeDef hpid1; /**< pid  handle */

/**
 * @}
 */

#endif /* PID_INC_PID_CONFIG_H_ */
