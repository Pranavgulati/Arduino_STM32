#include <ardADC.h>

/*
ADC_IN0..ADC_IN7        :: PA0..PA7
ADC_IN8,ADC_IN9         :: PB0,PB1
ADC_IN10..ADC_IN15      :: PC0..PC5
pin can have values 0-7
example analogRead(GPIOB,1);this  reads channel 9
*/
int *__ADC_data;
//bits is 12 10 8 or 6
int analogRead(GPIO_TypeDef* port,uint8_t pin,uint8_t bits){
//add assert param so that the pin parameter has correct values only
  
  ADC_InitTypeDef          ADC_InitStructure;
  GPIO_InitTypeDef         GPIO_InitStructure;
  
  /*port clock enable */
  int clockShift = (int)(((long int)port&0x00001C00)>>10);
  RCC_AHBPeriphClockCmd(((uint32_t)0x00020000)<<clockShift, ENABLE);
   /* ADC1 Peripheral clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  //port GPIOA clockshift=0 channel 0-7   pin 0-7 offset =0
  //port GPIOB clockshift=1 channel 8-9   pin 0,1 offset =8
  //port GPIOC clockshift=2 channel 10-15 pin 0-5 offset =10
  int channel = ((uint16_t)0x01<<(clockShift==2?10:8*clockShift)+pin);
  
  
  GPIO_InitStructure.GPIO_Pin = pin ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(port, &GPIO_InitStructure);
  
  switch (bits){
  case 12:
    ADC_InitStructure.ADC_Resolution=ADC_Resolution_12b;    
    break;
  case 10:
    ADC_InitStructure.ADC_Resolution=ADC_Resolution_10b;
    break;
    case 8:
      ADC_InitStructure.ADC_Resolution=ADC_Resolution_8b;
    break;
    case 6:
      ADC_InitStructure.ADC_Resolution=ADC_Resolution_6b;
    break;
  }
    
  ADC_DeInit(ADC1);
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;    
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_TRGO;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
  ADC_Init(ADC1, &ADC_InitStructure); 
  
  ADC_ChannelConfig(ADC1, channel , ADC_SampleTime_28_5Cycles); 
  /* ADC Calibration */
  ADC_GetCalibrationFactor(ADC1);
  
  /* Enable the ADC peripheral */
  ADC_Cmd(ADC1, ENABLE);     
  
  /* Wait the ADRDY flag */
  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADRDY)); 
  
#if defined (ADC_LOWPOWER)
  ADC_WaitModeCmd(ADC1, ENABLE); 
  ADC_AutoPowerOffCmd(ADC1, ENABLE); 
#endif
  
  /* ADC1 regular Software Start Conv */ 
  ADC_StartOfConversion(ADC1);
  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)); 
  return ADC_GetConversionValue(ADC1);

}
        
uint8_t analogRead(GPIO_TypeDef* port,uint8_t pin,int* data,uint8_t bits){

 __ADC_data=data;//pointer assignment
  
  NVIC_InitTypeDef NVIC_InitStructure;
  ADC_InitTypeDef          ADC_InitStructure;
  GPIO_InitTypeDef         GPIO_InitStructure;
  
  
  /*port clock enable */
  int clockShift = (int)(((long int)port&0x00001C00)>>10);
  RCC_AHBPeriphClockCmd(((uint32_t)0x00020000)<<clockShift, ENABLE);
   /* ADC1 Peripheral clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  //port GPIOA clockshift=0 channel 0-7   pin 0-7 offset =0
  //port GPIOB clockshift=1 channel 8-9   pin 0,1 offset =8
  //port GPIOC clockshift=2 channel 10-15 pin 0-5 offset =10
  int channel = ((uint16_t)0x01<<(clockShift==2?10:8*clockShift)+pin);
  
  
  GPIO_InitStructure.GPIO_Pin = pin ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(port, &GPIO_InitStructure);
  
  ADC_DeInit(ADC1);
 switch (bits){
  case 12:
    ADC_InitStructure.ADC_Resolution=ADC_Resolution_12b;    
    break;
  case 10:
    ADC_InitStructure.ADC_Resolution=ADC_Resolution_10b;
    break;
    case 8:
      ADC_InitStructure.ADC_Resolution=ADC_Resolution_8b;
    break;
    case 6:
      ADC_InitStructure.ADC_Resolution=ADC_Resolution_6b;
    break;
  }
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;    
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_TRGO;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
  ADC_Init(ADC1, &ADC_InitStructure); 
  
  ADC_ChannelConfig(ADC1, channel , ADC_SampleTime_28_5Cycles); 
  /* ADC Calibration */
  ADC_GetCalibrationFactor(ADC1);
  
  /* Enable OVR interupt */
  ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
  
  /* Configure and enable ADC1 interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = ADC1_COMP_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);  
  
  /* Enable the ADC peripheral */
  ADC_Cmd(ADC1, ENABLE);     
  
  /* Wait the ADRDY flag */
  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADRDY)); 
  
#if defined (ADC_LOWPOWER)
  ADC_WaitModeCmd(ADC1, ENABLE); 
  ADC_AutoPowerOffCmd(ADC1, ENABLE); 
#endif
  
  /* ADC1 regular Software Start Conv */ 
  ADC_StartOfConversion(ADC1);
return 1;
}

int analogRead(GPIO_TypeDef* port,uint8_t pin){
  return analogRead(port,pin,12);
}


int analogRead(GPIO_TypeDef* port,uint8_t pin,int* data){
 return analogRead(port,pin,data,12);
}

