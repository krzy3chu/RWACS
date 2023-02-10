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
#include <stdlib.h>

/* Public function prototypes ------------------------------------------------*/

/**
 * @brief           Pid initialize function
 * @param[in]       *pid points to a pid handle
 * @return          Nothing
 */
void PID_Init(PID_HandleTypeDef* hpid){
	hpid->Pid = malloc(sizeof(arm_pid_instance_f32));
	hpid->Pid->Kp=hpid->Kp;
	hpid->Pid->Ki=hpid->Ki;
	hpid->Pid->Kd=hpid->Kd;
	arm_pid_init_f32(hpid->Pid, 1);

}


/**
 * @brief           Pid control function
 * @param[in]       *pid points to a pid handle
 * @param[in]       *feedback points to feedback buffer
 * @param[out]      *control points to feedback control
 * @return Nothing
 */
void PID_Control(PID_HandleTypeDef* hpid, float32_t* feedback, float32_t* control){
	*control = (-1) * arm_pid_f32(hpid->Pid, ((int) (hpid->Setpoint - *feedback)));

	/* ---------- scale pid signal to reduce non-linear object dynamic ---------- */
	if(*control < -100){
		*control -= 900;
	}else if(*control > 100){
		*control += 900;
	}else{
		*control *= 10;
	}
}
