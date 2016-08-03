/*************************************************************************
 *
 *    Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2012
 *
 *    File name   : i2c2_drv.h
 *    Description : I2C2 Master mode driver include file
 *
 *    History :
 *    1. Date        : February 23, 2012
 *       Author      : Stanimir Bonev
 *       Description : Create
 *
 *    $Revision: 103 $
 **************************************************************************/
#include "arm_comm.h"
#include "stm320Fxx_ksk.h"

#ifndef __I2C2_DRV_H
#define __I2C2_DRV_H

#ifdef  I2C2_DRV_GLOBAL
#define I2C2_DRV_EXTERN
#else
#define I2C2_DRV_EXTERN  extern
#endif

#define I2C2_SPEED          100000
#define I2C_LONG_TIMEOUT    1000

/*************************************************************************
 * Function Name: I2C2_Init
 * Parameters: none
 *
 * Return: none
 *
 * Description: Init I2C2 interface
 *
 *************************************************************************/
void I2C2_Init (void);

/*************************************************************************
 * Function Name: I2C2_Open
 * Parameters: none
 *
 * Return: Boolean
 *
 * Description: Init I2C2 interface open
 *
 *************************************************************************/
Boolean I2C2_Open (void);

/*************************************************************************
 * Function Name: I2C2_Close
 * Parameters: none
 *
 * Return: none
 *
 * Description: Init I2C2 interface release
 *
 *************************************************************************/
void I2C2_Close (void);

/*************************************************************************
 * Function Name: I2C2_DataTransfer
 * Parameters: Int8U SlaveAddr, pInt8U pData, Int32U Size
 *
 * Return: none
 *
 * Description: I2C2 transfer data to/from slave
 *
 *************************************************************************/
Boolean I2C2_DataTransfer (Int8U SlaveAddr, pInt8U pData, Int32U Size);

#endif // __I2C2_DRV_H