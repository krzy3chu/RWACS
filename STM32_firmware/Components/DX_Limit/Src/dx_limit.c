/**
  ******************************************************************************
  * @file		: dx_limit.c
  * @author  	: Krzysztof Witkowski
  * @date    	: Jan 18, 2023
  * @brief   	: Derivative limiter source code file
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include <math.h>				// pow, abs
#include <string.h>				// sizeof
#include "dx_limit.h"

/* Public function -----------------------------------------------------------*/

/**
 * @brief 		Initialize derivative limiter function
 * @param[in] 	*hdx derivative_limiter handler
 * @return 		Nothing
 */
void DX_Init(DX_HandleTypeDef* hdx){
	memset(hdx->state, 0, sizeof(hdx->state));
}

/**
 * @brief 		Limit derivative of signal
 * @param[in] 	*in input sample of signal
 * @param[out] 	*out output filtered sample of signal
 * @return 		Nothing
 */
void DX_Limit(DX_HandleTypeDef* hdx, float* in, float* out)
{
	hdx->state[0] = hdx->state[1];
	hdx->state[1] = *in;
	float dx = (hdx->state[1] - hdx->state[0]) * hdx->fs;

	// First derivative limiter
    if(dx > hdx->dx_limit){
    	hdx->state[1] = hdx->state[0] + (hdx->dx_limit / hdx->fs);
    }
    if(dx < -hdx->dx_limit){
    	hdx->state[1] = hdx->state[0] - (hdx->dx_limit / hdx->fs);
    }
	*out = hdx->state[1];
}
