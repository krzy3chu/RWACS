/**
  ******************************************************************************
  * @file		: fir.c
  * @author  	: Krzysztof Witkowski
  * @date    	: Jan 13, 2023
  * @brief   	: fir filter source code file
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include "fir.h"
#include <stdlib.h>  // calloc

/* Public function -----------------------------------------------------------*/

void FIR_Init(FIR_HandleTypeDef* hfir)
{
	hfir->State	= calloc(hfir->Length, sizeof(float32_t));
	arm_fir_init_f32(hfir->Fir, hfir->Length, hfir->Coeffs, hfir->State, 1);
}

void FIR_Filter(FIR_HandleTypeDef* hfir, float32_t* signal, float32_t* signal_filtered)
{
	arm_fir_f32(hfir->Fir, signal, signal_filtered, 1);
}
