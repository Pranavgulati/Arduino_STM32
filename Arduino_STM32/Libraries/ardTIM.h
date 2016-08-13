#ifndef _ardTIM_h
#define _ardTIM_h

#include <stm32f0xx_tim.h>
/*
11 completely non conflicting PWMs are available 
10 conflicting PWMs are available with each conflicting with one other pin
3  conflicting PWMs are available with each conflicting with 2 other pins

therfore 11 + 10/2 +3/3 = 17 total PWMs are available which can run simultaneously

for sake of simplicity i'm listing only the non- conflicting ones but the API supports all

GPIOA 4,8,9,10,11
GPIOB 0,1,4,5,14,15

for more details look in TimerPortMap.h 
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
