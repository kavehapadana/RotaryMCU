
#include "User_ADC.h"
#include <stdio.h>
void ADC_IRQHandler(void)
{
}
void User_ADC_Init(uint8_t ADC_Channel, uint32_t ADC_ConvertRate, FunctionalState interruptEn)
{
  
  PINSEL_CFG_Type PinCfg;
  
  switch (ADC_Channel)
  {
  case 0:
    /*
     * Init ADC pin connect
     * AD0.0 on P0.23
     */
    PinCfg.Funcnum = 1;
    PinCfg.OpenDrain = 0;
    PinCfg.Pinmode = 0;
    PinCfg.Pinnum = 23;
    PinCfg.Portnum = 0;
    PINSEL_ConfigPin(&PinCfg);
    break;
    
  case 1:
    /*
     * Init ADC pin connect
     * AD0.1 on P0.24
     */
    PinCfg.Funcnum = 1;
    PinCfg.OpenDrain = 0;
    PinCfg.Pinmode = 0;
    PinCfg.Pinnum = 24;
    PinCfg.Portnum = 0;
    PINSEL_ConfigPin(&PinCfg);
    break;
    
  case 2:
    /*
     * Init ADC pin connect
     * AD0.2 on P0.25
     */
    PinCfg.Funcnum = 1;
    PinCfg.OpenDrain = 0;
    PinCfg.Pinmode = 0;
    PinCfg.Pinnum = 25;
    PinCfg.Portnum = 0;
    PINSEL_ConfigPin(&PinCfg);
    break;
    
  case 3:
    /*
     * Init ADC pin connect
     * AD0.3 on P0.26
     */
    PinCfg.Funcnum = 1;
    PinCfg.OpenDrain = 0;
    PinCfg.Pinmode = 0;
    PinCfg.Pinnum = 26;
    PinCfg.Portnum = 0;
    PINSEL_ConfigPin(&PinCfg);
    break;
    
  case 4:
    /*
     * Init ADC pin connect
     * AD0.4 on P1.30
     */
    PinCfg.Funcnum = 3;
    PinCfg.OpenDrain = 0;
    PinCfg.Pinmode = 0;
    PinCfg.Pinnum = 30;
    PinCfg.Portnum = 1;
    PINSEL_ConfigPin(&PinCfg);
    break;
    
  case 5:
    /*
     * Init ADC pin connect
     * AD0.5 on P1.31
     */
    PinCfg.Funcnum = 3;
    PinCfg.OpenDrain = 0;
    PinCfg.Pinmode = 0;
    PinCfg.Pinnum = 31;
    PinCfg.Portnum = 1;
    PINSEL_ConfigPin(&PinCfg);
    break;
    
  case 6:
    /*
     * Init ADC pin connect
     * AD0.6 on P0.3
     */
    PinCfg.Funcnum = 2;
    PinCfg.OpenDrain = 0;
    PinCfg.Pinmode = 0;
    PinCfg.Pinnum = 3;
    PinCfg.Portnum = 0;
    PINSEL_ConfigPin(&PinCfg);
    break;
    
  case 7:
    /*
     * Init ADC pin connect
     * AD0.7 on P0.2
     */
    PinCfg.Funcnum = 2;
    PinCfg.OpenDrain = 0;
    PinCfg.Pinmode = 0;
    PinCfg.Pinnum = 2;
    PinCfg.Portnum = 0;
    PINSEL_ConfigPin(&PinCfg);
    break;
  }
  
  ADC_Init(LPC_ADC, ADC_ConvertRate);
  ADC_IntConfig(LPC_ADC,(ADC_TYPE_INT_OPT) ADC_Channel,interruptEn);
  ADC_ChannelCmd(LPC_ADC,(ADC_TYPE_INT_OPT) ADC_Channel,ENABLE);
}

uint16_t read_adc(uint8_t ADC_Channel)
{
  uint16_t adc_value;
    
  // Start conversion
  ADC_StartCmd(LPC_ADC,ADC_START_NOW);
  //Wait conversion complete
  while (!(ADC_ChannelGetStatus(LPC_ADC,ADC_Channel,ADC_DATA_DONE)));
  adc_value = ADC_ChannelGetData(LPC_ADC,ADC_Channel);
  return adc_value;
}

uint16_t read_adc_pro_1(uint8_t ADC_Channel,uint16_t repeat, uint32_t delay)
{
  int i,j;
  uint32_t tmp;
  uint16_t vf;
//  static uint32_t v1[1000];
  
  vf = 0;
  tmp = 0;
  
  for (i=0;i<repeat;i++)
  {
    tmp = tmp + read_adc(ADC_Channel);
    for (j=0;j<delay;j++);
  }
  vf = tmp/repeat;
  return vf;
}

uint16_t read_adc_pro_2(uint8_t ADC_Channel,uint16_t repeat, int16_t maxlev, uint16_t repmarg)
{
  int i,j;
  int16_t tmp1;
  uint16_t tmp;
  uint16_t tmpnum;
  uint16_t vf;
  uint16_t vft;
  static uint16_t v1[100];
  static uint16_t num[100];
  int16_t nummax;
  uint16_t samplemax;
  
  vf = 0; 
  vft = 0;
  tmp = 0;
  tmpnum = 0;
  nummax = 0;
  samplemax = 0;
  
  for (i=0;i<repeat;i++)
  {
    v1[i] = read_adc(ADC_Channel);
  }
  
  for (i=0;i<repeat;i++)
  {
    num[i] = 0;
    for (j=0;j<repeat;j++)
      if (v1[i] == v1[j])
      {
        num[i]++;
      }
  }
  
  for (i=0;i<repeat;i++)
  {
      if (num[i] > nummax)
      {
        nummax = num[i];
        samplemax = i;
      }
  }
  
  tmp1 = nummax-maxlev;
  
  for (i=0;i<repeat;i++)
  {
    if ((!maxlev || (num[i] > (nummax-maxlev))) && (num[i] > (repmarg*repeat/100)))
    {
      tmp = tmp + v1[i];
      tmpnum++;
    }
    else
    {
      tmp1 = tmpnum;
    }
  }
  
  vf = tmp/tmpnum;
  if (tmpnum == 0)
  {
    return 5000;
  }
  return vf;
}

uint16_t read_adc_pro_3(uint8_t ADC_Channel,uint16_t repeat, uint16_t noiseErrorLevel)
{
  int i,j;
  int m;

  uint16_t repeat_2 = 5;
//  uint32_t tmp;
  uint16_t tmp2[5];
  uint16_t vf;
  uint16_t vft[100];
  uint16_t v1[100];
  m = repeat;
  vf = 0; 
  for (j=0;j<m;j++) vft[j] = 0;
  for (j=0;j<m;j++)
  {
    tmp2[0] = repeat_2-2;
    for (i=0;i<repeat_2;i++)
    {
      v1[i] = read_adc(ADC_Channel);
//      if (v1[i] <2300)
//      {
//        tmp2[1] = v1[i];
//        tmp2[1] = read_adc(ADC_Channel);
//        tmp2[2] = read_adc(ADC_Channel);
//        tmp2[3] = read_adc(ADC_Channel);
//        tmp2[4] = read_adc(ADC_Channel);
//      }
//      vft[j] = vft[j]+v1[i];
//      for(tmp = 0; tmp < 100; tmp++);
    }
    
    for (i=1;i<(repeat_2-1);i++)
    {
      if ((!noiseErrorLevel)||((v1[i]+noiseErrorLevel>v1[i+1]) && (v1[i+1]+noiseErrorLevel>v1[i])) || ((v1[i-1]+noiseErrorLevel>v1[i]) && (v1[i]+noiseErrorLevel>v1[i-1])))
      {
        vft[j] = vft[j]+v1[i];
      }else{
        tmp2[0]--;
      }
    }
    vft[j] = vft[j]/tmp2[0];
  }
  
  for (j=0;j<m;j++)
  {
    vf = vf+vft[j];
  }
  vf = vf/m;
  return vf;
}

int32_t read_voltage(uint8_t ADC_Channel, uint8_t mode)
{
  int32_t voltDig = 0;
  int32_t voltAn = 0;
  switch (mode)
  {
  case 0:
    voltDig = read_adc(ADC_Channel);
    break;
  case 1:
    voltDig = read_adc_pro_1(ADC_Channel,25,0);
    break;
  case 2:
    voltDig = read_adc_pro_2(ADC_Channel,100,0,10);
    break;
  case 3:
    voltDig = read_adc_pro_3(ADC_Channel,100,0);
    break;
  }

  if (voltDig == 5000) return -1;
  
  voltAn = voltDig*2260;
  voltAn = voltAn/2800;
  
  return voltAn;
}
