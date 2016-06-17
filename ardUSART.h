

#ifndef _ardUSART_h
#define _ardUSART_h 
#include "stm32f0xx_usart.h"
#define RECV_BUF_LEN 256
//USART1 is the default USART port and hence is used for all serial comm.
typedef struct {
USART_TypeDef USART;
USART_InitTypeDef USART_props;
 uint8_t recvBuf[256];
 uint8_t recvBuf_tail;
 uint8_t recvBuf_head;
} serial;

static serial Serial;
void Serial_stop();
void Serial_stopAll();
void Serial_begin(uint32_t baudRate);
void Serial_write(uint16_t Data);
uint16_t Serial_read(USART_TypeDef* USARTx);
uint8_t Serial_available();



#endif