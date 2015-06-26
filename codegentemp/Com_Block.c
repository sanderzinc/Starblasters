/*******************************************************************************
* File Name: Com_Block.c
* Version 2.60
*
* Description:
*  This file provides all API functionality of the SPI Slave component.
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

#if (Com_Block_TX_SOFTWARE_BUF_ENABLED)

    volatile uint16 Com_Block_txBuffer[Com_Block_TX_BUFFER_SIZE] = {0u};
    volatile uint8 Com_Block_txBufferRead;
    volatile uint8 Com_Block_txBufferWrite;
    volatile uint8 Com_Block_txBufferFull;

#endif /* Com_Block_TX_SOFTWARE_BUF_ENABLED*/

#if (Com_Block_RX_SOFTWARE_BUF_ENABLED)

    volatile uint16 Com_Block_rxBuffer[Com_Block_RX_BUFFER_SIZE] = {0u};
    volatile uint8 Com_Block_rxBufferRead;
    volatile uint8 Com_Block_rxBufferWrite;
    volatile uint8 Com_Block_rxBufferFull;

#endif /* Com_Block_RX_SOFTWARE_BUF_ENABLED */

uint8 Com_Block_initVar = 0u;

volatile uint8 Com_Block_swStatusTx;
volatile uint8 Com_Block_swStatusRx;


/*******************************************************************************
* Function Name: Com_Block_Init
********************************************************************************
*
* Summary:
*  Inits/Restores default SPIS configuration provided with customizer.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  When this function is called it initializes all of the necessary parameters
*  for execution. i.e. setting the initial interrupt mask, configuring the
*  interrupt service routine, configuring the bit-counter parameters and
*  clearing the FIFO and Status Register.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Com_Block_Init(void) 
{
    /*Initialize the Bit counter */
    Com_Block_COUNTER_PERIOD_REG = Com_Block_BITCTR_INIT;

    /* ISR initialization */
    #if(Com_Block_INTERNAL_TX_INT_ENABLED)

        CyIntDisable(Com_Block_TX_ISR_NUMBER);

        /* Set the ISR to point to the Com_Block_isr Interrupt. */
        (void)CyIntSetVector(Com_Block_TX_ISR_NUMBER, &Com_Block_TX_ISR);

        /* Set the priority. */
        CyIntSetPriority(Com_Block_TX_ISR_NUMBER, Com_Block_TX_ISR_PRIORITY);

    #endif /* Com_Block_INTERNAL_TX_INT_ENABLED */

    #if(Com_Block_INTERNAL_RX_INT_ENABLED)

        CyIntDisable(Com_Block_RX_ISR_NUMBER);

        /* Set the ISR to point to the Com_Block_isr Interrupt. */
        (void)CyIntSetVector(Com_Block_RX_ISR_NUMBER, &Com_Block_RX_ISR);

        /* Set the priority. */
        CyIntSetPriority(Com_Block_RX_ISR_NUMBER, Com_Block_RX_ISR_PRIORITY);

    #endif /* Com_Block_INTERNAL_RX_INT_ENABLED */

    /* Clear any stray data from the RX and TX FIFO */
    Com_Block_ClearFIFO();

    #if(Com_Block_RX_SOFTWARE_BUF_ENABLED)
        Com_Block_txBufferFull = 0u;
        Com_Block_rxBufferRead = 0u;
        Com_Block_rxBufferWrite = 0u;
    #endif /* Com_Block_RX_SOFTWARE_BUF_ENABLED */

    #if(Com_Block_TX_SOFTWARE_BUF_ENABLED)
        Com_Block_txBufferFull = 0u;
        Com_Block_txBufferRead = 0u;
        Com_Block_txBufferWrite = 0u;
    #endif /* Com_Block_TX_SOFTWARE_BUF_ENABLED */

    (void) Com_Block_ReadTxStatus(); /* Clear any pending status bits */
    (void) Com_Block_ReadRxStatus(); /* Clear any pending status bits */


    /* Configure the Initial interrupt mask */
    #if (Com_Block_TX_SOFTWARE_BUF_ENABLED)
        Com_Block_TX_STATUS_MASK_REG  = (Com_Block_TX_INIT_INTERRUPTS_MASK &
                                                (uint8)~Com_Block_STS_TX_FIFO_NOT_FULL);
    #else /* Com_Block_TX_SOFTWARE_BUF_ENABLED */
        Com_Block_TX_STATUS_MASK_REG  = Com_Block_TX_INIT_INTERRUPTS_MASK;
    #endif /* Com_Block_TX_SOFTWARE_BUF_ENABLED */

    Com_Block_RX_STATUS_MASK_REG  = Com_Block_RX_INIT_INTERRUPTS_MASK;

}


/*******************************************************************************
* Function Name: Com_Block_Enable
********************************************************************************
*
* Summary:
*  Enable SPIS component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Com_Block_Enable(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    Com_Block_COUNTER_CONTROL_REG |= Com_Block_CNTR_ENABLE;
    Com_Block_TX_STATUS_ACTL_REG |= Com_Block_INT_ENABLE;
    Com_Block_RX_STATUS_ACTL_REG |= Com_Block_INT_ENABLE;

    CyExitCriticalSection(enableInterrupts);

    #if(Com_Block_INTERNAL_TX_INT_ENABLED)
        CyIntEnable(Com_Block_TX_ISR_NUMBER);
    #endif /* Com_Block_INTERNAL_TX_INT_ENABLED */

    #if(Com_Block_INTERNAL_RX_INT_ENABLED)
        CyIntEnable(Com_Block_RX_ISR_NUMBER);
    #endif /* Com_Block_INTERNAL_RX_INT_ENABLED */
}


/*******************************************************************************
* Function Name: Com_Block_Start
********************************************************************************
*
* Summary:
*  Initialize and Enable the SPI Slave component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  Com_Block_initVar - used to check initial configuration, modified on
*  first function call.
*
* Theory:
*  Enable the clock input to enable operation.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Com_Block_Start(void) 
{
    if(Com_Block_initVar == 0u)
    {
        Com_Block_Init();
        Com_Block_initVar = 1u;
    }

    Com_Block_Enable();
}


/*******************************************************************************
* Function Name: Com_Block_Stop
********************************************************************************
*
* Summary:
*  Disable the SPI Slave component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Disable the internal interrupt if one is used.
*
*******************************************************************************/
void Com_Block_Stop(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    Com_Block_TX_STATUS_ACTL_REG &= (uint8)~Com_Block_INT_ENABLE;
    Com_Block_RX_STATUS_ACTL_REG &= (uint8)~Com_Block_INT_ENABLE;

    CyExitCriticalSection(enableInterrupts);

    #if(Com_Block_INTERNAL_TX_INT_ENABLED)
        CyIntDisable(Com_Block_TX_ISR_NUMBER);
    #endif /* Com_Block_INTERNAL_TX_INT_ENABLED */

    #if(Com_Block_INTERNAL_RX_INT_ENABLED)
        CyIntDisable(Com_Block_RX_ISR_NUMBER);
    #endif /* Com_Block_INTERNAL_RX_INT_ENABLED */
}


/*******************************************************************************
* Function Name: Com_Block_EnableTxInt
********************************************************************************
*
* Summary:
*  Enable internal Tx interrupt generation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Enable the internal Tx interrupt output -or- the interrupt component itself.
*
*******************************************************************************/
void Com_Block_EnableTxInt(void) 
{
    #if(Com_Block_INTERNAL_TX_INT_ENABLED)
        CyIntEnable(Com_Block_TX_ISR_NUMBER);
    #endif /* Com_Block_INTERNAL_TX_INT_ENABLED */
}


/*******************************************************************************
* Function Name: Com_Block_EnableRxInt
********************************************************************************
*
* Summary:
*  Enable internal Rx interrupt generation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Enable the internal Rx interrupt output -or- the interrupt component itself.
*
*******************************************************************************/
void Com_Block_EnableRxInt(void) 
{
    #if(Com_Block_INTERNAL_RX_INT_ENABLED)
        CyIntEnable(Com_Block_RX_ISR_NUMBER);
    #endif /* Com_Block_INTERNAL_RX_INT_ENABLED */
}


/*******************************************************************************
* Function Name: Com_Block_DisableTxInt
********************************************************************************
*
* Summary:
*  Disable internal Tx interrupt generation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Disable the internal Tx interrupt output -or- the interrupt component itself.
*
*******************************************************************************/
void Com_Block_DisableTxInt(void) 
{
    #if(Com_Block_INTERNAL_TX_INT_ENABLED)
        CyIntDisable(Com_Block_TX_ISR_NUMBER);
    #endif /* Com_Block_INTERNAL_TX_INT_ENABLED */
}


/*******************************************************************************
* Function Name: Com_Block_DisableRxInt
********************************************************************************
*
* Summary:
*  Disable internal Rx interrupt generation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Disable the internal Rx interrupt output -or- the interrupt component itself.
*
*******************************************************************************/
void Com_Block_DisableRxInt(void) 
{
    #if(Com_Block_INTERNAL_RX_INT_ENABLED)
        CyIntDisable(Com_Block_RX_ISR_NUMBER);
    #endif /* Com_Block_INTERNAL_RX_INT_ENABLED */
}


/*******************************************************************************
* Function Name: Com_Block_SetTxInterruptMode
********************************************************************************
*
* Summary:
*  Configure which status bits trigger an interrupt event.
*
* Parameters:
*  intSrc: An or'd combination of the desired status bit masks (defined in the
*  header file).
*
* Return:
*  None.
*
* Theory:
*  Enables the output of specific status bits to the interrupt controller.
*
*******************************************************************************/
void Com_Block_SetTxInterruptMode(uint8 intSrc) 
{
    Com_Block_TX_STATUS_MASK_REG  = intSrc;
}


/*******************************************************************************
* Function Name: Com_Block_SetRxInterruptMode
********************************************************************************
*
* Summary:
*  Configure which status bits trigger an interrupt event.
*
* Parameters:
*  intSrc: An or'd combination of the desired status bit masks (defined in the
*  header file).
*
* Return:
*  None.
*
* Theory:
*  Enables the output of specific status bits to the interrupt controller.
*
*******************************************************************************/
void Com_Block_SetRxInterruptMode(uint8 intSrc) 
{
    Com_Block_RX_STATUS_MASK_REG  = intSrc;
}


/*******************************************************************************
* Function Name: Com_Block_ReadTxStatus
********************************************************************************
*
* Summary:
*  Read the Tx status register for the component.
*
* Parameters:
*  None.
*
* Return:
*  Contents of the Tx status register.
*
* Global variables:
*  Com_Block_swStatusTx - used to store in software status register,
*  modified every function call - resets to zero.
*
* Theory:
*  Allows the user and the API to read the Tx status register for error
*  detection and flow control.
*
* Side Effects:
*  Clear Tx status register of the component.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 Com_Block_ReadTxStatus(void) 
{
    uint8 tmpStatus;

    #if (Com_Block_TX_SOFTWARE_BUF_ENABLED)

        Com_Block_DisableTxInt();

        tmpStatus = Com_Block_GET_STATUS_TX(Com_Block_swStatusTx);

        Com_Block_swStatusTx = 0u;

        /* Enable Interrupts */
        Com_Block_EnableTxInt();

    #else /* !Com_Block_TX_SOFTWARE_BUF_ENABLED */

        tmpStatus = Com_Block_TX_STATUS_REG;

    #endif /* Com_Block_TX_SOFTWARE_BUF_ENABLED */

    return(tmpStatus);
}


/*******************************************************************************
* Function Name: Com_Block_ReadRxStatus
********************************************************************************
*
* Summary:
*  Read the Rx status register for the component.
*
* Parameters:
*  None.
*
* Return:
*  Contents of the Rx status register.
*
* Global variables:
*  Com_Block_swStatusRx - used to store in software Rx status register,
*  modified every function call - resets to zero.
*
* Theory:
*  Allows the user and the API to read the Rx status register for error
*  detection and flow control.
*
* Side Effects:
*  Clear Rx status register of the component.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 Com_Block_ReadRxStatus(void) 
{
    uint8 tmpStatus;

    #if (Com_Block_RX_SOFTWARE_BUF_ENABLED)

        Com_Block_DisableRxInt();

        tmpStatus = Com_Block_GET_STATUS_RX(Com_Block_swStatusRx);

        Com_Block_swStatusRx = 0u;

        /* Enable Interrupts */
        Com_Block_EnableRxInt();

    #else /* !Com_Block_RX_SOFTWARE_BUF_ENABLED */

        tmpStatus = Com_Block_RX_STATUS_REG;

    #endif /* Com_Block_RX_SOFTWARE_BUF_ENABLED */

    return(tmpStatus);
}


/*******************************************************************************
* Function Name: Com_Block_WriteTxData
********************************************************************************
*
* Summary:
*  Write a byte of data to be sent across the SPI.
*
* Parameters:
*  txDataByte: The data value to send across the SPI.
*
* Return:
*  None.
*
* Global variables:
*  Com_Block_txBufferWrite - used for the account of the bytes which
*  have been written down in the TX software buffer, modified every function
*  call if TX Software Buffer is used.
*  Com_Block_txBufferRead - used for the account of the bytes which
*  have been read from the TX software buffer.
*  Com_Block_txBuffer[Com_Block_TX_BUFFER_SIZE] - used to store
*  data to sending, modified every function call if TX Software Buffer is used.
*
* Theory:
*  Allows the user to transmit any byte of data in a single transfer.
*
* Side Effects:
*  If this function is called again before the previous byte is finished then
*  the next byte will be appended to the transfer with no time between
*  the byte transfers. Clear Tx status register of the component.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Com_Block_WriteTxData(uint16 txData) 
{
    #if(Com_Block_TX_SOFTWARE_BUF_ENABLED)

        uint8 tempStatus;
        uint8 tmpTxBufferRead;

        /* Block if buffer is full, so we don't overwrite. */
        do
        {
            tmpTxBufferRead = Com_Block_txBufferRead;
            if (0u == tmpTxBufferRead)
            {
                tmpTxBufferRead = Com_Block_TX_BUFFER_SIZE - 1u;
            }
            else
            {
                tmpTxBufferRead--;
            }

        } while(tmpTxBufferRead == Com_Block_txBufferWrite);

        /* Disable Interrupt to protect variables that could change on interrupt. */
        Com_Block_DisableTxInt();

        tempStatus = Com_Block_GET_STATUS_TX(Com_Block_swStatusTx);
        Com_Block_swStatusTx = tempStatus;

        if((Com_Block_txBufferRead == Com_Block_txBufferWrite) &&
            (0u != (Com_Block_swStatusTx & Com_Block_STS_TX_FIFO_NOT_FULL)))
        {
            /* Add directly to the FIFO. */
            CY_SET_REG16(Com_Block_TXDATA_PTR, txData);
        }
        else
        {
            /* Add to the software buffer. */
            Com_Block_txBufferWrite++;
            if(Com_Block_txBufferWrite >= Com_Block_TX_BUFFER_SIZE)
            {
                Com_Block_txBufferWrite = 0u;
            }

            if(Com_Block_txBufferWrite == Com_Block_txBufferRead)
            {
                Com_Block_txBufferRead++;
                if(Com_Block_txBufferRead >= Com_Block_RX_BUFFER_SIZE)
                {
                    Com_Block_txBufferRead = 0u;
                }
                Com_Block_txBufferFull = 1u;
            }

            Com_Block_txBuffer[Com_Block_txBufferWrite] = txData;

            Com_Block_TX_STATUS_MASK_REG |= Com_Block_STS_TX_FIFO_NOT_FULL;
        }

        /* Enable Interrupt. */
        Com_Block_EnableTxInt();

    #else /* !Com_Block_TX_SOFTWARE_BUF_ENABLED*/

        
        while(0u == (Com_Block_TX_STATUS_REG & Com_Block_STS_TX_FIFO_NOT_FULL))
		{
			; /* Block while FIFO is full */
		}

        /* Then write the byte */
        CY_SET_REG16(Com_Block_TXDATA_PTR, txData);

    #endif /* Com_Block_TX_SOFTWARE_BUF_ENABLED */
}

#if(Com_Block_MODE_USE_ZERO != 0u)

    /*******************************************************************************
    * Function Name: Com_Block_WriteTxDataZero
    ********************************************************************************
    *
    * Summary:
    *  Write a byte zero of data to be sent across the SPI. This must be used in
    *  Mode 00 and 01 if the FIFO is empty and data is not being sent.
    *
    * Parameters:
    *  txDataByte: The data value to send across the SPI.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Allows the user to transmit any byte of data in a single transfer. Clear
    *  status register of the component.
    *
    *******************************************************************************/
    void Com_Block_WriteTxDataZero(uint16 txDataByte)
                                        
    {
        CY_SET_REG16(Com_Block_TXDATA_ZERO_PTR, txDataByte);
    }

#endif /* (Com_Block_MODE_USE_ZERO != 0u) */


/*******************************************************************************
* Function Name: Com_Block_ReadRxData
********************************************************************************
*
* Summary:
*  Read the next byte of data received across the SPI.
*
* Parameters:
*  None.
*
* Return:
*  The next byte of data read from the FIFO.
*
* Global variables:
*  Com_Block_rxBufferWrite - used for the account of the bytes which
*  have been written down in the RX software buffer.
*  Com_Block_rxBufferRead - used for the account of the bytes which
*  have been read from the RX software buffer, modified every function
*  call if RX Software Buffer is used.
*  Com_Block_rxBuffer[Com_Block_RX_BUFFER_SIZE] - used to store
*  received data.
*
* Theory:
*  Allows the user to read a byte of data received.
*
* Side Effects:
*  Will return invalid data if the FIFO is empty.  User should poll for FIFO
*  empty status before calling Read function.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint16 Com_Block_ReadRxData(void) 
{
    uint16 rxData;

    #if(Com_Block_RX_SOFTWARE_BUF_ENABLED)

        /* Disable Interrupt to protect variables that could change on interrupt. */
        Com_Block_DisableRxInt();

        if(Com_Block_rxBufferRead != Com_Block_rxBufferWrite)
        {
            if(Com_Block_rxBufferFull == 0u)
            {
                Com_Block_rxBufferRead++;
                if(Com_Block_rxBufferRead >= Com_Block_RX_BUFFER_SIZE)
                {
                    Com_Block_rxBufferRead = 0u;
                }
            }
            else
            {
                Com_Block_rxBufferFull = 0u;
            }
        }

        rxData = Com_Block_rxBuffer[Com_Block_rxBufferRead];

        /* Enable Interrupt. */
        Com_Block_EnableRxInt();

    #else /* !Com_Block_RX_SOFTWARE_BUF_ENABLED */

        rxData = CY_GET_REG16(Com_Block_RXDATA_PTR);

    #endif /* Com_Block_RX_SOFTWARE_BUF_ENABLED */

    return (rxData);

}


/*******************************************************************************
* Function Name: Com_Block_GetRxBufferSize
********************************************************************************
*
* Summary:
*  Returns the number of bytes/words of data currently held in the RX buffer.
*  If RX Software Buffer not used then function return 0 if FIFO empty or 1 if
*  FIFO not empty. In another case function return size of RX Software Buffer.
*
* Parameters:
*  None.
*
* Return:
*  Integer count of the number of bytes/words in the RX buffer.
*
* Global variables:
*  Com_Block_rxBufferWrite - used for the account of the bytes which
*  have been written down in the RX software buffer.
*  Com_Block_rxBufferRead - used for the account of the bytes which
*  have been read from the RX software buffer.
*
* Theory:
*  Allows the user to find out how full the RX Buffer is.
*
*******************************************************************************/
uint8 Com_Block_GetRxBufferSize(void) 
{
    uint8 size;

    #if(Com_Block_RX_SOFTWARE_BUF_ENABLED)

        /* Disable Interrupt to protect variables that could change on interrupt. */
        Com_Block_DisableRxInt();

        if(Com_Block_rxBufferRead == Com_Block_rxBufferWrite)
        {
            size = 0u; /* No data in RX buffer */
        }
        else if(Com_Block_rxBufferRead < Com_Block_rxBufferWrite)
        {
            size = (Com_Block_rxBufferWrite - Com_Block_rxBufferRead);
        }
        else
        {
            size = (Com_Block_RX_BUFFER_SIZE - Com_Block_rxBufferRead) + Com_Block_rxBufferWrite;
        }

        /* Enable interrupt. */
        Com_Block_EnableRxInt();

    #else /* !Com_Block_RX_SOFTWARE_BUF_ENABLED*/

        /* We can only know if there is data in the fifo. */
        size = ((Com_Block_RX_STATUS_REG & Com_Block_STS_RX_FIFO_NOT_EMPTY) != 0u) ? 1u : 0u;

    #endif /* Com_Block_RX_SOFTWARE_BUF_ENABLED */

    return (size);
}


/*******************************************************************************
* Function Name: Com_Block_GetTxBufferSize
********************************************************************************
*
* Summary:
*  Returns the number of bytes/words of data currently held in the TX buffer.
*  If TX Software Buffer not used then function return 0 - if FIFO empty, 1 - if
*  FIFO not full, 4 - if FIFO full. In another case function return size of TX
*  Software Buffer.
*
* Parameters:
*  None.
*
* Return:
*  Integer count of the number of bytes/words in the TX buffer.
*
* Global variables:
*  Com_Block_txBufferWrite - used for the account of the bytes which
*  have been written down in the TX software buffer.
*  Com_Block_txBufferRead - used for the account of the bytes which
*  have been read from the TX software buffer.
*
* Theory:
*  Allows the user to find out how full the TX Buffer is.
*
* Side Effects:
*  Clear status register of the component.
*
*******************************************************************************/
uint8  Com_Block_GetTxBufferSize(void) 
{
    uint8 size;

    #if(Com_Block_TX_SOFTWARE_BUF_ENABLED)

        /* Disable Interrupt to protect variables that could change on interrupt. */
        Com_Block_DisableTxInt();

        if(Com_Block_txBufferRead == Com_Block_txBufferWrite)
        {
            size = 0u;
        }
        else if(Com_Block_txBufferRead < Com_Block_txBufferWrite)
        {
            size = (Com_Block_txBufferWrite - Com_Block_txBufferRead);
        }
        else
        {
            size = (Com_Block_TX_BUFFER_SIZE - Com_Block_txBufferRead) + Com_Block_txBufferWrite;
        }

        /* Enable Interrupt. */
        Com_Block_EnableTxInt();

    #else /* !Com_Block_TX_SOFTWARE_BUF_ENABLED */

        size = Com_Block_TX_STATUS_REG;

        /* Is the fifo is full. */
        if((size & Com_Block_STS_TX_FIFO_EMPTY) != 0u)
        {
            size = 0u;
        }
        else if((size & Com_Block_STS_TX_FIFO_NOT_FULL) != 0u)
        {
            size = 1u;
        }
        else
        {
            size = 4u;
        }

    #endif /* Com_Block_TX_SOFTWARE_BUF_ENABLED */

    return (size);
}


/*******************************************************************************
* Function Name: Com_Block_ClearRxBuffer
********************************************************************************
*
* Summary:
*  Clear the RX RAM buffer by setting the read and write pointers both to zero.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  Com_Block_rxBufferWrite - used for the account of the bytes which
*  have been written down in the RX software buffer, modified every function
*  call - resets to zero.
*  Com_Block_rxBufferRead - used for the account of the bytes which
*  have been read from the RX software buffer, modified every function call -
*  resets to zero.
*
* Theory:
*  Setting the pointers to zero makes the system believe there is no data to
*  read and writing will resume at address 0 overwriting any data that may have
*  remained in the RAM.
*
* Side Effects:
*  Any received data not read from the RAM buffer will be lost when overwritten.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Com_Block_ClearRxBuffer(void) 
{
    /* Clear Hardware RX FIFO */
    while((Com_Block_RX_STATUS_REG & Com_Block_STS_RX_FIFO_NOT_EMPTY) != 0u)
    {
        CY_GET_REG16(Com_Block_RXDATA_PTR);
    }

    #if(Com_Block_RX_SOFTWARE_BUF_ENABLED)

        /* Disable interrupt to protect variables that could change on interrupt. */
        Com_Block_DisableRxInt();

        Com_Block_rxBufferRead  = 0u;
        Com_Block_rxBufferWrite = 0u;
		Com_Block_rxBufferFull  = 0u;
        /* Enable interrupt. */
        Com_Block_EnableRxInt();

    #endif /* Com_Block_RX_SOFTWARE_BUF_ENABLED */
}


/*******************************************************************************
* Function Name: Com_Block_ClearTxBuffer
********************************************************************************
*
* Summary:
*  Clear the TX RAM buffer by setting the read and write pointers both to zero.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  Com_Block_txBufferWrite - used for the account of the bytes which
*  have been written down in the TX software buffer, modified every function
*  call - resets to zero.
*  Com_Block_txBufferRead - used for the account of the bytes which
*  have been read from the TX software buffer, modified every function call -
*  resets to zero.
*
* Theory:
*  Setting the pointers to zero makes the system believe there is no data to
*  read and writing will resume at address 0 overwriting any data that may have
*  remained in the RAM.
*
* Side Effects:
*  Any data not yet transmitted from the RAM buffer will be lost when
*  overwritten.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Com_Block_ClearTxBuffer(void) 
{
    uint8 enableInterrupts;

    /* Clear Hardware TX FIFO */
    enableInterrupts = CyEnterCriticalSection();

    #if(Com_Block_DATA_WIDTH <= 8u)

        /* Clear TX FIFO */
        Com_Block_TX_AUX_CONTROL_DP0_REG |= (uint8)Com_Block_FIFO_CLR;
        Com_Block_TX_AUX_CONTROL_DP0_REG &= (uint8)~Com_Block_FIFO_CLR;

    #else

        /* Clear TX FIFO */
        Com_Block_TX_AUX_CONTROL_DP0_REG |= (uint8)Com_Block_FIFO_CLR;
        Com_Block_TX_AUX_CONTROL_DP0_REG &= (uint8)~Com_Block_FIFO_CLR;
        Com_Block_TX_AUX_CONTROL_DP1_REG |= (uint8)Com_Block_FIFO_CLR;
        Com_Block_TX_AUX_CONTROL_DP1_REG &= (uint8)~Com_Block_FIFO_CLR;

    #endif /* Com_Block_DATA_WIDTH > 8u */

    CyExitCriticalSection(enableInterrupts);

    #if(Com_Block_TX_SOFTWARE_BUF_ENABLED)

        /* Disable Interrupt to protect variables that could change on interrupt. */
        Com_Block_DisableTxInt();

        Com_Block_txBufferRead  = 0u;
        Com_Block_txBufferWrite = 0u;
		Com_Block_txBufferFull  = 0u;
		
        /* If Buffer is empty then disable TX FIFO status interrupt */
        Com_Block_TX_STATUS_MASK_REG &= (uint8)~Com_Block_STS_TX_FIFO_NOT_FULL;

        /* Enable Interrupt. */
        Com_Block_EnableTxInt();

    #endif /* Com_Block_TX_SOFTWARE_BUF_ENABLED */
}


#if (Com_Block_BIDIRECTIONAL_MODE != 0u)

    /*******************************************************************************
    * Function Name: Com_Block_TxEnable
    ********************************************************************************
    *
    * Summary:
    *  If the SPI Slave is configured to use a single bi-directional pin then this
    *  will set the bi-directional pin to transmit.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void Com_Block_TxEnable(void) 
    {
            Com_Block_CONTROL_REG |= Com_Block_CTRL_TX_SIGNAL_EN;
    }


    /*******************************************************************************
    * Function Name: Com_Block_TxDisable
    ********************************************************************************
    *
    * Summary:
    *  If the SPI Slave is configured to use a single bi-directional pin then this
    *  will set the bi-directional pin to receive.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void Com_Block_TxDisable(void) 
    {
            Com_Block_CONTROL_REG &= (uint8)~Com_Block_CTRL_TX_SIGNAL_EN;
    }

#endif /* Com_Block_BIDIRECTIONAL_MODE != 0u */


/*******************************************************************************
* Function Name: Com_Block_PutArray
********************************************************************************
*
* Summary:
*  Write available data from RAM/ROM to the TX buffer while space is available
*  in the TX buffer. Keep trying until all data is passed to the TX buffer. If
*  used Mode 00 or 01 before PutArray() function should be called
*  WriteTxDataZero() function.
*
* Parameters:
*  *buffer: Pointer to the location in RAM containing the data to send
*  byteCount: The number of bytes to move to the transmit buffer.
*
* Return:
*  None.
*
* Side Effects:
*  Will stay in this routine until all data has been sent.  May get locked in
*  this loop if data is not being initiated by the master if there is not
*  enough room in the TX FIFO.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Com_Block_PutArray(const uint16 buffer[], uint8 byteCount)
                                                                    
{
    uint8 bufIndex;
    bufIndex = 0u;

    while(byteCount > 0u)
    {
        Com_Block_WriteTxData(buffer[bufIndex]);
        bufIndex++;
        byteCount--;
    }
}


/*******************************************************************************
* Function Name: Com_Block_ClearFIFO
********************************************************************************
*
* Summary:
*  Clear the RX and TX FIFO's of all data for a fresh start.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  Clear status register of the component.
*
*******************************************************************************/
void Com_Block_ClearFIFO(void) 
{
    uint8 enableInterrupts;

    while((Com_Block_RX_STATUS_REG & Com_Block_STS_RX_FIFO_NOT_EMPTY) != 0u)
    {
        CY_GET_REG16(Com_Block_RXDATA_PTR);
    }

    enableInterrupts = CyEnterCriticalSection();

    #if(Com_Block_DATA_WIDTH <= 8u)

        /* Clear TX FIFO */
        Com_Block_TX_AUX_CONTROL_DP0_REG |= (uint8)Com_Block_FIFO_CLR;
        Com_Block_TX_AUX_CONTROL_DP0_REG &= (uint8)~Com_Block_FIFO_CLR;

    #else

        /* Clear TX FIFO */
        Com_Block_TX_AUX_CONTROL_DP0_REG |= (uint8)Com_Block_FIFO_CLR;
        Com_Block_TX_AUX_CONTROL_DP0_REG &= (uint8)~Com_Block_FIFO_CLR;
        Com_Block_TX_AUX_CONTROL_DP1_REG |= (uint8)Com_Block_FIFO_CLR;
        Com_Block_TX_AUX_CONTROL_DP1_REG &= (uint8)~Com_Block_FIFO_CLR;

    #endif /* Com_Block_DATA_WIDTH <= 8u */

    CyExitCriticalSection(enableInterrupts);
}


/* Following functions are for version Compatibility, they are obsolete.
*  Please do not use it in new projects.
*/


/*******************************************************************************
* Function Name: Com_Block_EnableInt
********************************************************************************
*
* Summary:
*  Enable internal interrupt generation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Enable the internal interrupt output -or- the interrupt component itself.
*
*******************************************************************************/
void Com_Block_EnableInt(void) 
{
    #if(Com_Block_INTERNAL_TX_INT_ENABLED)
        CyIntEnable(Com_Block_TX_ISR_NUMBER);
    #endif /* Com_Block_INTERNAL_TX_INT_ENABLED */

    #if(Com_Block_INTERNAL_RX_INT_ENABLED)
        CyIntEnable(Com_Block_RX_ISR_NUMBER);
    #endif /* Com_Block_INTERNAL_RX_INT_ENABLED */
}


/*******************************************************************************
* Function Name: Com_Block_DisableInt
********************************************************************************
*
* Summary:
*  Disable internal interrupt generation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Theory:
*  Disable the internal interrupt output -or- the interrupt component itself.
*
*******************************************************************************/
void Com_Block_DisableInt(void) 
{
    #if(Com_Block_INTERNAL_TX_INT_ENABLED)
        CyIntDisable(Com_Block_TX_ISR_NUMBER);
    #endif /* Com_Block_INTERNAL_TX_INT_ENABLED */

    #if(Com_Block_INTERNAL_RX_INT_ENABLED)
        CyIntDisable(Com_Block_RX_ISR_NUMBER);
    #endif /* Com_Block_INTERNAL_RX_INT_ENABLED */
}


/*******************************************************************************
* Function Name: Com_Block_SetInterruptMode
********************************************************************************
*
* Summary:
*  Configure which status bits trigger an interrupt event.
*
* Parameters:
*  intSrc: An or'd combination of the desired status bit masks (defined in the
*  header file).
*
* Return:
*  None.
*
* Theory:
*  Enables the output of specific status bits to the interrupt controller.
*
*******************************************************************************/
void Com_Block_SetInterruptMode(uint8 intSrc) 
{
    Com_Block_TX_STATUS_MASK_REG  = intSrc;
    Com_Block_RX_STATUS_MASK_REG  = intSrc;
}


/*******************************************************************************
* Function Name: Com_Block_ReadStatus
********************************************************************************
*
* Summary:
*  Read the status register for the component.
*
* Parameters:
*  None.
*
* Return:
*  Contents of the status register.
*
* Global variables:
*  Com_Block_swStatus - used to store in software status register,
*  modified every function call - resets to zero.
*
* Theory:
*  Allows the user and the API to read the status register for error detection
*  and flow control.
*
* Side Effects:
*  Clear status register of the component.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 Com_Block_ReadStatus(void) 
{
    uint8 tmpStatus;

    #if ((Com_Block_TX_SOFTWARE_BUF_ENABLED) || (Com_Block_RX_SOFTWARE_BUF_ENABLED))

        Com_Block_DisableInt();

        tmpStatus = Com_Block_GET_STATUS_TX(Com_Block_swStatusTx) |
              (Com_Block_GET_STATUS_RX(Com_Block_swStatusRx) & (uint8)~Com_Block_STS_RX_FIFO_FULL);

        Com_Block_swStatusTx = 0u;
        Com_Block_swStatusRx = 0u;

        /* Enable Interrupts */
        Com_Block_EnableInt();

    #else /* !((Com_Block_TX_SOFTWARE_BUF_ENABLED) || (Com_Block_RX_SOFTWARE_BUF_ENABLED)) */

        tmpStatus = Com_Block_TX_STATUS_REG | (Com_Block_RX_STATUS_REG &
                                                      (uint8)~Com_Block_STS_RX_FIFO_FULL);

    #endif /* (Com_Block_TX_SOFTWARE_BUF_ENABLED) || (Com_Block_RX_SOFTWARE_BUF_ENABLED) */

    return(tmpStatus);
}


/* [] END OF FILE */
