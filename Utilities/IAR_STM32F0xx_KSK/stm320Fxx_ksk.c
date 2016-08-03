/*************************************************************************
 *
 *    Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2012
 *
 *    File name   : stm320Fxx_ksk.c
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
#include <string.h>
#include "stm320Fxx_ksk.h"

static uint32_t CP_CalCntr = 0;
static uint32_t CP_Index = 0;
static uint32_t CB_Cal_Count[6];
static volatile uint32_t CB_Res = 0;
static volatile uint32_t CP_Error = 0;

#define CP_THRESHOLD_LEVEL  3000

GPIO_TypeDef* GPIO_PORT[LEDn] = {LED1_GPIO_PORT, LED2_GPIO_PORT, LED3_GPIO_PORT,
                                 LED4_GPIO_PORT};
const uint16_t GPIO_PIN[LEDn] = {LED1_PIN, LED2_PIN, LED3_PIN,
                                 LED4_PIN};
const uint32_t GPIO_CLK[LEDn] = {LED1_GPIO_CLK, LED2_GPIO_CLK, LED3_GPIO_CLK,
                                 LED4_GPIO_CLK};

GPIO_TypeDef* BUTTON_PORT[BUTTONn] = {USR1_BUTTON_GPIO_PORT, USR2_BUTTON_GPIO_PORT};

const uint16_t BUTTON_PIN[BUTTONn] = {USR1_BUTTON_PIN, USR2_BUTTON_PIN};

const uint32_t BUTTON_CLK[BUTTONn] = {USR1_BUTTON_GPIO_CLK, USR2_BUTTON_GPIO_CLK};

const uint16_t BUTTON_EXTI_LINE[BUTTONn] = {USR1_BUTTON_EXTI_LINE,
                                            USR2_BUTTON_EXTI_LINE
																						};

const uint16_t BUTTON_PORT_SOURCE[BUTTONn] = {USR1_BUTTON_EXTI_PORT_SOURCE,
                                              USR2_BUTTON_EXTI_PORT_SOURCE
                                             };
								
const uint16_t BUTTON_PIN_SOURCE[BUTTONn] = {USR1_BUTTON_EXTI_PIN_SOURCE,
                                             USR2_BUTTON_EXTI_PIN_SOURCE
                                            };

const uint16_t BUTTON_IRQn[BUTTONn] = {USR1_BUTTON_EXTI_IRQn, USR2_BUTTON_EXTI_IRQn};

USART_TypeDef* COM_USART[COMn] = {RS232_COM1, UXT_COM2};

const uint32_t COM_USART_CLK[COMn] = {RS232_COM1_CLK, UXT_COM2_CLK};

GPIO_TypeDef* COM_TX_PORT[COMn] = {RS232_COM1_TX_GPIO_PORT, UXT_COM2_TX_GPIO_PORT};

GPIO_TypeDef* COM_RX_PORT[COMn] = {RS232_COM1_RX_GPIO_PORT, UXT_COM2_RX_GPIO_PORT};

const uint32_t COM_TX_PORT_CLK[COMn] = {RS232_COM1_TX_GPIO_CLK, UXT_COM2_TX_GPIO_CLK};

const uint32_t COM_RX_PORT_CLK[COMn] = {RS232_COM1_RX_GPIO_CLK, UXT_COM2_RX_GPIO_CLK};

const uint16_t COM_TX_PIN[COMn] = {RS232_COM1_TX_PIN, UXT_COM2_TX_PIN};

const uint16_t COM_RX_PIN[COMn] = {RS232_COM1_RX_PIN, UXT_COM2_RX_PIN};

const uint16_t COM_TX_PIN_SOURCE[COMn] = {RS232_COM1_TX_SOURCE, UXT_COM2_TX_SOURCE};

const uint16_t COM_RX_PIN_SOURCE[COMn] = {RS232_COM1_RX_SOURCE, UXT_COM2_RX_SOURCE};

const uint16_t COM_TX_AF[COMn] = {RS232_COM1_TX_AF, UXT_COM2_TX_AF};

const uint16_t COM_RX_AF[COMn] = {RS232_COM1_RX_AF, UXT_COM2_RX_AF};

const uint8_t COM_FLOW_CTRL[COMn] = {1, 0};

GPIO_TypeDef* COM_CTS_PORT[COMn] = {RS232_COM1_CTS_GPIO_PORT};

const uint32_t COM_CTS_PORT_CLK[COMn] = {RS232_COM1_CTS_GPIO_CLK};

const uint16_t COM_CTS_PIN[COMn] = {RS232_COM1_CTS_PIN};

const uint16_t COM_CTS_PIN_SOURCE[COMn] = {RS232_COM1_CTS_SOURCE};

const uint16_t COM_CTS_AF[COMn] = {RS232_COM1_CTS_AF};

GPIO_TypeDef* COM_RTS_PORT[COMn] = {RS232_COM1_RTS_GPIO_PORT};

const uint32_t COM_RTS_PORT_CLK[COMn] = {RS232_COM1_RTS_GPIO_CLK};

const uint16_t COM_RTS_PIN[COMn] = {RS232_COM1_RTS_PIN};

const uint16_t COM_RTS_PIN_SOURCE[COMn] = {RS232_COM1_RTS_SOURCE};

const uint16_t COM_RTS_AF[COMn] = {RS232_COM1_RTS_AF};

/**
  * @brief  Configures LED GPIO.
  * @param  Led: Specifies the Led to be configured.
  *   This parameter can be one of following parameters:
  *     @arg LED1
  *     @arg LED2
  *     @arg LED3
  *     @arg LED4
  * @retval None
  */
void LEDInit(Led_TypeDef Led)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  /* Enable the GPIO_LED Clock */
  RCC_AHBPeriphClockCmd(GPIO_CLK[Led], ENABLE);

  /* Configure the GPIO_LED pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN[Led];
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIO_PORT[Led], &GPIO_InitStructure);
  GPIO_PORT[Led]->BSRR = GPIO_PIN[Led];
}

/**
  * @brief  Turns selected LED On.
  * @param  Led: Specifies the Led to be set on.
  *   This parameter can be one of following parameters:
  *     @arg LED1
  *     @arg LED2
  *     @arg LED3
  *     @arg LED4
  * @retval None
  */
void LEDOn(Led_TypeDef Led)
{
  GPIO_PORT[Led]->BRR = GPIO_PIN[Led];
}

/**
  * @brief  Turns selected LED Off.
  * @param  Led: Specifies the Led to be set off.
  *   This parameter can be one of following parameters:
  *     @arg LED1
  *     @arg LED2
  *     @arg LED3
  *     @arg LED4
  * @retval None
  */
void LEDOff(Led_TypeDef Led)
{
  GPIO_PORT[Led]->BSRR = GPIO_PIN[Led];
}

/**
  * @brief  Toggles the selected LED.
  * @param  Led: Specifies the Led to be toggled.
  *   This parameter can be one of following parameters:
  *     @arg LED1
  *     @arg LED2
  *     @arg LED3
  *     @arg LED4
  * @retval None
  */
void LEDToggle(Led_TypeDef Led)
{
  GPIO_PORT[Led]->ODR ^= GPIO_PIN[Led];
}

/**
  * @brief  Configures Button GPIO and EXTI Line.
  * @param  Button: Specifies the Button to be configured.
  *   This parameter can be one of following parameters:
  *     @arg USR1_BUTTON: User Push Button 1
  *     @arg USR2_BUTTON: User Push Button 2
  * @param  Button_Mode: Specifies Button mode.
  *   This parameter can be one of following parameters:
  *     @arg BUTTON_MODE_GPIO: Button will be used as simple IO
  *     @arg BUTTON_MODE_EXTI: Button will be connected to EXTI line with interrupt
  *                     generation capability
  * @retval None
  */
void PBInit(Button_TypeDef Button, ButtonMode_TypeDef Button_Mode)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Enable the BUTTON Clock */
  RCC_AHBPeriphClockCmd(BUTTON_CLK[Button], ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

  /* Configure Button pin as input */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = BUTTON_PIN[Button];
  GPIO_Init(BUTTON_PORT[Button], &GPIO_InitStructure);

  if (Button_Mode == BUTTON_MODE_EXTI)
  {
    /* Connect Button EXTI Line to Button GPIO Pin */
    SYSCFG_EXTILineConfig(BUTTON_PORT_SOURCE[Button], BUTTON_PIN_SOURCE[Button]);

    /* Configure Button EXTI line */
    EXTI_InitStructure.EXTI_Line = BUTTON_EXTI_LINE[Button];
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    /* Enable and set Button EXTI Interrupt to the lowest priority */
    NVIC_InitStructure.NVIC_IRQChannel = BUTTON_IRQn[Button];
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0x03;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStructure);
  }
}

/**
  * @brief  Returns the selected Button state.
  * @param  Button: Specifies the Button to be checked.
  *   This parameter can be one of following parameters:
  *     @arg USR1_BUTTON: User Push Button 1
  *     @arg USR2_BUTTON: User Push Button 2
  * @retval The Button GPIO pin value.
  */
uint32_t PBGetState(Button_TypeDef Button)
{
  /* There is no Wakeup button on STM320518-EVAL. */
  return GPIO_ReadInputDataBit(BUTTON_PORT[Button], BUTTON_PIN[Button]);
}

/**
  * @brief  Configures COM port.
  * @param  COM: Specifies the COM port to be configured.
  *   This parameter can be one of following parameters:
  *     @arg COM1
  *     @arg COM2
  * @param  USART_InitStruct: pointer to a USART_InitTypeDef structure that
  *   contains the configuration information for the specified USART peripheral.
  * @retval None
  */
void COMInit(COM_TypeDef COM, USART_InitTypeDef* USART_InitStruct)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable GPIO clock */
  RCC_AHBPeriphClockCmd(COM_TX_PORT_CLK[COM] | COM_RX_PORT_CLK[COM], ENABLE);

  if(COM1 == COM)
  {
    /* Enable USART clock */
    RCC_APB2PeriphClockCmd(COM_USART_CLK[COM], ENABLE);
  }
  else
  {
    /* Enable USART clock */
    RCC_APB1PeriphClockCmd(COM_USART_CLK[COM], ENABLE);
  }

	if(COM_FLOW_CTRL[COM])
	{
	  RCC_AHBPeriphClockCmd(COM_CTS_PORT_CLK[COM] | COM_RTS_PORT_CLK[COM], ENABLE);
	  /* Connect PXx to USARTx_CTS */
	  GPIO_PinAFConfig(COM_CTS_PORT[COM], COM_CTS_PIN_SOURCE[COM], COM_CTS_AF[COM]);
	  /* Connect PXx to USARTx_RTS */
	  GPIO_PinAFConfig(COM_RTS_PORT[COM], COM_RTS_PIN_SOURCE[COM], COM_RTS_AF[COM]);		

	  /* Configure USART CTS as alternate function push-pull */
	  GPIO_InitStructure.GPIO_Pin = COM_CTS_PIN[COM];
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	  GPIO_Init(COM_TX_PORT[COM], &GPIO_InitStructure);
	
	  /* Configure USART RTS as alternate function push-pull */
	  GPIO_InitStructure.GPIO_Pin = COM_RTS_PIN[COM];
	  GPIO_Init(COM_RX_PORT[COM], &GPIO_InitStructure);
	
	}
	
  /* Connect PXx to USARTx_Tx */
  GPIO_PinAFConfig(COM_TX_PORT[COM], COM_TX_PIN_SOURCE[COM], COM_TX_AF[COM]);

  /* Connect PXx to USARTx_Rx */
  GPIO_PinAFConfig(COM_RX_PORT[COM], COM_RX_PIN_SOURCE[COM], COM_RX_AF[COM]);

  /* Configure USART Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = COM_TX_PIN[COM];
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(COM_TX_PORT[COM], &GPIO_InitStructure);

  /* Configure USART Rx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = COM_RX_PIN[COM];
  GPIO_Init(COM_RX_PORT[COM], &GPIO_InitStructure);

  /* USART configuration */
  USART_Init(COM_USART[COM], USART_InitStruct);

  /* Enable USART */
  USART_Cmd(COM_USART[COM], ENABLE);
}

/**
  * @brief  Initializes the ACC_I2C..
  * @param  None
  * @retval None
  */
void Acc_LowLevel_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  EXTI_InitTypeDef  EXTI_InitStructure;
  NVIC_InitTypeDef  NVIC_InitStructure;

  RCC_AHBPeriphClockCmd(ACC_INT_GPIO_CLK, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

  /*!< Configure ACC_INT pins: input */
  GPIO_InitStructure.GPIO_Pin = ACC_INT_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(ACC_INT_GPIO_PORT, &GPIO_InitStructure);

  SYSCFG_EXTILineConfig(ACC_INT_EXTI_PORT_SOURCE, ACC_INT_EXTI_PIN_SOURCE);

  /* Configure ACC INT line */
  EXTI_InitStructure.EXTI_Line = ACC_INT_EXTI_LINE;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  /* Enable and set Button EXTI Interrupt to the lowest priority */
  NVIC_InitStructure.NVIC_IRQChannel = ACC_INT_EXTI_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0x03;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

  NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief  Initializes the UXT_I2C..
  * @param  None
  * @retval None
  */
void UXT_I2C_LowLevel_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  /*!< UXT_I2C Periph clock enable */
  RCC_APB1PeriphClockCmd(UXT_I2C_CLK, ENABLE);

  /*!< UXT_I2C_SCL_GPIO_CLK, UXT_I2C_SDA_GPIO_CLK Periph clock enable */
  RCC_AHBPeriphClockCmd(UXT_I2C_SCL_GPIO_CLK | UXT_I2C_SDA_GPIO_CLK, ENABLE);

  /* Connect PXx to I2C_SCL */
  GPIO_PinAFConfig(UXT_I2C_SCL_GPIO_PORT, UXT_I2C_SCL_SOURCE, UXT_I2C_SCL_AF);

  /* Connect PXx to I2C_SDA */
  GPIO_PinAFConfig(UXT_I2C_SDA_GPIO_PORT, UXT_I2C_SDA_SOURCE, UXT_I2C_SDA_AF);

  /*!< Configure UXT_I2C pins: SCL */
  GPIO_InitStructure.GPIO_Pin = UXT_I2C_SCL_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(UXT_I2C_SCL_GPIO_PORT, &GPIO_InitStructure);

  /*!< Configure UXT_I2C pins: SDA */
  GPIO_InitStructure.GPIO_Pin = UXT_I2C_SDA_PIN;
  GPIO_Init(UXT_I2C_SDA_GPIO_PORT, &GPIO_InitStructure);
}

/**
  * @brief  Initializes the UXT SPI and put it into
  * @param  None
  * @retval None
  */
void UXT_SPI_LowLevel_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  SPI_InitTypeDef   SPI_InitStructure;

  /*!< UXT_SPI_CS_GPIO, UXT_SPI_MOSI_GPIO, UXT_SPI_MISO_GPIO,
       and UXT_SPI_SCK_GPIO Periph clock enable */
  RCC_AHBPeriphClockCmd(UXT_SPI_SCK_GPIO_CLK | UXT_SPI_MISO_GPIO_CLK | UXT_SPI_MOSI_GPIO_CLK |
                        UXT_CS_GPIO_CLK , ENABLE);

  /*!< UXT_SPI Periph clock enable */
  RCC_APB2PeriphClockCmd(UXT_SPI_CLK, ENABLE);

  /*!< Configure UXT_SPI pins: SCK */
  GPIO_InitStructure.GPIO_Pin = UXT_SPI_SCK_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_Init(UXT_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

  /*!< Configure UXT_SPI pins: MISO */
  GPIO_InitStructure.GPIO_Pin = UXT_SPI_MISO_PIN;
  GPIO_Init(UXT_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);

  /*!< Configure UXT_SPI pins: MOSI */
  GPIO_InitStructure.GPIO_Pin = UXT_SPI_MOSI_PIN;
  GPIO_Init(UXT_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

  /*!< Configure UXT_SPI_CS_PIN pin: UXT Card CS pin */
  GPIO_InitStructure.GPIO_Pin = UXT_CS_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(UXT_CS_GPIO_PORT, &GPIO_InitStructure);

  /* Connect PXx to UXT_SPI_SCK */
  GPIO_PinAFConfig(UXT_SPI_SCK_GPIO_PORT, UXT_SPI_SCK_SOURCE, UXT_SPI_SCK_AF);

  /* Connect PXx to UXT_SPI_MISO */
  GPIO_PinAFConfig(UXT_SPI_MISO_GPIO_PORT, UXT_SPI_MISO_SOURCE, UXT_SPI_MISO_AF);

  /* Connect PXx to UXT_SPI_MOSI */
  GPIO_PinAFConfig(UXT_SPI_MOSI_GPIO_PORT, UXT_SPI_MOSI_SOURCE, UXT_SPI_MOSI_AF);

  /*!< UXT_SPI Config */
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;

  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(UXT_SPI, &SPI_InitStructure);

  SPI_RxFIFOThresholdConfig(UXT_SPI, SPI_RxFIFOThreshold_QF);

  SPI_Cmd(UXT_SPI, ENABLE); /*!< UXT_SPI enable */
}

/**
  * @brief  Initializes the UXT PWR control
  * @param  None
  * @retval None
  */
void UXT_PWR_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  /* Enable the PWR Port Clock */
  RCC_AHBPeriphClockCmd(UXT_PWR_GPIO_CLK, ENABLE);

  /* Configure the PWR pin */
  GPIO_InitStructure.GPIO_Pin = UXT_PWR_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(UXT_PWR_GPIO_PORT, &GPIO_InitStructure);
  UXT_PWR_GPIO_PORT->BSRR = UXT_PWR_PIN;
}

/**
  * @brief  Enable/disable the UXT PWR
  * @param  Pwr
  * @retval None
  */
void UXT_PWR_Ctrl(PWR_CtrlDef Pwr)
{
	if(PWR_OFF == Pwr)
	{			
  	UXT_PWR_GPIO_PORT->BSRR = UXT_PWR_PIN;
	}
	else
	{			
  	UXT_PWR_GPIO_PORT->BRR = UXT_PWR_PIN;
	}
}

/**
  * @brief  Initializes the CEC_I2C..
  * @param  None
  * @retval None
  */
void CEC_I2C_LowLevel_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  /*!< CEC_I2C Periph clock enable */
  RCC_APB1PeriphClockCmd(CEC_I2C_CLK, ENABLE);

  /* Configure the I2C clock source. The clock is derived from the HSI */
  RCC_I2CCLKConfig(RCC_I2C1CLK_HSI);

  /*!< CEC_I2C_SCL_GPIO_CLK, CEC_I2C_SDA_GPIO_CLK Periph clock enable */
  RCC_AHBPeriphClockCmd(CEC_I2C_SCL_GPIO_CLK | CEC_I2C_SDA_GPIO_CLK, ENABLE);

  /* Connect PXx to I2C_SCL */
  GPIO_PinAFConfig(CEC_I2C_SCL_GPIO_PORT, CEC_I2C_SCL_SOURCE, CEC_I2C_SCL_AF);

  /* Connect PXx to I2C_SDA */
  GPIO_PinAFConfig(CEC_I2C_SDA_GPIO_PORT, CEC_I2C_SDA_SOURCE, CEC_I2C_SDA_AF);

  /*!< Configure CEC_I2C pins: SCL */
  GPIO_InitStructure.GPIO_Pin = CEC_I2C_SCL_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(CEC_I2C_SCL_GPIO_PORT, &GPIO_InitStructure);

  /*!< Configure CEC_I2C pins: SDA */
  GPIO_InitStructure.GPIO_Pin = CEC_I2C_SDA_PIN;
  GPIO_Init(CEC_I2C_SDA_GPIO_PORT, &GPIO_InitStructure);
}

/**
  * @brief  Initializes the DAT ...
  * @param  None
  * @retval None
  */
void AudioOut_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* DAC Periph clock enable */
  RCC_APB1PeriphClockCmd(DAC_CLK, ENABLE);

  /* GPIOA clock enable */
  RCC_AHBPeriphClockCmd(AUDIO_OUT_GPIO_CLK, ENABLE);

  /* Configure PA.04 (DAC_OUT1) as analog */
  GPIO_InitStructure.GPIO_Pin =  AUDIO_OUT_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(AUDIO_OUT_GPIO_PORT, &GPIO_InitStructure);

  DAC_DeInit();
}

/**
  * @brief  Initializes the ADC TRIM ...
  * @param  None
  * @retval None
  */
void Trim_Init(void)
{
ADC_InitTypeDef          ADC_InitStructure;
GPIO_InitTypeDef         GPIO_InitStructure;

  /* TRIM GPIO Periph clock enable */
  RCC_AHBPeriphClockCmd(TRIM_GPIO_CLK, ENABLE);

  /* TRIM ADC Periph clock enable */
  RCC_APB2PeriphClockCmd(TRIM_ADC_CLK, ENABLE);

  /* Configure TRIM as analog input */
  GPIO_InitStructure.GPIO_Pin = TRIM_PIN ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(TRIM_GPIO_PORT, &GPIO_InitStructure);

 	/* ADC DeInit */
  ADC_DeInit(TRIM_ADC);

  /* Initialize ADC structure */
  ADC_StructInit(&ADC_InitStructure);

  /* Configure the TRIM ADC in a 12 bits resolutuion */
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_ExternalTrigConv =  ADC_ExternalTrigConv_T1_TRGO;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
  ADC_Init(TRIM_ADC, &ADC_InitStructure);

  /* Convert the TRIM Channel with 239.5 Cycles as sampling time */
  ADC_ChannelConfig(TRIM_ADC, TRIM_ADC_CHANNEL, ADC_SampleTime_239_5Cycles);

  /* ADC Calibration */
  ADC_GetCalibrationFactor(TRIM_ADC);

  /* Enable ADCperipheral[PerIdx] */
  ADC_Cmd(TRIM_ADC, ENABLE);

  /* Wait the ADCEN falg */
  while(!ADC_GetFlagStatus(TRIM_ADC, ADC_FLAG_ADEN));
}

/**
  * @brief  Initializes the ADC Distance sensor ...
  * @param  None
  * @retval None
  */
void Dist_Init(void)
{
ADC_InitTypeDef          ADC_InitStructure;
GPIO_InitTypeDef         GPIO_InitStructure;

  /* DIST GPIO Periph clock enable */
  RCC_AHBPeriphClockCmd(DIST_GPIO_CLK, ENABLE);

  /* DIST ADC Periph clock enable */
  RCC_APB2PeriphClockCmd(DIST_ADC_CLK, ENABLE);

  /* Configure DIST as analog input */
  GPIO_InitStructure.GPIO_Pin = DIST_PIN ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(DIST_GPIO_PORT, &GPIO_InitStructure);

 	/* ADC DeInit */
  ADC_DeInit(DIST_ADC);

  /* Initialize ADC structure */
  ADC_StructInit(&ADC_InitStructure);

  /* Configure the TRIM ADC in a 12 bits resolutuion */
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_ExternalTrigConv =  ADC_ExternalTrigConv_T1_TRGO;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
  ADC_Init(DIST_ADC, &ADC_InitStructure);

  /* Convert the DIST Channel with 239.5 Cycles as sampling time */
  ADC_ChannelConfig(DIST_ADC, DIST_ADC_CHANNEL, ADC_SampleTime_239_5Cycles);

  /* ADC Calibration */
  ADC_GetCalibrationFactor(DIST_ADC);

  /* Enable ADCperipheral[PerIdx] */
  ADC_Cmd(DIST_ADC, ENABLE);

  /* Wait the ADCEN falg */
  while(!ADC_GetFlagStatus(DIST_ADC, ADC_FLAG_ADEN));
}

/**
  * @brief  Initializes the ADC Light sensor ...
  * @param  None
  * @retval None
  */
void Light_Init(void)
{
ADC_InitTypeDef          ADC_InitStructure;
GPIO_InitTypeDef         GPIO_InitStructure;

  /* LIGHT GPIO Periph clock enable */
  RCC_AHBPeriphClockCmd(LIGHT_GPIO_CLK | LIGHT_PWR_GPIO_CLK, ENABLE);

  /* LIGHT ADC Periph clock enable */
  RCC_APB2PeriphClockCmd(LIGHT_ADC_CLK, ENABLE);

  /* Configure LIGHT as analog input */
  GPIO_InitStructure.GPIO_Pin = LIGHT_PIN ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(LIGHT_GPIO_PORT, &GPIO_InitStructure);

  /* Configure LIGHT_PWR_PIN pin: Light sensor shutdown pin */
  GPIO_InitStructure.GPIO_Pin = LIGHT_PWR_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(LIGHT_PWR_GPIO_PORT, &GPIO_InitStructure);
  LIGHT_PWR_GPIO_PORT->BSRR = LIGHT_PWR_PIN;

	/* ADC DeInit */
  ADC_DeInit(LIGHT_ADC);

  /* Initialize ADC structure */
  ADC_StructInit(&ADC_InitStructure);

  /* Configure the LIGHT ADC in a 12 bits resolutuion */
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_ExternalTrigConv =  ADC_ExternalTrigConv_T1_TRGO;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
  ADC_Init(LIGHT_ADC, &ADC_InitStructure);

  /* Convert the LIGHT Channel with 239.5 Cycles as sampling time */
  ADC_ChannelConfig(LIGHT_ADC, LIGHT_ADC_CHANNEL, ADC_SampleTime_239_5Cycles);

  /* ADC Calibration */
  ADC_GetCalibrationFactor(LIGHT_ADC);

  /* Enable ADCperipheral[PerIdx] */
  ADC_Cmd(LIGHT_ADC, ENABLE);

  /* Wait the ADCEN falg */
  while(!ADC_GetFlagStatus(LIGHT_ADC, ADC_FLAG_ADEN));
}

/**
  * @brief  Light sensor power control ...
  * @param  Pwr
  * @retval None
  */
void Light_Ctrl(PWR_CtrlDef Pwr)
{
	if(PWR_OFF == Pwr)
	{			
  	LIGHT_PWR_GPIO_PORT->BSRR = LIGHT_PWR_PIN;
	}
	else
	{			
  	LIGHT_PWR_GPIO_PORT->BRR = LIGHT_PWR_PIN;
	}
}

/**
  * @brief  Touch sensing buttons calibration ...
  * @param  None
  * @retval uint32_t 0 - pass 1 - fault
  */
uint32_t CP_Calibrate(void)
{
  uint32_t status;
  CP_CalCntr = 0;
  memset(CB_Cal_Count,0,sizeof(CB_Cal_Count));
  CP_CalCntr = 8;
  while(CP_CalCntr);
  status = CB_GetStatus();
  if(!status)
  {
    // calibration pass
    for(int i = 0; i < sizeof(CB_Cal_Count)/sizeof(CB_Cal_Count[0]); i++)
    {
      CB_Cal_Count[i] /= 8+3;
    }
  }
  return status;
}

/**
  * @brief  Touch sensing buttons initialization ...
  * @param  None
  * @retval uint32_t 0 - pass 1 - fault
  */
uint32_t CB_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  CP_Index = 0;
  CB_Res = 0;
  CP_CalCntr = 0;
  memset(CB_Cal_Count,0,sizeof(CB_Cal_Count));

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_TS | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC, ENABLE);

  GPIO_PinAFConfig(GPIOB, GPIO_PinSource0, GPIO_AF_3);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource1, GPIO_AF_3);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource2, GPIO_AF_3);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_3);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_3);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_3);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_3);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource5, GPIO_AF_0);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2
                              | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_6
                              | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  TSC->CR  = (0xFUL << 28)  /* Charge transfer pulse high */
           | (0xFUL << 24)  /* Charge transfer pulse low */
           | (6UL   <<  5)  /* Max count value */
           ;
  /* Disable I/O hysteresis */
  TSC->IOHCR &= ~(  (0xFul << 8)  /* Group 3 */
                  | (0xFul <<16)  /* Group 5 */
                  );
  /* Enable analog switches */
  TSC->IOASCR = 0;
  TSC->IOSCR = (1UL << 8)      /* PC5 */
             | (1UL << 16)      /* PB3 */
             ;

  TSC->IOCCR = (  (1UL << (CP_Index+9))
                | (1UL << (CP_Index+17))
               );
  TSC->IOGCSR = (1UL << 2)      /* Group 3 */
              | (1UL << 4)      /* Group 5 */
              ;

  TSC->ICR = 3; /* clear EOAIE and MCEIE  */
  TSC->IER = 3; /* enable EOAIE and MCEIE  */

  /* Enable and set Button EXTI Interrupt to the lowest priority */
  NVIC_InitStructure.NVIC_IRQChannel = TS_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0x03;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

  NVIC_Init(&NVIC_InitStructure);
  TSC->CR |= 3;

  return CP_Calibrate();
}

/**
  * @brief  Touch sensing buttons interrupt handler ...
  * @param  None
  * @retval None
  */
void CB_Handler(void)
{
  static uint32_t sycn = 0;
  if((1UL << 1) & TSC->ISR)
  {
    /* Max count error */
    TSC->ICR = 2;
    sycn = CP_CalCntr = 0;
    CP_Error = 1;
  }
  else if((1UL << 0) & TSC->ISR)
  {
    /* End of acquisition */
    TSC->ICR = 1;

    if(sycn && CP_CalCntr)
    {
      /* Calibration data collection */
      CB_Cal_Count[CP_Index]   += TSC->IOGXCR[3-1];
      CB_Cal_Count[CP_Index+3] += TSC->IOGXCR[5-1];
    }
    else
    {
      /* Buttons' state data collection */
      if( CB_Cal_Count[CP_Index] > TSC->IOGXCR[3-1])
      {
        CB_Res |= 1UL << CP_Index;
      }
      else
      {
        CB_Res &=~(1UL << CP_Index);
      }

      if(CB_Cal_Count[CP_Index+3] > TSC->IOGXCR[5-1])
      {
        CB_Res |= (1UL << (CP_Index+3));
      }
      else
      {
        CB_Res &=~(1UL << (CP_Index+3));
      }
    }
    /*  Next channel */
    if(++CP_Index >= 3)
    {
      CP_Index = 0;
      if(!sycn)
      {
        sycn = !!CP_CalCntr;
      }
      else if(CP_CalCntr)
      {
        --CP_CalCntr;
      }
      else
      {
        sycn = 0;
      }
    }
    TSC->IOCCR = ((1UL << (CP_Index+9)) | (1UL << (CP_Index+17)));
    /*  Start new acquisition*/
    TSC->CR |= 2;
  }
}

/**
  * @brief  Return state of touch buttons ...
  * @param  None
  * @retval uint32_t 0 - no touched 1- touched
  */
uint32_t CB_GetState(void)
{
	return CB_Res;
}

/**
  * @brief  Return status of touch buttons ...
  * @param  None
  * @retval uint32_t 1 - Max count error
  */
uint32_t CB_GetStatus(void)
{
  uint32_t ret = CP_Error;
	return ret;
}
