/**
  ******************************************************************************
  * @file		: drv8825.h
  * @author  	: Krzysztof Witkowski
  * @date    	: Dec 17, 2022
  * @brief   	: DRV8825 step motor driver configuration header file
  *
  ******************************************************************************
  */

#ifndef INC_DRV8825_H_
#define INC_DRV8825_H_

/* Includes ------------------------------------------------------------------*/
#include "tim.h"

/* Define --------------------------------------------------------------------*/

#define DRV8825_MaxSpeedType 	1000		/* Maximum absolute value of motor rotational speed expressed in [RPM]					*/
#define DRV8825_PulseWidthType 	10			/* Width of pulse applied to STEP pin on DRV8825 board, expressed in milliseconds [ms]	*/

#define DRV8825_TimType 		TIM_HandleTypeDef*
#define DRV8825_TimChannelType	uint32_t
#define DRV8825_SpeedType 		int16_t
#define DRV8825_DirPortType 	GPIO_TypeDef*
#define DRV8825_DirPinType		uint16_t

/* Typedef -------------------------------------------------------------------*/

/**
  * @brief DRV8825 step motor driver handler
  */
typedef struct {
	DRV8825_TimType 		Tim;			/* Timer which is used for pulse generation with specified frequency and pulse width 	*/
	DRV8825_TimChannelType	TimChannel;		/* Timer channel which pin should be connected to STEP pin on DRV8825 board 			*/
	DRV8825_SpeedType 		Speed;			/* Rotational speed of step motor expressed in rotations per minute [RPM] 				*/
	DRV8825_DirPortType 	DirPort;		/* GPIO port to which DIR pin on DRV8825 board is connected								*/
	DRV8825_DirPinType 		DirPin;			/* GPIO pin to which DIR pin on DRV8825 board is connected, high when Speed is positive	*/
} DRV8825_HandleTypeDef;

/* Public function prototypes ------------------------------------------------*/

/**
 * @brief
 * @param[in] hdrv8825: DRV8825 handler
 * @return
 */
HAL_StatusTypeDef DRV8825_Start(DRV8825_HandleTypeDef* hdrv8825);

/**
 * @brief
 * @param[in] hdrv8825: DRV8825 handler
 * @return
 */
HAL_StatusTypeDef DRV8825_SetSpeed(DRV8825_HandleTypeDef* hdrv8825, DRV8825_SpeedType speed);

#endif /* INC_DRV8825_H_ */
