/*
each timer register has a differnet set of avaialabilities 
not even two general purpose timers have a common register map
proposal
1.make a class that has a union of all features and then initialize it for
diff timers

2. categorize code in specific functions IC/counting,OC/PWM,Pulse,base time
then call these functions to do things
this will therfore limit the things that are done with the library

analogWrite - fixed freq variable duty
PWMout - duty nd freq control

getFrequency
getHighTime
getLowTime
getDuty

pulseOut - width offset 

keep the following in the arduino.h lib so that this can be accessed in the future without timers
attachInterrupt -timer events and others

#2 sounds better and beautiful actually


use TIM6 for event generations

use TIM 1/2/3 for pwm/input capture  most of the port A and B pins



*/

#include <ardTIM.h>
unsigned int *__freqPointer=new unsigned int;
void PWMout(GPIO_TypeDef* port,int pin,int percentValue,int frequency){
  //choose a timer for analog write here
  //APB1 or APB2
  //so timer selection happens on the basis of the port and pin 
  
  
  //only PA and PB are supported 
   //assert here that only port a or b is sent as the argument 
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  //i wanted the map to be a portable unit so i did this
  //dont know how it affects performance though
  #include <TimerPortMap.h>
  //timer is selected based on the pins and port so
  unsigned int APBperiphClock=0;
  unsigned int AFnumber=0;
  TIM_TypeDef* timer=0;
  unsigned int channelNumber=0;
  if     (port==GPIOA){
    APBperiphClock=portAtimClkMap[pin];
    AFnumber=portAtimAFMap[pin];
    timer=portAtimMap[pin];
    channelNumber=portAchMap[pin];
  }
  else if(port==GPIOB){
    APBperiphClock=portBtimClkMap[pin];
    AFnumber=portBtimAFMap[pin];
    timer=portBtimMap[pin];
    channelNumber=portBchMap[pin];
  }
  
  if(IS_TIM_LIST2_PERIPH(timer)){
  RCC_APB2PeriphClockCmd(APBperiphClock, ENABLE);
  }
  else if (!IS_TIM_LIST2_PERIPH(timer)) {
  RCC_APB1PeriphClockCmd(APBperiphClock, ENABLE);
  }
  else{
  //ther is no available timer or there could be a conflict if the timer is 
  // operated at the at the requested pin and port combination
  //please try someother port and pin
  return;
  //also even if this test is passed it may happen 
  }
     //gpio clock
  int clockShift = (int)(((long int)port&0x00001C00)>>10);
  RCC_AHBPeriphClockCmd(((uint32_t)0x00020000)<<clockShift, ENABLE);
 
  /* GPIO port structure config */
  GPIO_InitStructure.GPIO_Pin = ((uint16_t)0x0001)<<pin;;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(port, &GPIO_InitStructure); 
  /* Connect TIM Channels to AF of pins */
  GPIO_PinAFConfig(port, pin, AFnumber);

  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_OCStructInit(&TIM_OCInitStructure);

 
  /* TIMx Configuration ---------------------------------------------------
   TIMxCLK = PCLK2 = SystemCoreClock
   TIMxCLK = SystemCoreClock, Prescaler = 0, TIMx counter clock = SystemCoreClock
   SystemCoreClock is set to 48 MHz for STM32F0xx devices
   
   Note: 
    SystemCoreClock variable holds HCLK frequency and is defined in system_stm32f0xx.c file.
    Each time the core clock (HCLK) changes, user had to call SystemCoreClockUpdate()
    function to update SystemCoreClock variable value. Otherwise, any configuration
    based on this variable will be incorrect. 
  ----------------------------------------------------------------------- */
  
  uint16_t TimerPeriod = 0;
  uint16_t CCR_val = 0;
  /* Compute the value to be set in ARR regiter to generate signal at given frequency  */
  TimerPeriod = (SystemCoreClock / frequency ) - 1;
  /* Compute CCR1 value to generate a duty cycle at percentValue for channel */
  CCR_val = (uint16_t) (((uint32_t) percentValue * (TimerPeriod - 1)) / 100);
  
  /* Time Base configuration */
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = TimerPeriod;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

  TIM_TimeBaseInit(timer, &TIM_TimeBaseStructure);

  /* Channel 1, 2,3 and 4 Configuration in PWM mode */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR_val;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
  
  switch(channelNumber){
  case 1:
    TIM_OC1Init(timer, &TIM_OCInitStructure);
    break;
  case 2:
    TIM_OC2Init(timer, &TIM_OCInitStructure);
    break;
  case 3 :
    TIM_OC3Init(timer, &TIM_OCInitStructure);
    break;
  case 4:
    TIM_OC4Init(timer, &TIM_OCInitStructure);
    break;
  default:
    //ERROOOORRR ssup?
    break;
  }
  /* TIM1 counter enable */
  TIM_Cmd(timer, ENABLE);

  /* TIM1 Main Output Enable */
  TIM_CtrlPWMOutputs(timer, ENABLE);

}

void analogWrite(GPIO_TypeDef* port,int pin,int value){
PWMout( port, pin,value,10000);
}

void PWMout(GPIO_TypeDef* port,int pin,int percentValue){
PWMout( port, pin,percentValue,10000);
}

uint8_t  getFrequency(GPIO_TypeDef* port,int pin,unsigned int *freqDataBuffer){
__freqPointer=freqDataBuffer;
//choose a timer for analog write here
  //APB1 or APB2
  //so timer selection happens on the basis of the port and pin 
  //only PA and PB are supported 
   //assert here that only port a or b is sent as the argument 
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_ICInitTypeDef  TIM_ICInitStruct;
  GPIO_InitTypeDef GPIO_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  //i wanted the map to be a portable unit so i did this
  //dont know how it affects performance though
  #include <TimerMapInput.h>
  unsigned int APBperiphClock=0;
  unsigned int AFnumber=0;
  unsigned int timerNVIC=0;
  TIM_TypeDef* timer=0;
  unsigned int channelNumber=0;
  int clockShift = (int)(((long int)port&0x00001C00)>>10);
  uint16_t TimerPeriod = 0;
  int risingChannelNo,fallingChannelNo;
  //timer is selected based on the pins and port so
  
  if     (port==GPIOA){
    APBperiphClock=portAtimClkMap[pin];
    AFnumber=portAtimAFMap[pin];
    timer=portAtimMap[pin];
    channelNumber=portAchMap[pin];
    timerNVIC=portAnvic[pin];
  }
  else if(port==GPIOB){
    APBperiphClock=portBtimClkMap[pin];
    AFnumber=portBtimAFMap[pin];
    timer=portBtimMap[pin];
    channelNumber=portBchMap[pin];
    timerNVIC=portBnvic[pin];
  }
  
  if(IS_TIM_LIST2_PERIPH(timer)){
  RCC_APB2PeriphClockCmd(APBperiphClock, ENABLE);
  }
  else if (!IS_TIM_LIST2_PERIPH(timer)) {
  RCC_APB1PeriphClockCmd(APBperiphClock, ENABLE);
  }
  else{
  //ther is no available timer or there could be a conflict if the timer is 
  // operated at the at the requested pin and port combination
  //please try someother port and pin
  return -1;
  //also even if this test is passed it may happen 
  }
     //gpio clock
  RCC_AHBPeriphClockCmd(((uint32_t)0x00020000)<<clockShift, ENABLE);
 
  // GPIO port structure config 
  GPIO_InitStructure.GPIO_Pin = pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(port, &GPIO_InitStructure); 
  //Connect TIM Channels to AF of pins 
  GPIO_PinAFConfig(port, pin, AFnumber);

  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_ICStructInit(&TIM_ICInitStruct);

 
//       TIMx Configuration ---------------------------------------------------
//       TIMxCLK = PCLK2 = SystemCoreClock
//       TIMxCLK = SystemCoreClock, Prescaler = 0, TIMx counter clock = SystemCoreClock
//       SystemCoreClock is set to 48 MHz for STM32F0xx devices
//       
//       Note: 
//        SystemCoreClock variable holds HCLK frequency and is defined in system_stm32f0xx.c file.
//        Each time the core clock (HCLK) changes, user had to call SystemCoreClockUpdate()
//        function to update SystemCoreClock variable value. Otherwise, any configuration
//        based on this variable will be incorrect. 
//      ----------------------------------------------------------------------- 
  
  // Compute the value to be set in ARR regiter to generate signal at given frequency  
  TimerPeriod = (SystemCoreClock / 100000 ) - 1;

  // Time Base configuration 
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = TimerPeriod;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

  TIM_TimeBaseInit(timer, &TIM_TimeBaseStructure);

  switch(channelNumber){
  case 1:
    risingChannelNo=1;
    fallingChannelNo=2;
    break;
  case 2:
    risingChannelNo=2;
    fallingChannelNo=1;
    break;
  case 3:
    risingChannelNo=3;
    fallingChannelNo=4;
    break;
  case 4:
    risingChannelNo=4;
    fallingChannelNo=3;
    break;

  }

  
  TIM_ICInitStruct.TIM_Channel = 4*(risingChannelNo-1);
  TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;
  TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStruct.TIM_ICFilter = 0x0;
  
  TIM_ICInit(timer, &TIM_ICInitStruct);
  
  TIM_ICInitStruct.TIM_Channel = 4*(fallingChannelNo-1);
  TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;
  TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
  
  TIM_ICInit(timer, &TIM_ICInitStruct);  

  //TIM enable counter 
  TIM_Cmd(timer, ENABLE);
//------------------------------------------------------
   
  TIM_ITConfig(timer, (1<<risingChannelNo)|(1<<fallingChannelNo)|TIM_IT_Update, ENABLE);
 
   //Enable the TIM1 global Interrupt 
  NVIC_InitStructure.NVIC_IRQChannel = timerNVIC;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  //exception for the timer 1 for which separate interrupt channel is there
  if(timerNVIC==TIM1_CC_IRQn){
    NVIC_InitStructure.NVIC_IRQChannel = TIM1_BRK_UP_TRG_COM_IRQn;
    NVIC_Init(&NVIC_InitStructure);
  }
  // TIM1 counter enable 
  TIM_Cmd(timer, ENABLE);

return 1;//all went well
}

