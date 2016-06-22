#include <Arduino.h>
#include <ardUSART.h>
#include <String.h>

serial Serial;

void Serial_stop(){
USART_DeInit(Serial.USART);
}

void Serial_stopAll(){
USART_DeInit(USART1);
USART_DeInit(USART2);
USART_DeInit(USART3);
USART_DeInit(USART4);
}
/*
@brief write something here
@param COM1=RX:TX::A10:A9 , COM2=RX:TX::A3:A2 
@param baudRate 9600,19200,115200 etc.

@retval None
*/
void Serial_begin(uint8_t COMPORT,uint32_t baudRate){
  USART_TypeDef* USART =USART1;
  USART_InitTypeDef USART_properties;
  GPIO_TypeDef* gpioPort=GPIOA;
  uint8_t RXpin=10,TXpin=9;
  uint32_t usartClock=RS232_COM1_CLK;
  switch(COMPORT){
    case COM1:
      USART =USART1;
      gpioPort=GPIOA;
      RXpin=10;
      TXpin=9;
      usartClock=RS232_COM1_CLK;
      break;
    case COM2:
      USART =USART2;
      gpioPort=GPIOA;
      RXpin=3;
      TXpin=2;
      usartClock=UXT_COM2_CLK;
      break;
    default:
      //case 1 hence already initialized is used
      break;
    }  
  pinMode(gpioPort,TXpin,GPIO_Mode_AF,GPIO_PuPd_UP,GPIO_Speed_10MHz,GPIO_OType_PP);
  pinMode(gpioPort,RXpin,GPIO_Mode_AF,GPIO_PuPd_UP,GPIO_Speed_10MHz,GPIO_OType_PP);
  
  //enable usart clock
  RCC_APB2PeriphClockCmd(usartClock, ENABLE); 
  //alternate function config for the pins
  pinAFconfig(gpioPort,TXpin, GPIO_AF_1);
  pinAFconfig(gpioPort,RXpin, GPIO_AF_1);
  /* USART configuration */
  //setting the USART props in our struct so that they can be read also
  
  Serial.USART=USART;
  Serial.USART_props=&USART_properties;
  USART_StructInit(Serial.USART_props);
  Serial.USART_props->USART_BaudRate=baudRate;
  USART_Init(Serial.USART,Serial.USART_props);
  USART_ITConfig(Serial.USART,USART_IT_RXNE,  ENABLE);
  USART_Cmd(Serial.USART,ENABLE);
  //interrupts are registered only for USART1 and is considered the default port
  //PRO users may change this as they want
  NVIC_InitTypeDef NVIC_InitStructure;
  /* Enable the USART Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

}
 
void Serial_write(uint8_t Data){
  
  USART_SendData(USART1,Data);
}

uint16_t Serial_read(){
  
  // Empty buffer?
if (Serial.recvBuf_head == Serial.recvBuf_tail){ return -1;}
  // Read from "head"
  uint8_t d = Serial.recvBuf[Serial.recvBuf_head]; // grab next byte
  Serial.recvBuf_head = (Serial.recvBuf_head + 1) % RECV_BUF_LEN;
  return d;
}
uint8_t Serial_available(){
  return (Serial.recvBuf_tail + RECV_BUF_LEN - Serial.recvBuf_head) % RECV_BUF_LEN;
}

void Serial_Dprint(unsigned long data,...){
  uint8_t mode;//BIN,HEX,DEC,normal(-1)
    va_list ap;
    va_start(ap, data);
    int temp=va_arg(ap, int);
    if(temp!=-1){ mode=temp;}
    else{mode=NORMAL;}
    va_end(ap);
    unsigned long int mask=0;
    uint8_t characters[10];
    uint8_t flag=0;
    switch(mode){
    case ARD_BIN:
      Serial_write('0');
      Serial_write('b');
      mask=0x80000000;
      for(unsigned int i=0;i<sizeof(data);i++){
        Serial_write(((data&mask)!=0?1:0)+'0');
       mask=mask>>1;
      }      
      break;
    case ARD_HEX:
      Serial_write('0');
      Serial_write('x');
       mask=0xF0000000;
      for(unsigned int i=0;i<8;i++){
        Serial_write((data&mask>>4*(7-i)));
       mask=mask>>4;
      }      
      
      break;
    case (ARD_DEC):
     for(unsigned int i=9;i!=0;i--){
       characters[i]=data%10;
       data=data/10;
        }      
     
     for(unsigned int i=0;i<10;i++){
       if(characters[i]!=0 || flag==1){flag=1;Serial_write(characters[i]+'0');}
     }
      break;
    default:
      Serial_write((uint8_t)data);
      break;
    
    }  


}

void Serial_print(uint8_t *data){
  int temp =strlen((const char*)data);
    for (int i=0;i<strlen((const char*)data);i++){
    Serial_Dprint(*(data++),ARD_HEX);}
}

void Serial_println(uint8_t *data){
  Serial_print(data);
  Serial_write('\n');
}


