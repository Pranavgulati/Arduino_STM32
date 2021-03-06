#ifndef _ardGPIO_h
#define _ardGPIO_h

#include <stm32f0xx_gpio.h>
#include <stdarg.h>



/*
  @param
port: GPIOA,B,C,D,F
pin: 0-15
mode:0-3

--Optional--
outputType:
  GPIO_OType_PP = 0x00, push pull
  GPIO_OType_OD = 0x01 open drain
PUPD:
  GPIO_PuPd_NOPULL = 0x00,
  GPIO_PuPd_UP     = 0x01,
  GPIO_PuPd_DOWN   = 0x02
speed:
  GPIO_Speed_Level_1  = 0x00,  I/O output speed: Low 2 MHz 
  GPIO_Speed_Level_2  = 0x01, I/O output speed: Medium 10 MHz 
  GPIO_Speed_Level_3  = 0x03  I/O output speed: High 50 MHz 
}GPIOSpeed_TypeDef;

*/
void pinMode(GPIO_TypeDef* port, uint8_t pin,uint8_t mode,uint8_t PUPD,uint8_t speed,uint8_t outputType);
void pinMode(GPIO_TypeDef* port, uint8_t pin,uint8_t mode,uint8_t PUPD,uint8_t speed);
void pinMode(GPIO_TypeDef* port, uint8_t pin,uint8_t mode,uint8_t PUPD);
void pinMode(GPIO_TypeDef* port, uint8_t pin,uint8_t mode);

void digitalWrite(GPIO_TypeDef* port, uint8_t pin,uint8_t state);
uint8_t digitalRead(GPIO_TypeDef* port, uint8_t pin);
uint8_t digitalReadOut(GPIO_TypeDef* port, uint8_t pin);
uint16_t digitalReadDataOut(GPIO_TypeDef* port);
void pinAFconfig(GPIO_TypeDef* port,uint16_t pinSource,uint8_t altFunction);

#ifdef __cplusplus
 extern "C" {
#endif


#ifdef __cplusplus
}
#endif

#endif