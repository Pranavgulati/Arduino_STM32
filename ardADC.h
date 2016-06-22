#ifndef _ardADC_h
#define _ardADC_h 

/*
the adc will in the following manner
to use interrupts in the best possible way 
the analog read will be made non-waiting by default,that will essentiall lead to
an older value but it makes sense to not hamper CPU exec just for ADC 
there will be support for waiting type analog read

12 bit adc 16 ext channels
ADC_IN0..ADC_IN7        :: PA0..PA7
ADC_IN8,ADC_IN9         :: PB0,PB1
ADC_IN10..ADC_IN15      :: PC0..PC5

NO CLASS for this lib
*/

#ifdef __cplusplus
 extern "C" {
#endif
/*we need to store the pin to channel correspondence in memory so that the 
programmer can simply call by pin name instead of channel name 
*/
//on demand conversion
int analogRead(GPIO_TypeDef* port,uint8_t pin);
/*interrupt based
the pointer is filled by the interrupt
it is slightly difficult to understand how this will work but lets see
this will be auto updating as well and will make sure that the data has 
the latest value always*/
int analogRead(GPIO_TypeDef* port,uint8_t pin,int* data);


 
   
   
   

#ifdef __cplusplus
 }
#endif

#endif