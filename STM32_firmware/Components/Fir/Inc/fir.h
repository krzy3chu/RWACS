/**
  ******************************************************************************
  * @file		: fir.h
  * @author  	: Krzysztof Witkowski
  * @date    	: Jan 13, 2023
  * @brief   	: fir configuration header file
  *
  ******************************************************************************
  */

#ifndef FIR_INC_FIR_H_
#define FIR_INC_FIR_H_

/* Includes ------------------------------------------------------------------*/
#include "arm_math.h"
#include "fir_coeff.h"

/* Typedef -------------------------------------------------------------------*/

typedef struct {
	arm_fir_instance_f32 Fir;
	float32_t State[FIR_LENGTH];
} FIR_HandleTypeDef;

/* Public variables ----------------------------------------------------------*/

extern FIR_HandleTypeDef hfir1;

/* Public function prototypes ------------------------------------------------*/

/**
 * @brief Initialize fir function
 * @param[in] hfir: fir handler
 * @return Nothing
 */
void FIR_Init(FIR_HandleTypeDef* hfir);

/**
 * @brief Filter input signal, and return as filtered_signal
 * @param[in] hfir: fir handler
 * @param[in] signal: input signal sample
 * @param[in] signal_filtered: computed filtered signal sample
 * @return Nothing
 */
void FIR_Filter(FIR_HandleTypeDef* hfir, float* signal, float* signal_filtered);

#endif /* FIR_INC_FIR_H_ */
