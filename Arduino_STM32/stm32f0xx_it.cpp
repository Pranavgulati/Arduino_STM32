/**
  ******************************************************************************
  * @file    Project/STM32F0xx_StdPeriph_Template/stm32f0xx_it.c
  * @author  MCD Application Team
  * @version V1.0.0RC1
  * @date    27-January-2012
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * FOR MORE INFORMATION PLEASE READ CAREFULLY THE LICENSE AGREEMENT FILE
  * LOCATED IN THE ROOT DIRECTORY OF THIS FIRMWARE PACKAGE.
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_it.h"
#include <main.h>
#include <Arduino.h>


/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  TimingDelay_Decrement();
}

/******************************************************************************/
/*                 STM32F0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f0xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/
void USART1_IRQHandler(void){
  
  if(USART_GetITStatus(Serial.USART, USART_IT_RXNE) != RESET ){
    USART_ClearFlag(Serial.USART,USART_IT_RXNE);
    //RXNE flag is cleared when the buffer is read so no clear reqd.
  uint16_t d = 0;
    //disable other interrupts for the time being or mayb stm32 does it itself
    d=(uint16_t)(Serial.USART->RDR & (uint16_t)0x01FF);;
    // if buffer full, set the overflow flag and return
    uint8_t next = (Serial.recvBuf_tail + 1) % RX_BUF_LEN;
    if (next != Serial.recvBuf_head)
    {
      // save new data in buffer: tail points to where byte goes
      Serial.recvBuf[Serial.recvBuf_tail] = (uint8_t)d; // save new byte
      Serial.recvBuf_tail= next;
    } 
    else 
    {
      //buffer overflow happened but circular buffer so we can let it pass
      //_buffer_overflow = true;
    }
  
  }
 if(USART_GetITStatus(Serial.USART, USART_IT_TXE) != RESET){
    //TC flag to be cleared     
    USART_ClearFlag(Serial.USART,USART_FLAG_TC);
    USART_ClearITPendingBit(Serial.USART,  USART_IT_TXE);
    if (Serial.txBuf_head == Serial.txBuf_tail){ USART_ITConfig(Serial.USART,USART_IT_TXE,DISABLE);return ;}
    else{
      unsigned char c = Serial.txBuf[Serial.txBuf_head];
      Serial.txBuf_head = (Serial.txBuf_head + 1) % TX_BUF_LEN;  
      USART_SendData(Serial.USART,c);       
    }      
 }

}


void ADC1_COMP_IRQHandler(void){
extern int *__ADC_data;
*__ADC_data= ADC_GetConversionValue(ADC1);
ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
}

  extern TIM_TypeDef * __ICtimerName;
  extern unsigned int __risingChannelNo;
  extern unsigned int __fallingChannelNo;
  extern unsigned int *__freqPointer;
  extern unsigned int *__dutyPointer;
  extern unsigned int __ICdone;
  unsigned long long totalDutyCount=0;
  unsigned long long totalFreqCount=0;
  unsigned int updateCounter=0;
  
extern "C"{
void TIM2_IRQHandler(void){
  if(TIM_GetITStatus(__ICtimerName,TIM_IT_Update)){
      TIM_ClearITPendingBit(__ICtimerName, TIM_IT_Update);
    updateCounter++;
  //do not alter the above variable anywhere in the following code
  //add update event related code here  
  }  
   if(TIM_GetITStatus(__ICtimerName,1<<__risingChannelNo)){
      TIM_ClearITPendingBit(__ICtimerName, 1<<__risingChannelNo);
      unsigned int offset=(((__risingChannelNo-1)*0x04)+0x34);
      uint16_t *CCRrisePointer=( uint16_t*)__ICtimerName;
      offset=offset/2;
      while(offset){CCRrisePointer++;offset--;}
  totalFreqCount= (updateCounter*0xFFFF)+ *CCRrisePointer;
    //set the counter to 0 at rising edge
    TIM_SetCounter(__ICtimerName,0x0000);
  }
    
  if(TIM_GetITStatus(__ICtimerName,1<<__fallingChannelNo)){
  TIM_ClearITPendingBit(__ICtimerName, 1<<__fallingChannelNo);
        unsigned int offset=(((__fallingChannelNo-1)*0x04)+0x34);
      uint16_t *CCRfallPointer=( uint16_t*)__ICtimerName;
      offset=offset/2;
      while(offset){CCRfallPointer++;offset--;}

    //reading the correct CCR register automatically
     totalDutyCount =(updateCounter*0xFFFF)+ *CCRfallPointer;
  //the total count now contains the width of the high pulse
  
  }
  if(totalFreqCount){
    *__dutyPointer = (totalDutyCount * 100) / totalFreqCount;
    *__freqPointer = SystemCoreClock / totalFreqCount;
    updateCounter=0;
    __ICdone++;
  }

}


void TIM1_BRK_UP_TRG_COM_IRQHandler(void){
TIM2_IRQHandler();
}
void TIM1_CC_IRQHandler(void){
TIM2_IRQHandler();
}


void TIM3_IRQHandler(void){
  TIM2_IRQHandler();

}

void TIM15_IRQHandler(void){
TIM2_IRQHandler();
}

}
/******************* (C) COPYRIGHT 2012 STMicroelectronics *****END OF FILE****/
