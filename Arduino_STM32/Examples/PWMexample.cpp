#include <Arduino.h>
#include <ardTIM.h>

#define SIMULATOR ~(1)


/*
All freely available PWM channels
GPIOA 4,8,9,10,11
GPIOB 0,1,4,5,14,15
GPIOC does nothing 
*/

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
  
  analogWrite(GPIOA,6,80);
  analogWrite(GPIOA,7,70);
  analogWrite(GPIOA,1,60);
  analogWrite(GPIOA,2,50);
  analogWrite(GPIOA,3,40);
  
  while(1)
  {
   

  
  }
}