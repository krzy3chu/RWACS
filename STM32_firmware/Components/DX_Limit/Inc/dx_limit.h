/**
  ******************************************************************************
  * @file		: dx_limit.h
  * @author  	: Krzysztof Witkowski
  * @date    	: Jan 18, 2023
  * @brief   	: Derivative limiter configuration header file
  *
  ******************************************************************************
  */

#ifndef DX_LIMIT_INC_DX_LIMIT_H_
#define DX_LIMIT_INC_DX_LIMIT_H_

/* Includes ------------------------------------------------------------------*/

#include "main.h"

/* Typedef -------------------------------------------------------------------*/

/**
 * @brief derivative limiter handle struct definition
 */
typedef struct {
  float dx_limit;
  uint16_t fs;
  float state[2];
}DX_HandleTypeDef;

/**
 * @brief 		Initialize derivative limiter function
 * @param[in] 	*hdx derivative_limiter handler
 * @return 		Nothing
 */
void DX_Init(DX_HandleTypeDef* hdx);

/**
 * @brief 		Limit derivative of signal
 * @param[in] 	*in input sample of signal
 * @param[out] 	*out output filtered sample of signal
 * @return 		Nothing
 */
void DX_Limit(DX_HandleTypeDef* hdx, float* in, float* out);

#endif /* DX_LIMIT_INC_DX_LIMIT_H_ */
