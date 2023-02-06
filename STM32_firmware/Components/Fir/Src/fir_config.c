/**
  ******************************************************************************
  * @file		: fir_config.c
  * @author  	: Krzysztof Witkowski
  * @date    	: Jan 15, 2023
  * @brief   	: fir filter configuration source code file
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include "fir_config.h"

/* Public variables ----------------------------------------------------------*/

FIR_HandleTypeDef hfir1 = {
		.Coeffs = FIR_coeffs,
		.Length = FIR_LENGTH
};
