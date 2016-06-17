#include <ardGPIO.h>


/*
  @param
port: 0-3,5 :: A,B,C,D,F
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


void pinMode(uint8_t port, uint8_t pin,uint8_t mode,uint8_t PUPD,uint8_t speed,uint8_t outputType)
*/
void pinMode(GPIO_TypeDef* port, uint8_t pin,uint8_t mode,...){
  uint8_t PUPD, speed, outputType;
    va_list ap;
    va_start(ap, mode);
    int temp=va_arg(ap, int);
    if(temp!=-1){ PUPD=temp;}
    else{PUPD=GPIO_PuPd_NOPULL;}
    temp=va_arg(ap, int);
    if(temp!=-1){speed=temp;}
    else{speed=GPIO_Speed_Level_3;}
    temp=va_arg(ap, int);
    if(temp!=-1){outputType=temp;}
    else{outputType=GPIO_OType_PP;}
    va_end(ap);
  
  GPIO_InitTypeDef  GPIO_InitStructure;
  int clockShift = (int)(((long int)port&0x00001C00)>>10);
  RCC_AHBPeriphClockCmd(((uint32_t)0x00020000)<<clockShift, ENABLE);

  //Configure the GPIO pin 
  GPIO_InitStructure.GPIO_Pin = ((uint16_t)0x0001)<<pin;
  GPIO_InitStructure.GPIO_Mode =(GPIOMode_TypeDef) mode;
  GPIO_InitStructure.GPIO_PuPd = (GPIOPuPd_TypeDef)PUPD;
  GPIO_InitStructure.GPIO_Speed = (GPIOSpeed_TypeDef)speed;
  GPIO_InitStructure.GPIO_OType = (GPIOOType_TypeDef)outputType;
  GPIO_Init(port, &GPIO_InitStructure);
  port->BSRR = ((uint16_t)0x0001)<<pin;
 

}



void digitalWrite(GPIO_TypeDef* port, uint8_t pin,uint8_t state){
 /* if(state!=0){
port->ODR |= (1<<pin);  
  }
  else {
port->ODR &= ~(1<<pin);    
  }
*/
//  can use the BSRR register for direct pin level actions as follows
  if(state!=0){  port->BSRR= (1<<pin);  }
  else {
  //since bit set register takes priority over the reset register 
  port->BSRR= (0<<pin);
  port->BRR= (1<<pin);
  }

  
}

uint8_t digitalRead(GPIO_TypeDef* port, uint8_t pin){
uint16_t inData=GPIO_ReadInputData(port);
return (uint8_t)(inData &(1<<pin))!=0?1:0;
}

uint8_t digitalReadOut(GPIO_TypeDef* port, uint8_t pin){
return (((uint16_t)port->ODR)&(1<<pin))!=0?1:0;
}

uint16_t digitalReadDataOut(GPIO_TypeDef* port){
return ((uint16_t)port->ODR);
}
