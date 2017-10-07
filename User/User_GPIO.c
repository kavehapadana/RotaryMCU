
/* Includes ------------------------------------------------------------------- */
#include "User_GPIO.h"
#include "User_Delay.h"

void pinConfig(pin *p)
{
  pin *pin1;
  pin1=p;
  
  GPIO_SetDir(pin1->port, 1<<pin1->position, pin1->direction);
}

void pinOn(pin *p)
{
  pin *pin1;
  pin1=p;
  
  GPIO_SetValue(pin1->port, 1<<pin1->position);
}

void pinOff(pin *p)
{
  pin *pin1;
  pin1=p;
  
  GPIO_ClearValue(pin1->port, 1<<pin1->position);
}

void pinToggle(pin *p)
{
	pin *pin1;
  pin1 = p;
  if(pinStatus(pin1))
		GPIO_ClearValue(pin1->port, (1<<pin1->position));
	else
		GPIO_SetValue(pin1->port, (1<<pin1->position)); 
}

void pinSet(pin *p,int s)
{
  int status;
  
  status=s&0x1;
  
  if(!status) pinOff(p);
  else pinOn(p); 
}

int pinStatus(pin *p)
{
  unsigned long status = 0;
	pin *pin1;
  pin1 = p;
  
  status = GPIO_ReadValue(pin1->port);
  status = (status>>(pin1->position))&0x01;
  return (int)status;
}

void pinFlash(pin *p , unsigned long period, int repeat, char mode, char end)
{
  int i;
  
  for(i=0;i<repeat;i++)
		{
			if (mode == 0) pinOn(p);
			else pinOff(p);
			Delay_Int(period);
			if (mode == 0) pinOff(p);
			else pinOn(p);
			if(((i+1)<repeat) || end) Delay_Int(period);
		}
}

