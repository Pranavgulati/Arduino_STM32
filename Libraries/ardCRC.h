#ifndef _ardCRC_h
#define _ardCRC_h

#include <stm32f0xx_crc.h>

class crc{
public:
void begin(uint32_t poly=0x4C11DB7);  

unsigned long int  calcBlockCRC(uint32_t *CRCBuffer,uint32_t size);




};
extern crc Crc;










#ifdef __cplusplus
 extern "C" {
#endif


#ifdef __cplusplus
}
#endif

#endif
