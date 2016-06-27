#ifndef _ardDAC_h
#define _ardDAC_h 
#include <stm32f0xx_dac.h>

class  dac{
uint8_t channel;
public:
  
  void stop();
  //channel : 0,1
  void begin(uint8_t chan);
  void begin();
  
  void out(uint16_t data);
  


};
extern dac Dac;








#ifdef __cplusplus
 extern "C" {
#endif
      

#ifdef __cplusplus
 }
#endif

#endif