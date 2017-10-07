#include "Messaging.h"
#include "main.h"

char Receive_Check_Sum;
uint32_t Message_Index;
char Message_ID;
char Message_Length;

unsigned char Transmit_Check_Sum;

Message_Status_t  	Message_Status;
Message_t			Message;
uint8_t _msg[RX_BUFFER_SIZE];
uint8_t _msg_trans[RX_BUFFER_SIZE];
#define CRC16 0x8005
uint16_t gen_crc16(const uint8_t *data, uint16_t size);
union Data_16_8
{
  uint16_t u16;
  uint8_t u8[2];
}u8_16;
char cntCRC = 0;
uint8_t testk[10];
int i =0 ;
void parseByte(unsigned char Data)
{
	if (Message_Status < msgGOT_PAYLOAD)
	Receive_Check_Sum += Data;
	testk[i++] = Data;
	if(i == 9) i = 0;
	switch(Message_Status)
	{
		case msgUNINIT:
		if (Data == msgRecieve_Sync1)
		{
			Message_Status++;
		}
		break;
		
		case msgGOT_SYNC1:
		if (Data != msgRecieve_Sync2)
		{
			goto restart;
		}
		Receive_Check_Sum = 0;
		Message_Index = 0;
		Message_Status++;
		break;
		
		case msgGOT_SYNC2:
		Message_ID = Data;
		Message_Status++;
		break;
		
		case msgGOT_ID:
		Message_Length = Data;
		Message_Status++;
		break;
		
		case msgGOT_LEN:
		Message.MessageChar[Message_Index] = Data;
		Message_Index++;
		if (Message_Index >= Message_Length) {
			Message_Status++;
		}
		break;
		
		case msgGOT_PAYLOAD:
			switch(cntCRC)
			{
				case 0:
					u8_16.u8[0] = Data;
					break;
				case 1:
					u8_16.u8[1] = Data;
					break;
			}
			cntCRC++;
			if(cntCRC == 2)
			{
				cntCRC = 0;
				memcpy(_msg,Message.MessageChar,(unsigned int)RX_BUFFER_SIZE);
				if(u8_16.u16 != gen_crc16(_msg,Message_Length))
					goto error;
				parse_Message(_msg, Message_Length, Message_ID);
			}
			else
				break;
//		if (Data != Receive_Check_Sum)
//		{
//			goto error;
//		}
//		
//		memcpy(_msg,Message.MessageChar,(unsigned int)RX_BUFFER_SIZE);
//		parse_Message(_msg, Message_Length, Message_ID);
		goto restart;
	}
	return;
	
	error:
	{
		//GPIO_ToggleBits(GPIOC, GPIO_Pin_5);
	}
	restart: Message_Status = msgUNINIT;
	return;
}

uint8_t* Make_Trans_Msg(uint8_t _id, uint8_t* msg_, uint8_t _lenght)
{
	uint8_t chksum = 0,cnt; 
	_msg_trans[0] = msgTrans_Sync1;
	_msg_trans[1] = msgTrans_Sync2;

	_msg_trans[2] = _id;
	chksum += _id;
	_msg_trans[3] = _lenght;
	chksum += _lenght;
	for(cnt = 0;cnt < _lenght;cnt++)
	{
		_msg_trans[cnt+4] = msg_[cnt];
		chksum += msg_[cnt];
	}
	_msg_trans[_lenght + 4] = chksum;
	return _msg_trans;
}

uint16_t gen_crc16(const uint8_t *data, uint16_t size)
{
    uint16_t out = 0;
    int bits_read = 0, bit_flag;
    int i;
    uint16_t crc = 0;
    int j = 0x0001;

    /* Sanity check: */
    if(data == (void *)0)
        return 0;

    while(size > 0)
    {
        bit_flag = out >> 15;

        /* Get next bit: */
        out <<= 1;
        out |= (*data >> bits_read) & 1; // item a) work from the least significant bits

        /* Increment bit counter: */
        bits_read++;
        if(bits_read > 7)
        {
            bits_read = 0;
            data++;
            size--;
        }

        /* Cycle check: */
        if(bit_flag)
            out ^= CRC16;

    }

    // item b) "push out" the last 16 bits
    //int i; go to first
    for (i = 0; i < 16; ++i) {
        bit_flag = out >> 15;
        out <<= 1;
        if(bit_flag)
            out ^= CRC16;
    }

    // item c) reverse the bits
    i = 0x8000;
    for (; i != 0; i >>=1, j <<= 1) {
        if (i & out) crc |= j;
    }

    return crc;
}
