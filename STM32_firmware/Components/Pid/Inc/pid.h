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

typedef struct {
	float32_t Kp;
	float32_t Ki;
	float32_t Kd;
	arm_pid_instance_f32* Pid;
} PID_HandleTypeDef;

/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/**
 * @brief Initialize pid function
 * @param[in] hpid: pid handler
 * @return Nothing
 */
void PID_Init(PID_HandleTypeDef* hpid);

/**
 * @brief Initialize pid function
 * @param[in] hpid: pid handler
 * @param[in] setpoint: input reference value
 * @param[in] feedback: output state measured value
 * @param[in] control: output control signal
 * @return Nothing
 */
void PID_Control(PID_HandleTypeDef* hpid, float32_t* setpoint, float32_t* feedback, float32_t* control);

#endif /* PID_INC_PID_H_ */
