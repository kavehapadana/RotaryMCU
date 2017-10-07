#include "stdint.h"

#define TX_BUFFER_SIZE 					250
#define RX_BUFFER_SIZE 					250

#define msgRecieve_Sync1 				0xAC
#define msgRecieve_Sync2 				0xBD

#define msgTrans_Sync1					0x7B
#define msgTrans_Sync2					0xEA
#define msgTrans_RF_ID					0xAD
#define msgTrans_DC_ID					0xDF

//#define msgTrans_SetHigh_SUM_TX_ID			0xA6
//#define msgTrans_SetLow_SUM_TX_ID				0xA7
//#define msgTrans_SetHigh_Delta_TX_ID		0xA8
//#define msgTrans_SetLow_Delta_TX_ID			0xA9

#define Message_ID_PIDGain						0x13
#define Message_ID_SetPoint_Pos				0x15
#define Message_ID_SetPoint_Spe				0x17
#define Message_ID_SinusGenStart			0x19

#define Message_ID_SendData				0x90
#define Message_ID_Stop						0x11

#define cont_arraySize	3

void parse_Message(uint8_t* msg, uint8_t Message_Length, uint8_t Message_ID);
void parseByte(unsigned char Data);
uint8_t* Make_Trans_Msg(uint8_t _id, uint8_t* _msg, uint8_t _lenght); 
extern char tx_buffer[TX_BUFFER_SIZE];
extern unsigned char tx_wr_index,tx_rd_index,tx_counter;

extern char Receive_Check_Sum;
extern uint32_t Message_Index;
extern char Message_ID;
extern char Message_Length;
extern unsigned char Transmit_Check_Sum;

typedef enum
{
	msgUNINIT,
	msgGOT_SYNC1,
	msgGOT_SYNC2,
	msgGOT_ID,
	msgGOT_LEN,
	msgGOT_PAYLOAD,
} Message_Status_t;

typedef union 
{
	char			MessageChar[RX_BUFFER_SIZE];
	int16_t		MessageInt[RX_BUFFER_SIZE/2];
	float			MessageFloat[RX_BUFFER_SIZE/4];
	int				MessageInt32[RX_BUFFER_SIZE/4];
} Message_t;

extern Message_Status_t  Message_Status;
extern Message_t	Message;

typedef enum 
{
	RotMCU_ID = 0xA0,
	RotMCU_HighSUM = 0xA6,
	RotMCU_LowSUM,
	RotMCU_HighDelta,
	RotMCU_LowDelta,
	RotMCU_SelectDelta,
	RotMCU_SelectSLC	
} RotMCU_ID_t;
extern RotMCU_ID_t	RotMCU_msg_ID;
