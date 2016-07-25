#ifndef _ardTIM_h
#define _ardTIM_h

#include <stm32f0xx_tim.h>
/*

GPIOA 0,1,2,3,5,8,9,10,11,15
GPIOA 4,6,7 can only PWMout and getFrequency and not getDuty

GPIOB 0,1,3,4,5,10,11,14,15
GPIOB 8,9 can only PWMout and getFrequency and not getDuty

tim1,2,3 have 4 channels
tim15 has 2 channels for pwm and IC
tim14 has  1 channel for pwn or input capture
tim16 has  1 channel for pwn or input capture
tim17 has  1 channel for pwn or input capture
tim6 can only do basic timing
*/



void PWMout(GPIO_TypeDef* port,int pin,int percentValue,int frequency);
void PWMout(GPIO_TypeDef* port,int pin,int percentValue);
void analogWrite(GPIO_TypeDef* port,int pin,int value);
uint8_t  getFrequency(GPIO_TypeDef* port,int pin,unsigned int *freqDataBuffer,unsigned int *dutyDataBuffer,unsigned int minSamples);
#ifdef __cplusplus
 extern "C" {
#endif


#ifdef __cplusplus
}
#endif

#endif
