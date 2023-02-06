/**
  ******************************************************************************
  * @file		: iir_config.c
  * @author  	: Krzysztof Witkowski
  * @date    	: Jan 15, 2023
  * @brief   	: iir filter configuration source code file
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include "iir.h"

/* Public variables ----------------------------------------------------------*/

IIR_HandleTypeDef hiir1 = {
		.Coeffs = IIR_coeffs,
		.NumStages = IIR_NUM_STAGES
};
