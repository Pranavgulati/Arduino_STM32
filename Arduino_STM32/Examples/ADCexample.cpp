#include <arm_comm.h>
#include <Arduino.h>
#include <ardGPIO.h>
#include <ardUSART.h>
#include <ardADC.h>

/*The following pins only have an ADC channel therefore only any of these
pins shoulf be passed as parameters

  port GPIOA  pin 0-7 
  port GPIOB  pin 0,1 
  port GPIOC  pin 0-5 
*/

#define SIMULATOR ~(1)

//used to handle system wide delays, you can replace these with your own 
//implementation of a delay 
static __IO uint32_t TimingDelay;

void delayResolution100us(Int32U delay)
{
  for(volatile int i = 500; i;i--);
}

void delay(__IO uint32_t nTime)
{
  //assert parameter nTime >10
  TimingDelay = nTime;
  while(TimingDelay != 0);
}

void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  {
    TimingDelay--;
  }
}

int main(void)
{
RCC_ClocksTypeDef RCC_Clocks;

  /*!< At this stage the microcontroller clock setting is already configured,
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f0xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f0xx.c file
     */
  /* SysTick end of count event each 10ms */
  RCC_GetClocksFreq(&RCC_Clocks);
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);

  //PA10:PA9::RX:TX
  Serial.begin(115200);

  /*
  Interrupt based ADC measurement
  this implementation configures the ADC to fill the memory provided with the 
  latest value as soon as conversion completes 
  so anytime the varaible temp is referenced it will have the latest value from the ADC
  must be called again if some other analogRead was called after this statement
  since there is only one ADC and at a time only one measurement takes place
  */  
  int temp[]={0};
  analogRead(GPIOB,1,temp);
  while(1)
  {
     
    //blocking analogRead like arduino the interrupt is overridden once this call is made
    int a =analogRead(GPIOC,5); 
   
    Serial.print("ADC Value: ");
    Serial.println(a);
    
      
  }
}