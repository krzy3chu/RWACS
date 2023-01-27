/**
  ******************************************************************************
  * @file		: pid.c
  * @author  	: Krzysztof Witkowski
  * @date    	: Jan 27, 2023
  * @brief   	: Pid controller configuration source code file
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include "pid.h"
#include <stdlib.h>  // malloc

/* Public variables ----------------------------------------------------------*/

void PID_Init(PID_HandleTypeDef* hpid){
	hpid->Pid = malloc(sizeof(arm_pid_instance_f32));
	arm_pid_init_f32(hpid->Pid, 1);
}

void PID_Control(PID_HandleTypeDef* hpid, float32_t* setpoint, float32_t* feedback, float32_t* control){
	*control = (-1) * arm_pid_f32(hpid->Pid, (*setpoint - *feedback));
}
