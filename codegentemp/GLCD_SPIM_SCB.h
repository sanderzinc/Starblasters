/*******************************************************************************
* File Name: GLCD_SPIM_SCB.h
* Version 1.0
*
* Description:
*  This file provides constants and parameter values for the SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_GLCD_SPIM_SCB_H)
#define CY_SCB_GLCD_SPIM_SCB_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h"


/***************************************
*  Conditional Compilation Parameters
****************************************/

#define GLCD_SPIM_SCB_SCB_MODE                     (2u)

/* SCB modes enum */
#define GLCD_SPIM_SCB_SCB_MODE_I2C                 (0x01u)
#define GLCD_SPIM_SCB_SCB_MODE_SPI                 (0x02u)
#define GLCD_SPIM_SCB_SCB_MODE_UART                (0x04u)
#define GLCD_SPIM_SCB_SCB_MODE_UNCONFIG            (0xFFu)

/* Define run time operation mode */
#define GLCD_SPIM_SCB_SCB_MODE_I2C_RUNTM_CFG       (GLCD_SPIM_SCB_SCB_MODE_I2C       == GLCD_SPIM_SCB_scbMode)
#define GLCD_SPIM_SCB_SCB_MODE_SPI_RUNTM_CFG       (GLCD_SPIM_SCB_SCB_MODE_SPI       == GLCD_SPIM_SCB_scbMode)
#define GLCD_SPIM_SCB_SCB_MODE_UART_RUNTM_CFG      (GLCD_SPIM_SCB_SCB_MODE_UART      == GLCD_SPIM_SCB_scbMode)
#define GLCD_SPIM_SCB_SCB_MODE_UNCONFIG_RUNTM_CFG  (GLCD_SPIM_SCB_SCB_MODE_UNCONFIG  == GLCD_SPIM_SCB_scbMode)

/* Condition compilation depends on operation mode: unconfigured implies apply to all modes */
#define GLCD_SPIM_SCB_SCB_MODE_I2C_CONST_CFG       (GLCD_SPIM_SCB_SCB_MODE_I2C       == GLCD_SPIM_SCB_SCB_MODE)
#define GLCD_SPIM_SCB_SCB_MODE_SPI_CONST_CFG       (GLCD_SPIM_SCB_SCB_MODE_SPI       == GLCD_SPIM_SCB_SCB_MODE)
#define GLCD_SPIM_SCB_SCB_MODE_UART_CONST_CFG      (GLCD_SPIM_SCB_SCB_MODE_UART      == GLCD_SPIM_SCB_SCB_MODE)
#define GLCD_SPIM_SCB_SCB_MODE_UNCONFIG_CONST_CFG  (GLCD_SPIM_SCB_SCB_MODE_UNCONFIG  == GLCD_SPIM_SCB_SCB_MODE)

/* Condition compilation for includes */
#define GLCD_SPIM_SCB_SCB_MODE_I2C_INC       (0u !=(GLCD_SPIM_SCB_SCB_MODE_I2C       & GLCD_SPIM_SCB_SCB_MODE))
#define GLCD_SPIM_SCB_SCB_MODE_SPI_INC       (0u !=(GLCD_SPIM_SCB_SCB_MODE_SPI       & GLCD_SPIM_SCB_SCB_MODE))
#define GLCD_SPIM_SCB_SCB_MODE_UART_INC      (0u !=(GLCD_SPIM_SCB_SCB_MODE_UART      & GLCD_SPIM_SCB_SCB_MODE))

/* Interrupts remove options */
#define GLCD_SPIM_SCB_REMOVE_SCB_IRQ             (1u)
#define GLCD_SPIM_SCB_SCB_IRQ_INTERNAL           (0u == GLCD_SPIM_SCB_REMOVE_SCB_IRQ)

#define GLCD_SPIM_SCB_REMOVE_UART_RX_WAKEUP_IRQ  (1u)
#define GLCD_SPIM_SCB_UART_RX_WAKEUP_IRQ         (0u == GLCD_SPIM_SCB_REMOVE_UART_RX_WAKEUP_IRQ)

/* SCB interrupt enum */
#define GLCD_SPIM_SCB_SCB_INTR_MODE_NONE     (0u)
#define GLCD_SPIM_SCB_SCB_INTR_MODE_INTERNAL (1u)
#define GLCD_SPIM_SCB_SCB_INTR_MODE_EXTERNAL (2u)

/* Bootloader communication interface enable */
#define GLCD_SPIM_SCB_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_GLCD_SPIM_SCB) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))


/***************************************
*       Includes
****************************************/

#include "GLCD_SPIM_SCB_PINS.h"

#if(GLCD_SPIM_SCB_SCB_IRQ_INTERNAL)
    #include "GLCD_SPIM_SCB_SCB_IRQ.h"
#endif /* (GLCD_SPIM_SCB_SCB_IRQ_INTERNAL) */

#if(GLCD_SPIM_SCB_UART_RX_WAKEUP_IRQ)
    #include "GLCD_SPIM_SCB_RX_WAKEUP_IRQ.h"
#endif /* (GLCD_SPIM_SCB_UART_RX_WAKEUP_IRQ) */


/***************************************
*       Type Definitions
***************************************/

typedef struct
{
    uint8 enableState;
} GLCD_SPIM_SCB_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

/* Start and Stop APIs */
void GLCD_SPIM_SCB_Init(void);
void GLCD_SPIM_SCB_Enable(void);
void GLCD_SPIM_SCB_Start(void);
void GLCD_SPIM_SCB_Stop(void);

/* Sleep and Wakeup APis */
void GLCD_SPIM_SCB_Sleep(void);
void GLCD_SPIM_SCB_Wakeup(void);

/* Customer interrupt handler */
void GLCD_SPIM_SCB_SetCustomInterruptHandler(cyisraddress func);

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (GLCD_SPIM_SCB_BTLDR_COMM_ENABLED)

    /* Bootloader Physical layer functions */
    void GLCD_SPIM_SCB_CyBtldrCommStart(void);
    void GLCD_SPIM_SCB_CyBtldrCommStop (void);
    void GLCD_SPIM_SCB_CyBtldrCommReset(void);
    cystatus GLCD_SPIM_SCB_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus GLCD_SPIM_SCB_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    #if(CYDEV_BOOTLOADER_IO_COMP == CyBtldr_GLCD_SPIM_SCB)
        #define CyBtldrCommStart    GLCD_SPIM_SCB_CyBtldrCommStart
        #define CyBtldrCommStop     GLCD_SPIM_SCB_CyBtldrCommStop
        #define CyBtldrCommReset    GLCD_SPIM_SCB_CyBtldrCommReset
        #define CyBtldrCommWrite    GLCD_SPIM_SCB_CyBtldrCommWrite
        #define CyBtldrCommRead     GLCD_SPIM_SCB_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_GLCD_SPIM_SCB) */

#endif /*defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_GLCD_SPIM_SCB) || \
                                                     (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface)) */

/* Interface to internal interrupt component */
#if(GLCD_SPIM_SCB_SCB_IRQ_INTERNAL)
    #define GLCD_SPIM_SCB_EnableInt()    GLCD_SPIM_SCB_SCB_IRQ_Enable()
    #define GLCD_SPIM_SCB_DisableInt()   GLCD_SPIM_SCB_SCB_IRQ_Disable()
#endif /* (GLCD_SPIM_SCB_SCB_IRQ_INTERNAL) */

/* Get interrupt cause */
#define GLCD_SPIM_SCB_GetInterruptCause()    (GLCD_SPIM_SCB_INTR_CAUSE_REG)

/* APIs to service INTR_RX register */
#define GLCD_SPIM_SCB_SetRxInterruptMode(interruptMask)     GLCD_SPIM_SCB_WRITE_INTR_RX_MASK(interruptMask)
#define GLCD_SPIM_SCB_ClearRxInterruptSource(interruptMask) GLCD_SPIM_SCB_CLEAR_INTR_RX(interruptMask)
#define GLCD_SPIM_SCB_SetRxInterrupt(interruptMask)         GLCD_SPIM_SCB_SET_INTR_RX(interruptMask)
#define GLCD_SPIM_SCB_GetRxInterruptSource()                (GLCD_SPIM_SCB_INTR_RX_REG)
#define GLCD_SPIM_SCB_GetRxInterruptMode()                  (GLCD_SPIM_SCB_INTR_RX_MASK_REG)
#define GLCD_SPIM_SCB_GetRxInterruptSourceMasked()          (GLCD_SPIM_SCB_INTR_RX_MASKED_REG)

/* APIs to service INTR_TX register */
#define GLCD_SPIM_SCB_SetTxInterruptMode(interruptMask)     GLCD_SPIM_SCB_WRITE_INTR_TX_MASK(interruptMask)
#define GLCD_SPIM_SCB_ClearTxInterruptSource(interruptMask) GLCD_SPIM_SCB_CLEAR_INTR_TX(interruptMask)
#define GLCD_SPIM_SCB_SetTxInterrupt(interruptMask)         GLCD_SPIM_SCB_SET_INTR_TX(interruptMask)
#define GLCD_SPIM_SCB_GetTxInterruptSource()                (GLCD_SPIM_SCB_INTR_TX_REG)
#define GLCD_SPIM_SCB_GetTxInterruptMode()                  (GLCD_SPIM_SCB_INTR_TX_MASK_REG)
#define GLCD_SPIM_SCB_GetTxInterruptSourceMasked()          (GLCD_SPIM_SCB_INTR_TX_MASKED_REG)

/* APIs to service INTR_MASTER register */
#define GLCD_SPIM_SCB_SetMasterInterruptMode(interruptMask)    GLCD_SPIM_SCB_WRITE_INTR_MASTER_MASK(interruptMask)
#define GLCD_SPIM_SCB_ClearMasterInterruptSource(interruptMask) GLCD_SPIM_SCB_CLEAR_INTR_MASTER(interruptMask)
#define GLCD_SPIM_SCB_SetMasterInterrupt(interruptMask)         GLCD_SPIM_SCB_SET_INTR_MASTER(interruptMask)
#define GLCD_SPIM_SCB_GetMasterInterruptSource()                (GLCD_SPIM_SCB_INTR_MASTER_REG)
#define GLCD_SPIM_SCB_GetMasterInterruptMode()                  (GLCD_SPIM_SCB_INTR_MASTER_MASK_REG)
#define GLCD_SPIM_SCB_GetMasterInterruptSourceMasked()          (GLCD_SPIM_SCB_INTR_MASTER_MASKED_REG)

/* APIs to service INTR_SLAVE register */
#define GLCD_SPIM_SCB_SetSlaveInterruptMode(interruptMask)     GLCD_SPIM_SCB_WRITE_INTR_SLAVE_MASK(interruptMask)
#define GLCD_SPIM_SCB_ClearSlaveInterruptSource(interruptMask) GLCD_SPIM_SCB_CLEAR_INTR_SLAVE(interruptMask)
#define GLCD_SPIM_SCB_SetSlaveInterrupt(interruptMask)         GLCD_SPIM_SCB_SET_INTR_SLAVE(interruptMask)
#define GLCD_SPIM_SCB_GetSlaveInterruptSource()                (GLCD_SPIM_SCB_INTR_SLAVE_REG)
#define GLCD_SPIM_SCB_GetSlaveInterruptMode()                  (GLCD_SPIM_SCB_INTR_SLAVE_MASK_REG)
#define GLCD_SPIM_SCB_GetSlaveInterruptSourceMasked()          (GLCD_SPIM_SCB_INTR_SLAVE_MASKED_REG)


/**********************************
*     Vars with External Linkage
**********************************/

extern uint8 GLCD_SPIM_SCB_initVar;
extern cyisraddress GLCD_SPIM_SCB_customIntrHandler;
extern GLCD_SPIM_SCB_BACKUP_STRUCT GLCD_SPIM_SCB_backup;

#if(GLCD_SPIM_SCB_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common config vars */
    extern volatile uint8 GLCD_SPIM_SCB_scbMode;
    extern volatile uint8 GLCD_SPIM_SCB_scbEnableWake;

    /* I2C config vars */
    extern volatile uint8 GLCD_SPIM_SCB_mode;
    extern volatile uint8 GLCD_SPIM_SCB_acceptAddr;

    /* SPI/UART config vars */
    extern volatile uint8 * GLCD_SPIM_SCB_rxBuffer;
    extern volatile uint8   GLCD_SPIM_SCB_rxDataBits;
    extern volatile uint32  GLCD_SPIM_SCB_rxBufferSize;

    extern volatile uint8 * GLCD_SPIM_SCB_txBuffer;
    extern volatile uint8   GLCD_SPIM_SCB_txDataBits;
    extern volatile uint32  GLCD_SPIM_SCB_txBufferSize;

#endif /* (GLCD_SPIM_SCB_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*              Registers
***************************************/

#define GLCD_SPIM_SCB_CTRL_REG               (*(reg32 *) GLCD_SPIM_SCB_SCB__CTRL)
#define GLCD_SPIM_SCB_CTRL_PTR               ( (reg32 *) GLCD_SPIM_SCB_SCB__CTRL)

#define GLCD_SPIM_SCB_STATUS_REG             (*(reg32 *) GLCD_SPIM_SCB_SCB__STATUS)
#define GLCD_SPIM_SCB_STATUS_PTR             ( (reg32 *) GLCD_SPIM_SCB_SCB__STATUS)

#define GLCD_SPIM_SCB_SPI_CTRL_REG           (*(reg32 *) GLCD_SPIM_SCB_SCB__SPI_CTRL)
#define GLCD_SPIM_SCB_SPI_CTRL_PTR           ( (reg32 *) GLCD_SPIM_SCB_SCB__SPI_CTRL)

#define GLCD_SPIM_SCB_SPI_STATUS_REG         (*(reg32 *) GLCD_SPIM_SCB_SCB__SPI_STATUS)
#define GLCD_SPIM_SCB_SPI_STATUS_PTR         ( (reg32 *) GLCD_SPIM_SCB_SCB__SPI_STATUS)

#define GLCD_SPIM_SCB_UART_CTRL_REG          (*(reg32 *) GLCD_SPIM_SCB_SCB__UART_CTRL)
#define GLCD_SPIM_SCB_UART_CTRL_PTR          ( (reg32 *) GLCD_SPIM_SCB_SCB__UART_CTRL)

#define GLCD_SPIM_SCB_UART_TX_CTRL_REG       (*(reg32 *) GLCD_SPIM_SCB_SCB__UART_TX_CTRL)
#define GLCD_SPIM_SCB_UART_TX_CTRL_PTR       ( (reg32 *) GLCD_SPIM_SCB_SCB__UART_RX_CTRL)

#define GLCD_SPIM_SCB_UART_RX_CTRL_REG       (*(reg32 *) GLCD_SPIM_SCB_SCB__UART_RX_CTRL)
#define GLCD_SPIM_SCB_UART_RX_CTRL_PTR       ( (reg32 *) GLCD_SPIM_SCB_SCB__UART_RX_CTRL)

#define GLCD_SPIM_SCB_UART_RX_STATUS_REG     (*(reg32 *) GLCD_SPIM_SCB_SCB__UART_RX_STATUS)
#define GLCD_SPIM_SCB_UART_RX_STATUS_PTR     ( (reg32 *) GLCD_SPIM_SCB_SCB__UART_RX_STATUS)

#define GLCD_SPIM_SCB_I2C_CTRL_REG           (*(reg32 *) GLCD_SPIM_SCB_SCB__I2C_CTRL)
#define GLCD_SPIM_SCB_I2C_CTRL_PTR           ( (reg32 *) GLCD_SPIM_SCB_SCB__I2C_CTRL)

#define GLCD_SPIM_SCB_I2C_STATUS_REG         (*(reg32 *) GLCD_SPIM_SCB_SCB__I2C_STATUS)
#define GLCD_SPIM_SCB_I2C_STATUS_PTR         ( (reg32 *) GLCD_SPIM_SCB_SCB__I2C_STATUS)

#define GLCD_SPIM_SCB_I2C_MASTER_CMD_REG     (*(reg32 *) GLCD_SPIM_SCB_SCB__I2C_M_CMD)
#define GLCD_SPIM_SCB_I2C_MASTER_CMD_PTR     ( (reg32 *) GLCD_SPIM_SCB_SCB__I2C_M_CMD)

#define GLCD_SPIM_SCB_I2C_SLAVE_CMD_REG      (*(reg32 *) GLCD_SPIM_SCB_SCB__I2C_S_CMD)
#define GLCD_SPIM_SCB_I2C_SLAVE_CMD_PTR      ( (reg32 *) GLCD_SPIM_SCB_SCB__I2C_S_CMD)

#define GLCD_SPIM_SCB_I2C_CFG_REG            (*(reg32 *) GLCD_SPIM_SCB_SCB__I2C_CFG)
#define GLCD_SPIM_SCB_I2C_CFG_PTR            ( (reg32 *) GLCD_SPIM_SCB_SCB__I2C_CFG)

#define GLCD_SPIM_SCB_TX_CTRL_REG            (*(reg32 *) GLCD_SPIM_SCB_SCB__TX_CTRL)
#define GLCD_SPIM_SCB_TX_CTRL_PTR            ( (reg32 *) GLCD_SPIM_SCB_SCB__TX_CTRL)

#define GLCD_SPIM_SCB_TX_FIFO_CTRL_REG       (*(reg32 *) GLCD_SPIM_SCB_SCB__TX_FIFO_CTRL)
#define GLCD_SPIM_SCB_TX_FIFO_CTRL_PTR       ( (reg32 *) GLCD_SPIM_SCB_SCB__TX_FIFO_CTRL)

#define GLCD_SPIM_SCB_TX_FIFO_STATUS_REG     (*(reg32 *) GLCD_SPIM_SCB_SCB__TX_FIFO_STATUS)
#define GLCD_SPIM_SCB_TX_FIFO_STATUS_PTR     ( (reg32 *) GLCD_SPIM_SCB_SCB__TX_FIFO_STATUS)

#define GLCD_SPIM_SCB_TX_FIFO_WR_REG         (*(reg32 *) GLCD_SPIM_SCB_SCB__TX_FIFO_WR)
#define GLCD_SPIM_SCB_TX_FIFO_WR_PTR         ( (reg32 *) GLCD_SPIM_SCB_SCB__TX_FIFO_WR)

#define GLCD_SPIM_SCB_RX_CTRL_REG            (*(reg32 *) GLCD_SPIM_SCB_SCB__RX_CTRL)
#define GLCD_SPIM_SCB_RX_CTRL_PTR            ( (reg32 *) GLCD_SPIM_SCB_SCB__RX_CTRL)

#define GLCD_SPIM_SCB_RX_FIFO_CTRL_REG       (*(reg32 *) GLCD_SPIM_SCB_SCB__RX_FIFO_CTRL)
#define GLCD_SPIM_SCB_RX_FIFO_CTRL_PTR       ( (reg32 *) GLCD_SPIM_SCB_SCB__RX_FIFO_CTRL)

#define GLCD_SPIM_SCB_RX_FIFO_STATUS_REG     (*(reg32 *) GLCD_SPIM_SCB_SCB__RX_FIFO_STATUS)
#define GLCD_SPIM_SCB_RX_FIFO_STATUS_PTR     ( (reg32 *) GLCD_SPIM_SCB_SCB__RX_FIFO_STATUS)

#define GLCD_SPIM_SCB_RX_MATCH_REG           (*(reg32 *) GLCD_SPIM_SCB_SCB__RX_MATCH)
#define GLCD_SPIM_SCB_RX_MATCH_PTR           ( (reg32 *) GLCD_SPIM_SCB_SCB__RX_MATCH)

#define GLCD_SPIM_SCB_RX_FIFO_RD_REG         (*(reg32 *) GLCD_SPIM_SCB_SCB__RX_FIFO_RD)
#define GLCD_SPIM_SCB_RX_FIFO_RD_PTR         ( (reg32 *) GLCD_SPIM_SCB_SCB__RX_FIFO_RD)

#define GLCD_SPIM_SCB_RX_FIFO_RD_SILENT_REG  (*(reg32 *) GLCD_SPIM_SCB_SCB__RX_FIFO_RD_SILENT)
#define GLCD_SPIM_SCB_RX_FIFO_RD_SILENT_PTR  ( (reg32 *) GLCD_SPIM_SCB_SCB__RX_FIFO_RD_SILENT)

#define GLCD_SPIM_SCB_EZBUF_DATA00_REG       (*(reg32 *) GLCD_SPIM_SCB_SCB__EZ_DATA00)
#define GLCD_SPIM_SCB_EZBUF_DATA00_PTR       ( (reg32 *) GLCD_SPIM_SCB_SCB__EZ_DATA00)

#define GLCD_SPIM_SCB_INTR_CAUSE_REG         (*(reg32 *) GLCD_SPIM_SCB_SCB__INTR_CAUSE)
#define GLCD_SPIM_SCB_INTR_CAUSE_PTR         ( (reg32 *) GLCD_SPIM_SCB_SCB__INTR_CAUSE)

#define GLCD_SPIM_SCB_INTR_I2C_EC_REG        (*(reg32 *) GLCD_SPIM_SCB_SCB__INTR_I2C_EC)
#define GLCD_SPIM_SCB_INTR_I2C_EC_PTR        ( (reg32 *) GLCD_SPIM_SCB_SCB__INTR_I2C_EC)

#define GLCD_SPIM_SCB_INTR_I2C_EC_MASK_REG   (*(reg32 *) GLCD_SPIM_SCB_SCB__INTR_I2C_EC_MASK)
#define GLCD_SPIM_SCB_INTR_I2C_EC_MASK_PTR   ( (reg32 *) GLCD_SPIM_SCB_SCB__INTR_I2C_EC_MASK)

#define GLCD_SPIM_SCB_INTR_I2C_EC_MASKED_REG (*(reg32 *) GLCD_SPIM_SCB_SCB__INTR_I2C_EC_MASKED)
#define GLCD_SPIM_SCB_INTR_I2C_EC_MASKED_PTR ( (reg32 *) GLCD_SPIM_SCB_SCB__INTR_I2C_EC_MASKED)

#define GLCD_SPIM_SCB_INTR_SPI_EC_REG        (*(reg32 *) GLCD_SPIM_SCB_SCB__INTR_SPI_EC)
#define GLCD_SPIM_SCB_INTR_SPI_EC_PTR        ( (reg32 *) GLCD_SPIM_SCB_SCB__INTR_SPI_EC)

#define GLCD_SPIM_SCB_INTR_SPI_EC_MASK_REG   (*(reg32 *) GLCD_SPIM_SCB_SCB__INTR_SPI_EC_MASK)
#define GLCD_SPIM_SCB_INTR_SPI_EC_MASK_PTR   ( (reg32 *) GLCD_SPIM_SCB_SCB__INTR_SPI_EC_MASK)

#define GLCD_SPIM_SCB_INTR_SPI_EC_MASKED_REG (*(reg32 *) GLCD_SPIM_SCB_SCB__INTR_SPI_EC_MASKED)
#define GLCD_SPIM_SCB_INTR_SPI_EC_MASKED_PTR ( (reg32 *) GLCD_SPIM_SCB_SCB__INTR_SPI_EC_MASKED)

#define GLCD_SPIM_SCB_INTR_MASTER_REG        (*(reg32 *) GLCD_SPIM_SCB_SCB__INTR_M)
#define GLCD_SPIM_SCB_INTR_MASTER_PTR        ( (reg32 *) GLCD_SPIM_SCB_SCB__INTR_M)

#define GLCD_SPIM_SCB_INTR_MASTER_SET_REG    (*(reg32 *) GLCD_SPIM_SCB_SCB__INTR_M_SET)
#define GLCD_SPIM_SCB_INTR_MASTER_SET_PTR    ( (reg32 *) GLCD_SPIM_SCB_SCB__INTR_M_SET)

#define GLCD_SPIM_SCB_INTR_MASTER_MASK_REG   (*(reg32 *) GLCD_SPIM_SCB_SCB__INTR_M_MASK)
#define GLCD_SPIM_SCB_INTR_MASTER_MASK_PTR   ( (reg32 *) GLCD_SPIM_SCB_SCB__INTR_M_MASK)

#define GLCD_SPIM_SCB_INTR_MASTER_MASKED_REG (*(reg32 *) GLCD_SPIM_SCB_SCB__INTR_M_MASKED)
#define GLCD_SPIM_SCB_INTR_MASTER_MASKED_PTR ( (reg32 *) GLCD_SPIM_SCB_SCB__INTR_M_MASKED)

#define GLCD_SPIM_SCB_INTR_SLAVE_REG         (*(reg32 *) GLCD_SPIM_SCB_SCB__INTR_S)
#define GLCD_SPIM_SCB_INTR_SLAVE_PTR         ( (reg32 *) GLCD_SPIM_SCB_SCB__INTR_S)

#define GLCD_SPIM_SCB_INTR_SLAVE_SET_REG     (*(reg32 *) GLCD_SPIM_SCB_SCB__INTR_S_SET)
#define GLCD_SPIM_SCB_INTR_SLAVE_SET_PTR     ( (reg32 *) GLCD_SPIM_SCB_SCB__INTR_S_SET)

#define GLCD_SPIM_SCB_INTR_SLAVE_MASK_REG    (*(reg32 *) GLCD_SPIM_SCB_SCB__INTR_S_MASK)
#define GLCD_SPIM_SCB_INTR_SLAVE_MASK_PTR    ( (reg32 *) GLCD_SPIM_SCB_SCB__INTR_S_MASK)

#define GLCD_SPIM_SCB_INTR_SLAVE_MASKED_REG  (*(reg32 *) GLCD_SPIM_SCB_SCB__INTR_S_MASKED)
#define GLCD_SPIM_SCB_INTR_SLAVE_MASKED_PTR  ( (reg32 *) GLCD_SPIM_SCB_SCB__INTR_S_MASKED)

#define GLCD_SPIM_SCB_INTR_TX_REG            (*(reg32 *) GLCD_SPIM_SCB_SCB__INTR_TX)
#define GLCD_SPIM_SCB_INTR_TX_PTR            ( (reg32 *) GLCD_SPIM_SCB_SCB__INTR_TX)

#define GLCD_SPIM_SCB_INTR_TX_SET_REG        (*(reg32 *) GLCD_SPIM_SCB_SCB__INTR_TX_SET)
#define GLCD_SPIM_SCB_INTR_TX_SET_PTR        ( (reg32 *) GLCD_SPIM_SCB_SCB__INTR_TX_SET)

#define GLCD_SPIM_SCB_INTR_TX_MASK_REG       (*(reg32 *) GLCD_SPIM_SCB_SCB__INTR_TX_MASK)
#define GLCD_SPIM_SCB_INTR_TX_MASK_PTR       ( (reg32 *) GLCD_SPIM_SCB_SCB__INTR_TX_MASK)

#define GLCD_SPIM_SCB_INTR_TX_MASKED_REG     (*(reg32 *) GLCD_SPIM_SCB_SCB__INTR_TX_MASKED)
#define GLCD_SPIM_SCB_INTR_TX_MASKED_PTR     ( (reg32 *) GLCD_SPIM_SCB_SCB__INTR_TX_MASKED)

#define GLCD_SPIM_SCB_INTR_RX_REG            (*(reg32 *) GLCD_SPIM_SCB_SCB__INTR_RX)
#define GLCD_SPIM_SCB_INTR_RX_PTR            ( (reg32 *) GLCD_SPIM_SCB_SCB__INTR_RX)

#define GLCD_SPIM_SCB_INTR_RX_SET_REG        (*(reg32 *) GLCD_SPIM_SCB_SCB__INTR_RX_SET)
#define GLCD_SPIM_SCB_INTR_RX_SET_PTR        ( (reg32 *) GLCD_SPIM_SCB_SCB__INTR_RX_SET)

#define GLCD_SPIM_SCB_INTR_RX_MASK_REG       (*(reg32 *) GLCD_SPIM_SCB_SCB__INTR_RX_MASK)
#define GLCD_SPIM_SCB_INTR_RX_MASK_PTR       ( (reg32 *) GLCD_SPIM_SCB_SCB__INTR_RX_MASK)

#define GLCD_SPIM_SCB_INTR_RX_MASKED_REG     (*(reg32 *) GLCD_SPIM_SCB_SCB__INTR_RX_MASKED)
#define GLCD_SPIM_SCB_INTR_RX_MASKED_PTR     ( (reg32 *) GLCD_SPIM_SCB_SCB__INTR_RX_MASKED)


/***************************************
*        Registers Constants
***************************************/

/* GLCD_SPIM_SCB_CTRL */
#define GLCD_SPIM_SCB_CTRL_OVS_POS           (0u)  /* [3:0]   Oversampling factor                 */
#define GLCD_SPIM_SCB_CTRL_EC_AM_MODE_POS    (8u)  /* [8]     Externally clocked address match    */
#define GLCD_SPIM_SCB_CTRL_EC_OP_MODE_POS    (9u)  /* [9]     Externally clocked operation mode   */
#define GLCD_SPIM_SCB_CTRL_EZBUF_MODE_POS    (10u) /* [10]    EZ buffer is enabled                */
#define GLCD_SPIM_SCB_CTRL_ADDR_ACCEPT_POS   (16u) /* [16]    Put matched address in RX FIFO      */
#define GLCD_SPIM_SCB_CTRL_BLOCK_POS         (17u) /* [17]    Ext and Int logic to resolve colide */
#define GLCD_SPIM_SCB_CTRL_MODE_POS          (24u) /* [25:24] Operation mode                      */
#define GLCD_SPIM_SCB_CTRL_ENABLED_POS       (31u) /* [31]    Enable SCB block                    */
#define GLCD_SPIM_SCB_CTRL_OVS_MASK          ((uint32) 0x0Fu)
#define GLCD_SPIM_SCB_CTRL_EC_AM_MODE        ((uint32) ((uint32) 0x01u << GLCD_SPIM_SCB_CTRL_EC_AM_MODE_POS))
#define GLCD_SPIM_SCB_CTRL_EC_OP_MODE        ((uint32) ((uint32) 0x01u << GLCD_SPIM_SCB_CTRL_EC_OP_MODE_POS))
#define GLCD_SPIM_SCB_CTRL_EZBUF_MODE        ((uint32) ((uint32) 0x01u << GLCD_SPIM_SCB_CTRL_EZBUF_MODE_POS))
#define GLCD_SPIM_SCB_CTRL_ADDR_ACCEPT       ((uint32) ((uint32) 0x01u << GLCD_SPIM_SCB_CTRL_ADDR_ACCEPT_POS))
#define GLCD_SPIM_SCB_CTRL_BLOCK             ((uint32) ((uint32) 0x01u << GLCD_SPIM_SCB_CTRL_BLOCK_POS))
#define GLCD_SPIM_SCB_CTRL_MODE_MASK         ((uint32) ((uint32) 0x03u << GLCD_SPIM_SCB_CTRL_MODE_POS))
#define GLCD_SPIM_SCB_CTRL_MODE_I2C          ((uint32)  0x00u)
#define GLCD_SPIM_SCB_CTRL_MODE_SPI          ((uint32) ((uint32) 0x01u << GLCD_SPIM_SCB_CTRL_MODE_POS))
#define GLCD_SPIM_SCB_CTRL_MODE_UART         ((uint32) ((uint32) 0x02u << GLCD_SPIM_SCB_CTRL_MODE_POS))
#define GLCD_SPIM_SCB_CTRL_ENABLED           ((uint32) ((uint32) 0x01u << GLCD_SPIM_SCB_CTRL_ENABLED_POS))


/* GLCD_SPIM_SCB_STATUS_REG */
#define GLCD_SPIM_SCB_STATUS_EC_BUSY_POS     (0u)  /* [0] Bus busy. Externaly clocked loigc access to EZ memory */
#define GLCD_SPIM_SCB_STATUS_EC_BUSY         ((uint32) 0x0Fu)


/* GLCD_SPIM_SCB_SPI_CTRL_REG  */
#define GLCD_SPIM_SCB_SPI_CTRL_CONTINUOUS_POS        (0u)  /* [0]     Continuous or Separated SPI data transfers */
#define GLCD_SPIM_SCB_SPI_CTRL_SELECT_PRECEDE_POS    (1u)  /* [1]     Precedes or coincides start of data frame  */
#define GLCD_SPIM_SCB_SPI_CTRL_CPHA_POS              (2u)  /* [2]     SCLK phase                                 */
#define GLCD_SPIM_SCB_SPI_CTRL_CPOL_POS              (3u)  /* [3]     SCLK polarity                              */
#define GLCD_SPIM_SCB_SPI_CTRL_LATE_MISO_SAMPLE_POS  (4u)  /* [4]     Late MISO sample enabled                   */
#define GLCD_SPIM_SCB_SPI_CTRL_LOOPBACK_POS          (16u) /* [16]    Local loopback control enabled             */
#define GLCD_SPIM_SCB_SPI_CTRL_MODE_POS              (24u) /* [25:24] Submode of SPI operation                   */
#define GLCD_SPIM_SCB_SPI_CTRL_SLAVE_SELECT_POS      (26u) /* [27:26] Selects SPI SS signal                      */
#define GLCD_SPIM_SCB_SPI_CTRL_MASTER_MODE_POS       (31u) /* [31]    Master mode enabled                        */
#define GLCD_SPIM_SCB_SPI_CTRL_CONTINUOUS            ((uint32) 0x01u)
#define GLCD_SPIM_SCB_SPI_CTRL_SELECT_PRECEDE        ((uint32) ((uint32) 0x01u << \
                                                                    GLCD_SPIM_SCB_SPI_CTRL_SELECT_PRECEDE_POS))
#define GLCD_SPIM_SCB_SPI_CTRL_SCLK_MODE_MASK        ((uint32) ((uint32) 0x03u << \
                                                                    GLCD_SPIM_SCB_SPI_CTRL_CPHA_POS))
#define GLCD_SPIM_SCB_SPI_CTRL_CPHA                  ((uint32) ((uint32) 0x01u << \
                                                                    GLCD_SPIM_SCB_SPI_CTRL_CPHA_POS))
#define GLCD_SPIM_SCB_SPI_CTRL_CPOL                  ((uint32) ((uint32) 0x01u << \
                                                                    GLCD_SPIM_SCB_SPI_CTRL_CPOL_POS))
#define GLCD_SPIM_SCB_SPI_CTRL_LATE_MISO_SAMPLE      ((uint32) ((uint32) 0x01u << \
                                                                    GLCD_SPIM_SCB_SPI_CTRL_LATE_MISO_SAMPLE_POS))
#define GLCD_SPIM_SCB_SPI_CTRL_LOOPBACK              ((uint32) ((uint32) 0x01u << \
                                                                    GLCD_SPIM_SCB_SPI_CTRL_LOOPBACK_POS))
#define GLCD_SPIM_SCB_SPI_CTRL_MODE_MASK             ((uint32) ((uint32) 0x03u << \
                                                                    GLCD_SPIM_SCB_SPI_CTRL_MODE_POS))
#define GLCD_SPIM_SCB_SPI_CTRL_MODE_MOTOROLA         ((uint32) 0x00u)
#define GLCD_SPIM_SCB_SPI_CTRL_MODE_TI               ((uint32) ((uint32) 0x01u << GLCD_SPIM_SCB_CTRL_MODE_POS))
#define GLCD_SPIM_SCB_SPI_CTRL_MODE_NS               ((uint32) ((uint32) 0x02u << GLCD_SPIM_SCB_CTRL_MODE_POS))
#define GLCD_SPIM_SCB_SPI_CTRL_SLAVE_SELECT_MASK     ((uint32) ((uint32) 0x03u << \
                                                                    GLCD_SPIM_SCB_SPI_CTRL_SLAVE_SELECT_POS))
#define GLCD_SPIM_SCB_SPI_CTRL_SLAVE_SELECT0         ((uint32) 0x00u)
#define GLCD_SPIM_SCB_SPI_CTRL_SLAVE_SELECT1         ((uint32) ((uint32) 0x01u << \
                                                                    GLCD_SPIM_SCB_SPI_CTRL_SLAVE_SELECT_POS))
#define GLCD_SPIM_SCB_SPI_CTRL_SLAVE_SELECT2         ((uint32) ((uint32) 0x02u << \
                                                                    GLCD_SPIM_SCB_SPI_CTRL_SLAVE_SELECT_POS))
#define GLCD_SPIM_SCB_SPI_CTRL_SLAVE_SELECT3         ((uint32) ((uint32) 0x03u << \
                                                                    GLCD_SPIM_SCB_SPI_CTRL_SLAVE_SELECT_POS))
#define GLCD_SPIM_SCB_SPI_CTRL_MASTER                ((uint32) ((uint32) 0x01u << \
                                                                    GLCD_SPIM_SCB_SPI_CTRL_MASTER_MODE_POS))
#define GLCD_SPIM_SCB_SPI_CTRL_SLAVE                 ((uint32) 0x00u)


/* GLCD_SPIM_SCB_SPI_STATUS_REG  */
#define GLCD_SPIM_SCB_SPI_STATUS_BUS_BUSY_POS    (0u)  /* [0]    Bus busy - slave selected */
#define GLCD_SPIM_SCB_SPI_STATUS_EZBUF_ADDR_POS  (8u)  /* [15:8] EzAddress                 */
#define GLCD_SPIM_SCB_SPI_STATUS_BUS_BUSY        ((uint32) 0x01u)
#define GLCD_SPIM_SCB_SPI_STATUS_EZBUF_ADDR_MASK    ((uint32) ((uint32) 0xFFu << \
                                                                    GLCD_SPIM_SCB_I2C_STATUS_EZBUF_ADDR_POS))


/* GLCD_SPIM_SCB_UART_CTRL */
#define GLCD_SPIM_SCB_UART_CTRL_LOOPBACK_POS         (16u) /* [16] Loopback     */
#define GLCD_SPIM_SCB_UART_CTRL_MODE_POS             (24u) /* [24] UART subMode */
#define GLCD_SPIM_SCB_UART_CTRL_LOOPBACK             ((uint32) ((uint32) 0x01u << \
                                                                        GLCD_SPIM_SCB_UART_CTRL_LOOPBACK_POS))
#define GLCD_SPIM_SCB_UART_CTRL_MODE_UART_STD        ((uint32) 0x00u)
#define GLCD_SPIM_SCB_UART_CTRL_MODE_UART_SMARTCARD  ((uint32) ((uint32) 0x01u << \
                                                                        GLCD_SPIM_SCB_UART_CTRL_MODE_POS))
#define GLCD_SPIM_SCB_UART_CTRL_MODE_UART_IRDA       ((uint32) ((uint32) 0x02u << \
                                                                        GLCD_SPIM_SCB_UART_CTRL_MODE_POS))
#define GLCD_SPIM_SCB_UART_CTRL_MODE_MASK            ((uint32) ((uint32) 0x03u << \
                                                                        GLCD_SPIM_SCB_UART_CTRL_MODE_POS))


/* GLCD_SPIM_SCB_UART_TX_CTRL */
#define GLCD_SPIM_SCB_UART_TX_CTRL_STOP_BITS_POS         (0u)  /* [2:0] Stop bits: (Stop bits + 1) * 0.5 period */
#define GLCD_SPIM_SCB_UART_TX_CTRL_PARITY_POS            (4u)  /* [4]   Parity bit                              */
#define GLCD_SPIM_SCB_UART_TX_CTRL_PARITY_ENABLED_POS    (5u)  /* [5]   Parity enable                           */
#define GLCD_SPIM_SCB_UART_TX_CTRL_RETRY_ON_NACK_POS     (8u)  /* [8]   Smart Card: re-send frame on NACK       */
#define GLCD_SPIM_SCB_UART_TX_CTRL_ONE_STOP_BIT          ((uint32) 0x01u)
#define GLCD_SPIM_SCB_UART_TX_CTRL_ONE_HALF_STOP_BITS    ((uint32) 0x02u)
#define GLCD_SPIM_SCB_UART_TX_CTRL_TWO_STOP_BITS         ((uint32) 0x03u)
#define GLCD_SPIM_SCB_UART_TX_CTRL_STOP_BITS_MASK        ((uint32) 0x07u)
#define GLCD_SPIM_SCB_UART_TX_CTRL_PARITY                ((uint32) ((uint32) 0x01u << \
                                                                    GLCD_SPIM_SCB_UART_TX_CTRL_PARITY_POS))
#define GLCD_SPIM_SCB_UART_TX_CTRL_PARITY_ENABLED        ((uint32) ((uint32) 0x01u << \
                                                                    GLCD_SPIM_SCB_UART_TX_CTRL_PARITY_ENABLED_POS))
#define GLCD_SPIM_SCB_UART_TX_CTRL_RETRY_ON_NACK         ((uint32) ((uint32) 0x01u << \
                                                                    GLCD_SPIM_SCB_UART_TX_CTRL_RETRY_ON_NACK_POS))


/* GLCD_SPIM_SCB_UART_RX_CTRL */
#define GLCD_SPIM_SCB_UART_RX_CTRL_STOP_BITS_POS             (0u)  /* [2:0] Stop bits: (Stop bits + 1) * 0.5 prd   */
#define GLCD_SPIM_SCB_UART_RX_CTRL_PARITY_POS                (4u)  /* [4]   Parity bit                             */
#define GLCD_SPIM_SCB_UART_RX_CTRL_PARITY_ENABLED_POS        (5u)  /* [5]   Parity enable                          */
#define GLCD_SPIM_SCB_UART_RX_CTRL_POLARITY_POS              (6u)  /* [6]   IrDA: inverts polarity of RX signal    */
#define GLCD_SPIM_SCB_UART_RX_CTRL_DROP_ON_PARITY_ERR_POS    (8u)  /* [8]   Drop and lost RX FIFO on parity error  */
#define GLCD_SPIM_SCB_UART_RX_CTRL_DROP_ON_FRAME_ERR_POS     (9u)  /* [9]   Drop and lost RX FIFO on frame error   */
#define GLCD_SPIM_SCB_UART_RX_CTRL_MP_MODE_POS               (10u) /* [10]  Multi-processor mode                   */
#define GLCD_SPIM_SCB_UART_RX_CTRL_LIN_MODE_POS              (12u) /* [12]  Lin mode: applicable for UART Standart */
#define GLCD_SPIM_SCB_UART_RX_CTRL_SKIP_START_POS            (13u) /* [13]  Skip start not: only for UART Standart */
#define GLCD_SPIM_SCB_UART_RX_CTRL_BREAK_WIDTH_POS           (16u) /* [19:16]  Break width: (Break width + 1)      */
#define GLCD_SPIM_SCB_UART_TX_CTRL_ONE_STOP_BIT              ((uint32) 0x01u)
#define GLCD_SPIM_SCB_UART_TX_CTRL_ONE_HALF_STOP_BITS        ((uint32) 0x02u)
#define GLCD_SPIM_SCB_UART_TX_CTRL_TWO_STOP_BITS             ((uint32) 0x03u)
#define GLCD_SPIM_SCB_UART_RX_CTRL_STOP_BITS_MASK            ((uint32) 0x07u)
#define GLCD_SPIM_SCB_UART_RX_CTRL_PARITY                    ((uint32) ((uint32) 0x01u << \
                                                                    GLCD_SPIM_SCB_UART_RX_CTRL_PARITY_POS))
#define GLCD_SPIM_SCB_UART_RX_CTRL_PARITY_ENABLED            ((uint32) ((uint32) 0x01u << \
                                                                    GLCD_SPIM_SCB_UART_RX_CTRL_PARITY_ENABLED_POS))
#define GLCD_SPIM_SCB_UART_RX_CTRL_POLARITY                  ((uint32) ((uint32) 0x01u << \
                                                                    GLCD_SPIM_SCB_UART_RX_CTRL_POLARITY_POS))
#define GLCD_SPIM_SCB_UART_RX_CTRL_DROP_ON_PARITY_ERR        ((uint32) ((uint32) 0x01u << \
                                                                GLCD_SPIM_SCB_UART_RX_CTRL_DROP_ON_PARITY_ERR_POS))
#define GLCD_SPIM_SCB_UART_RX_CTRL_DROP_ON_FRAME_ERR         ((uint32) ((uint32) 0x01u << \
                                                                GLCD_SPIM_SCB_UART_RX_CTRL_DROP_ON_FRAME_ERR_POS))
#define GLCD_SPIM_SCB_UART_RX_CTRL_MP_MODE                   ((uint32) ((uint32) 0x01u << \
                                                                    GLCD_SPIM_SCB_UART_RX_CTRL_MP_MODE_POS))
#define GLCD_SPIM_SCB_UART_RX_CTRL_LIN_MODE                  ((uint32) ((uint32) 0x01u << \
                                                                    GLCD_SPIM_SCB_UART_RX_CTRL_LIN_MODE_POS))
#define GLCD_SPIM_SCB_UART_RX_CTRL_SKIP_START                ((uint32) ((uint32) 0x01u << \
                                                                  GLCD_SPIM_SCB_UART_RX_CTRL_SKIP_START_POS))
#define GLCD_SPIM_SCB_UART_RX_CTRL_BREAK_WIDTH_MASK          ((uint32) ((uint32) 0x0Fu << \
                                                                  GLCD_SPIM_SCB_UART_RX_CTRL_BREAK_WIDTH_POS))

/* GLCD_SPIM_SCB_UART_RX_STATUS_REG */
#define GLCD_SPIM_SCB_UART_RX_STATUS_BR_COUNTER_POS     (0u)  /* [11:0] Baute Rate counter */
#define GLCD_SPIM_SCB_UART_RX_STATUS_BR_COUNTER_MASK    ((uint32) 0xFFFu)


/* GLCD_SPIM_SCB_I2C_CTRL */
#define GLCD_SPIM_SCB_I2C_CTRL_HIGH_PHASE_OVS_POS           (0u)   /* [3:0] Oversampling factor high: masrer only */
#define GLCD_SPIM_SCB_I2C_CTRL_LOW_PHASE_OVS_POS            (4u)   /* [7:4] Oversampling factor low:  masrer only */
#define GLCD_SPIM_SCB_I2C_CTRL_M_READY_DATA_ACK_POS         (8u)   /* [8]   Master ACKs data wgile RX FIFO != FULL*/
#define GLCD_SPIM_SCB_I2C_CTRL_M_NOT_READY_DATA_NACK_POS    (9u)   /* [9]   Master NACKs data if RX FIFO ==  FULL */
#define GLCD_SPIM_SCB_I2C_CTRL_S_GENERAL_IGNORE_POS         (11u)  /* [11]  Slave ignores General call            */
#define GLCD_SPIM_SCB_I2C_CTRL_S_READY_ADDR_ACK_POS         (12u)  /* [12]  Slave ACKs Address if RX FIFO != FULL */
#define GLCD_SPIM_SCB_I2C_CTRL_S_READY_DATA_ACK_POS         (13u)  /* [13]  Slave ACKs data while RX FIFO == FULL */
#define GLCD_SPIM_SCB_I2C_CTRL_S_NOT_READY_ADDR_NACK_POS    (14u)  /* [14]  Slave NACKs address if RX FIFO == FULL*/
#define GLCD_SPIM_SCB_I2C_CTRL_S_NOT_READY_DATA_NACK_POS    (15u)  /* [15]  Slave NACKs data if RX FIFO is  FULL  */
#define GLCD_SPIM_SCB_I2C_CTRL_LOOPBACK_POS                 (16u)  /* [16]  Loopback                              */
#define GLCD_SPIM_SCB_I2C_CTRL_SLAVE_MODE_POS               (30u)  /* [30]  Slave mode enabled                    */
#define GLCD_SPIM_SCB_I2C_CTRL_MASTER_MODE_POS              (31u)  /* [31]  Master mode enabled                   */
#define GLCD_SPIM_SCB_I2C_CTRL_HIGH_PHASE_OVS_MASK  ((uint32) 0x0Fu)
#define GLCD_SPIM_SCB_I2C_CTRL_LOW_PHASE_OVS_MASK   ((uint32) ((uint32) 0x0Fu << \
                                                                GLCD_SPIM_SCB_I2C_CTRL_LOW_PHASE_OVS_POS))
#define GLCD_SPIM_SCB_I2C_CTRL_M_READY_DATA_ACK      ((uint32) ((uint32) 0x01u << \
                                                                GLCD_SPIM_SCB_I2C_CTRL_M_READY_DATA_ACK_POS))
#define GLCD_SPIM_SCB_I2C_CTRL_M_NOT_READY_DATA_NACK ((uint32) ((uint32) 0x01u << \
                                                                GLCD_SPIM_SCB_I2C_CTRL_M_NOT_READY_DATA_NACK_POS))
#define GLCD_SPIM_SCB_I2C_CTRL_S_GENERAL_IGNORE      ((uint32) ((uint32) 0x01u << \
                                                                GLCD_SPIM_SCB_I2C_CTRL_S_GENERAL_IGNORE_POS))
#define GLCD_SPIM_SCB_I2C_CTRL_S_READY_ADDR_ACK      ((uint32) ((uint32) 0x01u << \
                                                                GLCD_SPIM_SCB_I2C_CTRL_S_READY_ADDR_ACK_POS))
#define GLCD_SPIM_SCB_I2C_CTRL_S_READY_DATA_ACK      ((uint32) ((uint32) 0x01u << \
                                                                GLCD_SPIM_SCB_I2C_CTRL_S_READY_DATA_ACK_POS))
#define GLCD_SPIM_SCB_I2C_CTRL_S_NOT_READY_ADDR_NACK ((uint32) ((uint32) 0x01u << \
                                                                GLCD_SPIM_SCB_I2C_CTRL_S_NOT_READY_ADDR_NACK_POS))
#define GLCD_SPIM_SCB_I2C_CTRL_S_NOT_READY_DATA_NACK ((uint32) ((uint32) 0x01u << \
                                                                GLCD_SPIM_SCB_I2C_CTRL_S_NOT_READY_DATA_NACK_POS))
#define GLCD_SPIM_SCB_I2C_CTRL_LOOPBACK              ((uint32) ((uint32) 0x01u << \
                                                                GLCD_SPIM_SCB_I2C_CTRL_LOOPBACK_POS))
#define GLCD_SPIM_SCB_I2C_CTRL_SLAVE_MODE            ((uint32) ((uint32) 0x01u << \
                                                                GLCD_SPIM_SCB_I2C_CTRL_SLAVE_MODE_POS))
#define GLCD_SPIM_SCB_I2C_CTRL_MASTER_MODE           ((uint32) ((uint32) 0x01u << \
                                                                GLCD_SPIM_SCB_I2C_CTRL_MASTER_MODE_POS))
#define GLCD_SPIM_SCB_I2C_CTRL_SLAVE_MASTER_MODE_MASK    ((uint32) ((uint32) 0x03u << \
                                                                GLCD_SPIM_SCB_I2C_CTRL_SLAVE_MODE_POS))


/* GLCD_SPIM_SCB_I2C_STATUS_REG  */
#define GLCD_SPIM_SCB_I2C_STATUS_BUS_BUSY_POS    (0u)  /* [0]    Bus busy: internally clocked */
#define GLCD_SPIM_SCB_I2C_STATUS_S_READ_POS      (4u)  /* [4]    Slave is read by master      */
#define GLCD_SPIM_SCB_I2C_STATUS_M_READ_POS      (5u)  /* [5]    Master reads Slave           */
#define GLCD_SPIM_SCB_I2C_STATUS_EZBUF_ADDR_POS  (8u)  /* [15:8] EZAddress                    */
#define GLCD_SPIM_SCB_I2C_STATUS_BUS_BUSY        ((uint32) 0x01u)
#define GLCD_SPIM_SCB_I2C_STATUS_S_READ          ((uint32) ((uint32) 0x01u << \
                                                                    GLCD_SPIM_SCB_I2C_STATUS_S_READ_POS))
#define GLCD_SPIM_SCB_I2C_STATUS_M_READ          ((uint32) ((uint32) 0x01u << \
                                                                    GLCD_SPIM_SCB_I2C_STATUS_M_READ_POS))
#define GLCD_SPIM_SCB_I2C_STATUS_EZBUF_ADDR_MASK ((uint32) ((uint32) 0xFFu << \
                                                                    GLCD_SPIM_SCB_I2C_STATUS_EZBUF_ADDR_POS))


/* GLCD_SPIM_SCB_I2C_MASTER_CMD_REG */
#define GLCD_SPIM_SCB_I2C_MASTER_CMD_M_START_POS             (0u)  /* [0] Master generate Start                */
#define GLCD_SPIM_SCB_I2C_MASTER_CMD_M_START_ON_IDLE_POS     (1u)  /* [1] Master generate Start if bus is free */
#define GLCD_SPIM_SCB_I2C_MASTER_CMD_M_ACK_POS               (2u)  /* [2] Master generate ACK                  */
#define GLCD_SPIM_SCB_I2C_MASTER_CMD_M_NACK_POS              (3u)  /* [3] Master generate NACK                 */
#define GLCD_SPIM_SCB_I2C_MASTER_CMD_M_STOP_POS              (4u)  /* [4] Master generate Stop                 */
#define GLCD_SPIM_SCB_I2C_MASTER_CMD_M_START         ((uint32) 0x01u)
#define GLCD_SPIM_SCB_I2C_MASTER_CMD_M_START_ON_IDLE ((uint32) ((uint32) 0x01u << \
                                                                   GLCD_SPIM_SCB_I2C_MASTER_CMD_M_START_ON_IDLE_POS))
#define GLCD_SPIM_SCB_I2C_MASTER_CMD_M_ACK           ((uint32) ((uint32) 0x01u << \
                                                                   GLCD_SPIM_SCB_I2C_MASTER_CMD_M_ACK_POS))
#define GLCD_SPIM_SCB_I2C_MASTER_CMD_M_NACK          ((uint32) ((uint32) 0x01u << \
                                                                    GLCD_SPIM_SCB_I2C_MASTER_CMD_M_NACK_POS))
#define GLCD_SPIM_SCB_I2C_MASTER_CMD_M_STOP          ((uint32) ((uint32) 0x01u << \
                                                                    GLCD_SPIM_SCB_I2C_MASTER_CMD_M_STOP_POS))


/* GLCD_SPIM_SCB_I2C_SLAVE_CMD_REG  */
#define GLCD_SPIM_SCB_I2C_SLAVE_CMD_S_ACK_POS    (0u)  /* [0] Slave generate ACK  */
#define GLCD_SPIM_SCB_I2C_SLAVE_CMD_S_NACK_POS   (1u)  /* [1] Slave generate NACK */
#define GLCD_SPIM_SCB_I2C_SLAVE_CMD_S_ACK        ((uint32) 0x01u)
#define GLCD_SPIM_SCB_I2C_SLAVE_CMD_S_NACK       ((uint32) ((uint32) 0x01u << \
                                                                GLCD_SPIM_SCB_I2C_SLAVE_CMD_S_NACK_POS))

#define GLCD_SPIM_SCB_I2C_SLAVE_CMD_S_ACK_POS    (0u)  /* [0] Slave generate ACK  */
#define GLCD_SPIM_SCB_I2C_SLAVE_CMD_S_NACK_POS   (1u)  /* [1] Slave generate NACK */
#define GLCD_SPIM_SCB_I2C_SLAVE_CMD_S_ACK        ((uint32) 0x01u)
#define GLCD_SPIM_SCB_I2C_SLAVE_CMD_S_NACK       ((uint32) ((uint32) 0x01u << \
                                                                GLCD_SPIM_SCB_I2C_SLAVE_CMD_S_NACK_POS))
/* GLCD_SPIM_SCB_I2C_CFG  */
#define GLCD_SPIM_SCB_I2C_CFG_SDA_FILT_HYS_POS           (0u)  /* [1:0]   Trim bits for the I2C SDA filter         */
#define GLCD_SPIM_SCB_I2C_CFG_SDA_FILT_TRIM_POS          (2u)  /* [3:2]   Trim bits for the I2C SDA filter         */
#define GLCD_SPIM_SCB_I2C_CFG_SCL_FILT_HYS_POS           (4u)  /* [5:4]   Trim bits for the I2C SCL filter         */
#define GLCD_SPIM_SCB_I2C_CFG_SCL_FILT_TRIM_POS          (6u)  /* [7:6]   Trim bits for the I2C SCL filter         */
#define GLCD_SPIM_SCB_I2C_CFG_SDA_FILT_OUT_HYS_POS       (8u)  /* [9:8]   Trim bits for I2C SDA filter output path */
#define GLCD_SPIM_SCB_I2C_CFG_SDA_FILT_OUT_TRIM_POS      (10u) /* [11:10] Trim bits for I2C SDA filter output path */
#define GLCD_SPIM_SCB_I2C_CFG_SDA_FILT_HS_POS            (16u) /* [16]    '0': 50 ns filter, '1': 10 ns filter     */
#define GLCD_SPIM_SCB_I2C_CFG_SDA_FILT_ENABLED_POS       (17u) /* [17]    I2C SDA filter enabled                   */
#define GLCD_SPIM_SCB_I2C_CFG_SCL_FILT_HS_POS            (24u) /* [24]    '0': 50 ns filter, '1': 10 ns filter     */
#define GLCD_SPIM_SCB_I2C_CFG_SCL_FILT_ENABLED_POS       (25u) /* [25]    I2C SCL filter enabled                   */
#define GLCD_SPIM_SCB_I2C_CFG_SDA_FILT_OUT_HS_POS        (26u) /* [26]    '0': 50ns filter, '1': 10 ns filter      */
#define GLCD_SPIM_SCB_I2C_CFG_SDA_FILT_OUT_ENABLED_POS   (27u) /* [27]    I2C SDA output delay filter enabled      */
#define GLCD_SPIM_SCB_I2C_CFG_SDA_FILT_HYS_MASK          ((uint32) 0x00u)
#define GLCD_SPIM_SCB_I2C_CFG_SDA_FILT_TRIM_MASK         ((uint32) ((uint32) 0x03u << \
                                                                GLCD_SPIM_SCB_I2C_CFG_SDA_FILT_TRIM_POS))
#define GLCD_SPIM_SCB_I2C_CFG_SCL_FILT_HYS_MASK          ((uint32) ((uint32) 0x03u << \
                                                                GLCD_SPIM_SCB_I2C_CFG_SCL_FILT_HYS_POS))
#define GLCD_SPIM_SCB_I2C_CFG_SCL_FILT_TRIM_MASK         ((uint32) ((uint32) 0x03u << \
                                                                GLCD_SPIM_SCB_I2C_CFG_SCL_FILT_TRIM_POS))
#define GLCD_SPIM_SCB_I2C_CFG_SDA_FILT_OUT_HYS_MASK      ((uint32) ((uint32) 0x03u << \
                                                                GLCD_SPIM_SCB_I2C_CFG_SDA_FILT_OUT_HYS_POS))
#define GLCD_SPIM_SCB_I2C_CFG_SDA_FILT_OUT_TRIM_MASK     ((uint32) ((uint32) 0x03u << \
                                                                GLCD_SPIM_SCB_I2C_CFG_SDA_FILT_OUT_TRIM_POS))
#define GLCD_SPIM_SCB_I2C_CFG_SDA_FILT_HS                ((uint32) ((uint32) 0x01u << \
                                                                GLCD_SPIM_SCB_I2C_CFG_SDA_FILT_HS_POS))
#define GLCD_SPIM_SCB_I2C_CFG_SDA_FILT_ENABLED           ((uint32) ((uint32) 0x01u << \
                                                                GLCD_SPIM_SCB_I2C_CFG_SDA_FILT_ENABLED_POS))
#define GLCD_SPIM_SCB_I2C_CFG_SCL_FILT_HS                ((uint32) ((uint32) 0x01u << \
                                                                GLCD_SPIM_SCB_I2C_CFG_SCL_FILT_HS_POS))
#define GLCD_SPIM_SCB_I2C_CFG_SCL_FILT_ENABLED           ((uint32) ((uint32) 0x01u << \
                                                                GLCD_SPIM_SCB_I2C_CFG_SCL_FILT_ENABLED_POS))
#define GLCD_SPIM_SCB_I2C_CFG_SDA_FILT_OUT_HS            ((uint32) ((uint32) 0x01u << \
                                                                GLCD_SPIM_SCB_I2C_CFG_SDA_FILT_OUT_HS_POS))
#define GLCD_SPIM_SCB_I2C_CFG_SDA_FILT_OUT_ENABLED       ((uint32) ((uint32) 0x01u << \
                                                                GLCD_SPIM_SCB_I2C_CFG_SDA_FILT_OUT_ENABLED_POS))


/* GLCD_SPIM_SCB_TX_CTRL_REG */
#define GLCD_SPIM_SCB_TX_CTRL_DATA_WIDTH_POS     (0u)  /* [3:0] Dataframe width: (Data width - 1) */
#define GLCD_SPIM_SCB_TX_CTRL_MSB_FIRST_POS      (8u)  /* [8]   MSB first shifter-out             */
#define GLCD_SPIM_SCB_TX_CTRL_ENABLED_POS        (31u) /* [31]  Transmitter enabled               */
#define GLCD_SPIM_SCB_TX_CTRL_DATA_WIDTH_MASK    ((uint32) 0x0Fu)
#define GLCD_SPIM_SCB_TX_CTRL_MSB_FIRST          ((uint32) ((uint32) 0x01u << \
                                                                        GLCD_SPIM_SCB_TX_CTRL_MSB_FIRST_POS))
#define GLCD_SPIM_SCB_TX_CTRL_LSB_FIRST          ((uint32) 0x00u)
#define GLCD_SPIM_SCB_TX_CTRL_ENABLED            ((uint32) ((uint32) 0x01u << GLCD_SPIM_SCB_TX_CTRL_ENABLED_POS))


/* GLCD_SPIM_SCB_TX_CTRL_FIFO_REG */
#define GLCD_SPIM_SCB_TX_FIFO_CTRL_TRIGGER_LEVEL_POS     (0u)  /* [2:0] Trigger level                              */
#define GLCD_SPIM_SCB_TX_FIFO_CTRL_CLEAR_POS             (16u) /* [16]  Clear TX FIFO: claared after set           */
#define GLCD_SPIM_SCB_TX_FIFO_CTRL_FREEZE_POS            (17u) /* [17]  Freeze TX FIFO: HW do not inc read pointer */
#define GLCD_SPIM_SCB_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK    ((uint32) 0x07u)
#define GLCD_SPIM_SCB_TX_FIFO_CTRL_CLEAR                 ((uint32) ((uint32) 0x01u << \
                                                                    GLCD_SPIM_SCB_TX_FIFO_CTRL_CLEAR_POS))
#define GLCD_SPIM_SCB_TX_FIFO_CTRL_FREEZE                ((uint32) ((uint32) 0x01u << \
                                                                    GLCD_SPIM_SCB_TX_FIFO_CTRL_FREEZE_POS))


/* GLCD_SPIM_SCB_TX_FIFO_STATUS_REG */
#define GLCD_SPIM_SCB_TX_FIFO_STATUS_USED_POS    (0u)  /* [3:0]   Amount of entries in TX FIFO */
#define GLCD_SPIM_SCB_TX_FIFO_SR_VALID_POS       (15u) /* [15]    Shifter status of TX FIFO    */
#define GLCD_SPIM_SCB_TX_FIFO_STATUS_RD_PTR_POS  (16u) /* [18:16] TX FIFO read pointer         */
#define GLCD_SPIM_SCB_TX_FIFO_STATUS_WR_PTR_POS  (24u) /* [26:24] TX FIFO write pointer        */
#define GLCD_SPIM_SCB_TX_FIFO_STATUS_USED_MASK   ((uint32) 0x0Fu)
#define GLCD_SPIM_SCB_TX_FIFO_SR_VALID           ((uint32) ((uint32) 0x01u << \
                                                                    GLCD_SPIM_SCB_TX_FIFO_SR_VALID_POS))
#define GLCD_SPIM_SCB_TX_FIFO_STATUS_RD_PTR_MASK ((uint32) ((uint32) 0x07u << \
                                                                    GLCD_SPIM_SCB_TX_FIFO_STATUS_RD_PTR_POS))
#define GLCD_SPIM_SCB_TX_FIFO_STATUS_WR_PTR_MASK ((uint32) ((uint32) 0x07u << \
                                                                    GLCD_SPIM_SCB_TX_FIFO_STATUS_WR_PTR_POS))


/* GLCD_SPIM_SCB_TX_FIFO_WR_REG */
#define GLCD_SPIM_SCB_TX_FIFO_WR_POS    (0u)  /* [15:0] Data written into TX FIFO */
#define GLCD_SPIM_SCB_TX_FIFO_WR_MASK   ((uint32) 0xFFu)


/* GLCD_SPIM_SCB_RX_CTRL_REG */
#define GLCD_SPIM_SCB_RX_CTRL_DATA_WIDTH_POS     (0u)  /* [3:0] Dataframe width: (Data width - 1) */
#define GLCD_SPIM_SCB_RX_CTRL_MSB_FIRST_POS      (8u)  /* [8]   MSB first shifter-out             */
#define GLCD_SPIM_SCB_RX_CTRL_MEDIAN_POS         (9u)  /* [9]   Median filter                     */
#define GLCD_SPIM_SCB_RX_CTRL_ENABLED_POS        (31u) /* [31]  Receiver enabled                  */
#define GLCD_SPIM_SCB_RX_CTRL_DATA_WIDTH_MASK    ((uint32) 0x0Fu)
#define GLCD_SPIM_SCB_RX_CTRL_MSB_FIRST          ((uint32) ((uint32) 0x01u << \
                                                                        GLCD_SPIM_SCB_RX_CTRL_MSB_FIRST_POS))
#define GLCD_SPIM_SCB_RX_CTRL_LSB_FIRST          ((uint32) 0x00u)
#define GLCD_SPIM_SCB_RX_CTRL_MEDIAN             ((uint32) ((uint32) 0x01u << GLCD_SPIM_SCB_RX_CTRL_MEDIAN_POS))
#define GLCD_SPIM_SCB_RX_CTRL_ENABLED            ((uint32) ((uint32) 0x01u << GLCD_SPIM_SCB_RX_CTRL_ENABLED_POS))


/* GLCD_SPIM_SCB_RX_FIFO_CTRL_REG */
#define GLCD_SPIM_SCB_RX_FIFO_CTRL_TRIGGER_LEVEL_POS     (0u)   /* [2:0] Trigger level                            */
#define GLCD_SPIM_SCB_RX_FIFO_CTRL_CLEAR_POS             (16u)  /* [16]  Clear RX FIFO: claar after set           */
#define GLCD_SPIM_SCB_RX_FIFO_CTRL_FREEZE_POS            (17u)  /* [17]  Freeze RX FIFO: HW writes has not effect */
#define GLCD_SPIM_SCB_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK    ((uint32) 0x07u)
#define GLCD_SPIM_SCB_RX_FIFO_CTRL_CLEAR                 ((uint32) ((uint32) 0x01u << \
                                                                    GLCD_SPIM_SCB_RX_FIFO_CTRL_CLEAR_POS))
#define GLCD_SPIM_SCB_RX_FIFO_CTRL_FREEZE                ((uint32) ((uint32) 0x01u << \
                                                                    GLCD_SPIM_SCB_RX_FIFO_CTRL_FREEZE_POS))


/* GLCD_SPIM_SCB_RX_FIFO_STATUS_REG */
#define GLCD_SPIM_SCB_RX_FIFO_STATUS_USED_POS    (0u)   /* [3:0]   Amount of entries in RX FIFO */
#define GLCD_SPIM_SCB_RX_FIFO_SR_VALID_POS       (15u)  /* [15]    Shifter status of RX FIFO    */
#define GLCD_SPIM_SCB_RX_FIFO_STATUS_RD_PTR_POS  (16u)  /* [18:16] RX FIFO read pointer         */
#define GLCD_SPIM_SCB_RX_FIFO_STATUS_WR_PTR_POS  (24u)  /* [26:24] RX FIFO write pointer        */
#define GLCD_SPIM_SCB_RX_FIFO_STATUS_USED_MASK   ((uint32) 0x0Fu)
#define GLCD_SPIM_SCB_RX_FIFO_SR_VALID           ((uint32) ((uint32) 0x01u << \
                                                                  GLCD_SPIM_SCB_RX_FIFO_SR_VALID_POS))
#define GLCD_SPIM_SCB_RX_FIFO_STATUS_RD_PTR_MASK ((uint32) ((uint32) 0x07u << \
                                                                  GLCD_SPIM_SCB_RX_FIFO_STATUS_RD_PTR_POS))
#define GLCD_SPIM_SCB_RX_FIFO_STATUS_WR_PTR_MASK ((uint32) ((uint32) 0x07u << \
                                                                  GLCD_SPIM_SCB_RX_FIFO_STATUS_WR_PTR_POS))


/* GLCD_SPIM_SCB_RX_MATCH_REG */
#define GLCD_SPIM_SCB_RX_MATCH_ADDR_POS     (0u)  /* [7:0]   Slave address                        */
#define GLCD_SPIM_SCB_RX_MATCH_MASK_POS     (16u) /* [23:16] Slave address mask: 0 - doesn't care */
#define GLCD_SPIM_SCB_RX_MATCH_ADDR_MASK    ((uint32) 0xFFu)
#define GLCD_SPIM_SCB_RX_MATCH_MASK_MASK    ((uint32) ((uint32) 0xFFu << GLCD_SPIM_SCB_RX_MATCH_MASK_POS))


/* GLCD_SPIM_SCB_RX_FIFO_WR_REG */
#define GLCD_SPIM_SCB_RX_FIFO_RD_POS    (0u)  /* [15:0] Data read from RX FIFO */
#define GLCD_SPIM_SCB_RX_FIFO_RD_MASK   ((uint32) 0xFFu)


/* GLCD_SPIM_SCB_RX_FIFO_RD_SILENT_REG */
#define GLCD_SPIM_SCB_RX_FIFO_RD_SILENT_POS     (0u)  /* [15:0] Data read from RX FIFO: not remove data from FIFO */
#define GLCD_SPIM_SCB_RX_FIFO_RD_SILENT_MASK    ((uint32) 0xFFu)

/* GLCD_SPIM_SCB_RX_FIFO_RD_SILENT_REG */
#define GLCD_SPIM_SCB_RX_FIFO_RD_SILENT_POS     (0u)  /* [15:0] Data read from RX FIFO: not remove data from FIFO */
#define GLCD_SPIM_SCB_RX_FIFO_RD_SILENT_MASK    ((uint32) 0xFFu)

/* GLCD_SPIM_SCB_EZBUF_DATA_REG */
#define GLCD_SPIM_SCB_EZBUF_DATA_POS   (0u)  /* [7:0] Data from Ez Memory */
#define GLCD_SPIM_SCB_EZBUF_DATA_MASK  ((uint32) 0xFFu)

/*  GLCD_SPIM_SCB_INTR_CAUSE_REG */
#define GLCD_SPIM_SCB_INTR_CAUSE_MASTER_POS  (0u)  /* [0] Master interrupt active                 */
#define GLCD_SPIM_SCB_INTR_CAUSE_SLAVE_POS   (1u)  /* [1] Slave interrupt active                  */
#define GLCD_SPIM_SCB_INTR_CAUSE_TX_POS      (2u)  /* [2] Transmitter interrupt active            */
#define GLCD_SPIM_SCB_INTR_CAUSE_RX_POS      (3u)  /* [3] Receiver interrupt active               */
#define GLCD_SPIM_SCB_INTR_CAUSE_I2C_EC_POS  (4u)  /* [4] Externally clock I2C interrupt active   */
#define GLCD_SPIM_SCB_INTR_CAUSE_SPI_EC_POS  (5u)  /* [5] Externally clocked SPI interrupt active */
#define GLCD_SPIM_SCB_INTR_CAUSE_MASTER      ((uint32) 0x01u)
#define GLCD_SPIM_SCB_INTR_CAUSE_SLAVE       ((uint32) ((uint32) 0x01u << GLCD_SPIM_SCB_INTR_CAUSE_SLAVE_POS))
#define GLCD_SPIM_SCB_INTR_CAUSE_TX          ((uint32) ((uint32) 0x01u << GLCD_SPIM_SCB_INTR_CAUSE_TX_POS))
#define GLCD_SPIM_SCB_INTR_CAUSE_RX          ((uint32) ((uint32) 0x01u << GLCD_SPIM_SCB_INTR_CAUSE_RX_POS))
#define GLCD_SPIM_SCB_INTR_CAUSE_I2C_EC      ((uint32) ((uint32) 0x01u << GLCD_SPIM_SCB_INTR_CAUSE_I2C_EC_POS))
#define GLCD_SPIM_SCB_INTR_CAUSE_SPI_EC      ((uint32) ((uint32) 0x01u << GLCD_SPIM_SCB_INTR_CAUSE_SPI_EC_POS))


/* GLCD_SPIM_SCB_INTR_SPI_EC_REG, GLCD_SPIM_SCB_INTR_SPI_EC_MASK_REG, GLCD_SPIM_SCB_INTR_SPI_EC_MASKED_REG */
#define GLCD_SPIM_SCB_INTR_SPI_EC_WAKE_UP_POS          (0u)  /* [0] Address match: triggers wakeup of chip */
#define GLCD_SPIM_SCB_INTR_SPI_EC_EZBUF_STOP_POS       (1u)  /* [1] Externally clocked Stop detected       */
#define GLCD_SPIM_SCB_INTR_SPI_EC_EZBUF_WRITE_STOP_POS (2u)  /* [2] Externally clocked Write Stop detected */
#define GLCD_SPIM_SCB_INTR_SPI_EC_WAKE_UP              ((uint32) 0x01u)
#define GLCD_SPIM_SCB_INTR_SPI_EC_EZBUF_STOP           ((uint32) ((uint32) 0x01u << \
                                                                    GLCD_SPIM_SCB_INTR_SPI_EC_EZBUF_STOP_POS))
#define GLCD_SPIM_SCB_INTR_SPI_EC_EZBUF_WRITE_STOP     ((uint32) ((uint32) 0x01u << \
                                                                    GLCD_SPIM_SCB_INTR_SPI_EC_EZBUF_WRITE_STOP_POS))


/* GLCD_SPIM_SCB_INTR_I2C_EC, GLCD_SPIM_SCB_INTR_I2C_EC_MASK, GLCD_SPIM_SCB_INTR_I2C_EC_MASKED */
#define GLCD_SPIM_SCB_INTR_I2C_EC_WAKE_UP_POS          (0u)  /* [0] Address match: triggers wakeup of chip */
#define GLCD_SPIM_SCB_INTR_I2C_EC_EZBUF_STOP_POS       (1u)  /* [1] Externally clocked Stop detected       */
#define GLCD_SPIM_SCB_INTR_I2C_EC_EZBUF_WRITE_STOP_POS (2u)  /* [2] Externally clocked Write Stop detected */
#define GLCD_SPIM_SCB_INTR_I2C_EC_WAKE_UP              ((uint32) 0x01u)
#define GLCD_SPIM_SCB_INTR_I2C_EC_EZBUF_STOP           ((uint32) ((uint32) 0x01u << \
                                                                    GLCD_SPIM_SCB_INTR_I2C_EC_EZBUF_STOP_POS))
#define GLCD_SPIM_SCB_INTR_I2C_EC_EZBUF_WRITE_STOP     ((uint32) ((uint32) 0x01u << \
                                                                    GLCD_SPIM_SCB_INTR_I2C_EC_EZBUF_WRITE_STOP_POS))


/* GLCD_SPIM_SCB_INTR_MASTER, GLCD_SPIM_SCB_INTR_MASTER_SET,
   GLCD_SPIM_SCB_INTR_MASTER_MASK, GLCD_SPIM_SCB_INTR_MASTER_MASKED */
#define GLCD_SPIM_SCB_INTR_MASTER_I2C_ARB_LOST_POS   (0u)  /* [0] Master lost arbitration                          */
#define GLCD_SPIM_SCB_INTR_MASTER_I2C_NACK_POS       (1u)  /* [1] Master receives NACK: address or write to slave  */
#define GLCD_SPIM_SCB_INTR_MASTER_I2C_ACK_POS        (2u)  /* [2] Master receives NACK: address or write to slave  */
#define GLCD_SPIM_SCB_INTR_MASTER_I2C_STOP_POS       (4u)  /* [4] Master detects the Stop: only self generated Stop*/
#define GLCD_SPIM_SCB_INTR_MASTER_I2C_BUS_ERROR_POS  (8u)  /* [8] Master detects bus error: misplaced Start or Stop*/
#define GLCD_SPIM_SCB_INTR_MASTER_SPI_DONE_POS       (9u)  /* [9] Master complete trasfer: Only for SPI            */
#define GLCD_SPIM_SCB_INTR_MASTER_I2C_ARB_LOST       ((uint32) 0x01u)
#define GLCD_SPIM_SCB_INTR_MASTER_I2C_NACK           ((uint32) ((uint32) 0x01u << \
                                                                    GLCD_SPIM_SCB_INTR_MASTER_I2C_NACK_POS))
#define GLCD_SPIM_SCB_INTR_MASTER_I2C_ACK            ((uint32) ((uint32) 0x01u << \
                                                                    GLCD_SPIM_SCB_INTR_MASTER_I2C_ACK_POS))
#define GLCD_SPIM_SCB_INTR_MASTER_I2C_STOP           ((uint32) ((uint32) 0x01u << \
                                                                    GLCD_SPIM_SCB_INTR_MASTER_I2C_STOP_POS))
#define GLCD_SPIM_SCB_INTR_MASTER_I2C_BUS_ERROR      ((uint32) ((uint32) 0x01u << \
                                                                    GLCD_SPIM_SCB_INTR_MASTER_I2C_BUS_ERROR_POS))
#define GLCD_SPIM_SCB_INTR_MASTER_SPI_DONE           ((uint32) ((uint32) 0x01u << \
                                                                    GLCD_SPIM_SCB_INTR_MASTER_SPI_DONE_POS))

/*
* GLCD_SPIM_SCB_INTR_SLAVE, GLCD_SPIM_SCB_INTR_SLAVE_SET,
* GLCD_SPIM_SCB_INTR_SLAVE_MASK, GLCD_SPIM_SCB_INTR_SLAVE_MASKED
*/
#define GLCD_SPIM_SCB_INTR_SLAVE_I2C_ARB_LOST_POS         (0u)  /* [0]  Slave lost arbitration                   */
#define GLCD_SPIM_SCB_INTR_SLAVE_I2C_NACK_POS             (1u)  /* [1]  Slave receives NACK: master reads data   */
#define GLCD_SPIM_SCB_INTR_SLAVE_I2C_ACK_POS              (2u)  /* [2]  Slave receives ACK: master reads data    */
#define GLCD_SPIM_SCB_INTR_SLAVE_I2C_WRITE_STOP_POS       (3u)  /* [3]  Slave detects end of write transaction   */
#define GLCD_SPIM_SCB_INTR_SLAVE_I2C_STOP_POS             (4u)  /* [4]  Slave detects end of transaction intened */
#define GLCD_SPIM_SCB_INTR_SLAVE_I2C_START_POS            (5u)  /* [5]  Slave detects Start                      */
#define GLCD_SPIM_SCB_INTR_SLAVE_I2C_ADDR_MATCH_POS       (6u)  /* [6]  Slave address matches                    */
#define GLCD_SPIM_SCB_INTR_SLAVE_I2C_GENERAL_POS          (7u)  /* [7]  General call received                    */
#define GLCD_SPIM_SCB_INTR_SLAVE_I2C_BUS_ERROR_POS        (8u)  /* [8]  Slave detects bus error                  */
#define GLCD_SPIM_SCB_INTR_SLAVE_SPI_EZBUF_WRITE_STOP_POS (9u)  /* [9]  Slave write complete: Only for SPI       */
#define GLCD_SPIM_SCB_INTR_SLAVE_SPI_EZBUF_STOP_POS       (10u) /* [10] Slave end of transaciton: Only for SPI   */
#define GLCD_SPIM_SCB_INTR_SLAVE_SPI_BUS_ERROR_POS        (11u) /* [11] Slave detects bus error: Only for SPI    */
#define GLCD_SPIM_SCB_INTR_SLAVE_I2C_ARB_LOST             ((uint32) 0x01u)
#define GLCD_SPIM_SCB_INTR_SLAVE_I2C_NACK                 ((uint32) ((uint32) 0x01u << \
                                                                    GLCD_SPIM_SCB_INTR_SLAVE_I2C_NACK_POS))
#define GLCD_SPIM_SCB_INTR_SLAVE_I2C_ACK                  ((uint32) ((uint32) 0x01u << \
                                                                    GLCD_SPIM_SCB_INTR_SLAVE_I2C_ACK_POS))
#define GLCD_SPIM_SCB_INTR_SLAVE_I2C_WRITE_STOP           ((uint32) ((uint32) 0x01u << \
                                                                    GLCD_SPIM_SCB_INTR_SLAVE_I2C_WRITE_STOP_POS))
#define GLCD_SPIM_SCB_INTR_SLAVE_I2C_STOP                 ((uint32) ((uint32) 0x01u << \
                                                                    GLCD_SPIM_SCB_INTR_SLAVE_I2C_STOP_POS))
#define GLCD_SPIM_SCB_INTR_SLAVE_I2C_START                ((uint32) ((uint32) 0x01u << \
                                                                    GLCD_SPIM_SCB_INTR_SLAVE_I2C_START_POS))
#define GLCD_SPIM_SCB_INTR_SLAVE_I2C_ADDR_MATCH           ((uint32) ((uint32) 0x01u << \
                                                                    GLCD_SPIM_SCB_INTR_SLAVE_I2C_ADDR_MATCH_POS))
#define GLCD_SPIM_SCB_INTR_SLAVE_I2C_GENERAL              ((uint32) ((uint32) 0x01u << \
                                                                    GLCD_SPIM_SCB_INTR_SLAVE_I2C_GENERAL_POS))
#define GLCD_SPIM_SCB_INTR_SLAVE_I2C_BUS_ERROR            ((uint32) ((uint32) 0x01u << \
                                                                    GLCD_SPIM_SCB_INTR_SLAVE_I2C_BUS_ERROR_POS))
#define GLCD_SPIM_SCB_INTR_SLAVE_SPI_EZBUF_WRITE_STOP     ((uint32) ((uint32) 0x01u << \
                                                                    GLCD_SPIM_SCB_INTR_SLAVE_SPI_EZBUF_WRITE_STOP_POS))
#define GLCD_SPIM_SCB_INTR_SLAVE_SPI_EZBUF_STOP           ((uint32) ((uint32) 0x01u << \
                                                                    GLCD_SPIM_SCB_INTR_SLAVE_SPI_EZBUF_STOP_POS))
#define GLCD_SPIM_SCB_INTR_SLAVE_SPI_BUS_ERROR           ((uint32) ((uint32) 0x01u << \
                                                                    GLCD_SPIM_SCB_INTR_SLAVE_SPI_BUS_ERROR_POS))


/*
* GLCD_SPIM_SCB_INTR_TX, GLCD_SPIM_SCB_INTR_TX_SET,
* GLCD_SPIM_SCB_INTR_TX_MASK, GLCD_SPIM_SCB_INTR_TX_MASKED
*/
#define GLCD_SPIM_SCB_INTR_TX_TRIGGER_POS        (0u)  /* [0]  Trigger on TX FIFO entires                       */
#define GLCD_SPIM_SCB_INTR_TX_NOT_FULL_POS       (1u)  /* [1]  TX FIFO is not full                              */
#define GLCD_SPIM_SCB_INTR_TX_EMPTY_POS          (4u)  /* [4]  TX FIFO is empty                                 */
#define GLCD_SPIM_SCB_INTR_TX_OVERFLOW_POS       (5u)  /* [5]  Attempt to write to a full TX FIFO               */
#define GLCD_SPIM_SCB_INTR_TX_UNDERFLOW_POS      (6u)  /* [6]  Attempt to read from an empty TX FIFO            */
#define GLCD_SPIM_SCB_INTR_TX_BLOCKED_POS        (7u)  /* [7]  No access to the EZ memory                       */
#define GLCD_SPIM_SCB_INTR_TX_UART_NACK_POS      (8u)  /* [8]  UART transmitter received a NACK: SmartCard mode */
#define GLCD_SPIM_SCB_INTR_TX_UART_DONE_POS      (9u)  /* [9]  UART transmitter done even                       */
#define GLCD_SPIM_SCB_INTR_TX_UART_ARB_LOST_POS  (10u) /* [10] UART lost arbitration: LIN or SmartCard          */
#define GLCD_SPIM_SCB_INTR_TX_TRIGGER            ((uint32) 0x01u)
#define GLCD_SPIM_SCB_INTR_TX_NOT_FULL           ((uint32) ((uint32) 0x01u << \
                                                                        GLCD_SPIM_SCB_INTR_TX_NOT_FULL_POS))
#define GLCD_SPIM_SCB_INTR_TX_EMPTY              ((uint32) ((uint32) 0x01u << \
                                                                        GLCD_SPIM_SCB_INTR_TX_EMPTY_POS))
#define GLCD_SPIM_SCB_INTR_TX_OVERFLOW           ((uint32) ((uint32) 0x01u << \
                                                                        GLCD_SPIM_SCB_INTR_TX_OVERFLOW_POS))
#define GLCD_SPIM_SCB_INTR_TX_UNDERFLOW          ((uint32) ((uint32) 0x01u << \
                                                                        GLCD_SPIM_SCB_INTR_TX_UNDERFLOW_POS))
#define GLCD_SPIM_SCB_INTR_TX_BLOCKED            ((uint32) ((uint32) 0x01u << \
                                                                        GLCD_SPIM_SCB_INTR_TX_BLOCKED_POS))
#define GLCD_SPIM_SCB_INTR_TX_UART_NACK          ((uint32) ((uint32) 0x01u << \
                                                                        GLCD_SPIM_SCB_INTR_TX_UART_NACK_POS))
#define GLCD_SPIM_SCB_INTR_TX_UART_DONE          ((uint32) ((uint32) 0x01u << \
                                                                        GLCD_SPIM_SCB_INTR_TX_UART_DONE_POS))
#define GLCD_SPIM_SCB_INTR_TX_UART_ARB_LOST      ((uint32) ((uint32) 0x01u << \
                                                                        GLCD_SPIM_SCB_INTR_TX_UART_ARB_LOST_POS))


/*
* GLCD_SPIM_SCB_INTR_RX, GLCD_SPIM_SCB_INTR_RX_SET,
* GLCD_SPIM_SCB_INTR_RX_MASK, GLCD_SPIM_SCB_INTR_RX_MASKED
*/
#define GLCD_SPIM_SCB_INTR_RX_TRIGGER_POS        (0u)   /* [0]  Trigger on RX FIFO entires            */
#define GLCD_SPIM_SCB_INTR_RX_NOT_EMPTY_POS      (2u)   /* [2]  RX FIFO is not empty                  */
#define GLCD_SPIM_SCB_INTR_RX_FULL_POS           (3u)   /* [3]  RX FIFO is full                       */
#define GLCD_SPIM_SCB_INTR_RX_OVERFLOW_POS       (5u)   /* [5]  Attempt to write to a full RX FIFO    */
#define GLCD_SPIM_SCB_INTR_RX_UNDERFLOW_POS      (6u)   /* [6]  Attempt to read from an empty RX FIFO */
#define GLCD_SPIM_SCB_INTR_RX_BLOCKED_POS        (7u)   /* [7]  No access to the EZ memory            */
#define GLCD_SPIM_SCB_INTR_RX_FRAME_ERROR_POS    (8u)   /* [8]  Frame error in received data frame    */
#define GLCD_SPIM_SCB_INTR_RX_PARITY_ERROR_POS   (9u)   /* [9]  Parity error in received data frame   */
#define GLCD_SPIM_SCB_INTR_RX_BAUD_DETECT_POS    (10u)  /* [10] LIN baudrate detection is completed   */
#define GLCD_SPIM_SCB_INTR_RX_BREAK_DETECT_POS   (11u)  /* [11] Break detection is successful         */
#define GLCD_SPIM_SCB_INTR_RX_TRIGGER            ((uint32) 0x01u)
#define GLCD_SPIM_SCB_INTR_RX_NOT_EMPTY          ((uint32) ((uint32) 0x01u << \
                                                                        GLCD_SPIM_SCB_INTR_RX_NOT_EMPTY_POS))
#define GLCD_SPIM_SCB_INTR_RX_FULL               ((uint32) ((uint32) 0x01u << \
                                                                        GLCD_SPIM_SCB_INTR_RX_FULL_POS))
#define GLCD_SPIM_SCB_INTR_RX_OVERFLOW           ((uint32) ((uint32) 0x01u << \
                                                                        GLCD_SPIM_SCB_INTR_RX_OVERFLOW_POS))
#define GLCD_SPIM_SCB_INTR_RX_UNDERFLOW          ((uint32) ((uint32) 0x01u << \
                                                                        GLCD_SPIM_SCB_INTR_RX_UNDERFLOW_POS))
#define GLCD_SPIM_SCB_INTR_RX_BLOCKED            ((uint32) ((uint32) 0x01u << \
                                                                        GLCD_SPIM_SCB_INTR_RX_BLOCKED_POS))
#define GLCD_SPIM_SCB_INTR_RX_FRAME_ERROR        ((uint32) ((uint32) 0x01u << \
                                                                        GLCD_SPIM_SCB_INTR_RX_FRAME_ERROR_POS))
#define GLCD_SPIM_SCB_INTR_RX_PARITY_ERROR       ((uint32) ((uint32) 0x01u << \
                                                                        GLCD_SPIM_SCB_INTR_RX_PARITY_ERROR_POS))
#define GLCD_SPIM_SCB_INTR_RX_BAUD_DETECT        ((uint32) ((uint32) 0x01u << \
                                                                        GLCD_SPIM_SCB_INTR_RX_BAUD_DETECT_POS))
#define GLCD_SPIM_SCB_INTR_RX_BREAK_DETECT       ((uint32) ((uint32) 0x01u << \
                                                                        GLCD_SPIM_SCB_INTR_RX_BREAK_DETECT_POS))


/* Define all interupt soureces */
#define GLCD_SPIM_SCB_INTR_I2C_EC_ALL    (GLCD_SPIM_SCB_INTR_I2C_EC_WAKE_UP    | \
                                             GLCD_SPIM_SCB_INTR_I2C_EC_EZBUF_STOP | \
                                             GLCD_SPIM_SCB_INTR_I2C_EC_EZBUF_WRITE_STOP)

#define GLCD_SPIM_SCB_INTR_SPI_EC_ALL    (GLCD_SPIM_SCB_INTR_SPI_EC_WAKE_UP    | \
                                             GLCD_SPIM_SCB_INTR_SPI_EC_EZBUF_STOP | \
                                             GLCD_SPIM_SCB_INTR_SPI_EC_EZBUF_WRITE_STOP)

#define GLCD_SPIM_SCB_INTR_MASTER_ALL    (GLCD_SPIM_SCB_INTR_MASTER_I2C_ARB_LOST  | \
                                             GLCD_SPIM_SCB_INTR_MASTER_I2C_NACK      | \
                                             GLCD_SPIM_SCB_INTR_MASTER_I2C_ACK       | \
                                             GLCD_SPIM_SCB_INTR_MASTER_I2C_STOP      | \
                                             GLCD_SPIM_SCB_INTR_MASTER_I2C_BUS_ERROR | \
                                             GLCD_SPIM_SCB_INTR_MASTER_SPI_DONE )

#define GLCD_SPIM_SCB_INTR_SLAVE_ALL     (GLCD_SPIM_SCB_INTR_SLAVE_I2C_ARB_LOST      | \
                                             GLCD_SPIM_SCB_INTR_SLAVE_I2C_NACK          | \
                                             GLCD_SPIM_SCB_INTR_SLAVE_I2C_ACK           | \
                                             GLCD_SPIM_SCB_INTR_SLAVE_I2C_WRITE_STOP    | \
                                             GLCD_SPIM_SCB_INTR_SLAVE_I2C_STOP          | \
                                             GLCD_SPIM_SCB_INTR_SLAVE_I2C_START         | \
                                             GLCD_SPIM_SCB_INTR_SLAVE_I2C_ADDR_MATCH    | \
                                             GLCD_SPIM_SCB_INTR_SLAVE_I2C_GENERAL       | \
                                             GLCD_SPIM_SCB_INTR_SLAVE_I2C_BUS_ERROR     | \
                                             GLCD_SPIM_SCB_INTR_SLAVE_SPI_EZBUF_WRITE_STOP | \
                                             GLCD_SPIM_SCB_INTR_SLAVE_SPI_EZBUF_STOP       | \
                                             GLCD_SPIM_SCB_INTR_SLAVE_SPI_BUS_ERROR)

#define GLCD_SPIM_SCB_INTR_TX_ALL        (GLCD_SPIM_SCB_INTR_TX_TRIGGER   | \
                                             GLCD_SPIM_SCB_INTR_TX_NOT_FULL  | \
                                             GLCD_SPIM_SCB_INTR_TX_EMPTY     | \
                                             GLCD_SPIM_SCB_INTR_TX_OVERFLOW  | \
                                             GLCD_SPIM_SCB_INTR_TX_UNDERFLOW | \
                                             GLCD_SPIM_SCB_INTR_TX_BLOCKED   | \
                                             GLCD_SPIM_SCB_INTR_TX_UART_NACK | \
                                             GLCD_SPIM_SCB_INTR_TX_UART_DONE | \
                                             GLCD_SPIM_SCB_INTR_TX_UART_ARB_LOST)

#define GLCD_SPIM_SCB_INTR_RX_ALL        (GLCD_SPIM_SCB_INTR_RX_TRIGGER      | \
                                             GLCD_SPIM_SCB_INTR_RX_NOT_EMPTY    | \
                                             GLCD_SPIM_SCB_INTR_RX_FULL         | \
                                             GLCD_SPIM_SCB_INTR_RX_OVERFLOW     | \
                                             GLCD_SPIM_SCB_INTR_RX_UNDERFLOW    | \
                                             GLCD_SPIM_SCB_INTR_RX_BLOCKED      | \
                                             GLCD_SPIM_SCB_INTR_RX_FRAME_ERROR  | \
                                             GLCD_SPIM_SCB_INTR_RX_PARITY_ERROR | \
                                             GLCD_SPIM_SCB_INTR_RX_BAUD_DETECT  | \
                                             GLCD_SPIM_SCB_INTR_RX_BREAK_DETECT)

/* General usage HW definitions */
#define GLCD_SPIM_SCB_ONE_BYTE_WIDTH (8u)   /* Number of bits in one byte           */
#define GLCD_SPIM_SCB_FIFO_SIZE      (8u)   /* Size of TX or RX FIFO: defined by HW */
#define GLCD_SPIM_SCB_EZBUFFER_SIZE  (32u)  /* EZ Buffer size: defined by HW        */

/* I2C and EZI2C slave address defines */
#define GLCD_SPIM_SCB_I2C_SLAVE_ADDR_POS    (0x01u)    /* 7-bit address shift */
#define GLCD_SPIM_SCB_I2C_SLAVE_ADDR_MASK   (0xFEu)    /* 8-bit address mask */

/* OVS constants for IrDA Low Power operation */
#define GLCD_SPIM_SCB_CTRL_OVS_IRDA_LP_OVS16     (0x00u)
#define GLCD_SPIM_SCB_CTRL_OVS_IRDA_LP_OVS32     (0x01u)
#define GLCD_SPIM_SCB_CTRL_OVS_IRDA_LP_OVS48     (0x02u)
#define GLCD_SPIM_SCB_CTRL_OVS_IRDA_LP_OVS96     (0x03u)
#define GLCD_SPIM_SCB_CTRL_OVS_IRDA_LP_OVS192    (0x04u)
#define GLCD_SPIM_SCB_CTRL_OVS_IRDA_LP_OVS768    (0x05u)
#define GLCD_SPIM_SCB_CTRL_OVS_IRDA_LP_OVS1536   (0x06u)

/* OVS constant for IrDA */
#define GLCD_SPIM_SCB_CTRL_OVS_IRDA_OVS16        (GLCD_SPIM_SCB_UART_IRDA_LP_OVS16)


/***************************************
*    SCB Common Macro Definitions
***************************************/

/* 
* Re-enables SCB IP: this cause partial reset of IP: state, status, TX and RX FIFOs. 
* The triggered interrupts remains set.
*/
#define GLCD_SPIM_SCB_SCB_SW_RESET \
                        do{ \
                            GLCD_SPIM_SCB_CTRL_REG &= ((uint32) ~GLCD_SPIM_SCB_CTRL_ENABLED ); \
                            GLCD_SPIM_SCB_CTRL_REG |= ((uint32)  GLCD_SPIM_SCB_CTRL_ENABLED ); \
                        }while(0)

/* TX FIFO macro */
#define GLCD_SPIM_SCB_CLEAR_TX_FIFO \
                            do{        \
                                GLCD_SPIM_SCB_TX_FIFO_CTRL_REG |= ((uint32)  GLCD_SPIM_SCB_TX_FIFO_CTRL_CLEAR); \
                                GLCD_SPIM_SCB_TX_FIFO_CTRL_REG &= ((uint32) ~GLCD_SPIM_SCB_TX_FIFO_CTRL_CLEAR); \
                            }while(0)

#define GLCD_SPIM_SCB_GET_TX_FIFO_ENTRIES    (GLCD_SPIM_SCB_TX_FIFO_STATUS_REG & \
                                                 GLCD_SPIM_SCB_TX_FIFO_STATUS_USED_MASK)

#define GLCD_SPIM_SCB_GET_TX_FIFO_SR_VALID   ((0u != (GLCD_SPIM_SCB_TX_FIFO_STATUS_REG & \
                                                         GLCD_SPIM_SCB_TX_FIFO_SR_VALID)) ? (1u) : (0u))

/* RX FIFO macro */
#define GLCD_SPIM_SCB_CLEAR_RX_FIFO \
                            do{        \
                                GLCD_SPIM_SCB_RX_FIFO_CTRL_REG |= ((uint32)  GLCD_SPIM_SCB_RX_FIFO_CTRL_CLEAR); \
                                GLCD_SPIM_SCB_RX_FIFO_CTRL_REG &= ((uint32) ~GLCD_SPIM_SCB_RX_FIFO_CTRL_CLEAR); \
                            }while(0)

#define GLCD_SPIM_SCB_GET_RX_FIFO_ENTRIES    (GLCD_SPIM_SCB_RX_FIFO_STATUS_REG & \
                                                    GLCD_SPIM_SCB_RX_FIFO_STATUS_USED_MASK)

#define GLCD_SPIM_SCB_GET_RX_FIFO_SR_VALID   ((0u != (GLCD_SPIM_SCB_RX_FIFO_STATUS_REG & \
                                                         GLCD_SPIM_SCB_RX_FIFO_SR_VALID)) ? (1u) : (0u))

/* Writes interrupt source: set sourceMask bits in GLCD_SPIM_SCB_INTR_X_MASK_REG */
#define GLCD_SPIM_SCB_WRITE_INTR_I2C_EC_MASK(sourceMask) \
                                                do{         \
                                                    GLCD_SPIM_SCB_INTR_I2C_EC_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#define GLCD_SPIM_SCB_WRITE_INTR_SPI_EC_MASK(sourceMask) \
                                                do{         \
                                                    GLCD_SPIM_SCB_INTR_SPI_EC_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#define GLCD_SPIM_SCB_WRITE_INTR_MASTER_MASK(sourceMask) \
                                                do{         \
                                                    GLCD_SPIM_SCB_INTR_MASTER_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#define GLCD_SPIM_SCB_WRITE_INTR_SLAVE_MASK(sourceMask)  \
                                                do{         \
                                                    GLCD_SPIM_SCB_INTR_SLAVE_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#define GLCD_SPIM_SCB_WRITE_INTR_TX_MASK(sourceMask)     \
                                                do{         \
                                                    GLCD_SPIM_SCB_INTR_TX_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#define GLCD_SPIM_SCB_WRITE_INTR_RX_MASK(sourceMask)     \
                                                do{         \
                                                    GLCD_SPIM_SCB_INTR_RX_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

/* Enables interrupt source: set sourceMask bits in GLCD_SPIM_SCB_INTR_X_MASK_REG */
#define GLCD_SPIM_SCB_ENABLE_INTR_I2C_EC(sourceMask) \
                                                do{     \
                                                    GLCD_SPIM_SCB_INTR_I2C_EC_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

#define GLCD_SPIM_SCB_ENABLE_INTR_SPI_EC(sourceMask) \
                                                do{     \
                                                    GLCD_SPIM_SCB_INTR_SPI_EC_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

#define GLCD_SPIM_SCB_ENABLE_INTR_MASTER(sourceMask) \
                                                do{     \
                                                    GLCD_SPIM_SCB_INTR_MASTER_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

#define GLCD_SPIM_SCB_ENABLE_INTR_SLAVE(sourceMask)  \
                                                do{     \
                                                    GLCD_SPIM_SCB_INTR_SLAVE_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

#define GLCD_SPIM_SCB_ENABLE_INTR_TX(sourceMask)     \
                                                do{     \
                                                    GLCD_SPIM_SCB_INTR_TX_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

#define GLCD_SPIM_SCB_ENABLE_INTR_RX(sourceMask)     \
                                                do{     \
                                                    GLCD_SPIM_SCB_INTR_RX_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

/* Disables interrupt source: clear sourceMask bits in GLCD_SPIM_SCB_INTR_X_MASK_REG */
#define GLCD_SPIM_SCB_DISABLE_INTR_I2C_EC(sourceMask) \
                                do{                      \
                                    GLCD_SPIM_SCB_INTR_I2C_EC_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                }while(0)

#define GLCD_SPIM_SCB_DISABLE_INTR_SPI_EC(sourceMask) \
                                do{                      \
                                    GLCD_SPIM_SCB_INTR_SPI_EC_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                 }while(0)

#define GLCD_SPIM_SCB_DISABLE_INTR_MASTER(sourceMask) \
                                do{                      \
                                GLCD_SPIM_SCB_INTR_MASTER_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                }while(0)

#define GLCD_SPIM_SCB_DISABLE_INTR_SLAVE(sourceMask) \
                                do{                     \
                                    GLCD_SPIM_SCB_INTR_SLAVE_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                }while(0)

#define GLCD_SPIM_SCB_DISABLE_INTR_TX(sourceMask)    \
                                do{                     \
                                    GLCD_SPIM_SCB_INTR_TX_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                 }while(0)

#define GLCD_SPIM_SCB_DISABLE_INTR_RX(sourceMask)    \
                                do{                     \
                                    GLCD_SPIM_SCB_INTR_RX_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                }while(0)

/* Sets interrupt sources: write sourceMask bits in GLCD_SPIM_SCB_INTR_X_SET_REG */
#define GLCD_SPIM_SCB_SET_INTR_MASTER(sourceMask)    \
                                                do{     \
                                                    GLCD_SPIM_SCB_INTR_MASTER_SET_REG = (uint32) (sourceMask); \
                                                }while(0)

#define GLCD_SPIM_SCB_SET_INTR_SLAVE(sourceMask) \
                                                do{ \
                                                    GLCD_SPIM_SCB_INTR_SLAVE_SET_REG = (uint32) (sourceMask); \
                                                }while(0)

#define GLCD_SPIM_SCB_SET_INTR_TX(sourceMask)    \
                                                do{ \
                                                    GLCD_SPIM_SCB_INTR_TX_SET_REG = (uint32) (sourceMask); \
                                                }while(0)

#define GLCD_SPIM_SCB_SET_INTR_RX(sourceMask)    \
                                                do{ \
                                                    GLCD_SPIM_SCB_INTR_RX_SET_REG = (uint32) (sourceMask); \
                                                }while(0)

/* Clears interrupt sources: write sourceMask bits in GLCD_SPIM_SCB_INTR_X_REG */
#define GLCD_SPIM_SCB_CLEAR_INTR_I2C_EC(sourceMask)  \
                                                do{     \
                                                    GLCD_SPIM_SCB_INTR_I2C_EC_REG = (uint32) (sourceMask); \
                                                }while(0)

#define GLCD_SPIM_SCB_CLEAR_INTR_SPI_EC(sourceMask)  \
                                                do{     \
                                                    GLCD_SPIM_SCB_INTR_SPI_EC_REG = (uint32) (sourceMask); \
                                                }while(0)

#define GLCD_SPIM_SCB_CLEAR_INTR_MASTER(sourceMask)  \
                                                do{     \
                                                    GLCD_SPIM_SCB_INTR_MASTER_REG = (uint32) (sourceMask); \
                                                }while(0)

#define GLCD_SPIM_SCB_CLEAR_INTR_SLAVE(sourceMask)   \
                                                do{     \
                                                    GLCD_SPIM_SCB_INTR_SLAVE_REG  = (uint32) (sourceMask); \
                                                }while(0)

#define GLCD_SPIM_SCB_CLEAR_INTR_TX(sourceMask)      \
                                                do{     \
                                                    GLCD_SPIM_SCB_INTR_TX_REG     = (uint32) (sourceMask); \
                                                }while(0)

#define GLCD_SPIM_SCB_CLEAR_INTR_RX(sourceMask)      \
                                                do{     \
                                                    GLCD_SPIM_SCB_INTR_RX_REG     = (uint32) (sourceMask); \
                                                }while(0)

/* Return true if sourceMask is set in GLCD_SPIM_SCB_INTR_CAUSE_REG */
#define GLCD_SPIM_SCB_CHECK_CAUSE_INTR(sourceMask)    (0u != (GLCD_SPIM_SCB_INTR_CAUSE_REG & (sourceMask)))

/* Return true if sourceMask is set in  INTR_X_MASKED_REG */
#define GLCD_SPIM_SCB_CHECK_INTR_EC_I2C(sourceMask)  (0u != (GLCD_SPIM_SCB_INTR_I2C_EC_REG & (sourceMask)))
#define GLCD_SPIM_SCB_CHECK_INTR_EC_SPI(sourceMask)  (0u != (GLCD_SPIM_SCB_INTR_SPI_EC_REG & (sourceMask)))
#define GLCD_SPIM_SCB_CHECK_INTR_MASTER(sourceMask)  (0u != (GLCD_SPIM_SCB_INTR_MASTER_REG & (sourceMask)))
#define GLCD_SPIM_SCB_CHECK_INTR_SLAVE(sourceMask)   (0u != (GLCD_SPIM_SCB_INTR_SLAVE_REG  & (sourceMask)))
#define GLCD_SPIM_SCB_CHECK_INTR_TX(sourceMask)      (0u != (GLCD_SPIM_SCB_INTR_TX_REG     & (sourceMask)))
#define GLCD_SPIM_SCB_CHECK_INTR_RX(sourceMask)      (0u != (GLCD_SPIM_SCB_INTR_RX_REG     & (sourceMask)))

/* Return true if sourceMask is set in GLCD_SPIM_SCB_INTR_X_MASKED_REG */
#define GLCD_SPIM_SCB_CHECK_INTR_I2C_EC_MASKED(sourceMask)   (0u != (GLCD_SPIM_SCB_INTR_I2C_EC_MASKED_REG & \
                                                                       (sourceMask)))
#define GLCD_SPIM_SCB_CHECK_INTR_SPI_EC_MASKED(sourceMask)   (0u != (GLCD_SPIM_SCB_INTR_SPI_EC_MASKED_REG & \
                                                                       (sourceMask)))
#define GLCD_SPIM_SCB_CHECK_INTR_MASTER_MASKED(sourceMask)   (0u != (GLCD_SPIM_SCB_INTR_MASTER_MASKED_REG & \
                                                                       (sourceMask)))
#define GLCD_SPIM_SCB_CHECK_INTR_SLAVE_MASKED(sourceMask)    (0u != (GLCD_SPIM_SCB_INTR_SLAVE_MASKED_REG  & \
                                                                       (sourceMask)))
#define GLCD_SPIM_SCB_CHECK_INTR_TX_MASKED(sourceMask)       (0u != (GLCD_SPIM_SCB_INTR_TX_MASKED_REG     & \
                                                                       (sourceMask)))
#define GLCD_SPIM_SCB_CHECK_INTR_RX_MASKED(sourceMask)       (0u != (GLCD_SPIM_SCB_INTR_RX_MASKED_REG     & \
                                                                       (sourceMask)))

/* Return true if sourceMask is set in GLCD_SPIM_SCB_CTRL_REG: generaly is used to check enable bit */
#define GLCD_SPIM_SCB_GET_CTRL_ENABLED    (0u != (GLCD_SPIM_SCB_CTRL_REG & GLCD_SPIM_SCB_CTRL_ENABLED))

#define GLCD_SPIM_SCB_CHECK_SLAVE_AUTO_ADDR_NACK     (0u != (GLCD_SPIM_SCB_I2C_CTRL_REG & \
                                                                GLCD_SPIM_SCB_I2C_CTRL_S_NOT_READY_DATA_NACK))


/***************************************
*      I2C Macro Definitions
***************************************/

/* Enable auto ACK/NACK */
#define GLCD_SPIM_SCB_ENABLE_SLAVE_AUTO_ADDR_NACK \
                            do{                      \
                                GLCD_SPIM_SCB_I2C_CTRL_REG |= GLCD_SPIM_SCB_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define GLCD_SPIM_SCB_ENABLE_SLAVE_AUTO_DATA_ACK \
                            do{                     \
                                GLCD_SPIM_SCB_I2C_CTRL_REG |= GLCD_SPIM_SCB_I2C_CTRL_S_READY_DATA_ACK; \
                            }while(0)

#define GLCD_SPIM_SCB_ENABLE_SLAVE_AUTO_DATA_NACK \
                            do{                      \
                                GLCD_SPIM_SCB_I2C_CTRL_REG |= GLCD_SPIM_SCB_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define GLCD_SPIM_SCB_ENABLE_MASTER_AUTO_DATA_ACK \
                            do{                      \
                                GLCD_SPIM_SCB_I2C_CTRL_REG |= GLCD_SPIM_SCB_I2C_CTRL_M_READY_DATA_ACK; \
                            }while(0)

#define GLCD_SPIM_SCB_ENABLE_MASTER_AUTO_DATA_NACK \
                            do{                       \
                                GLCD_SPIM_SCB_I2C_CTRL_REG |= GLCD_SPIM_SCB_I2C_CTRL_M_NOT_READY_DATA_NACK; \
                            }while(0)

/* Disable auto ACK/NACK */
#define GLCD_SPIM_SCB_DISABLE_SLAVE_AUTO_ADDR_NACK \
                            do{                       \
                                GLCD_SPIM_SCB_I2C_CTRL_REG &= ~GLCD_SPIM_SCB_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define GLCD_SPIM_SCB_DISABLE_SLAVE_AUTO_DATA_ACK \
                            do{                      \
                                GLCD_SPIM_SCB_I2C_CTRL_REG &= ~GLCD_SPIM_SCB_I2C_CTRL_S_READY_DATA_ACK; \
                            }while(0)

#define GLCD_SPIM_SCB_DISABLE_SLAVE_AUTO_DATA_NACK \
                            do{                       \
                                GLCD_SPIM_SCB_I2C_CTRL_REG &= ~GLCD_SPIM_SCB_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define GLCD_SPIM_SCB_DISABLE_MASTER_AUTO_DATA_ACK \
                            do{                       \
                                GLCD_SPIM_SCB_I2C_CTRL_REG &= ~GLCD_SPIM_SCB_I2C_CTRL_M_READY_DATA_ACK; \
                            }while(0)

#define GLCD_SPIM_SCB_DISABLE_MASTER_AUTO_DATA_NACK \
                            do{                        \
                                GLCD_SPIM_SCB_I2C_CTRL_REG &= ~GLCD_SPIM_SCB_I2C_CTRL_M_NOT_READY_DATA_NACK; \
                            }while(0)

/* Enable Slave autoACK/NACK Data */
#define GLCD_SPIM_SCB_ENABLE_SLAVE_AUTO_DATA \
                            do{                 \
                                GLCD_SPIM_SCB_I2C_CTRL_REG |= (GLCD_SPIM_SCB_I2C_CTRL_S_READY_DATA_ACK |      \
                                                                  GLCD_SPIM_SCB_I2C_CTRL_S_NOT_READY_DATA_NACK); \
                            }while(0)

/* Disable Slave autoACK/NACK Data */
#define GLCD_SPIM_SCB_DISABLE_SLAVE_AUTO_DATA \
                            do{                  \
                                GLCD_SPIM_SCB_I2C_CTRL_REG &= ((uint32) \
                                                                  ~(GLCD_SPIM_SCB_I2C_CTRL_S_READY_DATA_ACK |       \
                                                                    GLCD_SPIM_SCB_I2C_CTRL_S_NOT_READY_DATA_NACK)); \
                            }while(0)

/* Disable Master autoACK/NACK Data */
#define GLCD_SPIM_SCB_DISABLE_MASTER_AUTO_DATA \
                            do{                   \
                                GLCD_SPIM_SCB_I2C_CTRL_REG &= ((uint32) \
                                                                  ~(GLCD_SPIM_SCB_I2C_CTRL_M_READY_DATA_ACK |       \
                                                                    GLCD_SPIM_SCB_I2C_CTRL_M_NOT_READY_DATA_NACK)); \
                            }while(0)

/* Master commands */
#define GLCD_SPIM_SCB_I2C_MASTER_GENERATE_START \
                            do{                    \
                                GLCD_SPIM_SCB_I2C_MASTER_CMD_REG = GLCD_SPIM_SCB_I2C_MASTER_CMD_M_START_ON_IDLE; \
                            }while(0)

#define GLCD_SPIM_SCB_I2C_MASTER_CLEAR_START \
                            do{                 \
                                GLCD_SPIM_SCB_I2C_MASTER_CMD_REG =  ((uint32) 0u); \
                            }while(0)

#define GLCD_SPIM_SCB_I2C_MASTER_GENERATE_RESTART GLCD_SPIM_SCB_I2CReStartGeneration()

#define GLCD_SPIM_SCB_I2C_MASTER_GENERATE_STOP \
                            do{                   \
                                GLCD_SPIM_SCB_I2C_MASTER_CMD_REG =                                            \
                                    (GLCD_SPIM_SCB_I2C_MASTER_CMD_M_STOP |                                    \
                                        (GLCD_SPIM_SCB_CHECK_I2C_STATUS(GLCD_SPIM_SCB_I2C_STATUS_M_READ) ? \
                                            (GLCD_SPIM_SCB_I2C_MASTER_CMD_M_NACK) : (0u)));                   \
                            }while(0)

#define GLCD_SPIM_SCB_I2C_MASTER_GENERATE_ACK \
                            do{                  \
                                GLCD_SPIM_SCB_I2C_MASTER_CMD_REG = GLCD_SPIM_SCB_I2C_MASTER_CMD_M_ACK; \
                            }while(0)

#define GLCD_SPIM_SCB_I2C_MASTER_GENERATE_NACK \
                            do{                   \
                                GLCD_SPIM_SCB_I2C_MASTER_CMD_REG = GLCD_SPIM_SCB_I2C_MASTER_CMD_M_NACK; \
                            }while(0)

/* Slave comamnds */
#define GLCD_SPIM_SCB_I2C_SLAVE_GENERATE_ACK \
                            do{                 \
                                GLCD_SPIM_SCB_I2C_SLAVE_CMD_REG = GLCD_SPIM_SCB_I2C_SLAVE_CMD_S_ACK; \
                            }while(0)

#define GLCD_SPIM_SCB_I2C_SLAVE_GENERATE_NACK \
                            do{                  \
                                GLCD_SPIM_SCB_I2C_SLAVE_CMD_REG = GLCD_SPIM_SCB_I2C_SLAVE_CMD_S_NACK; \
                            }while(0)


/* Return 8-bit address. The input address should be 7-bits */
#define GLCD_SPIM_SCB_GET_I2C_8BIT_ADDRESS(addr) (((uint32) ((uint32) (addr) << \
                                                                    GLCD_SPIM_SCB_I2C_SLAVE_ADDR_POS)) & \
                                                                        GLCD_SPIM_SCB_I2C_SLAVE_ADDR_MASK)

/* Adjust SDA filter Trim settings */
#define GLCD_SPIM_SCB_DEFAULT_I2C_CFG_SDA_FILT_TRIM  (0x02u)
#define GLCD_SPIM_SCB_EC_AM_I2C_CFG_SDA_FILT_TRIM    (0x03u)

#define GLCD_SPIM_SCB_SET_I2C_CFG_SDA_FILT_TRIM(sdaTrim) \
        do{                                                 \
            GLCD_SPIM_SCB_I2C_CFG_REG =                  \
                            ((GLCD_SPIM_SCB_I2C_CFG_REG & (uint32) ~GLCD_SPIM_SCB_I2C_CFG_SDA_FILT_TRIM_MASK) | \
                             ((uint32) ((uint32) (sdaTrim) <<GLCD_SPIM_SCB_I2C_CFG_SDA_FILT_TRIM_POS)));           \
        }while(0)

/* Returns slave select number in SPI_CTRL */
#define GLCD_SPIM_SCB_GET_SPI_CTRL_SS(activeSelect) (((uint32) ((uint32) (activeSelect) << \
                                                                    GLCD_SPIM_SCB_SPI_CTRL_SLAVE_SELECT_POS)) & \
                                                                        GLCD_SPIM_SCB_SPI_CTRL_SLAVE_SELECT_MASK)

/* Returns true if bit is set in GLCD_SPIM_SCB_I2C_STATUS_REG */
#define GLCD_SPIM_SCB_CHECK_I2C_STATUS(sourceMask)   (0u != (GLCD_SPIM_SCB_I2C_STATUS_REG & (sourceMask)))

/* Returns true if bit is set in GLCD_SPIM_SCB_SPI_STATUS_REG */
#define GLCD_SPIM_SCB_CHECK_SPI_STATUS(sourceMask)   (0u != (GLCD_SPIM_SCB_SPI_STATUS_REG & (sourceMask)))


/***************************************
*       SCB Init Macros Definitions
***************************************/

/* GLCD_SPIM_SCB_CTRL */
#define GLCD_SPIM_SCB_GET_CTRL_OVS(oversample)   ((((uint32) (oversample)) - 1u) & GLCD_SPIM_SCB_CTRL_OVS_MASK)

#define GLCD_SPIM_SCB_GET_CTRL_EC_OP_MODE(opMode)        ((0u != (opMode)) ? \
                                                                (GLCD_SPIM_SCB_CTRL_EC_OP_MODE)  : (0u))

#define GLCD_SPIM_SCB_GET_CTRL_EC_AM_MODE(amMode)        ((0u != (amMode)) ? \
                                                                (GLCD_SPIM_SCB_CTRL_EC_AM_MODE)  : (0u))

#define GLCD_SPIM_SCB_GET_CTRL_BLOCK(block)              ((0u != (block))  ? \
                                                                (GLCD_SPIM_SCB_CTRL_BLOCK)       : (0u))

#define GLCD_SPIM_SCB_GET_CTRL_ADDR_ACCEPT(acceptAddr)   ((0u != (acceptAddr)) ? \
                                                                (GLCD_SPIM_SCB_CTRL_ADDR_ACCEPT) : (0u))

/* GLCD_SPIM_SCB_I2C_CTRL */
#define GLCD_SPIM_SCB_GET_I2C_CTRL_HIGH_PHASE_OVS(oversampleHigh) (((uint32) (oversampleHigh) - 1u) & \
                                                                        GLCD_SPIM_SCB_I2C_CTRL_HIGH_PHASE_OVS_MASK)

#define GLCD_SPIM_SCB_GET_I2C_CTRL_LOW_PHASE_OVS(oversampleLow)   (((uint32) (((uint32) (oversampleLow) - 1u) << \
                                                                    GLCD_SPIM_SCB_I2C_CTRL_LOW_PHASE_OVS_POS)) &  \
                                                                    GLCD_SPIM_SCB_I2C_CTRL_LOW_PHASE_OVS_MASK)

#define GLCD_SPIM_SCB_GET_I2C_CTRL_S_NOT_READY_ADDR_NACK(wakeNack) ((0u != (wakeNack)) ? \
                                                            (GLCD_SPIM_SCB_I2C_CTRL_S_NOT_READY_ADDR_NACK) : (0u))

#define GLCD_SPIM_SCB_GET_I2C_CTRL_SL_MSTR_MODE(mode)    ((uint32) ((uint32)(mode) << \
                                                                    GLCD_SPIM_SCB_I2C_CTRL_SLAVE_MODE_POS))

/* GLCD_SPIM_SCB_SPI_CTRL */
#define GLCD_SPIM_SCB_GET_SPI_CTRL_CONTINUOUS(separate)  ((0u != (separate)) ? \
                                                                (GLCD_SPIM_SCB_SPI_CTRL_CONTINUOUS) : (0u))
                                                                
#define GLCD_SPIM_SCB_GET_SPI_CTRL_SELECT_PRECEDE(mode)  ((0u != (mode)) ? \
                                                                      (GLCD_SPIM_SCB_SPI_CTRL_SELECT_PRECEDE) : (0u))

#define GLCD_SPIM_SCB_GET_SPI_CTRL_SCLK_MODE(mode)       (((uint32) ((uint32) (mode) << \
                                                                        GLCD_SPIM_SCB_SPI_CTRL_CPHA_POS)) & \
                                                                        GLCD_SPIM_SCB_SPI_CTRL_SCLK_MODE_MASK)

#define GLCD_SPIM_SCB_GET_SPI_CTRL_LATE_MISO_SAMPLE(lateMiso) ((0u != (lateMiso)) ? \
                                                                    (GLCD_SPIM_SCB_SPI_CTRL_LATE_MISO_SAMPLE) : (0u))

#define GLCD_SPIM_SCB_GET_SPI_CTRL_SUB_MODE(mode)        (((uint32) (((uint32) (mode)) << \
                                                                        GLCD_SPIM_SCB_SPI_CTRL_MODE_POS)) & \
                                                                        GLCD_SPIM_SCB_SPI_CTRL_MODE_MASK)

#define GLCD_SPIM_SCB_GET_SPI_CTRL_SLAVE_SELECT(select)  (((uint32) ((uint32) (select) << \
                                                                      GLCD_SPIM_SCB_SPI_CTRL_SLAVE_SELECT_POS)) & \
                                                                      GLCD_SPIM_SCB_SPI_CTRL_SLAVE_SELECT_MASK)

#define GLCD_SPIM_SCB_GET_SPI_CTRL_MASTER_MODE(mode)     ((0u != (mode)) ? \
                                                                (GLCD_SPIM_SCB_SPI_CTRL_MASTER) : (0u))

/* GLCD_SPIM_SCB_UART_CTRL */
#define GLCD_SPIM_SCB_GET_UART_CTRL_MODE(mode)           (((uint32) ((uint32) (mode) << \
                                                                            GLCD_SPIM_SCB_UART_CTRL_MODE_POS)) & \
                                                                                GLCD_SPIM_SCB_UART_CTRL_MODE_MASK)

/* GLCD_SPIM_SCB_UART_RX_CTRL */
#define GLCD_SPIM_SCB_GET_UART_RX_CTRL_MODE(stopBits)    (((uint32) (stopBits) - 1u) & \
                                                                        GLCD_SPIM_SCB_UART_RX_CTRL_STOP_BITS_MASK)

#define GLCD_SPIM_SCB_GET_UART_RX_CTRL_PARITY(parity)    ((0u != (parity)) ? \
                                                                    (GLCD_SPIM_SCB_UART_RX_CTRL_PARITY) : (0u))

#define GLCD_SPIM_SCB_GET_UART_RX_CTRL_POLARITY(polarity)    ((0u != (polarity)) ? \
                                                                    (GLCD_SPIM_SCB_UART_RX_CTRL_POLARITY) : (0u))

#define GLCD_SPIM_SCB_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(dropErr) ((0u != (dropErr)) ? \
                                                        (GLCD_SPIM_SCB_UART_RX_CTRL_DROP_ON_PARITY_ERR) : (0u))

#define GLCD_SPIM_SCB_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(dropErr) ((0u != (dropErr)) ? \
                                                        (GLCD_SPIM_SCB_UART_RX_CTRL_DROP_ON_FRAME_ERR) : (0u))

#define GLCD_SPIM_SCB_GET_UART_RX_CTRL_MP_MODE(mpMode)   ((0u != (mpMode)) ? \
                                                        (GLCD_SPIM_SCB_UART_RX_CTRL_MP_MODE) : (0u))

/* GLCD_SPIM_SCB_UART_TX_CTRL */
#define GLCD_SPIM_SCB_GET_UART_TX_CTRL_MODE(stopBits)    (((uint32) (stopBits) - 1u) & \
                                                                GLCD_SPIM_SCB_UART_RX_CTRL_STOP_BITS_MASK)

#define GLCD_SPIM_SCB_GET_UART_TX_CTRL_PARITY(parity)    ((0u != (parity)) ? \
                                                               (GLCD_SPIM_SCB_UART_TX_CTRL_PARITY) : (0u))

#define GLCD_SPIM_SCB_GET_UART_TX_CTRL_RETRY_NACK(nack)  ((0u != (nack)) ? \
                                                               (GLCD_SPIM_SCB_UART_TX_CTRL_RETRY_ON_NACK) : (0u))

/* GLCD_SPIM_SCB_RX_CTRL */
#define GLCD_SPIM_SCB_GET_RX_CTRL_DATA_WIDTH(dataWidth)  (((uint32) (dataWidth) - 1u) & \
                                                                GLCD_SPIM_SCB_RX_CTRL_DATA_WIDTH_MASK)

#define GLCD_SPIM_SCB_GET_RX_CTRL_BIT_ORDER(bitOrder)    ((0u != (bitOrder)) ? \
                                                                (GLCD_SPIM_SCB_RX_CTRL_MSB_FIRST) : (0u))

#define GLCD_SPIM_SCB_GET_RX_CTRL_MEDIAN(filterEn)       ((0u != (filterEn)) ? \
                                                                (GLCD_SPIM_SCB_RX_CTRL_MEDIAN) : (0u))

/* GLCD_SPIM_SCB_RX_MATCH */
#define GLCD_SPIM_SCB_GET_RX_MATCH_ADDR(addr)    ((uint32) (addr) & GLCD_SPIM_SCB_RX_MATCH_ADDR_MASK)
#define GLCD_SPIM_SCB_GET_RX_MATCH_MASK(mask)    (((uint32) ((uint32) (mask) << \
                                                            GLCD_SPIM_SCB_RX_MATCH_MASK_POS)) & \
                                                            GLCD_SPIM_SCB_RX_MATCH_MASK_MASK)

/* GLCD_SPIM_SCB_RX_FIFO_CTRL */
#define GLCD_SPIM_SCB_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(level)  ((uint32) (level) & \
                                                                    GLCD_SPIM_SCB_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK)

/* GLCD_SPIM_SCB_TX_CTRL */
#define GLCD_SPIM_SCB_GET_TX_CTRL_DATA_WIDTH(dataWidth)  (((uint32) (dataWidth) - 1u) & \
                                                                GLCD_SPIM_SCB_RX_CTRL_DATA_WIDTH_MASK)

#define GLCD_SPIM_SCB_GET_TX_CTRL_BIT_ORDER(bitOrder)    ((0u != (bitOrder)) ? \
                                                                (GLCD_SPIM_SCB_TX_CTRL_MSB_FIRST) : (0u))

/* GLCD_SPIM_SCB_TX_FIFO_CTRL */
#define GLCD_SPIM_SCB_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(level)  ((uint32) (level) & \
                                                                    GLCD_SPIM_SCB_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK)

/* Clears register: config and interrupt mask */
#define GLCD_SPIM_SCB_CLEAR_REG          ((uint32) (0u))
#define GLCD_SPIM_SCB_NO_INTR_SOURCES    ((uint32) (0u))
#define GLCD_SPIM_SCB_DUMMY_PARAM        ((uint32) (0u))
#define GLCD_SPIM_SCB_SUBMODE_SPI_SLAVE  ((uint32) (0u))

/* Return in case I2C read error */
#define GLCD_SPIM_SCB_I2C_INVALID_BYTE   ((uint32) 0xFFFFFFFFu)
#define GLCD_SPIM_SCB_CHECK_VALID_BYTE   ((uint32) 0x80000000u)

#endif /* (CY_SCB_GLCD_SPIM_SCB_H) */


/* [] END OF FILE */
