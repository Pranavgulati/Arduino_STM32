
#include <arm_comm.h>
#include <main.h>
#include <Arduino.h>
#include <ardGPIO.h>
#include <ardUSART.h>
#include <ardADC.h>

static __IO uint32_t TimingDelay;

void delayResolution100us(Int32U delay)
{
  for(volatile int i = 500; i;i--);
}

void delay(__IO uint32_t nTime)
{
  TimingDelay = nTime;
  while(TimingDelay != 0);
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
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 10);

  /* Initialize LEDs, Key Button, LCD and COM port(USART) available on
     STM320518-EVAL board *****************************************************/
  
  pinMode(GPIOC,8,ARD_OUTPUT);
  pinMode(GPIOC,9,ARD_OUTPUT);
  pinMode(GPIOA,4,ARD_INPUT);
  pinMode(GPIOB,4,ARD_INPUT);
  pinMode(GPIOC,4,ARD_INPUT);
  pinMode(GPIOA,5,ARD_INPUT);
  //PA10:PA9::RX:TX
  Serial.begin(COM1,115200);
  digitalWrite(GPIOC,8,ARD_HIGH);
  
  while(1)
  {
    int a =analogRead(GPIOC,8);
    int temp=0;
    analogRead(GPIOC,8,&temp);
    uint16_t  input=0;
    if(digitalRead(GPIOA,4)!=0){digitalWrite(GPIOC,8,ARD_HIGH);}
    else{digitalWrite(GPIOC,8,ARD_LOW);}
    if(digitalRead(GPIOA,5)!=0){digitalWrite(GPIOC,9,ARD_HIGH);}
    else{digitalWrite(GPIOC,9,ARD_LOW);}
    
    //Serial.println("HELLO");
    Serial.print(1656,ARD_DEC);
    delay(10);
    if(Serial.available()){
    //be sure to Serial_begin with the port that you intend to listen on
   input = Serial.read();
    }
    if(input=='B'){
    digitalWrite(GPIOC,8,ARD_HIGH);
    delay(10);
    digitalWrite(GPIOC,8,ARD_LOW);
    delay(10);
    }
    delay(1);
  }
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



