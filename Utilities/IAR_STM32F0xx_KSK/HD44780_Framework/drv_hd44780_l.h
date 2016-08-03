/*************************************************************************
 *
 *    Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2006
 *
 *    File name   : drv_hd44780_l.h
 *    Description : STM32 HD44780 low level I/O function driver
 *
 *    History :
 *    1. Date        : July 19, 2007
 *       Author      : Stanimir Bonev
 *       Description : Create
 *
 *    $Revision: 103 $
 **************************************************************************/
#include "arm_comm.h"
#include "stm320Fxx_ksk.h"
#include "drv_hd44780_cnfg.h"

#ifndef  __DRV_HD44780_L_H
#define  __DRV_HD44780_L_H

#define LCD_RS                    GPIO_Pin_12
#define LCD_RS_PORT               GPIOC

#define LCD_E                     GPIO_Pin_10
#define LCD_E_PORT                GPIOC

#define LCD_RW                    GPIO_Pin_11
#define LCD_RW_PORT               GPIOC

#define LCD_DATA                  0x0FUL
#define LCD_DATA_SHIFT            4
#define LCD_DATA_PORT             GPIOF

/* Delay macro */
#define HD44780_BUS_DLY()         for(volatile int dly = 30;dly;--dly)

void HD44780_IO_Init (void);
void HD44780SetRS (Boolean Data);
void HD44780SetE (Boolean Data);
void HD44780WrIO (Int32U);
#if HD4780_WR > 0
void HD44780SetRW (Boolean Data);
Int8U HD44780RdIO (void);
#endif // HD4780_WR > 0

#endif  /* __DRV_HD44780_L_H */
