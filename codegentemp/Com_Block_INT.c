/*******************************************************************************
* File Name: Com_Block_INT.c
* Version 2.60
*
* Description:
*  This file provides all Interrupt Service Routine (ISR) for the SPI Slave
*  component.
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Com_Block_PVT.h"


/* User code required at start of ISR */
/* `#START Com_Block_ISR_START_DEF` */

/* `#END` */


/*******************************************************************************
* Function Name: Com_Block_TX_ISR
*
* Summary:
*  Interrupt Service Routine for TX portion of the SPI Slave.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  Com_Block_txBufferWrite - used for the account of the bytes which
*  have been written down in the TX software buffer.
*  Com_Block_txBufferRead - used for the account of the bytes which
*  have been read from the TX software buffer, modified when exist data to
*  sending and FIFO Not Full.
*  Com_Block_txBuffer[Com_Block_TX_BUFFER_SIZE] - used to store
*  data to sending.
*  All described above Global variables are used when Software Buffer is used.
*
*******************************************************************************/
CY_ISR(Com_Block_TX_ISR)
{

    #if(Com_Block_TX_SOFTWARE_BUF_ENABLED)
        uint8 tmpStatus;
    #endif /* (Com_Block_TX_SOFTWARE_BUF_ENABLED) */

    /* User code required at start of ISR */
    /* `#START Com_Block_ISR_TX_START` */

    /* `#END` */

    #if(Com_Block_TX_SOFTWARE_BUF_ENABLED)
        /* Component interrupt service code */

        /* See if TX data buffer is not empty and there is space in TX FIFO */
        while(Com_Block_txBufferRead != Com_Block_txBufferWrite)
        {
            tmpStatus = Com_Block_GET_STATUS_TX(Com_Block_swStatusTx);
            Com_Block_swStatusTx = tmpStatus;

            if ((Com_Block_swStatusTx & Com_Block_STS_TX_FIFO_NOT_FULL) != 0u)
            {
                if(Com_Block_txBufferFull == 0u)
                {
                   Com_Block_txBufferRead++;

                    if(Com_Block_txBufferRead >= Com_Block_TX_BUFFER_SIZE)
                    {
                        Com_Block_txBufferRead = 0u;
                    }
                }
                else
                {
                    Com_Block_txBufferFull = 0u;
                }

                /* Move data from the Buffer to the FIFO */
                CY_SET_REG16(Com_Block_TXDATA_PTR,
                Com_Block_txBuffer[Com_Block_txBufferRead]);
            }
            else
            {
                break;
            }
        }

        /* If Buffer is empty then disable TX FIFO status interrupt until there is data in the buffer */
        if(Com_Block_txBufferRead == Com_Block_txBufferWrite)
        {
            Com_Block_TX_STATUS_MASK_REG &= ((uint8)~Com_Block_STS_TX_FIFO_NOT_FULL);
        }

    #endif /* Com_Block_TX_SOFTWARE_BUF_ENABLED */

    /* User code required at end of ISR (Optional) */
    /* `#START Com_Block_ISR_TX_END` */

    /* `#END` */

   }


/*******************************************************************************
* Function Name: Com_Block_RX_ISR
*
* Summary:
*  Interrupt Service Routine for RX portion of the SPI Slave.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  Com_Block_rxBufferWrite - used for the account of the bytes which
*  have been written down in the RX software buffer modified when FIFO contains
*  new data.
*  Com_Block_rxBufferRead - used for the account of the bytes which
*  have been read from the RX software buffer, modified when overflow occurred.
*  Com_Block_rxBuffer[Com_Block_RX_BUFFER_SIZE] - used to store
*  received data, modified when FIFO contains new data.
*  All described above Global variables are used when Software Buffer is used.
*
*******************************************************************************/
CY_ISR(Com_Block_RX_ISR)
{
    #if(Com_Block_TX_SOFTWARE_BUF_ENABLED)
        uint8 tmpStatus;
        uint16 rxData;
    #endif /* (Com_Block_TX_SOFTWARE_BUF_ENABLED) */

    /* User code required at start of ISR */
    /* `#START Com_Block_RX_ISR_START` */

    /* `#END` */

    #if(Com_Block_RX_SOFTWARE_BUF_ENABLED)
        tmpStatus = Com_Block_GET_STATUS_RX(Com_Block_swStatusRx);
        Com_Block_swStatusRx = tmpStatus;
        /* See if RX data FIFO has some data and if it can be moved to the RX Buffer */
        while((Com_Block_swStatusRx & Com_Block_STS_RX_FIFO_NOT_EMPTY) != 0u)
        {
            rxData = CY_GET_REG16(Com_Block_RXDATA_PTR);

            /* Set next pointer. */
            Com_Block_rxBufferWrite++;
            if(Com_Block_rxBufferWrite >= Com_Block_RX_BUFFER_SIZE)
            {
                Com_Block_rxBufferWrite = 0u;
            }

            if(Com_Block_rxBufferWrite == Com_Block_rxBufferRead)
            {
                Com_Block_rxBufferRead++;
                if(Com_Block_rxBufferRead >= Com_Block_RX_BUFFER_SIZE)
                {
                    Com_Block_rxBufferRead = 0u;
                }
                Com_Block_rxBufferFull = 1u;
            }

            /* Move data from the FIFO to the Buffer */
            Com_Block_rxBuffer[Com_Block_rxBufferWrite] = rxData;

            tmpStatus = Com_Block_GET_STATUS_RX(Com_Block_swStatusRx);
            Com_Block_swStatusRx = tmpStatus;
        }
    #endif /* Com_Block_RX_SOFTWARE_BUF_ENABLED */

    /* User code required at end of ISR (Optional) */
    /* `#START Com_Block_RX_ISR_END` */

    /* `#END` */

}

/* [] END OF FILE */
