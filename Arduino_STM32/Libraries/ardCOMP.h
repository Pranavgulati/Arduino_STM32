#ifndef _ardCRC_h
#define _ardCRC_h

#include <stm32f0xx_comp.h>


class comp{
public:
  void begin();
  void begin(int mode);


};

extern  comp Comp;







#ifdef __cplusplus
 extern "C" {
#endif


#ifdef __cplusplus
}
#endif

#endif
