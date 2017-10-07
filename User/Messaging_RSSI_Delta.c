#include "Messaging_RSSI_Delta.h"
#include "main.h"
#include "User_GPIO.h"

#define RX_BUFFER_SIZE 					20
#define msgRecieve_RSSI_Delta_Sync1 				0x7B
#define msgRecieve_RSSI_Delta_Sync2 				0xEA
typedef enum
{
	msgUNINIT,
	msgGOT_SYNC1,
	msgGOT_SYNC2,
	msgGOT_PAYLOAD,
} Message_Status_RSSI_Delta_t;


char Receive_Check_Sum_RSSI_Delta;
uint32_t Message_Index_RSSI_Delta;

Message_Status_RSSI_Delta_t  	Message_Status_RSSI_Delta;
char _msg_RSSI_Delta[RX_BUFFER_SIZE];

void parseByte_RSSI_Delta(unsigned char Data)
{
	//if (Message_Status_RSSI_Delta < msgGOT_PAYLOAD)
	
	switch(Message_Status_RSSI_Delta)
	{
		case msgUNINIT:
			if (Data == msgRecieve_RSSI_Delta_Sync1)
			{
				Message_Status_RSSI_Delta++;
			}
		break;
		
		case msgGOT_SYNC1:
			if (Data != msgRecieve_RSSI_Delta_Sync2)
			{
				goto restart;
			}
			Receive_Check_Sum_RSSI_Delta = 0;
			Message_Index_RSSI_Delta = 0;
			Message_Status_RSSI_Delta++;
		break;
		
		case msgGOT_SYNC2:
			_msg_RSSI_Delta[Message_Index_RSSI_Delta] = Data;
		  Receive_Check_Sum_RSSI_Delta += Data;
			Message_Index_RSSI_Delta++; 
			if (Message_Index_RSSI_Delta >= Message_Length_RSSI_Delta) 
			{
				Message_Status_RSSI_Delta++;			
			}
		break;
		
		case msgGOT_PAYLOAD:
			if (Data != Receive_Check_Sum_RSSI_Delta)
			{
				goto error;
			}
			parse_Message_RSSI_Delta(_msg_RSSI_Delta);
			goto restart;
	}
	return;
	
	error:
	{
		pin LED_5 = {1,8,1};
		pinToggle(&LED_5);
	}
	restart: Message_Status_RSSI_Delta = msgUNINIT;
	return;
}


