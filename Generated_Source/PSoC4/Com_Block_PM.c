/*******************************************************************************
* File Name: Com_Block_PM.c
* Version 2.60
*
* Description:
*  This file contains the setup, control and status commands to support
*  component operations in low power mode.
*
* Note:
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Com_Block_PVT.h"

static Com_Block_BACKUP_STRUCT Com_Block_backup = 
{
    Com_Block_DISABLED,
    Com_Block_BITCTR_INIT,
    #if(CY_UDB_V0)
        Com_Block_TX_INIT_INTERRUPTS_MASK,
        Com_Block_RX_INIT_INTERRUPTS_MASK
    #endif /* CY_UDB_V0 */
};


/*******************************************************************************
* Function Name: Com_Block_SaveConfig
********************************************************************************
*
* Summary:
*  Saves SPIM configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  Com_Block_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Com_Block_SaveConfig(void) 
{
    /* Store Status Mask registers */
    #if (CY_UDB_V0)

       Com_Block_backup.saveSrTxIntMask = Com_Block_TX_STATUS_MASK_REG;
       Com_Block_backup.saveSrRxIntMask = Com_Block_RX_STATUS_MASK_REG;
       Com_Block_backup.cntrPeriod      = Com_Block_COUNTER_PERIOD_REG;

    #endif /* CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: Com_Block_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores SPIS configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  Com_Block_backup - used when non-retention registers are restored.
*
* Side Effects:
*  If this API is called without first calling SaveConfig then in the following
*  registers will be default values from Customizer:
*  Com_Block_STATUS_MASK_REG and Com_Block_COUNTER_PERIOD_REG.
*
*******************************************************************************/
void Com_Block_RestoreConfig(void) 
{
    /* Restore the data, saved by SaveConfig() function */
    #if (CY_UDB_V0)

        Com_Block_TX_STATUS_MASK_REG = Com_Block_backup.saveSrTxIntMask;
        Com_Block_RX_STATUS_MASK_REG = Com_Block_backup.saveSrRxIntMask;
        Com_Block_COUNTER_PERIOD_REG = Com_Block_backup.cntrPeriod;

    #endif /* CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: Com_Block_Sleep
********************************************************************************
*
* Summary:
*  Prepare SPIM Component goes to sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  Com_Block_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Com_Block_Sleep(void) 
{
    /* Save components enable state */
    if ((Com_Block_TX_STATUS_ACTL_REG & Com_Block_INT_ENABLE) != 0u)
    {
        Com_Block_backup.enableState = 1u;
    }
    else /* Components block is disabled */
    {
        Com_Block_backup.enableState = 0u;
    }

    Com_Block_Stop();

    Com_Block_SaveConfig();
}


/*******************************************************************************
* Function Name: Com_Block_Wakeup
********************************************************************************
*
* Summary:
*  Prepare SPIM Component to wake up.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  Com_Block_backup - used when non-retention registers are restored.
*  Com_Block_txBufferWrite - modified every function call - resets to
*  zero.
*  Com_Block_txBufferRead - modified every function call - resets to
*  zero.
*  Com_Block_rxBufferWrite - modified every function call - resets to
*  zero.
*  Com_Block_rxBufferRead - modified every function call - resets to
*  zero.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Com_Block_Wakeup(void) 
{
    Com_Block_RestoreConfig();

    #if (Com_Block_TX_SOFTWARE_BUF_ENABLED)
        Com_Block_txBufferFull = 0u;
        Com_Block_txBufferRead = 0u;
        Com_Block_txBufferWrite = 0u;
    #endif /* Com_Block_TX_SOFTWARE_BUF_ENABLED */

    #if (Com_Block_RX_SOFTWARE_BUF_ENABLED)
        Com_Block_rxBufferFull = 0u;
        Com_Block_rxBufferRead = 0u;
        Com_Block_rxBufferWrite = 0u;
    #endif /* Com_Block_RX_SOFTWARE_BUF_ENABLED */

    Com_Block_ClearFIFO();

    /* Restore components block enable state */
    if (Com_Block_backup.enableState != 0u)
    {
         /* Components block was enabled */
         Com_Block_Enable();
    } /* Do nothing if components block was disabled */
}


/* [] END OF FILE */
