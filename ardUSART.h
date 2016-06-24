

#ifndef _ardUSART_h
#define _ardUSART_h 


#include <stm32f0xx_usart.h>
#include <stm320Fxx_ksk.h>
#define RECV_BUF_LEN 256

#define NORMAL -1
#define ARD_BIN 0
#define ARD_HEX 1
#define ARD_DEC 2
class serial {
public:
 uint8_t recvBuf[256];
 uint8_t recvBuf_tail;
 uint8_t recvBuf_head;
USART_TypeDef* USART;
USART_InitTypeDef* USART_props;

void stop();
void stopAll();
void begin(uint8_t COMPORT,uint32_t baudRate);
void write(uint8_t Data);
uint16_t read();
uint8_t available();

void print(const char *data);
void print(unsigned long data);
void print(int data);
void print(unsigned long data,uint8_t mode);
void println(const char *data);
void println(unsigned long data);
void println(int data);
void println(unsigned long data,uint8_t mode);
};


extern serial Serial;



#ifdef __cplusplus
 extern "C" {
#endif


#ifdef __cplusplus
 }
#endif

#endif
