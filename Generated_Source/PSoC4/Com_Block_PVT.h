/*******************************************************************************
* File Name: .h
* Version 2.60
*
* Description:
*  This private header file contains internal definitions for the SPIS
*  component. Do not use these definitions directly in your application.
*
* Note:
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SPIS_PVT_Com_Block_H)
#define CY_SPIS_PVT_Com_Block_H

#include "Com_Block.h"


/**********************************
*   Functions with external linkage
**********************************/


/**********************************
*   Variables with external linkage
**********************************/
extern volatile uint8 Com_Block_swStatusTx;
extern volatile uint8 Com_Block_swStatusRx;

#if (Com_Block_RX_SOFTWARE_BUF_ENABLED)

    extern volatile uint16 Com_Block_rxBuffer[Com_Block_RX_BUFFER_SIZE];
    extern volatile uint8 Com_Block_rxBufferRead;
    extern volatile uint8 Com_Block_rxBufferWrite;
    extern volatile uint8 Com_Block_rxBufferFull;

#endif /* Com_Block_RX_SOFTWARE_BUF_ENABLED */

#if (Com_Block_TX_SOFTWARE_BUF_ENABLED)

    extern volatile uint16 Com_Block_txBuffer[Com_Block_TX_BUFFER_SIZE];
    extern volatile uint8 Com_Block_txBufferRead;
    extern volatile uint8 Com_Block_txBufferWrite;
    extern volatile uint8 Com_Block_txBufferFull;

#endif /* Com_Block_TX_SOFTWARE_BUF_ENABLED */

#endif /* CY_SPIS_PVT_Com_Block_H */


/* [] END OF FILE */
