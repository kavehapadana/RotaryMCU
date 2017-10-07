/***********************************************************************//**
 * @file		Board.c
 * @brief		Contains all macro definitions and function prototypes
 * 						support for Satellite_Receiver_DAB_TX Board
 * @version		1.00
 * @date		1. January. 2017
 * @author		ElecSys Co.
 **************************************************************************
 * Software that is described herein is Satellite_Receiver_DAB_TX Sourcs File
 **********************************************************************/

/* Includes ------------------------------------------------------------------- */
#include "Board.h"

/* Public Macros -------------------------------------------------------------- */
/**
 * @{
 */

/**
 * @}
 */

/* Public Variables ----------------------------------------------------------- */
/** @addtogroup LAYER2 UART_Public_Functions
 * @{
 */
// Declare Push Button Pins
pin Button_1 = {0,9,0};
pin Button_2 = {0,8,0};
pin Button_3 = {0,7,0};
pin Button_4 = {0,6,0};

// Declare LED Pins
pin LED_1 = {1,0,1};
pin LED_2 = {1,1,1};
pin LED_3 = {1,4,1};
pin LED_4 = {1,8,1};
pin LED_5 = {1,9,1};
pin LED_6 = {1,10,1};
pin LED_7 = {1,14,1};
pin LED_8 = {1,15,1};

// Declare Digital Out Pins
pin DOut_1 = {1,27,1};
pin DOut_2 = {1,28,1};
pin DOut_3 = {1,26,1};
pin DOut_4 = {3,25,1};

// Declare Encoder Pins
pin encoderData = {0,8,0};
pin encoderClock = {0,9,1};

/**
 * @}
 */


/* Public Functions ----------------------------------------------------------- */
/** @addtogroup LAYER2 UART_Public_Functions
 * @{
 */

/*----------------- INTERRUPT SERVICE ROUTINES --------------------------*/

/* End of Interrupt Service Routins ---------------------------------------------------- */

/*-------------------------PUBLIC FUNCTIONS------------------------------*/
/*********************************************************************//**
 * @brief	All Defined LEDs Initialling
 * @param[in]	None
 * @return	None
 **********************************************************************/
void LED_Init(void)
{
  pinConfig(&LED_1);
  pinConfig(&LED_2);
  pinConfig(&LED_3);
  pinConfig(&LED_4);
  pinConfig(&LED_5);
  pinConfig(&LED_6);
  pinConfig(&LED_7);
  pinConfig(&LED_8);
  
  pinOn(&LED_1);
  pinOn(&LED_2);
  pinOn(&LED_3);
  pinOn(&LED_4);
  pinOn(&LED_5);
  pinOn(&LED_6);
  pinOn(&LED_7);
  pinOn(&LED_8);
}

/*********************************************************************//**
 * @brief	All Defined Push Buttons Initialling
 * @param[in]	None
 * @return	None
 **********************************************************************/
void Pushbutton_Init(void)
{
  pinConfig(&Button_1);
  pinConfig(&Button_2);
  pinConfig(&Button_3);
  pinConfig(&Button_4);
}

/*********************************************************************//**
 * @brief	All Defined Digital Outputs Initialling
 * @param[in]	None
 * @return	None
 **********************************************************************/
void DigitalOut_Init(void)
{
  pinConfig(&DOut_1);
  pinConfig(&DOut_2);
  pinConfig(&DOut_3);
  pinConfig(&DOut_4);

  pinOff(&DOut_1);
  pinOff(&DOut_2);
  pinOff(&DOut_3);
  pinOff(&DOut_4);
}

/*********************************************************************//**
 * @brief	ADC Test Function
 * @param[in]	None
 * @return	None
 **********************************************************************/
void ADC_Test(void)
{
  int32_t voltage_value;
  uint32_t ADCtmp1 = 0;
  char str[10];
//  int32_t VMax = 0, VMin = 10000;
//  uint32_t ADCtmp2 = 0;
  

  voltage_value = read_voltage(_ADC_CHANNEL, 1);
//    if (voltage_value > VMax) VMax = voltage_value;
//    if (voltage_value < VMin) VMin = voltage_value;
  
//    if (voltage_value <2300)
//    {
//      ADCtmp2++;
//      UARTSendString(UART1,"\r\nVery Low Error\r\n");
//    }
  
//    for(tmp = 0; tmp < 100; tmp++);
  ADCtmp1++;
  if (ADCtmp1 == 1)
  {
    ADCtmp1 = 0;
    if (voltage_value >= 0)
    {
//      sprintf(str, "ADC value on channel %d: ", _ADC_CHANNEL);
//      UARTSendString(UART1,str);
      sprintf(str, "%d", voltage_value);
    //  UARTSendString(UART1,str, BLOCKING);
     // UARTSendString(UART1,"\n\r", BLOCKING);
//      sprintf(str, "VMax = %d\r\nVMin = %d\r\nDeltaV = %d\r\n", VMax, VMin, VMax-VMin);
//      UARTSendString(UART1,str);

//      VMax = 0;
//      VMin = 10000;
//      sprintf(str, "Verry Low Voltage Number = %d\r\n", ADCtmp2);
//      UARTSendString(UART1,str);
//      UARTSendString(UART1,"\r\nReset Max/Min\r\n");
//      ADCtmp2 = 0;
//      for(tmp = 0; tmp < 4000000; tmp++);
      Delay(6000);
    }
    else
    {
  //    UARTSendString(UART1,"Voltage Read Error\r\n", BLOCKING);
//      Delay(20000);
    }
  }
}

/*********************************************************************//**
 * @brief	USB Test Function
 * @param[in]	None
 * @return	None
 **********************************************************************/

/*********************************************************************//**
 * @brief	LED Test Function
 * @param[in]	None
 * @return	None
 **********************************************************************/
void LED_Test(void)
{
  pinFlash(&LED_1, 100000, 1, 1, 0);
  pinFlash(&LED_2, 100000, 1, 1, 0);
  pinFlash(&LED_3, 100000, 1, 1, 0);
  pinFlash(&LED_4, 100000, 1, 1, 0);
  pinFlash(&LED_5, 100000, 1, 1, 0);
  pinFlash(&LED_6, 100000, 1, 1, 0);
  pinFlash(&LED_7, 100000, 1, 1, 0);
  pinFlash(&LED_8, 100000, 1, 1, 0);
  
  pinFlash(&LED_8, 1000000, 10, 1, 0);
}

/*********************************************************************//**
 * @brief	Pushbutton Test Function
 * @param[in]	None
 * @return	None
 **********************************************************************/
void Pushbutton_Test(void)
{
  if(!pinStatus(&Button_1))
  {
    while (!pinStatus(&Button_1));
    pinFlash(&LED_1, 100000, 1, 1, 0);
  }
  if(!pinStatus(&Button_2))
  {
    while (!pinStatus(&Button_2));
    pinFlash(&LED_2, 100000, 1, 1, 0);
  }
  if(!pinStatus(&Button_3))
  {
    while (!pinStatus(&Button_3));
    pinFlash(&LED_3, 100000, 1, 1, 0);
  }
  if(!pinStatus(&Button_4))
  {
    while (!pinStatus(&Button_4));
    pinFlash(&LED_4, 100000, 1, 1, 0);
  }
}

/*********************************************************************//**
 * @brief	UART Test Function
 * @param[in]	None
 * @return	None
 **********************************************************************/
void UART_Test(void)
{
  unsigned char serialComBuf [32];

  if (UARTReceive(UART0, serialComBuf, 1))
  {
//    UARTSend(UART0, &serialComBuf[0], 1, BLOCKING);
  }
  if (UARTReceive(UART1, serialComBuf, 1))
  {
  //  UARTSend(UART1, &serialComBuf[0], 1, BLOCKING);
  }
  if (UARTReceive(UART2,serialComBuf,1))
  {
   // UARTSend(UART2, &serialComBuf[0], 1, BLOCKING);
  }
  if (UARTReceive(UART3,serialComBuf,1))
  {
  //  UARTSend(UART3, &serialComBuf[0], 1, BLOCKING);
  }
}

/* End of Public Functions ---------------------------------------------------- */

/**
 * @}
 */
/* --------------------------------- End Of File ------------------------------ */