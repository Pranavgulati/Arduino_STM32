
#include <arm_comm.h>
#include <main.h>
#include <Arduino.h>
#include <ardGPIO.h>
#include <ardUSART.h>
#include <ardADC.h>
#include <ardDAC.h>
#include <ardCRC.h>
#include <ardTIM.h>

#define SIMULATOR ~(1)


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
/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
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
  //PA10:PA9::RX:TX
  Serial.begin(COM1,115200);
  digitalWrite(GPIOC,8,ARD_LOW);
  digitalWrite(GPIOC,9,ARD_LOW);
  digitalWrite(GPIOC,8,ARD_HIGH);
  digitalWrite(GPIOC,9,ARD_HIGH);
  
     /*Only 32 bit input data CRC is calculated
    so all data must be casted to 32bit pointer */
   uint32_t CRCbuf[1]={12345};
  
  //port GPIOA  pin 0-7 
  //port GPIOB  pin 0,1 
  //port GPIOC  pin 0-5 
  //interrupt based adc 
  //must be called again if some other analogRead was called after this statement
  int temp[]={0};
  analogRead(GPIOB,1,temp);
  
  Dac.begin();
  analogWrite(GPIOA,6,80);
  analogWrite(GPIOA,7,70);
  analogWrite(GPIOA,1,60);
  analogWrite(GPIOA,2,50);
  analogWrite(GPIOA,3,40);
  while(1)
  {
  
  
  
 
   Crc.begin();
   /*Only 32 bit input data CRC is calculated
    so all data must be casted to 32bit pointer */
   long int check=Crc.calcBlockCRC(CRCbuf,sizeof(CRCbuf));
   Crc.stop();
     
    //blocking analogRead
    //int a =analogRead(GPIOC,5); 
   
    Serial.println("blabla");
    Serial.println(65536,ARD_DEC);
    Serial.println("tada");
    uint16_t input=0;
    if(digitalRead(GPIOA,4)!=0){digitalWrite(GPIOC,8,ARD_HIGH);}
    else{digitalWrite(GPIOC,8,ARD_LOW);}
    if(digitalRead(GPIOA,5)!=0){digitalWrite(GPIOC,9,ARD_HIGH);}
    else{digitalWrite(GPIOC,9,ARD_LOW);}
    
    if(Serial.available()){
    //be sure to Serial_begin with the port that you intend to listen on
   input = Serial.read();
    }
    if(input=='B'){
    Serial.println("HELLO");
    Serial.println(1656,ARD_DEC);
    Serial.println("bye");
    }
    digitalWrite(GPIOC,8,ARD_HIGH);
#if SIMULATOR
    delay(50);
#endif
    digitalWrite(GPIOC,8,ARD_LOW);
    #if SIMULATOR
    delay(50);
#endif
    
    for(int i=0;i<4094;i++){Dac.out(i);delay(2);}
    
  
  }
}





#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif



