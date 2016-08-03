/*************************************************************************
 *
 *    Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2008
 *
 *    File name   : accl_drv.c
 *    Description : Accelerometer sensor LIS3L020 driver source file
 *
 *    History :
 *    1. Date        : July 24, 2008
 *       Author      : Stanimir Bonev
 *       Description : Create
 *
 *    $Revision: 103 $
 **************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "arm_comm.h"
#include "accl_drv.h"
#include "i2c2_drv.h"

/* Private typedef -----------------------------------------------------------*/
typedef enum _Accl_regs_t
{
  WHO_AM_I = 0xF,
  OFFSET_X = 0x16, OFFSET_Y, OFFSET_Z, GAIN_X, GAIN_Y, GAIN_Z,
  CTRL_REG1 = 0x20, CTRL_REG2, CTRL_REG3, HP_FILTER_RESET,
  STATUS_REG = 0x27, OUTX_L, OUTX_H, OUTY_L, OUTY_H, OUTZ_L, OUTZ_H,
  FF_WU_CFG = 0x30, FF_WU_SRC, FF_WU_ACK,
  FF_WU_THS_L = 0x34, FF_WU_THS_H, FF_WU_DURATION,
  DD_CFG = 0x38, DD_SRC, DD_ACK,
  DD_THSI_L = 0x3C, DD_THSI_H, DD_THSE_L, DD_THSE_H
} Accl_regs_t;

/* Private define ------------------------------------------------------------*/
#define ACCL_DRV_GLOBAL
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : Accl_Init
* Description    : Init Accelerometer sensor
* Input          : None
* Output         : None
* Return         : Boolean.
*******************************************************************************/

Boolean Accl_Init (void)
{
Int8U Data[2];

  I2C2_Init();
  Acc_LowLevel_Init();

  if(FALSE == I2C2_Open())
  {
    return(FALSE);
  }

  // Get Accl sensor ID
  Data[0] = WHO_AM_I;
  if(FALSE == I2C2_DataTransfer(ACC_SENSOR_ADDR, Data, 1))
  {
    I2C2_Close();
    return(FALSE);
  }
  if(FALSE == I2C2_DataTransfer(ACC_SENSOR_ADDR | 1, Data, 1))
  {
    I2C2_Close();
    return(FALSE);
  }
  if(0x3A != Data[0])
  {
    I2C2_Close();
    return(FALSE);
  }

  // Sensor configure
  Data[0] = CTRL_REG1;
  Data[1] = 0x47; // enable all axes, device on
  if(FALSE == I2C2_DataTransfer(ACC_SENSOR_ADDR, Data, 2))
  {
    I2C2_Close();
    return(FALSE);
  }

  Data[0] = CTRL_REG2;
  Data[1] = 0x04; // enable data ready generation
  if(FALSE == I2C2_DataTransfer(ACC_SENSOR_ADDR, Data, 2))
  {
    I2C2_Close();
    return(FALSE);
  }


  I2C2_Close();
  return(TRUE);
}

/*************************************************************************
 * Function Name: Accl_Get
 * Parameters: pInt16S pX, pInt16S pY, pInt16S pZ
 *
 * Return: Boolean
 *
 * Description: Read X,Y,Z data
 *
 *************************************************************************/
Boolean Accl_Get (pInt16S pX, pInt16S pY, pInt16S pZ)
{
#pragma pack(1)
union
{
  Int8U Data[6];
  struct
  {
    Int16S X;
    Int16S Y;
    Int16S Z;
  };
} OutData;
#pragma pack()

  if(FALSE == I2C2_Open())
  {
    return(FALSE);
  }

  // Get Accl sensor ID
  OutData.Data[0] = OUTX_L | 0x80;  // read multiple bytes
  if(FALSE == I2C2_DataTransfer(ACC_SENSOR_ADDR, OutData.Data, 1))
  {
    I2C2_Close();
    return(FALSE);
  }
  if(FALSE == I2C2_DataTransfer(ACC_SENSOR_ADDR | 1, OutData.Data, 6))
  {
    I2C2_Close();
    return(FALSE);
  }
  I2C2_Close();

  *pX = OutData.X;
  *pY = OutData.Y;
  *pZ = OutData.Z;
  return(TRUE);
}
