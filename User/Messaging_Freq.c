#include "Messaging_Freq.h"
#include "main.h"
#include "User_GPIO.h"

#define RX_BUFFER_SIZE 					20
#define msgRecieve_Freq_Sync1 				0x7B
#define msgRecieve_Freq_Sync2 				0xEA
typedef enum
{
	msgUNINIT,
	msgGOT_SYNC1,
	msgGOT_SYNC2,
	msgGOT_PAYLOAD,
} Message_Status_Freq_t;

char Receive_Check_Sum_Freq;
uint32_t Message_Index_Freq;

Message_Status_Freq_t  	Message_Status_Freq;
char _msg_Freq[RX_BUFFER_SIZE];
uint8_t dataTest_[100];
int cnt_ = 0;

int Message_Status_Freq_Int = 0;
float ffreq=0;
unsigned long freq=0,step=0,checksum=0,rchecksum=0,f_int=0,f_frac=0,lock=0;
char buff[20];
void resetBuffer(char *buf)
{int i=0;
	cnt_ = 0;
	freq=f_frac=f_int=checksum=lock=0;
	for(i=0;i<10;i++)
		buff[i]=buf[i];
	for(i=0;i<sizeof(dataTest_);i++)
		dataTest_[i]=0;
	parse_Message_Freq(dataTest_);
}

void parseByte_Freq(unsigned char Data)
{
	//static int freq=0,step=0,checksum=0,rchecksum=0,f_int=0,f_frac=0,lock=0;
	dataTest_[cnt_++] = Data;
	//if(buff[0]=='X')
	{
	//	if(cnt_>=8)
	{
		 if(dataTest_[5]==0x12 && dataTest_[6]==0x89 && dataTest_[7]==0x11)
		 {
			 lock=dataTest_[4]&1;
			 dataTest_[40]=0xbf ;
			 dataTest_[41]=0x1a;
		 	parse_Message_Freq(dataTest_);
		 }

	}
 }
	//else
	//if(buff[0]=='*')
	//if(cnt_>=42)
	{
		if( 
		dataTest_[36]==0x0a && dataTest_[37]==0x79 && dataTest_[38]==0x75 && 
		 dataTest_[21]==0x12  &&
		 dataTest_[27]==0x3 && dataTest_[33]==0x4 )
		{
			checksum=dataTest_[40]&1;
			lock=dataTest_[20]&1;
			f_int=dataTest_[26];
			f_frac=(dataTest_[30]<<16)+(dataTest_[31]<<8)+(dataTest_[32]);
			parse_Message_Freq(dataTest_);
			//cnt_=0;
		}
	//else
	//			cnt_=0;
	}
	//else
	//				freq=f_frac=f_int=checksum=lock=0;
	/*
	switch(Message_Status_Freq_Int)
	{
		case 0:
			if (Data == 0x53)
			{
				Message_Status_Freq_Int = 1;
				step=freq=f_frac=f_int=rchecksum=checksum=lock=cnt_=0;
			}
		else 	goto error;
				
		break;
		
		case 1:{
			freq=(freq<<8)+Data;
			step++;
			if(step==4){
				Message_Status_Freq_Int=2;
				step=0;
				//if(freq!=my_frec)
			//		goto error;
			}
		}
		break;
		
		case 2:
			if (Data == 0x54)
			{
				Message_Status_Freq_Int = 3;
				step=0;
			} else goto error;
			break;
		case 3:
			step++;
			if(step==1)rchecksum=Data;
		  if(step==2)checksum=Data;
		  if(step==2){
		  if(rchecksum!=checksum )//|| rchecksum!=my_checsum)
					goto error;
			}
			if(step==3){
				if(Data==0x0d)
				{
					Message_Status_Freq_Int = 4;
				  step=0;
				}
				else	goto error;
			}
		break;
		case(4):
			if (Data == 0x55)
			{
				Message_Status_Freq_Int = 5;
				step=0;
			}
			else//0x1f
					goto error;
			break;
		case (5):
			  step++;
				if(step==1) f_int=Data;
				if(step==2)
				{					
					if(Data==0x56){
					Message_Status_Freq_Int=6;
					step=0;
			}
					else // 0x1f
					goto error;
				}
			break;
		case( 6):
			step++;
			if(step<4) f_frac=(f_frac<<8)+Data;
			else{
					if(Data==0x57){
					Message_Status_Freq_Int=7;
					step=0;
					} 
					else
						goto error;
			}
				break;
		case(7):
			step++;
			if(Data==0x58){
					Message_Status_Freq_Int=8;
					step=0;
			}
			if(step>30)
				goto error;
			break;
		case(8):
			step++;
			if(step<5);
		  else
		  if(step==5)
				lock=Data&1;
			else if(step==6){
					if(Data!=0x12)
						lock=0;
					//step=freq=f_frac=f_int=rchecksum=checksum=lock=cnt_=0;
			}
			else
			if(step>=28)
			{
				 int f_int_chip=dataTest_[51];
				 int f_frac_chip=(dataTest_[56]<<16)+(dataTest_[57]<<8)+(dataTest_[58]);
				 if(f_int==f_int_chip && f_frac==f_frac_chip)
           parse_Message_Freq(dataTest_);
				 Message_Status_Freq_Int=0;
			}
			break;
		default:
			Message_Status_Freq_Int=step=freq=f_frac=f_int=rchecksum=checksum=lock=cnt_=0;
			break;
	}
	dataTest_[cnt_++] = Data;*/
	return;
	error:
	{
		pin LED_4 = {1,8,1};
		pinToggle(&LED_4);
	  Message_Status_Freq_Int=step=freq=f_frac=f_int=rchecksum=checksum=lock=cnt_=0;
	}
//	restart: Message_Status_Freq_Int = 0;

	return;
}


