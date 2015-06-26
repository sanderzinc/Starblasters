/*******************************************************************************
* File Name: GLCD_SPIM_SCB_SPI.c
* Version 1.0
*
* Description:
*  This file provides the source code to the API for the SCB Component in
*  SPI mode.
*
* Note:
*
*******************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "GLCD_SPIM_SCB_PVT.h"
#include "GLCD_SPIM_SCB_SPI_UART_PVT.h"

#if(GLCD_SPIM_SCB_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Config Structure Initialization
    ***************************************/

    const GLCD_SPIM_SCB_SPI_INIT_STRUCT GLCD_SPIM_SCB_configSpi =
    {
        GLCD_SPIM_SCB_SPI_MODE,
        GLCD_SPIM_SCB_SPI_SUB_MODE,
        GLCD_SPIM_SCB_SPI_CLOCK_MODE,
        GLCD_SPIM_SCB_SPI_OVS_FACTOR,
        GLCD_SPIM_SCB_SPI_MEDIAN_FILTER_ENABLE,
        GLCD_SPIM_SCB_SPI_LATE_MISO_SAMPLE_ENABLE,
        GLCD_SPIM_SCB_SPI_WAKE_ENABLE,
        GLCD_SPIM_SCB_SPI_RX_DATA_BITS_NUM,
        GLCD_SPIM_SCB_SPI_TX_DATA_BITS_NUM,
        GLCD_SPIM_SCB_SPI_BITS_ORDER,
        GLCD_SPIM_SCB_SPI_TRANSFER_SEPARATION,
        0u,
        NULL,
        0u,
        NULL,
        GLCD_SPIM_SCB_SPI_INTERRUPT_ENABLE,
        GLCD_SPIM_SCB_SPI_INTR_RX_MASK,
        GLCD_SPIM_SCB_SPI_RX_TRIGGER_LEVEL,
        GLCD_SPIM_SCB_SPI_INTR_TX_MASK,
        GLCD_SPIM_SCB_SPI_TX_TRIGGER_LEVEL
    };


    /*******************************************************************************
    * Function Name: GLCD_SPIM_SCB_SpiInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for SPI operation.
    *
    * Parameters:
    *  config:  Pointer to a structure that contains the following ordered list of
    *           fields. These fields match the selections available in the
    *           customizer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void GLCD_SPIM_SCB_SpiInit(const GLCD_SPIM_SCB_SPI_INIT_STRUCT *config)
    {
        if(NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due bad fucntion parameter */
        }
        else
        {
            /* Configure pins */
            GLCD_SPIM_SCB_SetPins(GLCD_SPIM_SCB_SCB_MODE_SPI, config->mode, GLCD_SPIM_SCB_DUMMY_PARAM);

            /* Store internal configuration */
            GLCD_SPIM_SCB_scbMode       = (uint8) GLCD_SPIM_SCB_SCB_MODE_SPI;
            GLCD_SPIM_SCB_scbEnableWake = (uint8) config->enableWake;

            /* Set RX direction internal variables */
            GLCD_SPIM_SCB_rxBuffer      =         config->rxBuffer;
            GLCD_SPIM_SCB_rxDataBits    = (uint8) config->rxDataBits;
            GLCD_SPIM_SCB_rxBufferSize  = (uint8) config->rxBufferSize;

            /* Set TX direction internal variables */
            GLCD_SPIM_SCB_txBuffer      =         config->txBuffer;
            GLCD_SPIM_SCB_txDataBits    = (uint8) config->txDataBits;
            GLCD_SPIM_SCB_txBufferSize  = (uint8) config->txBufferSize;


            /* Configure SPI interface */
            GLCD_SPIM_SCB_CTRL_REG     = GLCD_SPIM_SCB_GET_CTRL_OVS(config->oversample)        |
                                            GLCD_SPIM_SCB_GET_CTRL_EC_AM_MODE(config->enableWake) |
                                            GLCD_SPIM_SCB_CTRL_SPI;

            GLCD_SPIM_SCB_SPI_CTRL_REG = GLCD_SPIM_SCB_GET_SPI_CTRL_CONTINUOUS    (config->transferSeperation)  |
                                            GLCD_SPIM_SCB_GET_SPI_CTRL_SELECT_PRECEDE(config->submode & 
                                                                          GLCD_SPIM_SCB_SPI_MODE_TI_PRECEDES_MASK) |
                                            GLCD_SPIM_SCB_GET_SPI_CTRL_SCLK_MODE     (config->sclkMode)            |
                                            GLCD_SPIM_SCB_GET_SPI_CTRL_LATE_MISO_SAMPLE(config->enableLateSampling)|
                                            GLCD_SPIM_SCB_GET_SPI_CTRL_SUB_MODE      (config->submode)             |
                                            GLCD_SPIM_SCB_GET_SPI_CTRL_MASTER_MODE   (config->mode);

            /* Configure RX direction */
            GLCD_SPIM_SCB_RX_CTRL_REG     =  GLCD_SPIM_SCB_GET_RX_CTRL_DATA_WIDTH(config->rxDataBits)         |
                                                GLCD_SPIM_SCB_GET_RX_CTRL_BIT_ORDER (config->bitOrder)           |
                                                GLCD_SPIM_SCB_GET_RX_CTRL_MEDIAN    (config->enableMedianFilter) |
                                                GLCD_SPIM_SCB_SPI_RX_CTRL;

            GLCD_SPIM_SCB_RX_FIFO_CTRL_REG = GLCD_SPIM_SCB_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);

            /* Configure TX direction */
            GLCD_SPIM_SCB_TX_CTRL_REG      = GLCD_SPIM_SCB_GET_TX_CTRL_DATA_WIDTH(config->txDataBits) |
                                                GLCD_SPIM_SCB_GET_TX_CTRL_BIT_ORDER (config->bitOrder)   |
                                                GLCD_SPIM_SCB_SPI_TX_CTRL;

            GLCD_SPIM_SCB_TX_FIFO_CTRL_REG = GLCD_SPIM_SCB_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(config->txTriggerLevel);

            /* Configure interrupt sources */
            GLCD_SPIM_SCB_INTR_I2C_EC_MASK_REG = GLCD_SPIM_SCB_NO_INTR_SOURCES;
            GLCD_SPIM_SCB_INTR_SPI_EC_MASK_REG = GLCD_SPIM_SCB_NO_INTR_SOURCES;
            GLCD_SPIM_SCB_INTR_SLAVE_MASK_REG  = GLCD_SPIM_SCB_GET_SPI_INTR_SLAVE_MASK(config->rxInterruptMask);
            GLCD_SPIM_SCB_INTR_MASTER_MASK_REG = GLCD_SPIM_SCB_GET_SPI_INTR_MASTER_MASK(config->txInterruptMask);
            GLCD_SPIM_SCB_INTR_RX_MASK_REG     = GLCD_SPIM_SCB_GET_SPI_INTR_RX_MASK(config->rxInterruptMask);
            GLCD_SPIM_SCB_INTR_TX_MASK_REG     = GLCD_SPIM_SCB_GET_SPI_INTR_TX_MASK(config->txInterruptMask);

            /* Configure interrupt source */
            GLCD_SPIM_SCB_SCB_IRQ_StartEx(&GLCD_SPIM_SCB_SPI_UART_ISR);
            if(0u == config->enableInterrupt)
            {
                GLCD_SPIM_SCB_SCB_IRQ_Disable();
            }


            /* Clear RX buffer indexes */
            GLCD_SPIM_SCB_rxBufferHead     = 0u;
            GLCD_SPIM_SCB_rxBufferTail     = 0u;
            GLCD_SPIM_SCB_rxBufferOverflow = 0u;

            /* Clrea TX buffer indexes */
            GLCD_SPIM_SCB_txBufferHead = 0u;
            GLCD_SPIM_SCB_txBufferTail = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: GLCD_SPIM_SCB_SpiInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for SPI operation.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void GLCD_SPIM_SCB_SpiInit(void)
    {
        /* Configure SPI interface */
        GLCD_SPIM_SCB_CTRL_REG     = GLCD_SPIM_SCB_SPI_DEFAULT_CTRL;
        GLCD_SPIM_SCB_SPI_CTRL_REG = GLCD_SPIM_SCB_SPI_DEFAULT_SPI_CTRL;

        /* Configure TX and RX direction */
        GLCD_SPIM_SCB_RX_CTRL_REG      = GLCD_SPIM_SCB_SPI_DEFAULT_RX_CTRL;
        GLCD_SPIM_SCB_RX_FIFO_CTRL_REG = GLCD_SPIM_SCB_SPI_DEFAULT_RX_FIFO_CTRL;

        /* Configure TX and RX direction */
        GLCD_SPIM_SCB_TX_CTRL_REG      = GLCD_SPIM_SCB_SPI_DEFAULT_TX_CTRL;
        GLCD_SPIM_SCB_TX_FIFO_CTRL_REG = GLCD_SPIM_SCB_SPI_DEFAULT_TX_FIFO_CTRL;

        /* Configure interrupt sources */
        GLCD_SPIM_SCB_INTR_I2C_EC_MASK_REG = GLCD_SPIM_SCB_SPI_DEFAULT_INTR_I2C_EC_MASK;
        GLCD_SPIM_SCB_INTR_SPI_EC_MASK_REG = GLCD_SPIM_SCB_SPI_DEFAULT_INTR_SPI_EC_MASK;
        GLCD_SPIM_SCB_INTR_SLAVE_MASK_REG  = GLCD_SPIM_SCB_SPI_DEFAULT_INTR_SLAVE_MASK;
        GLCD_SPIM_SCB_INTR_MASTER_MASK_REG = GLCD_SPIM_SCB_SPI_DEFAULT_INTR_MASTER_MASK;
        GLCD_SPIM_SCB_INTR_RX_MASK_REG     = GLCD_SPIM_SCB_SPI_DEFAULT_INTR_RX_MASK;
        GLCD_SPIM_SCB_INTR_TX_MASK_REG     = GLCD_SPIM_SCB_SPI_DEFAULT_INTR_TX_MASK;


        /* Configure interrupt source */
        #if(GLCD_SPIM_SCB_SCB_IRQ_INTERNAL)
            GLCD_SPIM_SCB_SCB_IRQ_StartEx(&GLCD_SPIM_SCB_SPI_UART_ISR);

            #if(GLCD_SPIM_SCB_SPI_INTERRUPT_DISABLE)
                GLCD_SPIM_SCB_SCB_IRQ_Disable();
            #endif /* (GLCD_SPIM_SCB_SPI_INTERRUPT_DISABLE) */
        #endif /* (GLCD_SPIM_SCB_SCB_IRQ_INTERNAL) */


        #if(GLCD_SPIM_SCB_INTERNAL_RX_SW_BUFFER_CONST)
            GLCD_SPIM_SCB_rxBufferHead     = 0u;
            GLCD_SPIM_SCB_rxBufferTail     = 0u;
            GLCD_SPIM_SCB_rxBufferOverflow = 0u;
        #endif /* (GLCD_SPIM_SCB_INTERNAL_RX_SW_BUFFER_CONST) */

        #if(GLCD_SPIM_SCB_INTERNAL_TX_SW_BUFFER_CONST)
            GLCD_SPIM_SCB_txBufferHead = 0u;
            GLCD_SPIM_SCB_txBufferTail = 0u;
        #endif /* (GLCD_SPIM_SCB_INTERNAL_TX_SW_BUFFER_CONST) */
    }

#endif /* (GLCD_SPIM_SCB_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: GLCD_SPIM_SCB_SetActiveSlaveSelect
********************************************************************************
*
* Summary:
*  Selects one of the four SPI slave select signals.
*  The component should be in one of the following states to change the active
*  slave select signal source correctly:
*   - the component is disabled
*   - the component has completed all transactions (TX FIFO is empty and the
*     SpiDone flag is set)
*  This function does not check that these conditions are met.
*  At initialization time the active slave select line is slave select 0.
*
* Parameters:
*  activeSelect: The four lines available to utilize Slave Select function.
*
* Return:
*  None
*
*******************************************************************************/
void GLCD_SPIM_SCB_SpiSetActiveSlaveSelect(uint32 activeSelect)
{
    uint32 spiCtrl;
    
    spiCtrl = GLCD_SPIM_SCB_SPI_CTRL_REG;
    
    spiCtrl &= (uint32) ~GLCD_SPIM_SCB_SPI_CTRL_SLAVE_SELECT_MASK; /* Clear SS bits */
    spiCtrl |= (uint32)  GLCD_SPIM_SCB_GET_SPI_CTRL_SS(activeSelect);
    
    GLCD_SPIM_SCB_SPI_CTRL_REG = spiCtrl;
}


/*******************************************************************************
* Function Name: GLCD_SPIM_SCB_SpiSaveConfig
********************************************************************************
*
* Summary:
*  Wakeup disabled: does nothing.
*  Wakeup  enabled: clears SCB_backup.enableState to keep component enabled
*  while DeepSleep. The SCB_INTR_SPI_EC_WAKE_UP enabled while initialization
*  and tracks in active mode therefore it does not require to be cleared.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  None
*
*******************************************************************************/
void GLCD_SPIM_SCB_SpiSaveConfig(void)
{
    #if(GLCD_SPIM_SCB_CHECK_SPI_WAKE_ENABLE)
    {
        GLCD_SPIM_SCB_backup.enableState = 0u; /* Keep SCB enabled */
        
        /* Clear wake-up before enable */
        GLCD_SPIM_SCB_ClearSpiExtClkInterruptSource(GLCD_SPIM_SCB_INTR_SPI_EC_WAKE_UP);
        
        /* Enable interrupt to wakeup the device */
        GLCD_SPIM_SCB_SetSpiExtClkInterruptMode(GLCD_SPIM_SCB_INTR_SPI_EC_WAKE_UP);
    }
    #endif
}


/*******************************************************************************
* Function Name: GLCD_SPIM_SCB_SpiRestoreConfig
********************************************************************************
*
* Summary:
*  Does nothing.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  None
*
*******************************************************************************/
void GLCD_SPIM_SCB_SpiRestoreConfig(void)
{
    #if(GLCD_SPIM_SCB_CHECK_SPI_WAKE_ENABLE)
    {
        /* Disable interrupt to wakeup the device */
        GLCD_SPIM_SCB_SetSpiExtClkInterruptMode(GLCD_SPIM_SCB_NO_INTR_SOURCES);
    }
    #endif
}


/* [] END OF FILE */
