/***********************************************************************//**
 * @file		User_ADC.h
 * @brief		Contains all macro definitions and function prototypes
 * 				support for ADC Layer2 library on LPC17xx
 * @version		1.00
 * @date		2. January. 2017
 * @author		ElecSys Co.
 **************************************************************************
 * Software that is described herein is Peripheral Layer2 Functions for ADC
 **************************************************************************/

/* Peripheral group ----------------------------------------------------------- */
/** @defgroup LAYER2 ADC
 * @ingroup LPC1700CMSIS_FwLib_Drivers
 * @{
 */

#ifndef __USER_ADC_H
#define __USER_ADC_H

/* Includes ------------------------------------------------------------------- */
#include "Board.h"

/* Public Macros -------------------------------------------------------------- */
/** @defgroup LAYER2_ADC_Public_Macros
 * @{
 */


/**
 * @}
 */


/* Public Types --------------------------------------------------------------- */
/** @defgroup LAYER2_ADC_Public_Types
 * @{
 */

/**
 * @}
 */


/* Public Functions ----------------------------------------------------------- */
/** @defgroup LAYER 2_ADC_Public_Functions
 * @{
 */
/* Interrupt service routines */
void ADC_IRQHandler(void);

void User_ADC_Init(uint8_t ADC_Channel, uint32_t ADC_ConvertRate, FunctionalState interruptEn);
uint16_t read_adc(uint8_t ADC_Channel);
uint16_t read_adc_pro_1(uint8_t ADC_Channel,uint16_t repeat, uint32_t delay);
uint16_t read_adc_pro_2(uint8_t ADC_Channel,uint16_t repeat, int16_t maxlev, uint16_t repmarg);
uint16_t read_adc_pro_3(uint8_t ADC_Channel,uint16_t repeat, uint16_t noiseErrorLevel);
int32_t read_voltage(uint8_t ADC_Channel, uint8_t mode);

/**
 * @}
 */

#endif /* __USER_ADC_H */

/**
 * @}
 */

/* --------------------------------- End Of File ------------------------------ */
