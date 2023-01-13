/**
  ******************************************************************************
  * @file		: fir.c
  * @author  	: Krzysztof Witkowski
  * @date    	: Jan 13, 2023
  * @brief   	: fir source code file
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "fir.h"

/* Public variables ----------------------------------------------------------*/

FIR_HandleTypeDef hfir1;

/* Public function -----------------------------------------------------------*/

void FIR_Init(FIR_HandleTypeDef* hfir)
{
	  memset(hfir->State, 0, sizeof(hfir->State));
	  arm_fir_init_f32(&(hfir->Fir), FIR_LENGTH, (float32_t*) FIR_b, (float32_t *) &(hfir->State), 1);
}

void FIR_Filter(FIR_HandleTypeDef* hfir, float32_t* signal, float32_t* signal_filtered)
{
	arm_fir_f32(&(hfir->Fir), signal, signal_filtered, 1);
}
