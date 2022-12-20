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

#define DRV8825_MaxSpeed 			400		/* Maximum absolute value of motor rotational speed expressed in [RPM]					*/
#define DRV8825_PulseWidthUs 		10			/* Width of pulse applied to STEP pin on DRV8825 board, expressed in microseconds [us]	*/
#define DRV8825_StepsPerRevolution 	(200*16)	/* Number of motor steps per full shaft revolution multiplied by microstep resolution	*/

#define DRV8825_TimType 		TIM_HandleTypeDef*
#define DRV8825_TimChannelType	uint32_t
#define DRV8825_SpeedType 		int16_t
#define DRV8825_DirPortType 	GPIO_TypeDef*
#define DRV8825_DirPinType		uint16_t
#define DRV8825_EnblPortType 	GPIO_TypeDef*
#define DRV8825_EnblPinType		uint16_t

/* Macros --------------------------------------------------------------------*/

/* Width of pulse applied to STEP pin on DRV8825 board, expressed in system clock cycles */
#define DRV8825_PulseWidthCycles ( DRV8825_PulseWidthUs * HAL_RCC_GetSysClockFreq() / 1000000 )

/* Value of Auto-Reload Register in timer, calculated based on target speed */
#define DRV8825_TimArrSpeed ( ( HAL_RCC_GetSysClockFreq() / DRV8825_StepsPerRevolution * 60 / speed ) - 1 )

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
	DRV8825_EnblPortType 	EnblPort;		/* GPIO port which is connected to ENABLE pin on DRV8825 board							*/
	DRV8825_EnblPinType 	EnblPin;		/* GPIO pin which is connected to ENABLE pin on DRV8825, motor is disable when pin high	*/
} DRV8825_HandleTypeDef;

/* Public function prototypes ------------------------------------------------*/

/**
 * @brief Start Tim timer in PWM mode
 * @param[in] hdrv8825: DRV8825 handler
 * @retval HAL status from PWM start function
 */
HAL_StatusTypeDef DRV8825_Start(DRV8825_HandleTypeDef* hdrv8825);

/**
 * @brief Set timer, Dir and Enbl pins properly according to target speed
 * @param[in] hdrv8825: DRV8825 handler
 * @param[in] speed: target motor rotational speed
 * @retval HAL_OK: speed is setup properly
 * @retval HAL_ERROR: absolute value of target speed is higher than maximum motor rotational speed set in DRV8825_MaxSpeed definition
 */
HAL_StatusTypeDef DRV8825_SetSpeed(DRV8825_HandleTypeDef* hdrv8825, DRV8825_SpeedType speed);

#endif /* INC_DRV8825_H_ */
