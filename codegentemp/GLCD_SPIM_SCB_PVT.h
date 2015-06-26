/*******************************************************************************
* File Name: .h
* Version 1.0
*
* Description:
*  This private file provides constants and parameter values for the
*  SCB Component in I2C mode.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PVT_GLCD_SPIM_SCB_H)
#define CY_SCB_PVT_GLCD_SPIM_SCB_H

#include "GLCD_SPIM_SCB.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define GLCD_SPIM_SCB_SetI2CExtClkInterruptMode(interruptMask) GLCD_SPIM_SCB_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define GLCD_SPIM_SCB_ClearI2CExtClkInterruptSource(interruptMask) GLCD_SPIM_SCB_CLEAR_INTR_I2C_EC(interruptMask)
#define GLCD_SPIM_SCB_GetI2CExtClkInterruptSource()                (GLCD_SPIM_SCB_INTR_I2C_EC_REG)
#define GLCD_SPIM_SCB_GetI2CExtClkInterruptMode()                  (GLCD_SPIM_SCB_INTR_I2C_EC_MASK_REG)
#define GLCD_SPIM_SCB_GetI2CExtClkInterruptSourceMasked()          (GLCD_SPIM_SCB_INTR_I2C_EC_MASKED_REG)

/* APIs to service INTR_SPI_EC register */
#define GLCD_SPIM_SCB_SetSpiExtClkInterruptMode(interruptMask) GLCD_SPIM_SCB_WRITE_INTR_SPI_EC_MASK(interruptMask)
#define GLCD_SPIM_SCB_ClearSpiExtClkInterruptSource(interruptMask) GLCD_SPIM_SCB_CLEAR_INTR_SPI_EC(interruptMask)
#define GLCD_SPIM_SCB_GetExtSpiClkInterruptSource()                 (GLCD_SPIM_SCB_INTR_SPI_EC_REG)
#define GLCD_SPIM_SCB_GetExtSpiClkInterruptMode()                   (GLCD_SPIM_SCB_INTR_SPI_EC_MASK_REG)
#define GLCD_SPIM_SCB_GetExtSpiClkInterruptSourceMasked()           (GLCD_SPIM_SCB_INTR_SPI_EC_MASKED_REG)

#if(GLCD_SPIM_SCB_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void GLCD_SPIM_SCB_SetPins(uint32 mode, uint32 subMode, uint32 uartTxRx);
#endif /* (GLCD_SPIM_SCB_SCB_MODE_UNCONFIG_CONST_CFG) */

#endif /* (CY_SCB_PVT_GLCD_SPIM_SCB_H) */


/* [] END OF FILE */
