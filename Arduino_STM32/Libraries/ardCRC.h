#ifndef _ardCRC_h
#define _ardCRC_h

#include <stm32f0xx_crc.h>

class crc{
public:
  //polynomial cannot be changed for STM32f03 and STM32f05 series devices
void begin(uint32_t poly);  
void begin();  
/*Only 32 bit input data CRC is calculated so all data must be casted to 32bits */
unsigned long int  calcBlockCRC(uint32_t *CRCBuffer,uint32_t size);
unsigned long int  calcCRC(uint32_t CRCBuffer);

void stop();
};
extern crc Crc;










#ifdef __cplusplus
 extern "C" {
#endif


#ifdef __cplusplus
}
#endif

#endif
