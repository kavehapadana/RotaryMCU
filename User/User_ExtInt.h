/***********************************************************************//**
 * @file		User_ExtInt.h
 * @brief		Contains all macro definitions and function prototypes
 * 				support for ExtInt firmware library on LPC17xx
 * @version		1.00
 * @date		1. January. 2017
 * @author		ElecSys Co.
 **************************************************************************
 * Software that is described herein is Peripheral Layer2 Functions for ExtInt
 **************************************************************************/

/* Peripheral group ----------------------------------------------------------- */
/** @defgroup LAYER2 ExtInt
 * @ingroup LPC1700CMSIS_FwLib_Drivers
 * @{
 */

#ifndef __USER_EXTINT_H
#define __USER_EXTINT_H

/* Includes ------------------------------------------------------------------- */
#include <stdint.h>

/* Public Macros -------------------------------------------------------------- */
/** @defgroup LAYER2_ExtInt_Public_Macros
 * @{
 */
 
/* Interrupt mode
 * - 0: Tail-chaining interrupt
 * - 1: Late-arriving interrupt
 */
#define INT_MODE	1

/**
 * @}
 */


/* Public Types --------------------------------------------------------------- */
/** @defgroup LAYER2_UART_Public_Types UART
 * @{
 */

/**
 * @}
 */


/* Public Functions ----------------------------------------------------------- */
/** @defgroup LAYER 2_UART_Public_Functions UART
 * @{
 */
/* Interrupt service routines */
void EINT0_IRQHandler(void);
void EINT1_IRQHandler(void);
void EINT2_IRQHandler(void);
void EINT3_IRQHandler(void);

void EINT_Init(uint8_t intNum,uint8_t priority);

void EXTI_ClearEXTIFlag_L2(uint8_t channel);

void delay (void);

/**
 * @}
 */


#endif /* __USER_EXTINT_H */

/**
 * @}
 */

/* --------------------------------- End Of File ------------------------------ */
