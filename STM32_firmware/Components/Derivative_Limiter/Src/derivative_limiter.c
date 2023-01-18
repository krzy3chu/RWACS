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

void DXX_Init(DXX_HandleTypeDef* hdxx){
	memset(hdxx->state_in, 0, sizeof(hdxx->state_in));
	memset(hdxx->state_out, 0, sizeof(hdxx->state_out));
}

void DXX_Limit(DXX_HandleTypeDef* hdxx, float* in, float* out)
{
	hdxx->state_in[0] = hdxx->state_in[1];
	hdxx->state_in[1] = *in;
	hdxx->state_out[0] = hdxx->state_out[1];
	hdxx->state_out[1] = hdxx->state_out[2];
	hdxx->state_out[2] = *in;

	float din = (hdxx->state_in[1] - hdxx->state_in[0]) * hdxx->fs;
	float dx1a = (hdxx->state_out[1] - hdxx->state_out[0]) * hdxx->fs;

// ---------- protect from overshooting ---------- //
   float dtr =  pow((dx1a - din), 2) / (2 * hdxx->dxx_limit);   		// distance on vertical axis to meet with reference signal
   if(fabs(hdxx->state_in[0] - hdxx->state_out[1]) <= dtr && hdxx->state_in[0] != hdxx->state_out[1])	// if actual difference is lower than dtr
   {
	   float pull = 0;		// pulls output signal up if positive, down if negative

	   if(hdxx->state_in[1] > hdxx->state_out[1]){		// if reference signal is greater than output
		   if(din < dx1a){
			   pull = -0.1;
		   }else{
			   pull = 0.1;
		   }
	   }else{
		   if(din > dx1a){
			   pull = 0.1;
		   }else{
			   pull = -0.1;
		   }
	   }
	   hdxx->state_out[2] = hdxx->state_out[1] + pull;
   }

	float dx1b = (hdxx->state_out[2] - hdxx->state_out[1]) * hdxx->fs;
	float dx2 = (dx1b - dx1a) * hdxx->fs;

	/*---------- first derivative limiter ---------- */
    if(dx1b > hdxx->dx_limit){
    	hdxx->state_out[2] = hdxx->state_out[1] + (hdxx->dx_limit / hdxx->fs);
    }
    if(dx1b < -hdxx->dx_limit){
    	hdxx->state_out[2] = hdxx->state_out[1] - (hdxx->dx_limit / hdxx->fs);
    }

    /* ---------- second derivative limiter ---------- */
    if(dx2 > hdxx->dxx_limit){
    	hdxx->state_out[2] = -hdxx->state_out[0] + 2*(hdxx->state_out[1]) + (hdxx->dxx_limit / pow(hdxx->fs, 2));
    }
    if(dx2 < -hdxx->dxx_limit){
    	hdxx->state_out[2] = -hdxx->state_out[0] + 2*(hdxx->state_out[1]) - (hdxx->dxx_limit / pow(hdxx->fs, 2));
    }

	*out = hdxx->state_out[2];
}
