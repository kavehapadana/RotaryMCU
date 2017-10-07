
#include "User_ExtInt.h"
#include "Board.h"
#include "main.h"
extern pin LED_1;
extern pin LED_2;
extern pin LED_3;
extern pin LED_4;
void EINT_Init(uint8_t intNum,uint8_t priority);

void EINT0_IRQHandler(void)
{
  EXTI_ClearEXTIFlag_L2(0);
  pinFlash(&LED_1, 100000, 1, 1, 0);
	external_Interrupt_Fnc(0); // 0 is mean the Interrupt of pin 0 is raised
}

void EINT1_IRQHandler(void)
{
  EXTI_ClearEXTIFlag_L2(1);
  pinFlash(&LED_2, 100000, 1, 1, 0);
	external_Interrupt_Fnc(1); // 1 is mean the Interrupt of pin 1 is raised
}

void EINT2_IRQHandler(void)
{
//  uint8_t i;
  EXTI_ClearEXTIFlag_L2(2);
  pinFlash(&LED_3, 100000, 1, 1, 0);
	external_Interrupt_Fnc(2); // 2 is mean the Interrupt of pin 2 is raised
}

void EINT3_IRQHandler(void)
{
//  uint32_t i;
  EXTI_ClearEXTIFlag_L2(3);
  pinFlash(&LED_4, 100000, 1, 1, 0);
	external_Interrupt_Fnc(3); // 3 is mean the Interrupt of pin 3 is raised
}

/*-------------------------PUBLIC FUNCTIONS------------------------------*/
void EINT_Init(uint8_t intNum,uint8_t priority)
{
  
  EXTI_InitTypeDef EXTICfg;
  PINSEL_CFG_Type PinCfg;
  
  switch (intNum)
  {
  case 0:
    /* Setting P2.10 as EINT0 */
    PinCfg.Funcnum = 1;
    PinCfg.OpenDrain = 0;
    PinCfg.Pinmode = 0;
    PinCfg.Pinnum = 10;
    PinCfg.Portnum = 2;
    PINSEL_ConfigPin(&PinCfg);
    break;
  case 1:
    /* Setting P2.11 as EINT0 */
    PinCfg.Funcnum = 1;
    PinCfg.OpenDrain = 0;
    PinCfg.Pinmode = 0;
    PinCfg.Pinnum = 11;
    PinCfg.Portnum = 2;
    PINSEL_ConfigPin(&PinCfg);
    break;
  case 2:
    /* Setting P2.12 as EINT0 */
    PinCfg.Funcnum = 1;
    PinCfg.OpenDrain = 0;
    PinCfg.Pinmode = 0;
    PinCfg.Pinnum = 12;
    PinCfg.Portnum = 2;
    PINSEL_ConfigPin(&PinCfg);
    break;
  case 3:
    /* Setting P2.13 as EINT0 */
    PinCfg.Funcnum = 1;
    PinCfg.OpenDrain = 0;
    PinCfg.Pinmode = 0;
    PinCfg.Pinnum = 13;
    PinCfg.Portnum = 2;
    PINSEL_ConfigPin(&PinCfg);
    break;
  }
  
  EXTI_Init();
  switch (intNum)
  {
  case 0:
    EXTICfg.EXTI_Line = EXTI_EINT0;
    break;
  case 1:
    EXTICfg.EXTI_Line = EXTI_EINT1;
    break;
  case 2:
    EXTICfg.EXTI_Line = EXTI_EINT2;
    break;
  case 3:
    EXTICfg.EXTI_Line = EXTI_EINT3;
    break;
  }
  
  /* edge sensitive */
  EXTICfg.EXTI_Mode = EXTI_MODE_EDGE_SENSITIVE;
  EXTICfg.EXTI_polarity = EXTI_POLARITY_LOW_ACTIVE_OR_FALLING_EDGE;
  EXTI_Config(&EXTICfg);
    
  #if (INT_MODE == 0) //same group, different sub-levels (Tail-chaining example)
  NVIC_SetPriorityGrouping(4); //sets group priorities: 8 - subpriorities: 3
  switch (intNum)
  {
		case 0:
			NVIC_SetPriority(EINT0_IRQn, priority);  //000:10 (bit 7:3)  assign eint0 to group 0, sub-priority 2 within group 0
			break;
		case 1:
			NVIC_SetPriority(EINT1_IRQn, priority);  //000:10 (bit 7:3)  assign eint0 to group 0, sub-priority 2 within group 0
			break;
		case 2:
			NVIC_SetPriority(EINT2_IRQn, priority);  //000:10 (bit 7:3)  assign eint0 to group 0, sub-priority 2 within group 0
			break;
		case 3:
			NVIC_SetPriority(EINT3_IRQn, priority);  //000:10 (bit 7:3)  assign eint0 to group 0, sub-priority 2 within group 0
			break;
		}
  
  #else //different group - (Late-arriving example)
  NVIC_SetPriorityGrouping(4);  //sets group priorities: 8 - subpriorities: 3
  switch (intNum)
  {
  case 0:
    NVIC_SetPriority(EINT0_IRQn, priority);   //000:00 (bit 7:3) assign eint0 to group 0, sub-priority 0 within group 0
    break;
  case 1:
    NVIC_SetPriority(EINT1_IRQn, priority);   //000:00 (bit 7:3) assign eint0 to group 0, sub-priority 0 within group 0
    break;
  case 2:
    NVIC_SetPriority(EINT2_IRQn, priority);   //000:00 (bit 7:3) assign eint0 to group 0, sub-priority 0 within group 0
    break;
  case 3:
    NVIC_SetPriority(EINT3_IRQn, priority);   //000:00 (bit 7:3) assign eint0 to group 0, sub-priority 0 within group 0
    break;
  }
  #endif
  
  switch (intNum)
  {
  case 0:
    NVIC_EnableIRQ(EINT0_IRQn);
    break;
  case 1:
    NVIC_EnableIRQ(EINT1_IRQn);
    break;
  case 2:
    NVIC_EnableIRQ(EINT2_IRQn);
    break;
  case 3:
    NVIC_EnableIRQ(EINT3_IRQn);
    break;
  }
}        

void EXTI_ClearEXTIFlag_L2(uint8_t channel)
{
  EXTI_ClearEXTIFlag((EXTI_LINE_ENUM) channel);
}
