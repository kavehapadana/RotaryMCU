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
#include "User_Delay.h"

/* Public Variables ----------------------------------------------------------- */
/** @addtogroup LAYER2 Delay_Public_Functions
 * @{
 */
/* SysTick Counter */
volatile unsigned long SysTickCnt;

/**
 * @}
 */


/* Public Functions ----------------------------------------------------------- */
/** @addtogroup LAYER2 Delay_Public_Functions
 * @{
 */
/*----------------- INTERRUPT SERVICE ROUTINES --------------------------*/
/*********************************************************************//**
 * @brief	System Tick Handler
 * @param[in]	None
 * @return 	None
 **********************************************************************/
void SysTick_Handler (void)
{
  SysTickCnt++;
}
/* End of Interrupt Service Routins ----------------------------------------- */

/*-------------------------PUBLIC FUNCTIONS------------------------------*/
/*********************************************************************//**
 * @brief	Interrupt Base Delay Function
 * @param[in]	tick	number of System ticks that will be Delayed
 * @return	None
 **********************************************************************/
void Delay (uint32_t tick)
{
  uint32_t systickcnt;

  systickcnt = SysTickCnt;
  while ((SysTickCnt - systickcnt) < tick);
}

/*********************************************************************//**
 * @brief	Advanced Delay Function
 * @param[in]	tick	number of System ticks that will be Delayed
 * @return	None
 **********************************************************************/
void Delay_Pro (uint32_t tick, uint8_t mode)
{
  if (mode == 0)
  {
    Delay(tick);
  }
  else
  {
    Delay_Int(tick);
  }
}

/*********************************************************************//**
 * @brief	Simple Delay Function:
                      use in Interrupt Handler Routines for Safety
 * @param[in]	tick	number of System ticks that will be Delayed
 * @return	None
 **********************************************************************/
void Delay_Int (uint32_t tick)
{
  uint32_t timeDelay;
  uint32_t i;
  timeDelay = tick*5/12;
  for (i=0;i<10*timeDelay;i++);
}
/*********************************************************************//**
 * @brief	Return System Time in System Tick Counter
 * @param[in]	None
 * @return	None
 **********************************************************************/
unsigned long SystemTime(void)
{
  return SysTickCnt;
}

/* End of Public Functions ---------------------------------------------------- */

/**
 * @}
 */
/* --------------------------------- End Of File ------------------------------ */
