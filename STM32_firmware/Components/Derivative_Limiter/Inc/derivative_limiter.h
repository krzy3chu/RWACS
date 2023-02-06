/**
  ******************************************************************************
  * @file		: derivative_limiter.h
  * @author  	: Krzysztof Witkowski
  * @date    	: Jan 18, 2023
  * @brief   	: Derivative limiter configuration header file
  *
  ******************************************************************************
  */

#ifndef DERIVATIVE_LIMITER_INC_DERIVATIVE_LIMITER_H_
#define DERIVATIVE_LIMITER_INC_DERIVATIVE_LIMITER_H_

/* Includes ------------------------------------------------------------------*/

#include "main.h"

/* Typedef -------------------------------------------------------------------*/

typedef struct {
  float dx_limit;
  uint16_t fs;
  float state[2];
}DX_HandleTypeDef;

/**
 * @brief Initialize derivative_limiter function
 * @param[in] hcomp: derivative_limiter handler
 * @return Nothing
 */
void DX_Init(DX_HandleTypeDef* hdx);

/**
 * @brief Initialize derivative_limiter function
 * @param[in] hcomp: derivative_limiter handler
 * TODO
 * @return Nothing
 */
void DX_Limit(DX_HandleTypeDef* hdx, float* in, float* out);

#endif /* DERIVATIVE_LIMITER_INC_DERIVATIVE_LIMITER_H_ */
