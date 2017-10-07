/***********************************************************************//**
 * @file		Board.h
 * @brief		Contains all macro definitions and function prototypes
 * 						support for Satellite_Receiver_DAB_TX Board
 * @version		1.00
 * @date		1. January. 2017
 * @author		ElecSys Co.
 **************************************************************************
 * Software that is described herein is Satellite_Receiver_DAB_TX Header File
 **************************************************************************/

#ifndef __BOARD_H
#define __BOARD_H

/* Includes ------------------------------------------------------------------- */
#include "lpc17xx_libcfg.h"
#include "lpc17xx_pinsel.h"
#include "LPC17xx.h"
#include "lpc_types.h"

#include "lpc17xx_nvic.h"

#include <stdio.h>

#include "lpc17xx_gpio.h"
#include "lpc17xx_uart.h"
#include "lpc17xx_exti.h"
#include "lpc17xx_adc.h"
#include "lpc17xx_timer.h"


#include "User_GPIO.h"
#include "User_Uart.h"
#include "User_ADC.h"

/* Public Macros -------------------------------------------------------------- */
#define UART_OUT              UART1
#define UART_OUT_IRQ          UART1_IRQn

#define UART_OUT_BAUDRATE     19200

#define _ADC_CHANNEL	      5

/* Public Variables ----------------------------------------------------------- */

/* Public Types --------------------------------------------------------------- */

/* Public Functions ----------------------------------------------------------- */
void LED_Init(void);
void Pushbutton_Init(void);
void DigitalOut_Init(void);

void Pushbutton_Test(void);
void LED_Test(void);
void USB_Test(void);
void UART_Test(void);
void ADC_Test(void);


#endif /* __BOARD_H */

/**
 * @}
 */

/* --------------------------------- End Of File ------------------------------ */

