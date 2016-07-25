#include <TimerPortMap.h>
unsigned int portAnvic[16]={
    TIM2_IRQn,        //ch1
    TIM2_IRQn,        //ch2
    TIM2_IRQn,        //ch3
    TIM2_IRQn,        //ch4
    TIM14_IRQn,       //ch1
    TIM2_IRQn,        //ch1
    TIM16_IRQn,       //ch1
    TIM17_IRQn,       //ch1
    TIM1_CC_IRQn,        //ch1
    TIM1_CC_IRQn,        //ch2
    TIM1_CC_IRQn,        //ch3
    TIM1_CC_IRQn,        //ch4
    0,                          //ch etr
    0,
    0,
    TIM2_IRQn,        //ch1
  };

//available timer input for input capture
//PB 0,1,3,4,5
    unsigned int portBnvic[16]={
    TIM3_IRQn,        //ch3
    TIM3_IRQn,        //ch4
    0,                          //no timer
    TIM2_IRQn,        //ch2
    TIM3_IRQn,        //ch1
    TIM3_IRQn,        //ch2
    0,                          //ch1n
    0,                          //ch1n
    TIM16_IRQn,       //ch1
    TIM17_IRQn,       //ch1
    TIM2_IRQn,        //ch3
    TIM2_IRQn,        //ch4
    0,                          //ch bk1n
    0,                          //ch1n
    TIM15_IRQn,       //ch1
    TIM15_IRQn        //ch2
  };