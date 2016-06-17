#include <ardUSART.h>
#include <ardGPIO.h>


void Serial_stop(){
USART_DeInit(&Serial.USART);
}

void Serial_stopAll(){
USART_DeInit(USART1);
USART_DeInit(USART2);
USART_DeInit(USART3);
USART_DeInit(USART4);
}
void Serial_begin(uint32_t baudRate){
//  void STM_EVAL_COMInit(COM_TypeDef COM, USART_InitTypeDef* USART_InitStruct)
pinMode(GPIOA,9,GPIO_MODE_AF);
  GPIO_InitTypeDef GPIO_InitStructure;
  uint8_t COM=0;//default com port pin A9,A10
  /* Enable GPIO clock */
  RCC_AHBPeriphClockCmd(COM_TX_PORT_CLK[COM] | COM_RX_PORT_CLK[COM], ENABLE);
  /* Enable USART clock */
  RCC_APB2PeriphClockCmd(COM_USART_CLK[COM], ENABLE); 
  /* Connect PXx to USARTx_Tx */
  GPIO_PinAFConfig(COM_TX_PORT[COM], COM_TX_PIN_SOURCE[COM], COM_TX_AF[COM]);
  /* Connect PXx to USARTx_Rx */
  GPIO_PinAFConfig(COM_RX_PORT[COM], COM_RX_PIN_SOURCE[COM], COM_RX_AF[COM]);
  
  /* Configure USART Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = COM_TX_PIN[COM];
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(COM_TX_PORT[COM], &GPIO_InitStructure);
    
  /* Configure USART Rx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = COM_RX_PIN[COM];
  GPIO_Init(COM_RX_PORT[COM], &GPIO_InitStructure);

  /* USART configuration */
  USART_Init(Serial.USART, USART_InitStruct);
  /* Enable USART */
  USART_Cmd(Serial.USART, ENABLE); 
  
Serial.USART=*USART1;
USART_StructInit(&(Serial.USART_props));

Serial.USART_props.USART_BaudRate=baudRate;
USART_Init(&Serial.USART,&Serial.USART_props);
USART_ITConfig(USART1,USART_IT_RXNE,  ENABLE);
USART_Cmd(Serial.USART,ENABLE);
NVIC_SetPriority(USART1_IRQn,1);
}
 

void Serial_write(uint16_t Data){
  USART_SendData(USART1,Data);
}

uint16_t Serial_read(USART_TypeDef* USARTx)
{
    // Empty buffer?
  if (Serial.recvBuf_head == Serial.recvBuf_tail)
    return -1;

  // Read from "head"
  uint8_t d = Serial.recvBuf[Serial.recvBuf_head]; // grab next byte
  Serial.recvBuf_head = (Serial.recvBuf_head + 1) % RECV_BUF_LEN;
  return d;
}
uint8_t Serial_available()
{
  return (Serial.recvBuf_tail + RECV_BUF_LEN - Serial.recvBuf_head) % RECV_BUF_LEN;
}


