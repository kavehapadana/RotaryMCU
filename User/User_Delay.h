/***********************************************************************//**
 * @file		User_Delay.c
 * @brief		Contains User Layer2 functions support for UART
 *                              firmware library on LPC17xx
 * @version		1.00
 * @date		1. January. 2017
 * @author		ElecSys Co.
 **************************************************************************
 * Software that is described herein is Peripheral Layer2 Functions for Delay
 **********************************************************************/

/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup LAYER2 Delay
 * @{
 */

/* Includes ------------------------------------------------------------------- */
#include "Board.h"

/************************** PUBLIC VARIABLES *************************/

/*----------------- INTERRUPT SERVICE ROUTINES --------------------------*/
/*********************************************************************/
void SysTick_Handler (void);

/*-------------------------PUBLIC FUNCTIONS------------------------------*/
/*********************************************************************/
void Delay (uint32_t tick);
void Delay_Pro (uint32_t tick, uint8_t mode);
void Delay_Int (uint32_t tick);
unsigned long SystemTime(void);
