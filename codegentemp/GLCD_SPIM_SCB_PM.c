/*******************************************************************************
* File Name: GLCD_SPIM_SCB_PM.c
* Version 1.0
*
* Description:
*  This file provides the source code to the Power Management support for
*  the SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "GLCD_SPIM_SCB.h"

#if(GLCD_SPIM_SCB_SCB_MODE_I2C_INC)
    #include "GLCD_SPIM_SCB_I2C_PVT.h"
#endif /* (GLCD_SPIM_SCB_SCB_MODE_I2C_INC) */

#if(GLCD_SPIM_SCB_SCB_MODE_SPI_INC || GLCD_SPIM_SCB_SCB_MODE_UART_INC)
    #include "GLCD_SPIM_SCB_SPI_UART_PVT.h"
#endif /* (GLCD_SPIM_SCB_SCB_MODE_SPI_INC || GLCD_SPIM_SCB_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

GLCD_SPIM_SCB_BACKUP_STRUCT GLCD_SPIM_SCB_backup =
{
    0u, /* enableState */
};


/*******************************************************************************
* Function Name: GLCD_SPIM_SCB_Sleep
********************************************************************************
*
* Summary:
*  Calls SaveConfig function fucntion for selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void GLCD_SPIM_SCB_Sleep(void)
{
    GLCD_SPIM_SCB_backup.enableState = (uint8) GLCD_SPIM_SCB_GET_CTRL_ENABLED;

    #if(GLCD_SPIM_SCB_SCB_MODE_UNCONFIG_CONST_CFG)

        if(GLCD_SPIM_SCB_SCB_MODE_I2C_RUNTM_CFG)
        {
            GLCD_SPIM_SCB_I2CSaveConfig();
        }
        else if(GLCD_SPIM_SCB_SCB_MODE_SPI_RUNTM_CFG)
        {
            GLCD_SPIM_SCB_SpiSaveConfig();
        }
        else if(GLCD_SPIM_SCB_SCB_MODE_UART_RUNTM_CFG)
        {
            GLCD_SPIM_SCB_UartSaveConfig();
        }
        else
        {
            /* Unknown mode: do nothing */
        }

    #elif(GLCD_SPIM_SCB_SCB_MODE_I2C_CONST_CFG)
        GLCD_SPIM_SCB_I2CSaveConfig();

    #elif(GLCD_SPIM_SCB_SCB_MODE_SPI_CONST_CFG)
        GLCD_SPIM_SCB_SpiSaveConfig();

    #elif(GLCD_SPIM_SCB_SCB_MODE_UART_CONST_CFG)
        GLCD_SPIM_SCB_UartSaveConfig();

    #else
        /* Do nothing */

    #endif /* (GLCD_SPIM_SCB_SCB_MODE_UNCONFIG_CONST_CFG) */

    if(0u != GLCD_SPIM_SCB_backup.enableState)
    {
        GLCD_SPIM_SCB_Stop();
    }
}


/*******************************************************************************
* Function Name: GLCD_SPIM_SCB_Wakeup
********************************************************************************
*
* Summary:
*  Calls RestoreConfig function fucntion for selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void GLCD_SPIM_SCB_Wakeup(void)
{
    #if(GLCD_SPIM_SCB_SCB_MODE_UNCONFIG_CONST_CFG)

        if(GLCD_SPIM_SCB_SCB_MODE_I2C_RUNTM_CFG)
        {
            GLCD_SPIM_SCB_I2CRestoreConfig();
        }
        else if(GLCD_SPIM_SCB_SCB_MODE_SPI_RUNTM_CFG)
        {
            GLCD_SPIM_SCB_SpiRestoreConfig();
        }
        else if(GLCD_SPIM_SCB_SCB_MODE_UART_RUNTM_CFG)
        {
            GLCD_SPIM_SCB_UartRestoreConfig();
        }
        else
        {
            /* Unknown mode: do nothing */
        }

    #elif(GLCD_SPIM_SCB_SCB_MODE_I2C_CONST_CFG)
        GLCD_SPIM_SCB_I2CRestoreConfig();

    #elif(GLCD_SPIM_SCB_SCB_MODE_SPI_CONST_CFG)
        GLCD_SPIM_SCB_SpiRestoreConfig();

    #elif(GLCD_SPIM_SCB_SCB_MODE_UART_CONST_CFG)
        GLCD_SPIM_SCB_UartRestoreConfig();

    #else
        /* Do nothing */

    #endif /* (GLCD_SPIM_SCB_SCB_MODE_UNCONFIG_CONST_CFG) */

    if(0u != GLCD_SPIM_SCB_backup.enableState)
    {
        GLCD_SPIM_SCB_Enable();
    }
}


/* [] END OF FILE */
