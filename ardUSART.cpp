#include <Arduino.h>
#include <ardUSART.h>
#include <String.h>

serial Serial;

void serial::stop(){
USART_DeInit(Serial.USART);
}
void serial::stopAll(){
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
void serial::begin(uint8_t COMPORT,uint32_t baudRate){
  recvBuf_tail=0;
  recvBuf_head=0;
  txBuf_tail=0;
  txBuf_head=0;
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
 
void serial::write(uint8_t Data){
  USART_SendData(Serial.USART,Data);
}
void serial::write(uint8_t *data,uint32_t size){
     //disable other interrupts for the time being or mayb stm32 does it itself
    // if buffer full, then wait for it to empty
  for(int i=0;i<size;i++){
    uint8_t next = (Serial.txBuf_tail + 1) % TX_BUF_LEN;
    if (next != Serial.txBuf_head)
    {
      // save new data in buffer: tail points to where byte goes
      Serial.txBuf[Serial.txBuf_tail] = (*(data++)); // save new byte
      Serial.txBuf_tail= next;
    } 
    /*
      by doing this when 'i' is incremented the code will try again to 
      assign data into the buffer,and the loop will not end until the buffer 
      has been sent
      this is a partially blocking write but it should work since the TC happens
      fast and the buffer is cleared as its written    
    */
    else 
    {
      i--;      
    }
  }
  
}

//BIN,HEX,DEC,normal(-1)
void serial::print(unsigned long data,uint8_t mode){
    unsigned long int mask=0;
    uint8_t characters[10]={0};
    uint8_t flag=0;
    switch(mode){
    case ARD_BIN:
      write('0');
      write('b');
      mask=0x80000000;
      for(unsigned int i=0;i<sizeof(data)*8;i++){
        if(i%4==0){write(' ');}
        write((uint8_t)((data&mask)!=0?1:0)+'0');
       mask=mask>>1;
      }
      break;
    case ARD_HEX:
      write('0');
      write('x');
       mask=0xF0000000;
      for(unsigned int i=0;i<8;i++){
        write((data&mask)>>4*(7-i));
       mask=mask>>4;
      }      
      
      break;
    case (ARD_DEC):
     for(unsigned int i=9;i!=0;i--){
       characters[i]=data%10;
       data=data/10;
        }      
     
     for(unsigned int i=0;i<10;i++){
       if(characters[i]!=0 || flag==1){flag=1;write((uint8_t)characters[i]+'0');}
     }
      break;
    default:
      write((uint8_t)data);
      break;
    
    }  


}
void serial::print(const char* data){
  int temp =strlen(data);
    for (int i=0;i<temp;i++){
    write(*(data++));
    }
}
void serial::print(unsigned long data){
      print((uint8_t)data,ARD_DEC);
}  
void serial::print(int data){
      print((uint8_t)data,ARD_DEC);
}  

void serial::println(int data){

print(data);
  write('\n');
}
void serial::println(unsigned long data){
print(data);
write('\n');
}
void serial::println(unsigned long data,uint8_t mode){

  print(data);
  write('\n');
}
void serial::println(const char* data){
  print(data);
  write('\n');
}


uint16_t serial::read(){
  
  // Empty buffer?
if (Serial.recvBuf_head == Serial.recvBuf_tail){ return -1;}
  // Read from "head"
  uint8_t d = Serial.recvBuf[Serial.recvBuf_head]; // grab next byte
  Serial.recvBuf_head = (Serial.recvBuf_head + 1) % RX_BUF_LEN;
  return d;
}
uint8_t serial::available(){
  return (Serial.recvBuf_tail + RX_BUF_LEN - Serial.recvBuf_head) % RX_BUF_LEN;
}

