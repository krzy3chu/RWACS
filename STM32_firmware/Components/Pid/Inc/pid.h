/**
  ******************************************************************************
  * @file		: pid.h
  * @author  	: Krzysztof Witkowski
  * @date    	: Jan 27, 2023
  * @brief   	: Pid controller configuration header file
  *
  ******************************************************************************
  */

#ifndef PID_INC_PID_H_
#define PID_INC_PID_H_

/* Includes ------------------------------------------------------------------*/

#include "arm_math.h"

/* Typedef -------------------------------------------------------------------*/

/**
 * @brief pid structure definition
 */
typedef struct {
	float32_t Kp;
	float32_t Ki;
	float32_t Kd;
	float32_t Setpoint;
	arm_pid_instance_f32* Pid;
} PID_HandleTypeDef;

/* Public function prototypes ------------------------------------------------*/

/**
 * @brief           Pid initialize function
 * @param[in]       *hpid points to a pid handle
 * @return          Nothing
 */
void PID_Init(PID_HandleTypeDef* hpid);

/**
 * @brief           Pid control function
 * @param[in]       *hpid points to a pid handle
 * @param[in]       *feedback points to feedback buffer
 * @param[out]      *control points to feedback control
 * @return Nothing
 */
void PID_Control(PID_HandleTypeDef* hpid, float32_t* feedback, float32_t* control);

#endif /* PID_INC_PID_H_ */
