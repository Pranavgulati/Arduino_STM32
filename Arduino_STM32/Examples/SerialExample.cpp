
#include <Arduino.h>
#include <ardUSART.h>


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

  
//Serial=RX:TX::A10:A9 , Serial1=RX:TX::A3:A2 
  Serial1.begin(115200);
  Serial.begin(9600);
  while(1)
  {
    
   
    Serial.println("Hello World");
    Serial.println(65536,ARD_DEC);
    Serial.println(65536,ARD_BIN);
    Serial.println(65536,ARD_HEX);   
   
    char input='A';
    if(Serial.available()){
    //be sure to Serial_begin with the port that you intend to listen on
   input = Serial.read();
    }
    if(input=='B'){
    Serial.println("HELLO");
    Serial.print("so you pressed: ");
    Serial.println(input);    
    }
 
  }

}