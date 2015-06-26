/*******************************************************************************
* File Name: .h
* Version 2.40
*
* Description:
*  This private header file contains internal definitions for the SPIM
*  component. Do not use these definitions directly in your application.
*
* Note:
*
********************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SPIM_PVT_GLCD_SPIM_UDB_H)
#define CY_SPIM_PVT_GLCD_SPIM_UDB_H

#include "GLCD_SPIM_UDB.h"


/**********************************
*   Functions with external linkage
**********************************/


/**********************************
*   Variables with external linkage
**********************************/

extern volatile uint8 GLCD_SPIM_UDB_swStatusTx;
extern volatile uint8 GLCD_SPIM_UDB_swStatusRx;

#if(GLCD_SPIM_UDB_TX_SOFTWARE_BUF_ENABLED)
    extern volatile uint16 GLCD_SPIM_UDB_txBuffer[GLCD_SPIM_UDB_TX_BUFFER_SIZE];
    extern volatile uint8 GLCD_SPIM_UDB_txBufferRead;
    extern volatile uint8 GLCD_SPIM_UDB_txBufferWrite;
    extern volatile uint8 GLCD_SPIM_UDB_txBufferFull;
#endif /* (GLCD_SPIM_UDB_TX_SOFTWARE_BUF_ENABLED) */

#if(GLCD_SPIM_UDB_RX_SOFTWARE_BUF_ENABLED)
    extern volatile uint16 GLCD_SPIM_UDB_rxBuffer[GLCD_SPIM_UDB_RX_BUFFER_SIZE];
    extern volatile uint8 GLCD_SPIM_UDB_rxBufferRead;
    extern volatile uint8 GLCD_SPIM_UDB_rxBufferWrite;
    extern volatile uint8 GLCD_SPIM_UDB_rxBufferFull;
#endif /* (GLCD_SPIM_UDB_RX_SOFTWARE_BUF_ENABLED) */

#endif /* CY_SPIM_PVT_GLCD_SPIM_UDB_H */


/* [] END OF FILE */
