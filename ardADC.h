#ifndef _ardADC_h
#define _ardADC_h 
#include <Arduino.h>
#include <stm32f0xx_adc.h>
#include <stm32f0xx_it.h>
/*
12 bit adc 16 ext channels
ADC_IN0..ADC_IN7        :: PA0..PA7
ADC_IN8,ADC_IN9         :: PB0,PB1
ADC_IN10..ADC_IN15      :: PC0..PC5

call is made by pin name and not channel name
NO CLASS for this lib
*/
extern int* ADC_data;
uint8_t analogRead(GPIO_TypeDef* port,uint8_t pin,int* data,uint8_t bits);
int analogRead(GPIO_TypeDef* port,uint8_t pin,uint8_t bits);
//on demand conversion
int analogRead(GPIO_TypeDef* port,uint8_t pin);
/*interrupt based
the pointer is filled by the interrupt
it is slightly difficult to understand how this will work but lets see
this will be auto updating as well and will make sure that the data has 
the latest value always*/
int analogRead(GPIO_TypeDef* port,uint8_t pin,int* data);



#ifdef __cplusplus
 extern "C" {
#endif
      

#ifdef __cplusplus
 }
#endif

#endif