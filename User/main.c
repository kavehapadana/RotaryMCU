/* Includes ------------------------------------------------------------------- */
#define  GLOBAL_VAR
#define  GLOBAL_PINS
#define  IMPORTANT_VAR
#define  Functions
#define	 USRATS_DEFINES
#define  VARIABLES
#define  GLOBAL_BOARD
#define  INTERRUPT_HANDLERS

#define HeaderMSG						5

#include "lpc17xx_libcfg.h"
#include "lpc17xx_timer.h"
#include "User_Uart.h"
#include "lpc17xx_pinsel.h"
#include "User_GPIO.h"
#include "MASK.h"
#include "Messaging.h" 
#include <stdio.h>
#include "lpc17xx_adc.h"
#include "Board.h"
#include "User_ExtInt.h"
#include "main.h"
#include "User_Delay.h"
#include "Messaging_RSSI_SUM.h"
#include "Messaging_RSSI_Delta.h"

//timer init
TIM_TIMERCFG_Type TIM_ConfigStruct;
TIM_MATCHCFG_Type TIM_MatchConfigStruct ;
uint8_t volatile timer0_flag = FALSE, timer1_flag = FALSE;
FunctionalState LEDStatus = ENABLE;

/************************** PRIVATE FUNCTION *************************/
/* Interrupt service routine */
void TIMER0_IRQHandler(void);
void UART0_IRQHandler(void);

#ifdef GLOBAL_BOARD
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

// Declare Output to RSSI Boards
pin RSSI_SUM_Serial_GPIO = {0,0,1};
pin RSSI_DeltaSLC_Serial_GPIO = {0,10,1};
	

//Declare External Interrupt pin
pin ExIntPin0 = {2,10,0}; // 2 = port ,10 = pinNo, 0 is input
#endif
#ifdef GLOBAL_VAR
#ifdef GLOBAL_PINS

#endif
#ifdef IMPORTANT_VAR

#define RF_Message_Lenght			9	
	typedef struct
	{
		uint8_t bitWatch;
		uint8_t Interrupt_Bits;
		uint8_t RSSI_SUM_UART_Data[3];
		uint8_t DopplerData;
		uint8_t RSSI_Delta_UART_Data[3];
	}RMCU_Data_t;
	
	typedef union
	{
		RMCU_Data_t stc;
		uint8_t Trans_MSG_RF_Array[RF_Message_Lenght];	
	}RMCU_Array_s;
	
	RMCU_Array_s Data_Trans_u;
	
	char cnt_e_com_SUM = 0,cnt_e_com_Delta = 0;
	
typedef enum
{
    we_Rot_COM_SUM = 0,
    we_Rot_COM_Delta,
    w_Rot_SUM_Serial_Pin,
    w_Rot_DeltaSLC_Serial_Pin,
    w_Rot_SelectDeltaSLC,
    e_Not4,
    e_Not5,
    e_Not6
} bitwatch_Status_t;
 extern bitwatch_Status_t bitwatch;


#endif
#ifdef	VARIABLES
int Cnt_timer0 = 0,Cnt_timer1 = 0;
uint8_t cmd_OK_flg = 0;
union Data_16_8
{
  uint16_t u16;
  uint8_t u8[2];
}u8to16;

int Cnt = 0;  uint16_t Degree = 0, rev = 0;
unsigned long Data = 0;
char temp[5];
int tempCnt = 0;
#endif

#endif
#ifdef USRATS_DEFINES
#define UART_MS            		  		UART1 
#define UART_LPC_MS             		LPC_UART1
#define UART_MS_BAUDRATE   					19200
#define	UART_MS_IRQHandler	 				UART1_IRQHandler

#define UART_FPGA_SUM            		UART3 
#define UART_LPC_FPGA_SUM         	LPC_UART3
#define UART_FPGA_SUM_BAUDRATE   		9600
#define	UART_FPGA_SUM_IRQHandler		UART3_IRQHandler

#define UART_FPGA_Delta            	UART2
#define UART_LPC_FPGA_Delta         LPC_UART2
#define UART_FPGA_Delta_BAUDRATE   	9600
#define	UART_FPGA_Delta_IRQHandler	UART2_IRQHandler

#define UART_SetFreq            		UART0
#define UART_LPC_SetFreq         		LPC_UART0
#define UART_SetFreq_BAUDRATE   		9600
#define	UART_SetFreq_IRQHandler			UART0_IRQHandler

char flgSendSerial = 0;

#endif
#ifdef INIT_FUNCTIONS
#endif

uint8_t myData[100];
int maxBuff = 300;
int rcvLen = 0;
int cntBuffLen = 0;
int sleepCnt = 10000;
int dumm=0;
uint8_t testDataSUM[100],testDataDelta[100];
int cntTestSUM,cntTestDelta = 0;

int main(void)
{
	Com_Init(UART_MS,ENABLE,DISABLE,22,UART_MS_BAUDRATE,1);
  Com_Init_Tx_Canceled(UART_FPGA_SUM,ENABLE,DISABLE,21,UART_FPGA_SUM_BAUDRATE,1);
  Com_Init_Tx_Canceled(UART_FPGA_Delta,ENABLE,DISABLE,20,UART_FPGA_Delta_BAUDRATE,1);
  
	Init_Timer0();
	LED_Init();
	// User_ADC_Init(_ADC_CHANNEL, 200000, DISABLE);	
	// EINT_Init(0, 14);
	// EINT_Init(1, 15);
	// EINT_Init(2, 16);
	// EINT_Init(3, 17);
	
  while(1)
	{
		if(flgSendSerial)
		{
			flgSendSerial = 0;
			Trans_2FixedMic_Message();			
		}
		rcvLen = UARTReceive(UART_FPGA_SUM,myData,maxBuff);
		cntBuffLen = 0;
		while(cntBuffLen < rcvLen)
		{
			parseByte_RSSI_SUM(myData[cntBuffLen]);
			cntBuffLen++;
		}
		
		rcvLen = UARTReceive(UART_FPGA_Delta,myData,maxBuff);
		cntBuffLen = 0;
		while(cntBuffLen < rcvLen)
		{
			parseByte_RSSI_Delta(myData[cntBuffLen]);
			cntBuffLen++;
		}
	}	
}

void parse_Message(uint8_t* msg, uint8_t Message_Length, uint8_t Message_ID)
{
	if(Message_ID == RotMCU_ID)
	{
		switch(msg[0])
		{
				case RotMCU_HighSUM:
				{
					pinOff(&RSSI_SUM_Serial_GPIO);
				}
				break;
				case RotMCU_LowSUM:
				{
					pinOn(&RSSI_SUM_Serial_GPIO);
				}
				break;
				case RotMCU_HighDelta:
				{
					pinOff(&RSSI_DeltaSLC_Serial_GPIO);
				}		
				break;
				case RotMCU_LowDelta:
				{
					pinOn(&RSSI_DeltaSLC_Serial_GPIO);
				}
				break;
				case RotMCU_SelectDelta:
				{
					pinOn(&LED_7);
				}
				break;
				case RotMCU_SelectSLC:
				{
					pinOff(&LED_7);
				}
				break;
		}
	
		if(msg[0] == msgRecieve_Sync1) // because the Message is Full
		{
			int a = 0;
		}
	}
}
void external_Interrupt_Fnc(uint8_t _mask)
{
//	Data_Trans_u.stc.Interrupt_Bits = 0;
//	Data_Trans_u.stc.Interrupt_Bits = setMask(Data_Trans_u.stc.Interrupt_Bits,_mask);
//	Trans_2FixedMic_Message();
}

uint8_t LED_flg = 0;
void Init_Timer0(void)
{
	// Initialize 4 timers, prescale count time of 100uS
	TIM_ConfigStruct.PrescaleOption = TIM_PRESCALE_USVAL;
	TIM_ConfigStruct.PrescaleValue	= 100; 

	TIM_Init(LPC_TIM0, TIM_TIMER_MODE,&TIM_ConfigStruct);
	// Configure 4 match channels
	// use channel 0, MR0
	TIM_MatchConfigStruct.MatchChannel = 0;
	// Enable interrupt when MR0 matches the value in TC register
	TIM_MatchConfigStruct.IntOnMatch   = TRUE;
	//Enable reset on MR0: TIMER will reset if MR0 matches it
	TIM_MatchConfigStruct.ResetOnMatch = TRUE;
	//Stop on MR0 if MR0 matches it
	TIM_MatchConfigStruct.StopOnMatch  = FALSE;
	//Toggle MR0 pin if MR0 matches it
	TIM_MatchConfigStruct.ExtMatchOutputType = TIM_EXTMATCH_NOTHING;
	// Set Match value
	TIM_MatchConfigStruct.MatchValue   = 80 - 1 ; // x - y : x is matchvalue and y is always 1
	// Set configuration for Tim_MatchConfig
	TIM_ConfigMatch(LPC_TIM0,&TIM_MatchConfigStruct);
	/* preemption = 1, sub-priority = 1 */
	NVIC_SetPriority(TIMER0_IRQn, 23);//((0x01<<3)|0x01));
	/* Enable interrupt for timer 0 */
	NVIC_EnableIRQ(TIMER0_IRQn);
	// To start timer 0
	TIM_Cmd(LPC_TIM0,ENABLE);
}
	uint8_t u8test = 0;
void parse_Message_RSSI_SUM(char* msg)
{		
		memcpy(Data_Trans_u.stc.RSSI_SUM_UART_Data,msg,3);
		Data_Trans_u.stc.DopplerData = (msg[3] + msg[4]*256 + msg[5]*65536)/1568;
		Data_Trans_u.stc.bitWatch = unsetMask(Data_Trans_u.stc.bitWatch,we_Rot_COM_SUM);
	  cnt_e_com_SUM = 0;
		u8test = unsetMask(Data_Trans_u.stc.bitWatch,we_Rot_COM_SUM);
}

void parse_Message_RSSI_Delta(char* msg)
{
		memcpy(Data_Trans_u.stc.RSSI_Delta_UART_Data,msg,3);
		cnt_e_com_Delta = 0;	
		Data_Trans_u.stc.bitWatch = unsetMask(Data_Trans_u.stc.bitWatch,we_Rot_COM_Delta);
}

int dataSendCnt = 0;
uint32_t _mainData = 0;
uint8_t _Dopp = 0;
uint32_t _RSSI_Delta_Data = 0;
void Trans_2FixedMic_Message(void)
{	
	if(dataSendCnt++%2)
		pinOn(&LED_4);
	else
		pinOff(&LED_4);
	
	 _mainData    = Data_Trans_u.stc.RSSI_SUM_UART_Data[0] + Data_Trans_u.stc.RSSI_SUM_UART_Data[1]*256 + Data_Trans_u.stc.RSSI_SUM_UART_Data[2]*65536;
	 _Dopp         = Data_Trans_u.stc.DopplerData;
	 _RSSI_Delta_Data = Data_Trans_u.stc.RSSI_Delta_UART_Data[0] + Data_Trans_u.stc.RSSI_Delta_UART_Data[1]*256 + Data_Trans_u.stc.RSSI_Delta_UART_Data[2]*65536;

		testDataSUM[cntTestSUM++] = _mainData;
		if(cntTestSUM == 99)
			cntTestSUM = 0;
		
		UARTSend(UART_MS, Make_Trans_Msg(msgTrans_RF_ID,Data_Trans_u.Trans_MSG_RF_Array,RF_Message_Lenght), (RF_Message_Lenght + HeaderMSG));
}
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
  
	pinConfig(&ExIntPin0);
	
	pinConfig(&RSSI_SUM_Serial_GPIO);
	pinConfig(&RSSI_DeltaSLC_Serial_GPIO);
	
  pinOn(&LED_1);
  pinOn(&LED_2); // For 1 Hz LED 
  pinOn(&LED_3);
  pinOn(&LED_4); // Sending Data
  pinOn(&LED_5); // RCV DATA RF
  pinOn(&LED_6); // Recieve Data RSSI_SUM
  pinOn(&LED_7); // for Test Delta_SLC
  pinOn(&LED_8); // Recieve Data RSSI_Delta 
}

/*----------------- INTERRUPT SERVICE ROUTINES --------------------------*/
#ifdef INTERRUPT_HANDLERS
//int32_t voltage_value;
void TIMER0_IRQHandler(void)
{
	if (TIM_GetIntStatus(LPC_TIM0, TIM_MR0_INT)== SET)
	{		
	}
	TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);
	Cnt_timer0++;
	if(Cnt_timer0 == 125)
	{		
		dataSendCnt = 0;
		Cnt_timer0 = 0;
		pinToggle(&LED_2);
		
		cnt_e_com_SUM++;
		if(cnt_e_com_SUM == 2)
		{
			cnt_e_com_SUM = 0;
			Data_Trans_u.stc.bitWatch = setMask(Data_Trans_u.stc.bitWatch,we_Rot_COM_SUM);
		}
		cnt_e_com_Delta++;
		if(cnt_e_com_Delta == 2)
		{
			cnt_e_com_Delta = 0;
			Data_Trans_u.stc.bitWatch = setMask(Data_Trans_u.stc.bitWatch,we_Rot_COM_Delta);
		}
		if(pinStatus(&RSSI_SUM_Serial_GPIO))
			Data_Trans_u.stc.bitWatch = setMask(Data_Trans_u.stc.bitWatch,w_Rot_SUM_Serial_Pin);
		else
			Data_Trans_u.stc.bitWatch = unsetMask(Data_Trans_u.stc.bitWatch,w_Rot_SUM_Serial_Pin);
		
		if(pinStatus(&RSSI_DeltaSLC_Serial_GPIO))
			Data_Trans_u.stc.bitWatch = setMask(Data_Trans_u.stc.bitWatch,w_Rot_DeltaSLC_Serial_Pin);
		else
			Data_Trans_u.stc.bitWatch = unsetMask(Data_Trans_u.stc.bitWatch,w_Rot_DeltaSLC_Serial_Pin);

		
		if(pinStatus(&LED_7))
			Data_Trans_u.stc.bitWatch = setMask(Data_Trans_u.stc.bitWatch,w_Rot_SelectDeltaSLC);
		else
			Data_Trans_u.stc.bitWatch = unsetMask(Data_Trans_u.stc.bitWatch,w_Rot_SelectDeltaSLC);

		}
	Data_Trans_u.stc.Interrupt_Bits = !(uint8_t)pinStatus(&ExIntPin0); // not is because of the Max in line
	flgSendSerial = 1;			
}

void UART_MS_IRQHandler(void)
{
	uint32_t intsrc, tmp, tmp1;

	/* Determine the interrupt source */
	intsrc = UART_GetIntId((LPC_UART_TypeDef *)UART_LPC_MS);
	tmp = intsrc & UART_IIR_INTID_MASK;

	// Receive Line Status
	if (tmp == UART_IIR_INTID_RLS){
		// Check line status
		tmp1 = UART_GetLineStatus((LPC_UART_TypeDef *)UART_LPC_MS);
		// Mask out the Receive Ready and Transmit Holding empty status
		tmp1 &= (UART_LSR_OE | UART_LSR_PE | UART_LSR_FE \
				| UART_LSR_BI | UART_LSR_RXFE);
		// If any error exist
		if (tmp1) {
				UART_IntErr(tmp1);
		}
	}

	// Receive Data Available or Character time-out
	if ((tmp == UART_IIR_INTID_RDA) || (tmp == UART_IIR_INTID_CTI)){
	if ((((LPC_UART_TypeDef *)UART_MS)->LSR & UART_LSR_RDR)) {
					uint8_t Data = UART_ReceiveByte(UART_MS);
					if(Data == 0x44);
							pinToggle(&LED_5);
					parseByte(Data);
			}
	}

	// Transmit Holding Empty
	if (tmp == UART_IIR_INTID_THRE){
			UART_IntTransmit((LPC_UART_TypeDef *)UART_LPC_MS);
	}
}

uint8_t buffer[600];
int ind = 0;
void UART_FPGA_SUM_IRQHandler(void)
{
	uint32_t intsrc, tmp, tmp1;

	/* Determine the interrupt source */
	intsrc = UART_GetIntId((LPC_UART_TypeDef *)UART_LPC_FPGA_SUM);
	tmp = intsrc & UART_IIR_INTID_MASK;

	// Receive Line Status
	if (tmp == UART_IIR_INTID_RLS){
		// Check line status
		tmp1 = UART_GetLineStatus((LPC_UART_TypeDef *)UART_LPC_FPGA_SUM);
		// Mask out the Receive Ready and Transmit Holding empty status
		tmp1 &= (UART_LSR_OE | UART_LSR_PE | UART_LSR_FE \
				| UART_LSR_BI | UART_LSR_RXFE);
		// If any error exist
		if (tmp1) {
				UART_IntErr(tmp1);
		}
	}
	// Receive Data Available or Character time-out
	if ((tmp == UART_IIR_INTID_RDA) || (tmp == UART_IIR_INTID_CTI)){
			if (((LPC_UART_TypeDef *)UART_FPGA_SUM)->LSR & UART_LSR_RDR) {
				//uint8_t data = UART_ReceiveByte(UART_FPGA_SUM);
			  pinToggle(&LED_6);
//				if(ind<(600))
//						buffer[ind] = data;
//				else
//					  ind = 0;
//				ind++;
				//parseByte_RSSI_SUM(data);
				UART_IntReceive((LPC_UART_TypeDef *)UART_LPC_FPGA_SUM);
				}	
	}

	// Transmit Holding Empty
	if (tmp == UART_IIR_INTID_THRE){
			UART_IntTransmit((LPC_UART_TypeDef *)UART_LPC_FPGA_SUM);
	}
}

void UART_FPGA_Delta_IRQHandler(void)
{
	uint32_t intsrc, tmp, tmp1;

	/* Determine the interrupt source */
	intsrc = UART_GetIntId((LPC_UART_TypeDef *)UART_LPC_FPGA_Delta);
	tmp = intsrc & UART_IIR_INTID_MASK;

	// Receive Line Status
	if (tmp == UART_IIR_INTID_RLS){
		// Check line status
		tmp1 = UART_GetLineStatus((LPC_UART_TypeDef *)UART_LPC_FPGA_Delta);
		// Mask out the Receive Ready and Transmit Holding empty status
		tmp1 &= (UART_LSR_OE | UART_LSR_PE | UART_LSR_FE \
				| UART_LSR_BI | UART_LSR_RXFE);
		// If any error exist
		if (tmp1) {
				UART_IntErr(tmp1);
		}
	}
	// Receive Data Available or Character time-out
	if ((tmp == UART_IIR_INTID_RDA) || (tmp == UART_IIR_INTID_CTI)){
			if ((((LPC_UART_TypeDef *)UART_FPGA_Delta)->LSR & UART_LSR_RDR)) 
			{					
				//uint8_t _data = UART_ReceiveByte(UART_FPGA_Delta);
				//parseByte_RSSI_Delta(_data);
				UART_IntReceive((LPC_UART_TypeDef *)UART_FPGA_Delta);
				pinToggle(&LED_8);
			}	
	}

	// Transmit Holding Empty
	if (tmp == UART_IIR_INTID_THRE){
			UART_IntTransmit((LPC_UART_TypeDef *)UART_LPC_FPGA_Delta);
	}
}

void UART_SetFreq_IRQHandler(void)
{
	uint32_t intsrc, tmp, tmp1;

	/* Determine the interrupt source */
	intsrc = UART_GetIntId(UART_LPC_SetFreq);
	tmp = intsrc & UART_IIR_INTID_MASK;

	// Receive Line Status
	if (tmp == UART_IIR_INTID_RLS){
		// Check line status
		tmp1 = UART_GetLineStatus(UART_LPC_SetFreq);
		// Mask out the Receive Ready and Transmit Holding empty status
		tmp1 &= (UART_LSR_OE | UART_LSR_PE | UART_LSR_FE \
				| UART_LSR_BI | UART_LSR_RXFE);
		// If any error exist
		if (tmp1) {
				UART_IntErr(tmp1);
		}
	}
	// Receive Data Available or Character time-out
	if ((tmp == UART_IIR_INTID_RDA) || (tmp == UART_IIR_INTID_CTI)){
			if ((UART_SetFreq->LSR & UART_LSR_RDR)) {
						//Data_Trans_u.stc.Sensors_UARTs_Data[2] = UART_ReceiveByte(UART_Sensor_2);
			}	
	}

	// Transmit Holding Empty
	if (tmp == UART_IIR_INTID_THRE){
			UART_IntTransmit((LPC_UART_TypeDef *)UART_LPC_SetFreq);
	}
}
#endif
