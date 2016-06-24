#include <ardDAC.h>


dac Dac;

void dac::stop(){
DAC_DeInit();

}
void dac::begin(uint8_t chan){
  DAC_InitTypeDef    DAC_InitStructure;
  GPIO_InitTypeDef   GPIO_InitStructure;

  /* Enable GPIOA clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  
  /* Configure PA.04 (DAC_OUT1) in analog mode -------------------------*/
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4<<chan;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Enable DAC clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
  
  /* DAC channel1 Configuration */
  DAC_InitStructure.DAC_Trigger = DAC_Trigger_None;
  DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
  DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
  DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;

  DAC_Init(DAC_Channel_2&(chan<<1), &DAC_InitStructure);
  DAC_Cmd(DAC_Channel_2&(chan<<1), ENABLE);
  dac::channel= chan;
  DAC_SoftwareTriggerCmd(DAC_Channel_2&(chan<<1),ENABLE);
}


void dac::begin(){
begin(0);
}
void dac::out(uint16_t data){
  if(channel==0){DAC_SetChannel1Data(DAC_Align_12b_R, data);}
  else{DAC_SetChannel2Data(DAC_Align_12b_R, data);}
}
