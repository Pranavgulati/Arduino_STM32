#include <ardGPIO.h>


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


void pinMode(uint8_t port, uint8_t pin,uint8_t mode,uint8_t PUPD,uint8_t speed,uint8_t outputType)
*/
void pinMode(GPIO_TypeDef* port, uint8_t pin,uint8_t mode,uint8_t PUPD,uint8_t speed,uint8_t outputType){

  
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
void pinMode(GPIO_TypeDef* port, uint8_t pin,uint8_t mode,uint8_t PUPD,uint8_t speed){
pinMode( port,  pin, mode, PUPD, speed, GPIO_OType_PP);

}

void pinMode(GPIO_TypeDef* port, uint8_t pin,uint8_t mode,uint8_t PUPD){

 pinMode( port,  pin, mode, PUPD, GPIO_Speed_Level_3, GPIO_OType_PP);

}
void pinMode(GPIO_TypeDef* port, uint8_t pin,uint8_t mode){
pinMode( port,  pin, mode, GPIO_PuPd_NOPULL, GPIO_Speed_Level_3, GPIO_OType_PP);

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

/** #wrapper function only #copied from existing lib.
  * @brief  Writes data to the specified GPIO data port.
  * @param  GPIO port like GPIOA,GPIOC,D,F
  * @param  GPIO_PinSource: specifies the pin for the Alternate function,0-15
  * @param  GPIO_AF: selects the pin to used as Alternate function.
  *          This parameter can be one of the following value:
  *            @arg GPIO_AF_0:  WKUP, EVENTOUT, TIM15, SPI1, TIM17, MCO, SWDAT, SWCLK,
  *                             TIM14, BOOT, USART1, CEC, IR_OUT, SPI2, TIM3, USART4,
  *                             CAN, USART2, CRS, TIM16, TIM1, TS 
  *            @arg GPIO_AF_1: USART2, CEC, TIM3, USART1, USART2, EVENTOUT, I2C1,
  *                            I2C2, TIM15, SPI2, USART3, TS, SPI1 
  *            @arg GPIO_AF_2: TIM2, TIM1, EVENTOUT, TIM16, TIM17, USB
  *            @arg GPIO_AF_3: TS, I2C1, TIM15, EVENTOUT 
  *            @arg GPIO_AF_4: TIM14, USART4, USART3, CRS, CAN
  *            @arg GPIO_AF_5: TIM16, TIM17, TIM15, SPI2, I2C2
  *            @arg GPIO_AF_6: EVENTOUT
  *            @arg GPIO_AF_7: COMP1 OUT, COMP2 OUT 
    @note   please use pinMode first to set pin as alternate function first
  * @note   Refer to the Alternate function mapping table in the device datasheet 
  *         for the detailed mapping of the system and peripherals'alternate 
  *         function I/O pins.
  * @retval None
  */
void pinAFconfig(GPIO_TypeDef* port,uint16_t pinSource,uint8_t altFunction){
GPIO_PinAFConfig(port,pinSource,altFunction);
}
