/*******************************************************************************
* File Name: GLCD_SPIM_UDB_INT.c
* Version 2.40
*
* Description:
*  This file provides all Interrupt Service Routine (ISR) for the SPI Master
*  component.
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "GLCD_SPIM_UDB_PVT.h"

/* User code required at start of ISR */
/* `#START GLCD_SPIM_UDB_ISR_START_DEF` */

/* `#END` */


/*******************************************************************************
* Function Name: GLCD_SPIM_UDB_TX_ISR
********************************************************************************
*
* Summary:
*  Interrupt Service Routine for TX portion of the SPI Master.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  GLCD_SPIM_UDB_txBufferWrite - used for the account of the bytes which
*  have been written down in the TX software buffer.
*  GLCD_SPIM_UDB_txBufferRead - used for the account of the bytes which
*  have been read from the TX software buffer, modified when exist data to
*  sending and FIFO Not Full.
*  GLCD_SPIM_UDB_txBuffer[GLCD_SPIM_UDB_TX_BUFFER_SIZE] - used to store
*  data to sending.
*  All described above Global variables are used when Software Buffer is used.
*
*******************************************************************************/
CY_ISR(GLCD_SPIM_UDB_TX_ISR)
{
    #if(GLCD_SPIM_UDB_TX_SOFTWARE_BUF_ENABLED)
        uint8 tmpStatus;
    #endif /* (GLCD_SPIM_UDB_TX_SOFTWARE_BUF_ENABLED) */

    /* User code required at start of ISR */
    /* `#START GLCD_SPIM_UDB_TX_ISR_START` */

    /* `#END` */

    #if(GLCD_SPIM_UDB_TX_SOFTWARE_BUF_ENABLED)
        /* Check if TX data buffer is not empty and there is space in TX FIFO */
        while(GLCD_SPIM_UDB_txBufferRead != GLCD_SPIM_UDB_txBufferWrite)
        {
            tmpStatus = GLCD_SPIM_UDB_GET_STATUS_TX(GLCD_SPIM_UDB_swStatusTx);
            GLCD_SPIM_UDB_swStatusTx = tmpStatus;

            if(0u != (GLCD_SPIM_UDB_swStatusTx & GLCD_SPIM_UDB_STS_TX_FIFO_NOT_FULL))
            {
                if(0u == GLCD_SPIM_UDB_txBufferFull)
                {
                   GLCD_SPIM_UDB_txBufferRead++;

                    if(GLCD_SPIM_UDB_txBufferRead >= GLCD_SPIM_UDB_TX_BUFFER_SIZE)
                    {
                        GLCD_SPIM_UDB_txBufferRead = 0u;
                    }
                }
                else
                {
                    GLCD_SPIM_UDB_txBufferFull = 0u;
                }

                /* Move data from the Buffer to the FIFO */
                CY_SET_REG16(GLCD_SPIM_UDB_TXDATA_PTR,
                    GLCD_SPIM_UDB_txBuffer[GLCD_SPIM_UDB_txBufferRead]);
            }
            else
            {
                break;
            }
        }

        if(GLCD_SPIM_UDB_txBufferRead == GLCD_SPIM_UDB_txBufferWrite)
        {
            /* TX Buffer is EMPTY: disable interrupt on TX NOT FULL */
            GLCD_SPIM_UDB_TX_STATUS_MASK_REG &= ((uint8) ~GLCD_SPIM_UDB_STS_TX_FIFO_NOT_FULL);
        }

    #endif /* (GLCD_SPIM_UDB_TX_SOFTWARE_BUF_ENABLED) */

    /* User code required at end of ISR (Optional) */
    /* `#START GLCD_SPIM_UDB_TX_ISR_END` */

    /* `#END` */
}


/*******************************************************************************
* Function Name: GLCD_SPIM_UDB_RX_ISR
********************************************************************************
*
* Summary:
*  Interrupt Service Routine for RX portion of the SPI Master.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  GLCD_SPIM_UDB_rxBufferWrite - used for the account of the bytes which
*  have been written down in the RX software buffer modified when FIFO contains
*  new data.
*  GLCD_SPIM_UDB_rxBufferRead - used for the account of the bytes which
*  have been read from the RX software buffer, modified when overflow occurred.
*  GLCD_SPIM_UDB_rxBuffer[GLCD_SPIM_UDB_RX_BUFFER_SIZE] - used to store
*  received data, modified when FIFO contains new data.
*  All described above Global variables are used when Software Buffer is used.
*
*******************************************************************************/
CY_ISR(GLCD_SPIM_UDB_RX_ISR)
{
    #if(GLCD_SPIM_UDB_RX_SOFTWARE_BUF_ENABLED)
        uint8 tmpStatus;
        uint16 rxData;
    #endif /* (GLCD_SPIM_UDB_RX_SOFTWARE_BUF_ENABLED) */

    /* User code required at start of ISR */
    /* `#START GLCD_SPIM_UDB_RX_ISR_START` */

    /* `#END` */

    #if(GLCD_SPIM_UDB_RX_SOFTWARE_BUF_ENABLED)

        tmpStatus = GLCD_SPIM_UDB_GET_STATUS_RX(GLCD_SPIM_UDB_swStatusRx);
        GLCD_SPIM_UDB_swStatusRx = tmpStatus;

        /* Check if RX data FIFO has some data to be moved into the RX Buffer */
        while(0u != (GLCD_SPIM_UDB_swStatusRx & GLCD_SPIM_UDB_STS_RX_FIFO_NOT_EMPTY))
        {
            rxData = CY_GET_REG16(GLCD_SPIM_UDB_RXDATA_PTR);

            /* Set next pointer. */
            GLCD_SPIM_UDB_rxBufferWrite++;
            if(GLCD_SPIM_UDB_rxBufferWrite >= GLCD_SPIM_UDB_RX_BUFFER_SIZE)
            {
                GLCD_SPIM_UDB_rxBufferWrite = 0u;
            }

            if(GLCD_SPIM_UDB_rxBufferWrite == GLCD_SPIM_UDB_rxBufferRead)
            {
                GLCD_SPIM_UDB_rxBufferRead++;
                if(GLCD_SPIM_UDB_rxBufferRead >= GLCD_SPIM_UDB_RX_BUFFER_SIZE)
                {
                    GLCD_SPIM_UDB_rxBufferRead = 0u;
                }

                GLCD_SPIM_UDB_rxBufferFull = 1u;
            }

            /* Move data from the FIFO to the Buffer */
            GLCD_SPIM_UDB_rxBuffer[GLCD_SPIM_UDB_rxBufferWrite] = rxData;

            tmpStatus = GLCD_SPIM_UDB_GET_STATUS_RX(GLCD_SPIM_UDB_swStatusRx);
            GLCD_SPIM_UDB_swStatusRx = tmpStatus;
        }

    #endif /* (GLCD_SPIM_UDB_RX_SOFTWARE_BUF_ENABLED) */

    /* User code required at end of ISR (Optional) */
    /* `#START GLCD_SPIM_UDB_RX_ISR_END` */

    /* `#END` */
}

/* [] END OF FILE */
