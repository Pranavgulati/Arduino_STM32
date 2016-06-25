

#ifndef _ardUSART_h
#define _ardUSART_h 


#include <stm32f0xx_usart.h>
#include <stm320Fxx_ksk.h>
#define RX_BUF_LEN 128
#define TX_BUF_LEN 128

#define NORMAL -1
#define ARD_BIN 0
#define ARD_HEX 1
#define ARD_DEC 2
class serial {
public:
 uint8_t recvBuf[RX_BUF_LEN];
  uint8_t txBuf[TX_BUF_LEN];
 uint8_t recvBuf_tail;
 uint8_t recvBuf_head;
 uint8_t txBuf_tail;
 uint8_t txBuf_head;
USART_TypeDef* USART;
USART_InitTypeDef* USART_props;



void stop();
void stopAll();
void begin(uint8_t COMPORT,uint32_t baudRate);
//TX functions
//non-interrupt based write
void write(uint8_t data);
//interrupt based write,set and forget if TX_BUF_LEN is not exceeded
void write(uint8_t *data,uint32_t size);

//all the folowing use the blocking write
void print(const char *data);
void print(int data);
void print(unsigned long data);
void print(unsigned long data,uint8_t mode);

void println(const char *data);
void println(int data);
void println(unsigned long data);
void println(unsigned long data,uint8_t mode);

//RX functions
uint16_t read();
uint8_t available();

};


extern serial Serial;



#ifdef __cplusplus
 extern "C" {
#endif


#ifdef __cplusplus
 }
#endif

#endif
