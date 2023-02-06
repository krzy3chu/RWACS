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

DX_HandleTypeDef hdx1 = {
		.dx_limit = 80000,
		.fs = 50
};
