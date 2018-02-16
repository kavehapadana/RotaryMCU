#include "Messaging_RSSI_SUM.h"
#include "main.h"
#include "User_GPIO.h"

#define RX_BUFFER_SIZE 					20
#define msgRecieve_RSSI_SUM_Sync1 				0x7B
#define msgRecieve_RSSI_SUM_Sync2 				0xEA
typedef enum
{
	msgUNINIT,
	msgGOT_SYNC1,
	msgGOT_SYNC2,
	msgGOT_PAYLOAD,
} Message_Status_RSSI_SUM_t;

char Receive_Check_Sum_RSSI_SUM;
uint32_t Message_Index_RSSI_SUM;

Message_Status_RSSI_SUM_t  	Message_Status_RSSI_SUM;
char _msg_RSSI_SUM[RX_BUFFER_SIZE];
uint8_t dataTest[100]; int cnt = 0;
void parseByte_RSSI_SUM(unsigned char Data)
{
	//if (Message_Status_RSSI_SUM < msgGOT_PAYLOAD)
	switch(Message_Status_RSSI_SUM)
	{
		case msgUNINIT:
			if (Data == msgRecieve_RSSI_SUM_Sync1)
			{
				Message_Status_RSSI_SUM++;
			}
		break;
		
		case msgGOT_SYNC1:
			if (Data != msgRecieve_RSSI_SUM_Sync2)
			{
				goto restart;
			}
			Receive_Check_Sum_RSSI_SUM = 0;
			Message_Index_RSSI_SUM = 0;
			Message_Status_RSSI_SUM++;
		break;
		
		case msgGOT_SYNC2:
			_msg_RSSI_SUM[Message_Index_RSSI_SUM] = Data;
		  Receive_Check_Sum_RSSI_SUM += Data;
			Message_Index_RSSI_SUM++; 
			if (Message_Index_RSSI_SUM >= Message_Length_RSSI_SUM) 
			{
				Message_Status_RSSI_SUM++;			
			}
		break;
		
		case msgGOT_PAYLOAD:
			if (Data != Receive_Check_Sum_RSSI_SUM)
			{
				goto error;
			}
			parse_Message_RSSI_SUM(_msg_RSSI_SUM);
			goto restart;
	}
	return;
	error:
	{
		pin LED_4 = {1,8,1};
		pinToggle(&LED_4);
	}
	restart: Message_Status_RSSI_SUM = msgUNINIT;
	return;
}


