
#include <Arduino.h>
#include <ardGPIO.h>


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

  pinMode(GPIOC,8,ARD_OUTPUT);
  pinMode(GPIOC,9,ARD_OUTPUT);
  pinMode(GPIOA,4,ARD_INPUT);
  pinMode(GPIOB,4,ARD_INPUT);
  pinMode(GPIOC,4,ARD_INPUT);
  pinMode(GPIOA,5,ARD_INPUT);
  while(1){
    
    if(digitalRead(GPIOA,4)!=0){digitalWrite(GPIOC,8,ARD_HIGH);}
    else{digitalWrite(GPIOC,8,ARD_LOW);}
    if(digitalRead(GPIOA,5)!=0){digitalWrite(GPIOC,9,ARD_HIGH);}
    else{digitalWrite(GPIOC,9,ARD_LOW);}
    #if SIMULATOR
    delay(50);
    #endif

  }
}