/**
  ******************************************************************************
  * @file		: iir.h
  * @author  	: Krzysztof Witkowski
  * @date    	: Jan 15, 2023
  * @brief   	: iir filter configuration header file
  *
  ******************************************************************************
  */

#ifndef IIR_INC_IIR_H_
#define IIR_INC_IIR_H_

/* Includes ------------------------------------------------------------------*/

#include "arm_math.h"
#include "iir_coeff.h"

/* Typedef -------------------------------------------------------------------*/

typedef struct {
	float32_t* Coeffs;
	uint16_t NumStages;
	arm_biquad_casd_df1_inst_f32* Iir;
	float32_t* State;
} IIR_HandleTypeDef;

/* Public function prototypes ------------------------------------------------*/

/**
 * @brief Initialize iir function
 * @param[in] hiir: iir handler
 * @return Nothing
 */
void IIR_Init(IIR_HandleTypeDef* hiir);

/**
 * @brief Filter input signal, and return as filtered_signal
 * @param[in] hiir: iir handler
 * @param[in] signal: input signal sample
 * @param[in] signal_filtered: computed filtered signal sample
 * @return Nothing
 */
void IIR_Filter(IIR_HandleTypeDef* hiir, float* signal, float* signal_filtered);

#endif /* IIR_INC_IIR_H_ */
