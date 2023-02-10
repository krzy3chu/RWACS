/**
  ******************************************************************************
  * @file		: dx_limit_config.c
  * @author  	: Krzysztof Witkowski
  * @date    	: Jan 18, 2023
  * @brief   	: Derivative limiter configuration source code file
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include "dx_limit_config.h"

/* Public variables ----------------------------------------------------------*/

/**
 * @brief derivative limiter handle definition
 */
DX_HandleTypeDef hdx1 = {
		.dx_limit = 80000,
		.fs = 50
};
