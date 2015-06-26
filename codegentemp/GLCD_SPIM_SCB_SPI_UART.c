/*******************************************************************************
* File Name: GLCD_SPIM_SCB_SPI_UART.c
* Version 1.0
*
* Description:
*  This file provides the source code to the API for the SCB Component in
*  SPI and UART modes.
*
* Note:
*
*******************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "GLCD_SPIM_SCB_SPI_UART_PVT.h"


/***************************************
*        SPI/UART Private Vars
***************************************/

#if(GLCD_SPIM_SCB_INTERNAL_RX_SW_BUFFER_CONST)
    volatile uint32 GLCD_SPIM_SCB_rxBufferHead;
    volatile uint32 GLCD_SPIM_SCB_rxBufferTail;
    volatile uint8  GLCD_SPIM_SCB_rxBufferOverflow;
#endif /* (GLCD_SPIM_SCB_INTERNAL_RX_SW_BUFFER_CONST) */

#if(GLCD_SPIM_SCB_INTERNAL_TX_SW_BUFFER_CONST)
    volatile uint32 GLCD_SPIM_SCB_txBufferHead;
    volatile uint32 GLCD_SPIM_SCB_txBufferTail;
#endif /* (GLCD_SPIM_SCB_INTERNAL_TX_SW_BUFFER_CONST) */

#if(GLCD_SPIM_SCB_INTERNAL_RX_SW_BUFFER)
    /* Add one element to the buffer to receive full packet. One byte in receive buffer is always empty */
    volatile uint16 GLCD_SPIM_SCB_rxBufferInternal[GLCD_SPIM_SCB_RX_BUFFER_SIZE];
#endif /* (GLCD_SPIM_SCB_INTERNAL_RX_SW_BUFFER) */

#if(GLCD_SPIM_SCB_INTERNAL_TX_SW_BUFFER)
    volatile uint16 GLCD_SPIM_SCB_txBufferInternal[GLCD_SPIM_SCB_TX_BUFFER_SIZE];
#endif /* (GLCD_SPIM_SCB_INTERNAL_TX_SW_BUFFER) */


#if(GLCD_SPIM_SCB_RX_DIRECTION)

    /*******************************************************************************
    * Function Name: GLCD_SPIM_SCB_SpiUartReadRxData
    ********************************************************************************
    *
    * Summary:
    *  Retrieves the next data element from the receive buffer. Undefined data will
    *  be returned if the RX buffer is empty.
    *  Call GLCD_SPIM_SCB_SpiUartGetRxBufferSize() to return buffer size.
    *   - RX software buffer disabled: Returns data element retrieved from RX FIFO.
    *   - RX software buffer enabled: Returns data element from the software
    *     receive buffer.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Next data element from the receive buffer.
    *
    * Global Variables:
    *  Look into GLCD_SPIM_SCB_SpiInit for description.
    *
    *******************************************************************************/
    uint32 GLCD_SPIM_SCB_SpiUartReadRxData(void)
    {
        uint32 rxData = 0u;
        
        #if(GLCD_SPIM_SCB_INTERNAL_RX_SW_BUFFER_CONST)
            uint32 locTail;
        #endif /* (GLCD_SPIM_SCB_INTERNAL_RX_SW_BUFFER_CONST) */

        #if(GLCD_SPIM_SCB_CHECK_RX_SW_BUFFER)
        {
            if(GLCD_SPIM_SCB_rxBufferHead != GLCD_SPIM_SCB_rxBufferTail)
            {
                /* There is data in RX software buffer */

                /* Calculate index to read from */
                locTail = (GLCD_SPIM_SCB_rxBufferTail + 1u);

                if(GLCD_SPIM_SCB_RX_BUFFER_SIZE == locTail)
                {
                    locTail = 0u;
                }

                /* Get data fron RX software buffer */
                rxData = GLCD_SPIM_SCB_GetWordFromRxBuffer(locTail);

                /* Change index in the buffer */
                GLCD_SPIM_SCB_rxBufferTail = locTail;
            }
        }
        #else
        {
            rxData = GLCD_SPIM_SCB_RX_FIFO_RD_REG; /* Read data from RX FIFO */
        }
        #endif

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: GLCD_SPIM_SCB_SpiUartGetRxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of received data elements in the receive buffer.
    *   - RX software buffer disabled: returns the number of used entries in
    *     RX FIFO.
    *   - RX software buffer enabled: returns the number of elements which were
    *     placed in receive buffer.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Number of received data elements
    *
    *******************************************************************************/
    uint32 GLCD_SPIM_SCB_SpiUartGetRxBufferSize(void)
    {
        uint32 size;
        #if(GLCD_SPIM_SCB_INTERNAL_RX_SW_BUFFER_CONST)
            uint32 locHead;
        #endif /* (GLCD_SPIM_SCB_INTERNAL_RX_SW_BUFFER_CONST) */

        #if(GLCD_SPIM_SCB_CHECK_RX_SW_BUFFER)
        {
            locHead = GLCD_SPIM_SCB_rxBufferHead;

            if(locHead >= GLCD_SPIM_SCB_rxBufferTail)
            {
                size = (locHead - GLCD_SPIM_SCB_rxBufferTail);
            }
            else
            {
                size = (locHead + (GLCD_SPIM_SCB_RX_BUFFER_SIZE - GLCD_SPIM_SCB_rxBufferTail));
            }
        }
        #else
        {
            size = GLCD_SPIM_SCB_GET_RX_FIFO_ENTRIES;
        }
        #endif

        return(size);
    }


    /*******************************************************************************
    * Function Name: GLCD_SPIM_SCB_SpiUartClearRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clear the receive buffer and RX FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void GLCD_SPIM_SCB_SpiUartClearRxBuffer(void)
    {
        #if(GLCD_SPIM_SCB_INTERNAL_RX_SW_BUFFER_CONST)
            uint32 intSourceMask;
        #endif /* (GLCD_SPIM_SCB_INTERNAL_RX_SW_BUFFER_CONST) */

        #if(GLCD_SPIM_SCB_CHECK_RX_SW_BUFFER)
        {
            intSourceMask = GLCD_SPIM_SCB_SpiUartDisableIntRx();

            GLCD_SPIM_SCB_CLEAR_RX_FIFO;

            /* Flush RX software buffer */
            GLCD_SPIM_SCB_rxBufferHead     = GLCD_SPIM_SCB_rxBufferTail;
            GLCD_SPIM_SCB_rxBufferOverflow = 0u;

            /* End RX transfer */
            GLCD_SPIM_SCB_ClearRxInterruptSource(GLCD_SPIM_SCB_INTR_RX_ALL);

            GLCD_SPIM_SCB_SpiUartEnableIntRx(intSourceMask);
        }
        #else
        {
            GLCD_SPIM_SCB_CLEAR_RX_FIFO;
        }
        #endif
    }

#endif /* (GLCD_SPIM_SCB_RX_DIRECTION) */


#if(GLCD_SPIM_SCB_TX_DIRECTION)

    /*******************************************************************************
    * Function Name: GLCD_SPIM_SCB_SpiUartWriteTxData
    ********************************************************************************
    *
    * Summary:
    *  Places a data entry into the transmit buffer to be sent at the next available
    *  bus time.
    *  This function is blocking and waits until there is space available to put the
    *  requested data in the transmit buffer.
    *
    * Parameters:
    *  txDataByte: the data to be transmitted.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void GLCD_SPIM_SCB_SpiUartWriteTxData(uint32 txDataByte)
    {
        #if(GLCD_SPIM_SCB_INTERNAL_TX_SW_BUFFER_CONST)
            uint32 locHead;
            uint32 intSourceMask;
        #endif /* (GLCD_SPIM_SCB_INTERNAL_TX_SW_BUFFER_CONST) */

        #if(GLCD_SPIM_SCB_CHECK_TX_SW_BUFFER)
        {
            /* Head index to put data */
            locHead = (GLCD_SPIM_SCB_txBufferHead + 1u);

            /* Adjust TX software buffer index */
            if(GLCD_SPIM_SCB_TX_BUFFER_SIZE == locHead)
            {
                locHead = 0u;
            }

            while(locHead == GLCD_SPIM_SCB_txBufferTail)
            {
                /* Wait for space in the TX software buffer */
            }

            /* The TX software buffer has at least one room */

            if((GLCD_SPIM_SCB_txBufferHead == GLCD_SPIM_SCB_txBufferTail) &&
               (GLCD_SPIM_SCB_FIFO_SIZE != GLCD_SPIM_SCB_GET_TX_FIFO_ENTRIES))
            {
                /* TX software buffer is empty: put data directly in TX FIFO */
                GLCD_SPIM_SCB_TX_FIFO_WR_REG = txDataByte;
            }
            /* Put data in the TX software buffer */
            else
            {
                /* Clear old status of INTR_TX_EMPTY. It sets at the end of transfer: TX FIFO empty. */
                GLCD_SPIM_SCB_ClearTxInterruptSource(GLCD_SPIM_SCB_INTR_TX_EMPTY);

                GLCD_SPIM_SCB_PutWordInTxBuffer(locHead, txDataByte);

                GLCD_SPIM_SCB_txBufferHead = locHead;

                /* Enable interrupt to transmit */
                intSourceMask  = GLCD_SPIM_SCB_INTR_TX_EMPTY;
                intSourceMask |= GLCD_SPIM_SCB_GetTxInterruptMode();
                GLCD_SPIM_SCB_SpiUartEnableIntTx(intSourceMask);
            }
        }
        #else
        {
            while(GLCD_SPIM_SCB_FIFO_SIZE == GLCD_SPIM_SCB_GET_TX_FIFO_ENTRIES)
            {
                /* Block while TX FIFO is FULL */
            }

            GLCD_SPIM_SCB_TX_FIFO_WR_REG = txDataByte;
        }
        #endif
    }


    /*******************************************************************************
    * Function Name: GLCD_SPIM_SCB_SpiUartPutArray
    ********************************************************************************
    *
    * Summary:
    *  Places an array of data into the transmit buffer to be sent.
    *  This function is blocking and waits until there is a space available to put
    *  all the requested data in the transmit buffer. The array size can be greater
    *  than transmit buffer size.
    *
    * Parameters:
    *  wrBuf:  pointer to an array with data to be placed in transmit buffer.
    *  count:  number of data elements to be placed in the transmit buffer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void GLCD_SPIM_SCB_SpiUartPutArray(const uint16 wrBuf[], uint32 count)
    {
        uint32 i;

        for(i=0u; i < count; i++)
        {
            GLCD_SPIM_SCB_SpiUartWriteTxData((uint32) wrBuf[i]);
        }
    }


    /*******************************************************************************
    * Function Name: GLCD_SPIM_SCB_SpiUartGetTxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of elements currently in the transmit buffer.
    *  TX software buffer disabled: returns the number of used entries in TX FIFO.
    *  TX software buffer enabled: returns the number of elements currently used
    *  in the transmit buffer. This number does not include used entries in the
    *  TX FIFO. The transmit buffer size is zero until the TX FIFO is full.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Number of data elements ready to transmit.
    *
    *******************************************************************************/
    uint32 GLCD_SPIM_SCB_SpiUartGetTxBufferSize(void)
    {
        uint32 size;
        #if(GLCD_SPIM_SCB_INTERNAL_TX_SW_BUFFER_CONST)
            uint32 locTail;
        #endif /* (GLCD_SPIM_SCB_INTERNAL_TX_SW_BUFFER_CONST) */

        #if(GLCD_SPIM_SCB_CHECK_TX_SW_BUFFER)
        {
            /* Get current Tail index */
            locTail = GLCD_SPIM_SCB_txBufferTail;

            if(GLCD_SPIM_SCB_txBufferHead >= locTail)
            {
                size = (GLCD_SPIM_SCB_txBufferHead - locTail);
            }
            else
            {
                size = (GLCD_SPIM_SCB_txBufferHead + (GLCD_SPIM_SCB_TX_BUFFER_SIZE - locTail));
            }
        }
        #else
        {
            size = GLCD_SPIM_SCB_GET_TX_FIFO_ENTRIES;
        }
        #endif

        return(size);
    }


    /*******************************************************************************
    * Function Name: GLCD_SPIM_SCB_SpiUartClearTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the transmit buffer and TX FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void GLCD_SPIM_SCB_SpiUartClearTxBuffer(void)
    {
        #if(GLCD_SPIM_SCB_INTERNAL_TX_SW_BUFFER_CONST)
            uint32 intSourceMask;
        #endif /* (GLCD_SPIM_SCB_INTERNAL_TX_SW_BUFFER_CONST) */

        #if(GLCD_SPIM_SCB_CHECK_TX_SW_BUFFER)
        {
            intSourceMask = GLCD_SPIM_SCB_SpiUartDisableIntTx();

            GLCD_SPIM_SCB_CLEAR_TX_FIFO;

            /* Flush TX software buffer */
            GLCD_SPIM_SCB_txBufferHead = GLCD_SPIM_SCB_txBufferTail;

            /* End TX transfer if it is in progress */
            intSourceMask &= (uint32) ~GLCD_SPIM_SCB_INTR_TX_EMPTY;

            GLCD_SPIM_SCB_SpiUartEnableIntTx(intSourceMask);
        }
        #else
        {
            GLCD_SPIM_SCB_CLEAR_TX_FIFO;
        }
        #endif
    }

#endif /* (GLCD_SPIM_SCB_TX_DIRECTION) */


/*******************************************************************************
* Function Name: GLCD_SPIM_SCB_SpiUartDisableIntRx
********************************************************************************
*
* Summary:
*  Disables RX interrupt sources.
*
* Parameters:
*  None
*
* Return:
*  Returns RX interrupt soureces enabled before function call.
*
*******************************************************************************/
uint32 GLCD_SPIM_SCB_SpiUartDisableIntRx(void)
{
    uint32 intSource;

    intSource = GLCD_SPIM_SCB_GetRxInterruptMode();

    GLCD_SPIM_SCB_SetRxInterruptMode(GLCD_SPIM_SCB_NO_INTR_SOURCES);

    return(intSource);
}


/*******************************************************************************
* Function Name: GLCD_SPIM_SCB_SpiUartDisableIntTx
********************************************************************************
*
* Summary:
*  Disables TX interrupt sources.
*
* Parameters:
*  None
*
* Return:
*  Returns TX interrupt soureces enabled before function call.
*
*******************************************************************************/
uint32 GLCD_SPIM_SCB_SpiUartDisableIntTx(void)
{
    uint32 intSourceMask;

    intSourceMask = GLCD_SPIM_SCB_GetTxInterruptMode();

    GLCD_SPIM_SCB_SetTxInterruptMode(GLCD_SPIM_SCB_NO_INTR_SOURCES);

    return(intSourceMask);
}


#if(GLCD_SPIM_SCB_SCB_MODE_UNCONFIG_CONST_CFG)

    /*******************************************************************************
    * Function Name: GLCD_SPIM_SCB_PutWordInRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Stores byte/word into the RX buffer.
    *  Only available in Unconfigured operation mode.
    *
    * Parameters:
    *  index:      index to store data byte/word in the RX buffer.
    *  rxDataByte: byte/word to store.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void GLCD_SPIM_SCB_PutWordInRxBuffer(uint32 idx, uint32 rxDataByte)
    {
        /* Put data in the buffer */
        if(GLCD_SPIM_SCB_ONE_BYTE_WIDTH == GLCD_SPIM_SCB_rxDataBits)
        {
            GLCD_SPIM_SCB_rxBuffer[idx] = ((uint8) rxDataByte);
        }
        else
        {
            GLCD_SPIM_SCB_rxBuffer[(uint32)(idx << 1u)]      = LO8(LO16(rxDataByte));
            GLCD_SPIM_SCB_rxBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(rxDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: GLCD_SPIM_SCB_GetWordFromRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Reads byte/word from RX buffer.
    *  Only available in Unconfigured operation mode.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Returns byte/word read from RX buffer.
    *
    *******************************************************************************/
    uint32 GLCD_SPIM_SCB_GetWordFromRxBuffer(uint32 idx)
    {
        uint32 value;

        if(GLCD_SPIM_SCB_ONE_BYTE_WIDTH == GLCD_SPIM_SCB_rxDataBits)
        {
            value = GLCD_SPIM_SCB_rxBuffer[idx];
        }
        else
        {
            value  = (uint32) GLCD_SPIM_SCB_rxBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32)GLCD_SPIM_SCB_rxBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return(value);
    }


    /*******************************************************************************
    * Function Name: GLCD_SPIM_SCB_PutWordInTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Stores byte/word into the TX buffer.
    * Only available in Unconfigured operation mode.
    *
    * Parameters:
    *  idx:        index to store data byte/word in the TX buffer.
    *  txDataByte: byte/word to store.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void GLCD_SPIM_SCB_PutWordInTxBuffer(uint32 idx, uint32 txDataByte)
    {
        /* Put data in the buffer */
        if(GLCD_SPIM_SCB_ONE_BYTE_WIDTH == GLCD_SPIM_SCB_txDataBits)
        {
            GLCD_SPIM_SCB_txBuffer[idx] = ((uint8) txDataByte);
        }
        else
        {
            GLCD_SPIM_SCB_txBuffer[(uint32)(idx << 1u)]      = LO8(LO16(txDataByte));
            GLCD_SPIM_SCB_txBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(txDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: GLCD_SPIM_SCB_GetWordFromTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Reads byte/word from TX buffer.
    *  Only available in Unconfigured operation mode.
    *
    * Parameters:
    *  idx: index to get data byte/word from the TX buffer.
    *
    * Return:
    *  Returns byte/word read from TX buffer.
    *
    *******************************************************************************/
    uint32 GLCD_SPIM_SCB_GetWordFromTxBuffer(uint32 idx)
    {
        uint32 value;

        if(GLCD_SPIM_SCB_ONE_BYTE_WIDTH == GLCD_SPIM_SCB_txDataBits)
        {
            value = (uint32) GLCD_SPIM_SCB_txBuffer[idx];
        }
        else
        {
            value  = (uint32) GLCD_SPIM_SCB_txBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32) GLCD_SPIM_SCB_txBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return(value);
    }

#endif /* (GLCD_SPIM_SCB_SCB_MODE_UNCONFIG_CONST_CFG) */


/* [] END OF FILE */
