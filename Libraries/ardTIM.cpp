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

void PWMout(GPIO_TypeDef* port,int pin,int percentValue,int frequency){
  //choose a timer for analog write here
  //APB1 or APB2
  //so timer selection happens on the basis of the port and pin 
  
  
  //only PA and PB are supported 
   //assert here that only port a or b is sent as the argument 
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  // you havee to select timer,then its clock from port and pin 
  
  unsigned int portAtimClkMap[16]={
    RCC_APB1Periph_TIM2,        //ch1
    RCC_APB1Periph_TIM2,        //ch2
    RCC_APB1Periph_TIM2,        //ch3
    RCC_APB1Periph_TIM2,        //ch4
    RCC_APB1Periph_TIM14,       //ch1
    RCC_APB1Periph_TIM2,        //ch1
    RCC_APB2Periph_TIM16,       //ch1
    RCC_APB2Periph_TIM17,       //ch1
    RCC_APB2Periph_TIM1,        //ch1
    RCC_APB2Periph_TIM1,        //ch2
    RCC_APB2Periph_TIM1,        //ch3
    RCC_APB2Periph_TIM1,        //ch4
    0,                          //ch etr
    0,
    0,
    RCC_APB1Periph_TIM2,        //ch1
  };
    unsigned int portBtimClkMap[16]={
    RCC_APB1Periph_TIM3,        //ch3
    RCC_APB1Periph_TIM3,        //ch4
    0,                          //no timer
    RCC_APB1Periph_TIM2,        //ch2
    RCC_APB1Periph_TIM3,        //ch1
    RCC_APB1Periph_TIM3,        //ch2
    0,                          //ch1n
    0,                          //ch1n
    RCC_APB2Periph_TIM16,       //ch1
    RCC_APB2Periph_TIM17,       //ch1
    RCC_APB1Periph_TIM2,        //ch3
    RCC_APB1Periph_TIM2,        //ch4
    0,                          //ch bk1n
    0,                          //ch1n
    RCC_APB2Periph_TIM15,       //ch1
    RCC_APB2Periph_TIM15        //ch2
  };
    TIM_TypeDef* portAtimMap[16]={
    TIM2,        //ch1          //conflicts with PA0,PA5,PA15
    TIM2,        //ch2          //conflicts with PA1,PB3
    TIM2,        //ch3          //conflicts with PA2,PB10
    TIM2,        //ch4          //conflicts with PA3,PB11
    TIM14,       //ch1
    TIM2,        //ch1          //conflicts with PA0,PA5,PA15
    TIM16,       //ch1          //conflicts with PA6,PB8
    TIM17,       //ch1          //conflicts with PA7,PB9
    TIM1,        //ch1
    TIM1,        //ch2
    TIM1,        //ch3
    TIM1,        //ch4
    0,           //ch etr
    0,
    0,
    TIM2,        //ch1          //conflicts with PA0,PA5,PA15
  };
   TIM_TypeDef* portBtimMap[16]={
    TIM3,        //ch3
    TIM3,        //ch4
    0,           //no timer
    TIM2,        //ch2          //conflicts with PA1,PB3
    TIM3,        //ch1
    TIM3,        //ch2
    0,           //ch1n
    0,           //ch1n
    TIM16,       //ch1          //conflicts with PA6,PB8
    TIM17,       //ch1          //conflicts with PA7,PB9
    TIM2,        //ch3          //conflicts with PA2,PB10
    TIM2,        //ch4          //conflicts with PA3,PB11
    0,           //ch bk1n
    0,           //ch1n
    TIM15,       //ch1
    TIM15        //ch2
  };
      unsigned int portAchMap[16]={
    1,        //ch1
    2,        //ch2
    3,        //ch3
    4,        //ch4
    1,       //ch1
    1,        //ch1
    1,       //ch1
    1,       //ch1
    1,        //ch1
    2,        //ch2
    3,        //ch3
    4,        //ch4
    0,        //ch etr
    0,
    0,
    1,        //ch1
  };
    unsigned int portBchMap[16]={
    3,        //ch3
    4,        //ch4
    0,        //no timer
    2,        //ch2
    1,        //ch1
    2,        //ch2
    0,       //ch1n
    0,       //ch1n
    1,       //ch1
    1,       //ch1
    3,        //ch3
    4,        //ch4
    0,        //ch bk1n
    0,        //ch1n
    1,       //ch1
    2        //ch2
  };
  unsigned int portAtimAFMap[16]={
  GPIO_AF_2,
  GPIO_AF_2,
  GPIO_AF_2,
  GPIO_AF_2,
  GPIO_AF_4,
  GPIO_AF_2,
  GPIO_AF_5,
  GPIO_AF_5,
  GPIO_AF_2,
  GPIO_AF_2,
  GPIO_AF_2,
  GPIO_AF_2,
  0,
  0,
  0,
  GPIO_AF_2
  };
  unsigned int portBtimAFMap[16]={
  GPIO_AF_1,
  GPIO_AF_1,
  0,
  GPIO_AF_2,
  GPIO_AF_1,
  GPIO_AF_1,
  GPIO_AF_2,
  GPIO_AF_2,
  GPIO_AF_2,
  GPIO_AF_2,
  GPIO_AF_2,
  GPIO_AF_2,
  GPIO_AF_2,
  GPIO_AF_2,
  GPIO_AF_1,
  GPIO_AF_1,  
  };
  //timer is selected based on the pins and port so
  unsigned int APBperiphClock=0;
  unsigned int AFnumber=0;
  TIM_TypeDef* timerNumber=0;
  unsigned int channelNumber=0;
  if     (port==GPIOA){
    APBperiphClock=portAtimClkMap[pin];
    AFnumber=portAtimAFMap[pin];
    timerNumber=portAtimMap[pin];
    channelNumber=portAchMap[pin];
  }
  else if(port==GPIOB){
    APBperiphClock=portBtimClkMap[pin];
    AFnumber=portBtimAFMap[pin];
    timerNumber=portBtimMap[pin];
    channelNumber=portBchMap[pin];
  }
  
  if(IS_RCC_APB2_PERIPH(APBperiphClock)){
  RCC_APB2PeriphClockCmd(APBperiphClock, ENABLE);
  }
  else if(IS_RCC_APB1_PERIPH(APBperiphClock)){
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
  GPIO_InitStructure.GPIO_Pin = pin;
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

  TIM_TimeBaseInit(timerNumber, &TIM_TimeBaseStructure);

  /* Channel 1, 2,3 and 4 Configuration in PWM mode */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR_val;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  
  switch(channelNumber){
  case 1:
    TIM_OC1Init(timerNumber, &TIM_OCInitStructure);
    break;
  case 2:
    TIM_OC2Init(timerNumber, &TIM_OCInitStructure);
    break;
  case 3 :
    TIM_OC3Init(timerNumber, &TIM_OCInitStructure);
    break;
  case 4:
    TIM_OC4Init(timerNumber, &TIM_OCInitStructure);
    break;
  default:
    //ERROOOORRR ssup?
    break;
  }
  /* TIM1 counter enable */
  TIM_Cmd(timerNumber, ENABLE);

  /* TIM1 Main Output Enable */
  TIM_CtrlPWMOutputs(timerNumber, ENABLE);

}

void analogWrite(GPIO_TypeDef* port,int pin,int value){
PWMout( port, pin,value,10000);
}

void PWMout(GPIO_TypeDef* port,int pin,int percentValue){
PWMout( port, pin,percentValue,10000);
}
