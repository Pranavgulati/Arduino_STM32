/*************************************************************************
 *
 *    Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2012
 *
 *    File name   : I2C2_drv.c
 *    Description : I2C2 Master mode driver
 *
 *    History :
 *    1. Date        : February 23, 2012
 *       Author      : Stanimir Bonev
 *       Description : Create
 *
 *    $Revision: 103 $
 **************************************************************************/
#define I2C2_DRV_GLOBAL
#include "i2c2_drv.h"
static Boolean s_I2C_NotUsed;

/*************************************************************************
 * Function Name: I2C2_Init
 * Parameters: none
 *
 * Return: none
 *
 * Description: Init I2C2 interface
 *
 *************************************************************************/
void I2C2_Init (void)
{
I2C_InitTypeDef  I2C_InitStructure;
GPIO_InitTypeDef GPIO_InitStructure;

  s_I2C_NotUsed = TRUE;

  // Enable clock
  /*!< ACC_I2C Periph clock enable */
  RCC_APB1PeriphClockCmd(ACC_I2C_CLK, ENABLE);

  /*!< ACC_I2C_SCL_GPIO_CLK, ACC_I2C_SDA_GPIO_CLK
       and ACC_INT_GPIO_CLK Periph clock enable */
  RCC_AHBPeriphClockCmd(ACC_I2C_SCL_GPIO_CLK | ACC_I2C_SDA_GPIO_CLK, ENABLE);

  /* Connect PXx to I2C_SCL */
  GPIO_PinAFConfig(ACC_I2C_SCL_GPIO_PORT, ACC_I2C_SCL_SOURCE, ACC_I2C_SCL_AF);

  /* Connect PXx to I2C_SDA */
  GPIO_PinAFConfig(ACC_I2C_SDA_GPIO_PORT, ACC_I2C_SDA_SOURCE, ACC_I2C_SDA_AF);

  /*!< Configure ACC_I2C pins: SCL */
  GPIO_InitStructure.GPIO_Pin = ACC_I2C_SCL_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(ACC_I2C_SCL_GPIO_PORT, &GPIO_InitStructure);

  /*!< Configure ACC_I2C pins: SDA */
  GPIO_InitStructure.GPIO_Pin = ACC_I2C_SDA_PIN;
  GPIO_Init(ACC_I2C_SDA_GPIO_PORT, &GPIO_InitStructure);

  I2C_DeInit(I2C2);

  // I2C configuration
  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStructure.I2C_AnalogFilter = I2C_AnalogFilter_Enable;
  I2C_InitStructure.I2C_DigitalFilter = 0x00;
  I2C_InitStructure.I2C_OwnAddress1 = 0x00;
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_InitStructure.I2C_Timing = I2C2_SPEED;

  /* Apply I2C2 configuration after enabling it */
  I2C_Init(I2C2, &I2C_InitStructure);

  /* I2C2 Peripheral Enable */
  I2C_Cmd(I2C2, ENABLE);
}

/*************************************************************************
 * Function Name: I2C2_Open
 * Parameters: none
 *
 * Return: Boolean
 *
 * Description: Init I2C2 interface open
 *
 *************************************************************************/
Boolean I2C2_Open (void)
{
  return(0 != AtomicExchange(FALSE, &s_I2C_NotUsed));
}

/*************************************************************************
 * Function Name: I2C2_Close
 * Parameters: none
 *
 * Return: none
 *
 * Description: Init I2C2 interface release
 *
 *************************************************************************/
void I2C2_Close (void)
{
  AtomicExchange(TRUE, &s_I2C_NotUsed);
}

/*************************************************************************
 * Function Name: I2C2_DataTransfer
 * Parameters: Int8U SlaveAddr, pInt8U pData, Int32U Size
 *
 * Return: none
 *
 * Description: I2C2 transfer data to/from slave
 *
 *************************************************************************/
Boolean I2C2_DataTransfer (Int8U SlaveAddr, pInt8U pData, Int32U Size)
{
  Int32U to;
  Boolean read;
  read = !!(SlaveAddr & 1);
  SlaveAddr &= 0xFE;
  /* Configure slave address, nbytes, reload and generate start */
  I2C2->CR2 = (uint32_t)(SlaveAddr) | (uint32_t)(Size << 16) | I2C_CR2_AUTOEND | (read?I2C_CR2_RD_WRN:0);
  I2C2->CR2 |= I2C_CR2_START;

  while(Size--)
  {
    if(!read)
    {
      /* Wait until TXIS flag is set */
      to = I2C_LONG_TIMEOUT;
      while (!(I2C2->ISR & I2C_ISR_TXIS))
      {
        if((to--) == 0) return FALSE;
      }
      /* Send memory address */
      I2C2->TXDR = *pData++;
    }
    else
    {
      /* Wait until RXNE flag is set */
      to = I2C_LONG_TIMEOUT;
      while (!(I2C2->ISR & I2C_ISR_RXNE))
      {
        if((to--) == 0) return FALSE;
      }
      /* Read data from RXDR */
      *pData++ = (uint8_t)I2C2->RXDR;
    }
  }


  /* Wait until STOPF flag is set */
  to = I2C_LONG_TIMEOUT;
  while (!(I2C2->ISR & I2C_ISR_STOPF))
  {
    if((to--) == 0) return FALSE;
  }

  /* Clear STOPF flag */
  I2C2->ICR = I2C_ICR_STOPCF;

  return TRUE;
}
