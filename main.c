/*************************************************************************
 *
 *    Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2012
 *
 *    File name   : main.c
 *    Description : Define main module
 *
 *    History :
 *    1. Date        : 28, February 2012
 *       Author      : Stanimir Bonev
 *       Description : Create
 *
 *  This example project shows how to use the IAR Embedded Workbench for ARM
 * to develop code for the IAR-STM32F051R8-SK evaluation board. It shows
 * basic use of I/O, timer and the interrupt controllers.
 *  Displays running lights on the board LED's.
 *
 *    $Revision: 103 $
 **************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "arm_comm.h"
#include "main.h"
#include <stdarg.h>
static __IO uint32_t TimingDelay;

void DelayResolution100us(Int32U Delay)
{
  for(volatile int i = 500; i;i--);
}
#include <Arduino.h>


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
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 100);

  /* Initialize LEDs, Key Button, LCD and COM port(USART) available on
     STM320518-EVAL board *****************************************************/
  pinMode(GPIOC,6,ARD_OUTPUT);
  pinMode(GPIOC,7,ARD_OUTPUT);
  pinMode(GPIOC,8,ARD_OUTPUT);
  pinMode(GPIOC,9,ARD_OUTPUT);
  LEDInit(LED1);
  LEDInit(LED2);
  LEDInit(LED3);
  LEDInit(LED4);

  while(1)
  {
    digitalWrite(GPIOC,6,ARD_HIGH);
    /* Toggle LD1 */
    LEDToggle(LED1);
    /* Insert 50 ms delay */
    Delay(10);
    digitalWrite(GPIOC,6,ARD_LOW);
    /* Toggle LD1 */
    LEDToggle(LED1);
    Delay(10);
  }
}

void Delay(__IO uint32_t nTime)
{
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

/**
  * @}
  */


/******************* (C) COPYRIGHT 2012 STMicroelectronics *****END OF FILE****/
