

#ifndef _ardUSART_h
#define _ardUSART_h 

#ifdef __cplusplus
 extern "C" {
#endif



#include "stm32f0xx_usart.h"
#include <stm320Fxx_ksk.h>
#define RECV_BUF_LEN 256

#define NORMAL -1
#define ARD_BIN 0
#define ARD_HEX 1
#define ARD_DEC 2


//USART1 is the default USART port and hence is used for all serial comm.
typedef struct {
USART_TypeDef* USART;
USART_InitTypeDef* USART_props;
 uint8_t recvBuf[256];
 uint8_t recvBuf_tail;
 uint8_t recvBuf_head;
} serial;

extern serial Serial;

void Serial_stop();
void Serial_stopAll();
void Serial_begin(uint8_t COMPORT,uint32_t baudRate);
void Serial_write(uint8_t Data);
uint16_t Serial_read();
uint8_t Serial_available();

void Serial_println(uint8_t *data);
void Serial_print(uint8_t *data);
void Serial_Dprint(unsigned long data,...);


#ifdef __cplusplus
 }
#endif

#endif
