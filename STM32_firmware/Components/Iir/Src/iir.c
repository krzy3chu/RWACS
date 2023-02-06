/**
  ******************************************************************************
  * @file		: iir.c
  * @author  	: Krzysztof Witkowski
  * @date    	: Jan 15, 2023
  * @brief   	: iir filter source code file
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include "iir.h"
#include <stdlib.h>  // calloc, malloc

/* Public function -----------------------------------------------------------*/

void IIR_Init(IIR_HandleTypeDef* hiir)
{
	hiir->State	= calloc(4 * hiir->NumStages, sizeof(float32_t));
	hiir->Iir = malloc(sizeof(arm_biquad_casd_df1_inst_f32));
	arm_biquad_cascade_df1_init_f32(hiir->Iir, hiir->NumStages, hiir->Coeffs, hiir->State);
}

void IIR_Filter(IIR_HandleTypeDef* hiir, float32_t* signal, float32_t* signal_filtered)
{
	arm_biquad_cascade_df1_f32(hiir->Iir, signal, signal_filtered, 1);
}
