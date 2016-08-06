#include <Arduino.h>
#include <ardGPIO.h>
#include <ardUSART.h>
#include <ardADC.h>
#include <ardDAC.h>
#include <ardCRC.h>
#include <ardTIM.h>

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
    /*Only 32 bit input data CRC is calculated
    so all data must be casted to 32bit pointer */
   unsigned int CRCbuf[1]={12345};
  
  while(1)
  {
   /*clears the previous data in the registers compulsory to call for every new
   CRC computation*/
   Crc.begin();
   /*
   STM32 implements CRC32-MPEG2 which uses big endian and no final flip mask 
   compared to the zip CRC32 which uses little endian and a final flip mask.
   So the CRC maynot be as that found on the internet 
   */
   /*Only 32 bit input data CRC is calculated
    so all data must be casted to 32bit pointer */
   Serial.print("CRC input: ");
   Serial.println(CRCbuf[0],ARD_DEC);
   unsigned int check=Crc.calcBlockCRC(CRCbuf,sizeof(CRCbuf));
   Serial.print("CRC output: ");
   Serial.println(check,ARD_HEX);
   Crc.stop();
   delay(50);
  }
}