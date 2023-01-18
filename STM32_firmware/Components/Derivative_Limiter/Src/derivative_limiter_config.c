/**
  ******************************************************************************
  * @file		: derivative_limiter_config.c
  * @author  	: Krzysztof Witkowski
  * @date    	: Jan 18, 2023
  * @brief   	: Derivative limiter configuration source code file
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include "derivative_limiter_config.h"

/* Public variables ----------------------------------------------------------*/

DXX_HandleTypeDef hdxx1 = {
		.dx_limit = 20000,
		.dxx_limit = 80000,
		.fs = 200
};
