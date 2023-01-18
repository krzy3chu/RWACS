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
  float dxx_limit;
  uint16_t fs;
  float state_in[2];
  float state_out[3];
} DXX_HandleTypeDef;

/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/**
 * @brief Initialize derivative_limiter function
 * @param[in] hcomp: derivative_limiter handler
 * @return Nothing
 */
void DXX_Init(DXX_HandleTypeDef* hdxx);

/**
 * @brief Initialize derivative_limiter function
 * @param[in] hcomp: derivative_limiter handler
 * @return Nothing
 */
void DXX_Limit(DXX_HandleTypeDef* hdxx, float* in, float* out);

#endif /* DERIVATIVE_LIMITER_INC_DERIVATIVE_LIMITER_H_ */
