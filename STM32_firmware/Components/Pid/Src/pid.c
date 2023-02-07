/**
  ******************************************************************************
  * @file		: pid.c
  * @author  	: Krzysztof Witkowski
  * @date    	: Jan 27, 2023
  * @brief   	: Pid controller source code file
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include "pid.h"
#include <stdlib.h>  // malloc, abs

/* Public variables ----------------------------------------------------------*/

void PID_Init(PID_HandleTypeDef* hpid){
	hpid->Pid = malloc(sizeof(arm_pid_instance_f32));
	hpid->Pid->Kp=hpid->Kp;
	hpid->Pid->Ki=hpid->Ki;
	hpid->Pid->Kd=hpid->Kd;
	arm_pid_init_f32(hpid->Pid, 1);

}

void PID_Control(PID_HandleTypeDef* hpid, float32_t* feedback, float32_t* control){
	float cont = (-1) * arm_pid_f32(hpid->Pid, ((int) (hpid->Setpoint - *feedback)));

	/* ---------- scale pid signal to reduce non-linear object dynamic ---------- */
	if(cont < -100){
		cont -= 900;
	}else if(cont > 100){
		cont += 900;
	}else{
		cont *= 10;
	}
	*control = cont;
}
