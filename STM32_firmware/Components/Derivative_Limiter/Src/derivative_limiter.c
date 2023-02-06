/**
  ******************************************************************************
  * @file		: derivative_limiter.c
  * @author  	: Krzysztof Witkowski
  * @date    	: Jan 18, 2023
  * @brief   	: Derivative limiter source code file
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include <math.h>				// pow, abs
#include <string.h>				// sizeof
#include "derivative_limiter.h"

/* Public function -----------------------------------------------------------*/

void DX_Init(DX_HandleTypeDef* hdx){
	memset(hdx->state, 0, sizeof(hdx->state));
}

void DX_Limit(DX_HandleTypeDef* hdx, float* in, float* out)
{
	hdx->state[0] = hdx->state[1];
	hdx->state[1] = *in;

	float dx = (hdx->state[1] - hdx->state[0]) * hdx->fs;

	/*---------- first derivative limiter ---------- */
    if(dx > hdx->dx_limit){
    	hdx->state[1] = hdx->state[0] + (hdx->dx_limit / hdx->fs);
    }
    if(dx < -hdx->dx_limit){
    	hdx->state[1] = hdx->state[0] - (hdx->dx_limit / hdx->fs);
    }

	*out = hdx->state[1];
}
