/*************************************************************************
 *
 *    Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2012
 *
 *    File name   : stm320Fxx_ksk.h
 *    Description : board configuration
 *
 *    History :
 *    1. Date        : 14, February 2012
 *       Author      : Stanimir Bonev
 *       Description : Create
 *
 *
 *    $Revision: 103 $
 **************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM320FXX_KSK_H
#define __STM320FXX_KSK_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"

#if !defined (USE_IAR_STM32F0XX_KSK)
 #define USE_IAR_STM32F0XX_KSK
#endif

typedef enum
{
  LED1 = 0,
  LED2 = 1,
  LED3 = 2,
  LED4 = 3
} Led_TypeDef;

typedef enum
{
  BUTTON_USR1 = 0,
  BUTTON_USR2 = 1,
} Button_TypeDef;

typedef enum
{
  BUTTON_MODE_GPIO = 0,
  BUTTON_MODE_EXTI = 1
} ButtonMode_TypeDef;

typedef enum
{
  CBUTTON_1 = 1,
  CBUTTON_2 = 2,
  CBUTTON_3 = 4,
  CBUTTON_4 = 8,
  CBUTTON_5 = 16,
  CBUTTON_6 = 32,
} CButton_TypeDef;

typedef enum
{
  COM1 = 0,
  COM2 = 1
} COM_TypeDef;

typedef enum
{
	PWR_OFF = 0, PWR_ON
} PWR_CtrlDef;

#if !defined (USE_STM32FXX_KSK)
 #define USE_STM32FXX_KSK
#endif

#define LEDn                             	4
                                         	
#define LED1_PIN                         	GPIO_Pin_6
#define LED1_GPIO_PORT                   	GPIOC
#define LED1_GPIO_CLK                    	RCC_AHBPeriph_GPIOC
                                         	
#define LED2_PIN                         	GPIO_Pin_7
#define LED2_GPIO_PORT                   	GPIOC
#define LED2_GPIO_CLK                    	RCC_AHBPeriph_GPIOC
                                         	
#define LED3_PIN                         	GPIO_Pin_8
#define LED3_GPIO_PORT                   	GPIOC
#define LED3_GPIO_CLK                    	RCC_AHBPeriph_GPIOC
                                         	
#define LED4_PIN                         	GPIO_Pin_9
#define LED4_GPIO_PORT                   	GPIOC
#define LED4_GPIO_CLK                    	RCC_AHBPeriph_GPIOC
                                         	
#define BUTTONn                          	2
                                         	
#define USR1_BUTTON_PIN                	 	GPIO_Pin_0
#define USR1_BUTTON_GPIO_PORT            	GPIOA
#define USR1_BUTTON_GPIO_CLK             	RCC_AHBPeriph_GPIOA
#define USR1_BUTTON_EXTI_LINE            	EXTI_Line0
#define USR1_BUTTON_EXTI_PORT_SOURCE     	EXTI_PortSourceGPIOA
#define USR1_BUTTON_EXTI_PIN_SOURCE      	EXTI_PinSource0
#define USR1_BUTTON_EXTI_IRQn          	 	EXTI0_1_IRQn
                                         	
#define USR2_BUTTON_PIN                	 	GPIO_Pin_13
#define USR2_BUTTON_GPIO_PORT            	GPIOC
#define USR2_BUTTON_GPIO_CLK             	RCC_AHBPeriph_GPIOC
#define USR2_BUTTON_EXTI_LINE            	EXTI_Line13
#define USR2_BUTTON_EXTI_PORT_SOURCE     	EXTI_PortSourceGPIOC
#define USR2_BUTTON_EXTI_PIN_SOURCE      	EXTI_PinSource13
#define USR2_BUTTON_EXTI_IRQn          	 	EXTI4_15_IRQn
                                         	
#define COMn                             	2
#define RS232_COM1                       	USART1
#define RS232_COM1_CLK                   	RCC_APB2Periph_USART1
                                         	
#define RS232_COM1_TX_PIN                	GPIO_Pin_9
#define RS232_COM1_TX_GPIO_PORT          	GPIOA
#define RS232_COM1_TX_GPIO_CLK           	RCC_AHBPeriph_GPIOA
#define RS232_COM1_TX_SOURCE             	GPIO_PinSource9
#define RS232_COM1_TX_AF                 	GPIO_AF_1
                                         	
#define RS232_COM1_RX_PIN                	GPIO_Pin_10
#define RS232_COM1_RX_GPIO_PORT          	GPIOA
#define RS232_COM1_RX_GPIO_CLK           	RCC_AHBPeriph_GPIOA
#define RS232_COM1_RX_SOURCE             	GPIO_PinSource10
#define RS232_COM1_RX_AF                 	GPIO_AF_1
                                         	
#define RS232_COM1_CTS_PIN               	GPIO_Pin_11
#define RS232_COM1_CTS_GPIO_PORT         	GPIOA
#define RS232_COM1_CTS_GPIO_CLK          	RCC_AHBPeriph_GPIOA
#define RS232_COM1_CTS_SOURCE            	GPIO_PinSource11
#define RS232_COM1_CTS_AF                	GPIO_AF_1
                                         	
#define RS232_COM1_RTS_PIN               	GPIO_Pin_12
#define RS232_COM1_RTS_GPIO_PORT         	GPIOA
#define RS232_COM1_RTS_GPIO_CLK          	RCC_AHBPeriph_GPIOA
#define RS232_COM1_RTS_SOURCE            	GPIO_PinSource12
#define RS232_COM1_RTS_AF                	GPIO_AF_1
                                         	
#define RS232_COM1_IRQn                  	USART1_IRQn
                                         	
#define UXT_COM2                         	USART2
#define UXT_COM2_CLK                     	RCC_APB1Periph_USART2
                                         	
#define UXT_COM2_TX_PIN                  	GPIO_Pin_2
#define UXT_COM2_TX_GPIO_PORT            	GPIOA
#define UXT_COM2_TX_GPIO_CLK             	RCC_AHBPeriph_GPIOA
#define UXT_COM2_TX_SOURCE               	GPIO_PinSource2
#define UXT_COM2_TX_AF                   	GPIO_AF_1
                                         	
#define UXT_COM2_RX_PIN                  	GPIO_Pin_3
#define UXT_COM2_RX_GPIO_PORT            	GPIOA
#define UXT_COM2_RX_GPIO_CLK             	RCC_AHBPeriph_GPIOA
#define UXT_COM2_RX_SOURCE               	GPIO_PinSource3
#define UXT_COM2_RX_AF                   	GPIO_AF_1
                                         	
#define UXT_COM2_IRQn                    	USART2_IRQn
                                         	
#define UXT_SPI                          	SPI1
#define UXT_SPI_CLK                      	RCC_APB2Periph_SPI1
                                         	
#define UXT_SPI_SCK_PIN                  	GPIO_Pin_13                 /* PB.13 */
#define UXT_SPI_SCK_GPIO_PORT            	GPIOB                       /* GPIOB */
#define UXT_SPI_SCK_GPIO_CLK             	RCC_AHBPeriph_GPIOB
#define UXT_SPI_SCK_SOURCE               	GPIO_PinSource13
#define UXT_SPI_SCK_AF                   	GPIO_AF_0
                                         	
#define UXT_SPI_MISO_PIN                 	GPIO_Pin_14                 /* PB.14 */
#define UXT_SPI_MISO_GPIO_PORT           	GPIOB                       /* GPIOB */
#define UXT_SPI_MISO_GPIO_CLK            	RCC_AHBPeriph_GPIOB
#define UXT_SPI_MISO_SOURCE              	GPIO_PinSource14
#define UXT_SPI_MISO_AF                  	GPIO_AF_0
                                         	
#define UXT_SPI_MOSI_PIN                 	GPIO_Pin_15                 /* PB.15 */
#define UXT_SPI_MOSI_GPIO_PORT           	GPIOB                       /* GPIOB */
#define UXT_SPI_MOSI_GPIO_CLK            	RCC_AHBPeriph_GPIOB
#define UXT_SPI_MOSI_SOURCE              	GPIO_PinSource15
#define UXT_SPI_MOSI_AF                  	GPIO_AF_0
                                         	
#define UXT_CS_PIN                       	GPIO_Pin_12                 /* PB.12 */
#define UXT_CS_GPIO_PORT                 	GPIOB                       /* GPIOB */
#define UXT_CS_GPIO_CLK                  	RCC_AHBPeriph_GPIOB
                                         	
#define ACC_I2C                          	I2C2
#define ACC_I2C_CLK                      	RCC_APB1Periph_I2C2
                                         	
#define ACC_I2C_SCL_PIN                  	GPIO_Pin_10                 /* PB.10 */
#define ACC_I2C_SCL_GPIO_PORT            	GPIOB                       /* GPIOB */
#define ACC_I2C_SCL_GPIO_CLK             	RCC_AHBPeriph_GPIOB
#define ACC_I2C_SCL_SOURCE               	GPIO_PinSource10
#define ACC_I2C_SCL_AF                   	GPIO_AF_1
                                         	
#define ACC_I2C_SDA_PIN                  	GPIO_Pin_11                 /* PB.11 */
#define ACC_I2C_SDA_GPIO_PORT            	GPIOB                       /* GPIOB */
#define ACC_I2C_SDA_GPIO_CLK             	RCC_AHBPeriph_GPIOB
#define ACC_I2C_SDA_SOURCE               	GPIO_PinSource11
#define ACC_I2C_SDA_AF                   	GPIO_AF_1
                                         	
#define ACC_INT_PIN          						 	GPIO_Pin_4                  /* PC.04 */
#define ACC_INT_GPIO_PORT    						 	GPIOC                       /* GPIOC */
#define ACC_INT_GPIO_CLK     						 	RCC_AHBPeriph_GPIOC
#define ACC_INT_EXTI_LINE            			EXTI_Line4
#define ACC_INT_EXTI_PORT_SOURCE     			EXTI_PortSourceGPIOC
#define ACC_INT_EXTI_PIN_SOURCE      			EXTI_PinSource4
#define ACC_INT_EXTI_IRQn          	 			EXTI4_15_IRQn
                                         	
#define UXT_I2C                          	I2C2
#define UXT_I2C_CLK                      	RCC_APB1Periph_I2C2
                                         	
#define UXT_I2C_SCL_PIN                  	GPIO_Pin_10                 /* PB.10 */
#define UXT_I2C_SCL_GPIO_PORT            	GPIOB                       /* GPIOB */
#define UXT_I2C_SCL_GPIO_CLK             	RCC_AHBPeriph_GPIOB
#define UXT_I2C_SCL_SOURCE               	GPIO_PinSource10
#define UXT_I2C_SCL_AF                   	GPIO_AF_1
                                         	
#define UXT_I2C_SDA_PIN                  	GPIO_Pin_11                 /* PB.11 */
#define UXT_I2C_SDA_GPIO_PORT            	GPIOB                       /* GPIOB */
#define UXT_I2C_SDA_GPIO_CLK             	RCC_AHBPeriph_GPIOB
#define UXT_I2C_SDA_SOURCE               	GPIO_PinSource11
#define UXT_I2C_SDA_AF                   	GPIO_AF_1
                                         	
#define UXT_PWR_PIN                      	GPIO_Pin_3                  /* PC.03 */
#define UXT_PWR_GPIO_PORT                	GPIOC                       /* GPIOC */
#define UXT_PWR_GPIO_CLK                 	RCC_AHBPeriph_GPIOC
                                         	
#define CEC_I2C                          	I2C1
#define CEC_I2C_CLK                      	RCC_APB1Periph_I2C1
                                         	
#define CEC_I2C_SCL_PIN                  	GPIO_Pin_6                  /* PB.06 */
#define CEC_I2C_SCL_GPIO_PORT            	GPIOB                       /* GPIOB */
#define CEC_I2C_SCL_GPIO_CLK             	RCC_AHBPeriph_GPIOB
#define CEC_I2C_SCL_SOURCE               	GPIO_PinSource6
#define CEC_I2C_SCL_AF                   	GPIO_AF_1
                                         	
#define CEC_I2C_SDA_PIN                  	GPIO_Pin_7                  /* PB.07 */
#define CEC_I2C_SDA_GPIO_PORT            	GPIOB                       /* GPIOB */
#define CEC_I2C_SDA_GPIO_CLK             	RCC_AHBPeriph_GPIOB
#define CEC_I2C_SDA_SOURCE               	GPIO_PinSource7
#define CEC_I2C_SDA_AF                   	GPIO_AF_1

#define CAP_B1_PIN                  		 	GPIO_Pin_0                  /* PB.0 */
#define CAP_B1_GPIO_PORT            			GPIOB                       /* GPIOB */
#define CAP_B1_GPIO_CLK             			RCC_AHBPeriph_GPIOB

#define CAP_B2_PIN                  		 	GPIO_Pin_1                  /* PB.1 */
#define CAP_B2_GPIO_PORT            			GPIOB                       /* GPIOB */
#define CAP_B2_GPIO_CLK             			RCC_AHBPeriph_GPIOB

#define CAP_B3_PIN                  		 	GPIO_Pin_2                  /* PB.2 */
#define CAP_B3_GPIO_PORT            			GPIOB                       /* GPIOB */
#define CAP_B3_GPIO_CLK             			RCC_AHBPeriph_GPIOB

#define CAP_REF3_PIN                  		GPIO_Pin_3                  /* PB.3 */
#define CAP_REF3_GPIO_PORT            		GPIOB                       /* GPIOB */
#define CAP_REF3_GPIO_CLK             		RCC_AHBPeriph_GPIOB

#define CAP_B4_PIN                  		 	GPIO_Pin_4                  /* PB.4 */
#define CAP_B4_GPIO_PORT            			GPIOB                       /* GPIOB */
#define CAP_B4_GPIO_CLK             			RCC_AHBPeriph_GPIOB

#define CAP_B5_PIN                  		 	GPIO_Pin_6                  /* PB.6 */
#define CAP_B5_GPIO_PORT            			GPIOB                       /* GPIOB */
#define CAP_B5_GPIO_CLK             			RCC_AHBPeriph_GPIOB
#define CAP_B5_SOURCE               			GPIO_PinSource6
#define CAP_B5_AF                   		 	GPIO_AF_3

#define CAP_B6_PIN                  		 	GPIO_Pin_7                  /* PB.7 */
#define CAP_B6_GPIO_PORT            			GPIOB                       /* GPIOB */
#define CAP_B6_GPIO_CLK             			RCC_AHBPeriph_GPIOB
#define CAP_B6_SOURCE               			GPIO_PinSource7
#define CAP_B6_AF                   		 	GPIO_AF_3

#define CAP_REF2_PIN                  		GPIO_Pin_5                  /* PB.5 */
#define CAP_REF2_GPIO_PORT            		GPIOC                       /* GPIOB */
#define CAP_REF2_GPIO_CLK             		RCC_AHBPeriph_GPIOC
#define CAP_REF2_SOURCE               		GPIO_PinSource5
#define CAP_REF2_AF                   		GPIO_AF_3

// DAC
#define DAC_CLK                      			RCC_APB1Periph_DAC

#define AUDIO_OUT_PIN                  		GPIO_Pin_4                  /* PA.4 */
#define AUDIO_OUT_GPIO_PORT            		GPIOA                       /* GPIOA */
#define AUDIO_OUT_GPIO_CLK             		RCC_AHBPeriph_GPIOA

// ADC

#define TRIM_ADC													ADC1
#define TRIM_PIN                  				GPIO_Pin_0                  /* PC.0 */
#define TRIM_GPIO_PORT            				GPIOC                       /* GPIOC */
#define TRIM_GPIO_CLK             				RCC_AHBPeriph_GPIOC
#define TRIM_ADC_CHANNEL									ADC_Channel_10
#define TRIM_ADC_CLK                      RCC_APB2Periph_ADC1

#define DIST_ADC													ADC1
#define DIST_PIN                  				GPIO_Pin_1                  /* PC.1 */
#define DIST_GPIO_PORT            				GPIOC                       /* GPIOC */
#define DIST_GPIO_CLK             				RCC_AHBPeriph_GPIOC
#define DIST_ADC_CHANNEL									ADC_Channel_11
#define DIST_ADC_CLK                      RCC_APB2Periph_ADC1

#define LIGHT_ADC													ADC1
#define LIGHT_PIN                  				GPIO_Pin_2                  /* PC.2 */
#define LIGHT_GPIO_PORT            				GPIOC                       /* GPIOC */
#define LIGHT_GPIO_CLK             				RCC_AHBPeriph_GPIOC
#define LIGHT_ADC_CHANNEL									ADC_Channel_12
#define LIGHT_ADC_CLK                     RCC_APB2Periph_ADC1

#define LIGHT_PWR_PIN                     GPIO_Pin_2                 	/* PD.2 */
#define LIGHT_PWR_GPIO_PORT              	GPIOD                       /* GPIOD */
#define LIGHT_PWR_GPIO_CLK               	RCC_AHBPeriph_GPIOD
                                         	

void LEDInit(Led_TypeDef Led);
void LEDOn(Led_TypeDef Led);
void LEDOff(Led_TypeDef Led);
void LEDToggle(Led_TypeDef Led);
void PBInit(Button_TypeDef Button, ButtonMode_TypeDef Button_Mode);
uint32_t PBGetState(Button_TypeDef Button);
void COMInit(COM_TypeDef COM, USART_InitTypeDef* USART_InitStruct);
void Acc_LowLevel_Init(void);
void UXT_I2C_LowLevel_Init(void);
void UXT_SPI_LowLevel_Init(void);
void CEC_I2C_LowLevel_Init(void);
void UXT_PWR_Init(void);
void UXT_PWR_Ctrl(PWR_CtrlDef Pwr);
void AudioOut_Init(void);
void Trim_Init(void);
void Dist_Init(void);
void Light_Init(void);
void Light_Ctrl(PWR_CtrlDef Pwr);
uint32_t CB_Calibrate(void);
uint32_t CB_Init(void);
void CB_Handler(void);
uint32_t CB_GetState(void);
uint32_t CB_GetStatus(void);


#ifdef __cplusplus
}
#endif

#endif /* __STM32Fxx_KSK_H */
