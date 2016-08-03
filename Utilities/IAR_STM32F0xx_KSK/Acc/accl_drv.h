/*************************************************************************
 *
 *    Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2008
 *
 *    File name   : accl_drv.h
 *    Description : Accelerometer sensor LIS3L020 driver include file
 *
 *    History :
 *    1. Date        : July 24, 2008
 *       Author      : Stanimir Bonev
 *       Description : Create
 *
 *    $Revision: 103 $
 **************************************************************************/
#include "i2c2_drv.h"

#ifndef __ACCL_DRV_H
#define __ACCL_DRV_H

#ifdef  ACCL_DRV_GLOBAL
#define ACCL_DRV_EXTERN
#else
#define ACCL_DRV_EXTERN  extern
#endif

#define ACC_SENSOR_ADDR     0x3A

/*************************************************************************
 * Function Name: Accl_Init
 * Parameters: none
 *
 * Return: Boolean
 *
 * Description: Init Accelerometer sensor
 *
 *************************************************************************/
Boolean Accl_Init (void);

/*************************************************************************
 * Function Name: Accl_Get
 * Parameters: pInt16S pX, pInt16S pY, pInt16S pZ
 *
 * Return: Boolean
 *
 * Description: Read X,Y,Z data
 *
 *************************************************************************/
Boolean Accl_Get (pInt16S pX, pInt16S pY, pInt16S pZ);

#endif // __ACCL_DRV_H