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

keep this in the arduino.h lib so that this can be accessed in the future without timers
attachInterrupt -timer events and others

#2 sounds better and beautiful actually


use TIM6 for event generations

use TIM 1/2/3 for pwm/input capture  most of the port A and B pins



*/

#include <ardTIM.h>

void analogWrite(GPIO_TypeDef* port,int pin,int value){
  //choose a timer for analog write here
  //APB1 or APB2
  //so timer selection happens on the basis of the port and pin 
  
  
  //only PA and PB are supported 
   //assert here that only port a or b is sent as the argument 
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  /* clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  int clockShift = (int)(((long int)port&0x00001C00)>>10);
  RCC_AHBPeriphClockCmd(((uint32_t)0x00020000)<<clockShift, ENABLE);
   
  
  /* GPIOA Configuration: TIM3 CH1 (PA6) and TIM3 CH2 (PA7) */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(port, &GPIO_InitStructure); 

  /* GPIOB Configuration: TIM3 CH3 (PB0) and TIM3 CH4 (PB1) */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
    
  /* Connect TIM Channels to AF2 */
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_1); 
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource0, GPIO_AF_1);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource1, GPIO_AF_1);

  /* Initialize Leds mounted on STM320518-EVAL board */
  
  
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);

  TIM_OCStructInit(&TIM_OCInitStructure);

  /* ---------------------------------------------------------------------------
    TIM3 Configuration: Output Compare Active Mode:
    In this example TIM3 input clock (TIM3CLK) is set to APB1 clock (PCLK1)    
      TIM3CLK = PCLK1  
      PCLK1 = HCLK 
      => TIM3CLK = HCLK = SystemCoreClock 
          
    To get TIM3 counter clock at 1 KHz, the prescaler is computed as follows:
       Prescaler = (TIM3CLK / TIM3 counter clock) - 1
       Prescaler = (SystemCoreClock /1 KHz) - 1
       
    Generate 4 signals with 4 different delays:
    TIM3_CH1 delay = CCR1_Val/TIM3 counter clock = 1000 ms
    TIM3_CH2 delay = CCR2_Val/TIM3 counter clock = 500 ms
    TIM3_CH3 delay = CCR3_Val/TIM3 counter clock = 250 ms
    TIM3_CH4 delay = CCR4_Val/TIM3 counter clock = 125 ms

    Note: 
     SystemCoreClock variable holds HCLK frequency and is defined in system_stm32f0xx.c file.
     Each time the core clock (HCLK) changes, user had to call SystemCoreClockUpdate()
     function to update SystemCoreClock variable value. Otherwise, any configuration
     based on this variable will be incorrect. 
     
  --------------------------------------------------------------------------- */
  int CCR1_Val =3;
  int CCR2_Val =0;
  int CCR3_Val =1;
  int CCR4_Val =2;
  
  
  
  /*Compute the prescaler value */
 int PrescalerValue = (uint16_t) (SystemCoreClock / 1000) - 1;

  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = 65535;
  TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  /* Output Compare Active Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Active;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
  TIM_OC1Init(TIM3, &TIM_OCInitStructure);

  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Disable);
  TIM_ARRPreloadConfig(TIM3, DISABLE); 
  /* Output Compare Active Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_Pulse = CCR2_Val;
  TIM_OC2Init(TIM3, &TIM_OCInitStructure);

  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Disable);

  /* Output Compare Active Mode configuration: Channel3 */
  TIM_OCInitStructure.TIM_Pulse = CCR3_Val;
  TIM_OC3Init(TIM3, &TIM_OCInitStructure);

  TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Disable);

  /* Output Compare Active Mode configuration: Channel4 */
  TIM_OCInitStructure.TIM_Pulse = CCR4_Val;
  TIM_OC4Init(TIM3, &TIM_OCInitStructure);

  TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Disable);
 
  /* TIM3 enable counter */
  TIM_Cmd(TIM3, ENABLE);
  
  TIM_GenerateEvent(TIM3, TIM_EventSource_Update);


}
