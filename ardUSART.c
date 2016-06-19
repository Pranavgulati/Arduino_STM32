#include <Arduino.h>
#include <ardUSART.h>

void Serial_stop(){
USART_DeInit(&Serial.USART);
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
@param baudRate 9600.,19200,115200 etc.

@retval None
*/
void Serial_begin(uint8_t COMPORT,uint32_t baudRate){
  USART_TypeDef* USART =USART1;
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
  
  Serial.USART=*(USART);
  USART_StructInit(&(Serial.USART_props));
  Serial.USART_props.USART_BaudRate=baudRate;
  USART_Init(&Serial.USART,&Serial.USART_props);
  USART_ITConfig(&Serial.USART,USART_IT_RXNE,  ENABLE);
  USART_Cmd(&Serial.USART,ENABLE);
  //interrupts are registered only for USART1 and is considered the default port
  //PRO users may change this as they want
  NVIC_SetPriority(USART1_IRQn,1);
}
 
void Serial_write(uint8_t Data){
  
  USART_SendData(&Serial.USART,Data);
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


