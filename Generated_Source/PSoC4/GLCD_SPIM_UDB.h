/*******************************************************************************
* File Name: GLCD_SPIM_UDB.h
* Version 2.40
*
* Description:
*  Contains the function prototypes, constants and register definition
*  of the SPI Master Component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SPIM_GLCD_SPIM_UDB_H)
#define CY_SPIM_GLCD_SPIM_UDB_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component SPI_Master_v2_40 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define GLCD_SPIM_UDB_INTERNAL_CLOCK             (1u)

#if(0u != GLCD_SPIM_UDB_INTERNAL_CLOCK)
    #include "GLCD_SPIM_UDB_IntClock.h"
#endif /* (0u != GLCD_SPIM_UDB_INTERNAL_CLOCK) */

#define GLCD_SPIM_UDB_MODE                       (1u)
#define GLCD_SPIM_UDB_DATA_WIDTH                 (9u)
#define GLCD_SPIM_UDB_MODE_USE_ZERO              (1u)
#define GLCD_SPIM_UDB_BIDIRECTIONAL_MODE         (0u)

/* Internal interrupt handling */
#define GLCD_SPIM_UDB_TX_BUFFER_SIZE             (4u)
#define GLCD_SPIM_UDB_RX_BUFFER_SIZE             (4u)
#define GLCD_SPIM_UDB_INTERNAL_TX_INT_ENABLED    (0u)
#define GLCD_SPIM_UDB_INTERNAL_RX_INT_ENABLED    (0u)

#define GLCD_SPIM_UDB_SINGLE_REG_SIZE            (8u)
#define GLCD_SPIM_UDB_USE_SECOND_DATAPATH        (GLCD_SPIM_UDB_DATA_WIDTH > GLCD_SPIM_UDB_SINGLE_REG_SIZE)

#define GLCD_SPIM_UDB_FIFO_SIZE                  (4u)
#define GLCD_SPIM_UDB_TX_SOFTWARE_BUF_ENABLED    ((0u != GLCD_SPIM_UDB_INTERNAL_TX_INT_ENABLED) && \
                                                     (GLCD_SPIM_UDB_TX_BUFFER_SIZE > GLCD_SPIM_UDB_FIFO_SIZE))

#define GLCD_SPIM_UDB_RX_SOFTWARE_BUF_ENABLED    ((0u != GLCD_SPIM_UDB_INTERNAL_RX_INT_ENABLED) && \
                                                     (GLCD_SPIM_UDB_RX_BUFFER_SIZE > GLCD_SPIM_UDB_FIFO_SIZE))


/***************************************
*        Data Struct Definition
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
    uint8 cntrPeriod;
    #if(CY_UDB_V0)
        uint16 saveSrTxIntMask;
        uint16 saveSrRxIntMask;
    #endif /* (CY_UDB_V0) */

} GLCD_SPIM_UDB_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void  GLCD_SPIM_UDB_Init(void)                           ;
void  GLCD_SPIM_UDB_Enable(void)                         ;
void  GLCD_SPIM_UDB_Start(void)                          ;
void  GLCD_SPIM_UDB_Stop(void)                           ;

void  GLCD_SPIM_UDB_EnableTxInt(void)                    ;
void  GLCD_SPIM_UDB_EnableRxInt(void)                    ;
void  GLCD_SPIM_UDB_DisableTxInt(void)                   ;
void  GLCD_SPIM_UDB_DisableRxInt(void)                   ;

void  GLCD_SPIM_UDB_Sleep(void)                          ;
void  GLCD_SPIM_UDB_Wakeup(void)                         ;
void  GLCD_SPIM_UDB_SaveConfig(void)                     ;
void  GLCD_SPIM_UDB_RestoreConfig(void)                  ;

void  GLCD_SPIM_UDB_SetTxInterruptMode(uint8 intSrc)     ;
void  GLCD_SPIM_UDB_SetRxInterruptMode(uint8 intSrc)     ;
uint8 GLCD_SPIM_UDB_ReadTxStatus(void)                   ;
uint8 GLCD_SPIM_UDB_ReadRxStatus(void)                   ;
void  GLCD_SPIM_UDB_WriteTxData(uint16 txData)  \
                                                            ;
uint16 GLCD_SPIM_UDB_ReadRxData(void) \
                                                            ;
uint8 GLCD_SPIM_UDB_GetRxBufferSize(void)                ;
uint8 GLCD_SPIM_UDB_GetTxBufferSize(void)                ;
void  GLCD_SPIM_UDB_ClearRxBuffer(void)                  ;
void  GLCD_SPIM_UDB_ClearTxBuffer(void)                  ;
void  GLCD_SPIM_UDB_ClearFIFO(void)                              ;
void  GLCD_SPIM_UDB_PutArray(const uint16 buffer[], uint8 byteCount) \
                                                            ;

#if(0u != GLCD_SPIM_UDB_BIDIRECTIONAL_MODE)
    void  GLCD_SPIM_UDB_TxEnable(void)                   ;
    void  GLCD_SPIM_UDB_TxDisable(void)                  ;
#endif /* (0u != GLCD_SPIM_UDB_BIDIRECTIONAL_MODE) */

CY_ISR_PROTO(GLCD_SPIM_UDB_TX_ISR);
CY_ISR_PROTO(GLCD_SPIM_UDB_RX_ISR);


/**********************************
*   Variable with external linkage
**********************************/

extern uint8 GLCD_SPIM_UDB_initVar;


/***************************************
*           API Constants
***************************************/

#define GLCD_SPIM_UDB_TX_ISR_NUMBER     ((uint8) (GLCD_SPIM_UDB_TxInternalInterrupt__INTC_NUMBER))
#define GLCD_SPIM_UDB_RX_ISR_NUMBER     ((uint8) (GLCD_SPIM_UDB_RxInternalInterrupt__INTC_NUMBER))

#define GLCD_SPIM_UDB_TX_ISR_PRIORITY   ((uint8) (GLCD_SPIM_UDB_TxInternalInterrupt__INTC_PRIOR_NUM))
#define GLCD_SPIM_UDB_RX_ISR_PRIORITY   ((uint8) (GLCD_SPIM_UDB_RxInternalInterrupt__INTC_PRIOR_NUM))


/***************************************
*    Initial Parameter Constants
***************************************/

#define GLCD_SPIM_UDB_INT_ON_SPI_DONE    ((uint8) (0u   << GLCD_SPIM_UDB_STS_SPI_DONE_SHIFT))
#define GLCD_SPIM_UDB_INT_ON_TX_EMPTY    ((uint8) (0u   << GLCD_SPIM_UDB_STS_TX_FIFO_EMPTY_SHIFT))
#define GLCD_SPIM_UDB_INT_ON_TX_NOT_FULL ((uint8) (0u << \
                                                                           GLCD_SPIM_UDB_STS_TX_FIFO_NOT_FULL_SHIFT))
#define GLCD_SPIM_UDB_INT_ON_BYTE_COMP   ((uint8) (0u  << GLCD_SPIM_UDB_STS_BYTE_COMPLETE_SHIFT))
#define GLCD_SPIM_UDB_INT_ON_SPI_IDLE    ((uint8) (0u   << GLCD_SPIM_UDB_STS_SPI_IDLE_SHIFT))

/* Disable TX_NOT_FULL if software buffer is used */
#define GLCD_SPIM_UDB_INT_ON_TX_NOT_FULL_DEF ((GLCD_SPIM_UDB_TX_SOFTWARE_BUF_ENABLED) ? \
                                                                        (0u) : (GLCD_SPIM_UDB_INT_ON_TX_NOT_FULL))

/* TX interrupt mask */
#define GLCD_SPIM_UDB_TX_INIT_INTERRUPTS_MASK    (GLCD_SPIM_UDB_INT_ON_SPI_DONE  | \
                                                     GLCD_SPIM_UDB_INT_ON_TX_EMPTY  | \
                                                     GLCD_SPIM_UDB_INT_ON_TX_NOT_FULL_DEF | \
                                                     GLCD_SPIM_UDB_INT_ON_BYTE_COMP | \
                                                     GLCD_SPIM_UDB_INT_ON_SPI_IDLE)

#define GLCD_SPIM_UDB_INT_ON_RX_FULL         ((uint8) (0u << \
                                                                          GLCD_SPIM_UDB_STS_RX_FIFO_FULL_SHIFT))
#define GLCD_SPIM_UDB_INT_ON_RX_NOT_EMPTY    ((uint8) (0u << \
                                                                          GLCD_SPIM_UDB_STS_RX_FIFO_NOT_EMPTY_SHIFT))
#define GLCD_SPIM_UDB_INT_ON_RX_OVER         ((uint8) (0u << \
                                                                          GLCD_SPIM_UDB_STS_RX_FIFO_OVERRUN_SHIFT))

/* RX interrupt mask */
#define GLCD_SPIM_UDB_RX_INIT_INTERRUPTS_MASK    (GLCD_SPIM_UDB_INT_ON_RX_FULL      | \
                                                     GLCD_SPIM_UDB_INT_ON_RX_NOT_EMPTY | \
                                                     GLCD_SPIM_UDB_INT_ON_RX_OVER)
/* Nubmer of bits to receive/transmit */
#define GLCD_SPIM_UDB_BITCTR_INIT            (((uint8) (GLCD_SPIM_UDB_DATA_WIDTH << 1u)) - 1u)


/***************************************
*             Registers
***************************************/

#if(CY_PSOC3 || CY_PSOC5)
    #define GLCD_SPIM_UDB_TXDATA_REG (* (reg16 *) \
                                                GLCD_SPIM_UDB_BSPIM_sR16_Dp_u0__F0_REG)
    #define GLCD_SPIM_UDB_TXDATA_PTR (  (reg16 *) \
                                                GLCD_SPIM_UDB_BSPIM_sR16_Dp_u0__F0_REG)
    #define GLCD_SPIM_UDB_RXDATA_REG (* (reg16 *) \
                                                GLCD_SPIM_UDB_BSPIM_sR16_Dp_u0__F1_REG)
    #define GLCD_SPIM_UDB_RXDATA_PTR (  (reg16 *) \
                                                GLCD_SPIM_UDB_BSPIM_sR16_Dp_u0__F1_REG)
#else   /* PSOC4 */
    #if(GLCD_SPIM_UDB_USE_SECOND_DATAPATH)
        #define GLCD_SPIM_UDB_TXDATA_REG (* (reg16 *) \
                                          GLCD_SPIM_UDB_BSPIM_sR16_Dp_u0__16BIT_F0_REG)
        #define GLCD_SPIM_UDB_TXDATA_PTR (  (reg16 *) \
                                          GLCD_SPIM_UDB_BSPIM_sR16_Dp_u0__16BIT_F0_REG)
        #define GLCD_SPIM_UDB_RXDATA_REG (* (reg16 *) \
                                          GLCD_SPIM_UDB_BSPIM_sR16_Dp_u0__16BIT_F1_REG)
        #define GLCD_SPIM_UDB_RXDATA_PTR         (  (reg16 *) \
                                          GLCD_SPIM_UDB_BSPIM_sR16_Dp_u0__16BIT_F1_REG)
    #else
        #define GLCD_SPIM_UDB_TXDATA_REG (* (reg8 *) \
                                                GLCD_SPIM_UDB_BSPIM_sR16_Dp_u0__F0_REG)
        #define GLCD_SPIM_UDB_TXDATA_PTR (  (reg8 *) \
                                                GLCD_SPIM_UDB_BSPIM_sR16_Dp_u0__F0_REG)
        #define GLCD_SPIM_UDB_RXDATA_REG (* (reg8 *) \
                                                GLCD_SPIM_UDB_BSPIM_sR16_Dp_u0__F1_REG)
        #define GLCD_SPIM_UDB_RXDATA_PTR (  (reg8 *) \
                                                GLCD_SPIM_UDB_BSPIM_sR16_Dp_u0__F1_REG)
    #endif /* (GLCD_SPIM_UDB_USE_SECOND_DATAPATH) */
#endif     /* (CY_PSOC3 || CY_PSOC5) */

#define GLCD_SPIM_UDB_AUX_CONTROL_DP0_REG (* (reg8 *) \
                                        GLCD_SPIM_UDB_BSPIM_sR16_Dp_u0__DP_AUX_CTL_REG)
#define GLCD_SPIM_UDB_AUX_CONTROL_DP0_PTR (  (reg8 *) \
                                        GLCD_SPIM_UDB_BSPIM_sR16_Dp_u0__DP_AUX_CTL_REG)

#if(GLCD_SPIM_UDB_USE_SECOND_DATAPATH)
    #define GLCD_SPIM_UDB_AUX_CONTROL_DP1_REG  (* (reg8 *) \
                                        GLCD_SPIM_UDB_BSPIM_sR16_Dp_u1__DP_AUX_CTL_REG)
    #define GLCD_SPIM_UDB_AUX_CONTROL_DP1_PTR  (  (reg8 *) \
                                        GLCD_SPIM_UDB_BSPIM_sR16_Dp_u1__DP_AUX_CTL_REG)
#endif /* (GLCD_SPIM_UDB_USE_SECOND_DATAPATH) */

#define GLCD_SPIM_UDB_COUNTER_PERIOD_REG     (* (reg8 *) GLCD_SPIM_UDB_BSPIM_BitCounter__PERIOD_REG)
#define GLCD_SPIM_UDB_COUNTER_PERIOD_PTR     (  (reg8 *) GLCD_SPIM_UDB_BSPIM_BitCounter__PERIOD_REG)
#define GLCD_SPIM_UDB_COUNTER_CONTROL_REG    (* (reg8 *) GLCD_SPIM_UDB_BSPIM_BitCounter__CONTROL_AUX_CTL_REG)
#define GLCD_SPIM_UDB_COUNTER_CONTROL_PTR    (  (reg8 *) GLCD_SPIM_UDB_BSPIM_BitCounter__CONTROL_AUX_CTL_REG)

#define GLCD_SPIM_UDB_TX_STATUS_REG          (* (reg8 *) GLCD_SPIM_UDB_BSPIM_TxStsReg__STATUS_REG)
#define GLCD_SPIM_UDB_TX_STATUS_PTR          (  (reg8 *) GLCD_SPIM_UDB_BSPIM_TxStsReg__STATUS_REG)
#define GLCD_SPIM_UDB_RX_STATUS_REG          (* (reg8 *) GLCD_SPIM_UDB_BSPIM_RxStsReg__STATUS_REG)
#define GLCD_SPIM_UDB_RX_STATUS_PTR          (  (reg8 *) GLCD_SPIM_UDB_BSPIM_RxStsReg__STATUS_REG)

#define GLCD_SPIM_UDB_CONTROL_REG            (* (reg8 *) \
                                      GLCD_SPIM_UDB_BSPIM_BidirMode_SyncCtl_CtrlReg__CONTROL_REG)
#define GLCD_SPIM_UDB_CONTROL_PTR            (  (reg8 *) \
                                      GLCD_SPIM_UDB_BSPIM_BidirMode_SyncCtl_CtrlReg__CONTROL_REG)

#define GLCD_SPIM_UDB_TX_STATUS_MASK_REG     (* (reg8 *) GLCD_SPIM_UDB_BSPIM_TxStsReg__MASK_REG)
#define GLCD_SPIM_UDB_TX_STATUS_MASK_PTR     (  (reg8 *) GLCD_SPIM_UDB_BSPIM_TxStsReg__MASK_REG)
#define GLCD_SPIM_UDB_RX_STATUS_MASK_REG     (* (reg8 *) GLCD_SPIM_UDB_BSPIM_RxStsReg__MASK_REG)
#define GLCD_SPIM_UDB_RX_STATUS_MASK_PTR     (  (reg8 *) GLCD_SPIM_UDB_BSPIM_RxStsReg__MASK_REG)

#define GLCD_SPIM_UDB_TX_STATUS_ACTL_REG     (* (reg8 *) GLCD_SPIM_UDB_BSPIM_TxStsReg__STATUS_AUX_CTL_REG)
#define GLCD_SPIM_UDB_TX_STATUS_ACTL_PTR     (  (reg8 *) GLCD_SPIM_UDB_BSPIM_TxStsReg__STATUS_AUX_CTL_REG)
#define GLCD_SPIM_UDB_RX_STATUS_ACTL_REG     (* (reg8 *) GLCD_SPIM_UDB_BSPIM_RxStsReg__STATUS_AUX_CTL_REG)
#define GLCD_SPIM_UDB_RX_STATUS_ACTL_PTR     (  (reg8 *) GLCD_SPIM_UDB_BSPIM_RxStsReg__STATUS_AUX_CTL_REG)

#if(GLCD_SPIM_UDB_USE_SECOND_DATAPATH)
    #define GLCD_SPIM_UDB_AUX_CONTROLDP1     (GLCD_SPIM_UDB_AUX_CONTROL_DP1_REG)
#endif /* (GLCD_SPIM_UDB_USE_SECOND_DATAPATH) */


/***************************************
*       Register Constants
***************************************/

/* Status Register Definitions */
#define GLCD_SPIM_UDB_STS_SPI_DONE_SHIFT             (0x00u)
#define GLCD_SPIM_UDB_STS_TX_FIFO_EMPTY_SHIFT        (0x01u)
#define GLCD_SPIM_UDB_STS_TX_FIFO_NOT_FULL_SHIFT     (0x02u)
#define GLCD_SPIM_UDB_STS_BYTE_COMPLETE_SHIFT        (0x03u)
#define GLCD_SPIM_UDB_STS_SPI_IDLE_SHIFT             (0x04u)
#define GLCD_SPIM_UDB_STS_RX_FIFO_FULL_SHIFT         (0x04u)
#define GLCD_SPIM_UDB_STS_RX_FIFO_NOT_EMPTY_SHIFT    (0x05u)
#define GLCD_SPIM_UDB_STS_RX_FIFO_OVERRUN_SHIFT      (0x06u)

#define GLCD_SPIM_UDB_STS_SPI_DONE           ((uint8) (0x01u << GLCD_SPIM_UDB_STS_SPI_DONE_SHIFT))
#define GLCD_SPIM_UDB_STS_TX_FIFO_EMPTY      ((uint8) (0x01u << GLCD_SPIM_UDB_STS_TX_FIFO_EMPTY_SHIFT))
#define GLCD_SPIM_UDB_STS_TX_FIFO_NOT_FULL   ((uint8) (0x01u << GLCD_SPIM_UDB_STS_TX_FIFO_NOT_FULL_SHIFT))
#define GLCD_SPIM_UDB_STS_BYTE_COMPLETE      ((uint8) (0x01u << GLCD_SPIM_UDB_STS_BYTE_COMPLETE_SHIFT))
#define GLCD_SPIM_UDB_STS_SPI_IDLE           ((uint8) (0x01u << GLCD_SPIM_UDB_STS_SPI_IDLE_SHIFT))
#define GLCD_SPIM_UDB_STS_RX_FIFO_FULL       ((uint8) (0x01u << GLCD_SPIM_UDB_STS_RX_FIFO_FULL_SHIFT))
#define GLCD_SPIM_UDB_STS_RX_FIFO_NOT_EMPTY  ((uint8) (0x01u << GLCD_SPIM_UDB_STS_RX_FIFO_NOT_EMPTY_SHIFT))
#define GLCD_SPIM_UDB_STS_RX_FIFO_OVERRUN    ((uint8) (0x01u << GLCD_SPIM_UDB_STS_RX_FIFO_OVERRUN_SHIFT))

/* TX and RX masks for clear on read bits */
#define GLCD_SPIM_UDB_TX_STS_CLR_ON_RD_BYTES_MASK    (0x09u)
#define GLCD_SPIM_UDB_RX_STS_CLR_ON_RD_BYTES_MASK    (0x40u)

/* StatusI Register Interrupt Enable Control Bits */
/* As defined by the Register map for the AUX Control Register */
#define GLCD_SPIM_UDB_INT_ENABLE     (0x10u) /* Enable interrupt from statusi */
#define GLCD_SPIM_UDB_TX_FIFO_CLR    (0x01u) /* F0 - TX FIFO */
#define GLCD_SPIM_UDB_RX_FIFO_CLR    (0x02u) /* F1 - RX FIFO */
#define GLCD_SPIM_UDB_FIFO_CLR       (GLCD_SPIM_UDB_TX_FIFO_CLR | GLCD_SPIM_UDB_RX_FIFO_CLR)

/* Bit Counter (7-bit) Control Register Bit Definitions */
/* As defined by the Register map for the AUX Control Register */
#define GLCD_SPIM_UDB_CNTR_ENABLE    (0x20u) /* Enable CNT7 */

/* Bi-Directional mode control bit */
#define GLCD_SPIM_UDB_CTRL_TX_SIGNAL_EN  (0x01u)

/* Datapath Auxillary Control Register definitions */
#define GLCD_SPIM_UDB_AUX_CTRL_FIFO0_CLR         (0x01u)
#define GLCD_SPIM_UDB_AUX_CTRL_FIFO1_CLR         (0x02u)
#define GLCD_SPIM_UDB_AUX_CTRL_FIFO0_LVL         (0x04u)
#define GLCD_SPIM_UDB_AUX_CTRL_FIFO1_LVL         (0x08u)
#define GLCD_SPIM_UDB_STATUS_ACTL_INT_EN_MASK    (0x10u)

/* Component disabled */
#define GLCD_SPIM_UDB_DISABLED   (0u)


/***************************************
*       Macros
***************************************/

/* Returns true if componentn enabled */
#define GLCD_SPIM_UDB_IS_ENABLED (0u != (GLCD_SPIM_UDB_TX_STATUS_ACTL_REG & GLCD_SPIM_UDB_INT_ENABLE))

/* Retuns TX status register */
#define GLCD_SPIM_UDB_GET_STATUS_TX(swTxSts) ( (uint8)(GLCD_SPIM_UDB_TX_STATUS_REG | \
                                                          ((swTxSts) & GLCD_SPIM_UDB_TX_STS_CLR_ON_RD_BYTES_MASK)) )
/* Retuns RX status register */
#define GLCD_SPIM_UDB_GET_STATUS_RX(swRxSts) ( (uint8)(GLCD_SPIM_UDB_RX_STATUS_REG | \
                                                          ((swRxSts) & GLCD_SPIM_UDB_RX_STS_CLR_ON_RD_BYTES_MASK)) )


/***************************************
*       Obsolete definitions
***************************************/

/* Following definitions are for version compatibility.
*  They are obsolete in SPIM v2_30.
*  Please do not use it in new projects
*/

#define GLCD_SPIM_UDB_WriteByte   GLCD_SPIM_UDB_WriteTxData
#define GLCD_SPIM_UDB_ReadByte    GLCD_SPIM_UDB_ReadRxData
void  GLCD_SPIM_UDB_SetInterruptMode(uint8 intSrc)       ;
uint8 GLCD_SPIM_UDB_ReadStatus(void)                     ;
void  GLCD_SPIM_UDB_EnableInt(void)                      ;
void  GLCD_SPIM_UDB_DisableInt(void)                     ;

/* Obsolete register names. Not to be used in new designs */
#define GLCD_SPIM_UDB_TXDATA                 (GLCD_SPIM_UDB_TXDATA_REG)
#define GLCD_SPIM_UDB_RXDATA                 (GLCD_SPIM_UDB_RXDATA_REG)
#define GLCD_SPIM_UDB_AUX_CONTROLDP0         (GLCD_SPIM_UDB_AUX_CONTROL_DP0_REG)
#define GLCD_SPIM_UDB_TXBUFFERREAD           (GLCD_SPIM_UDB_txBufferRead)
#define GLCD_SPIM_UDB_TXBUFFERWRITE          (GLCD_SPIM_UDB_txBufferWrite)
#define GLCD_SPIM_UDB_RXBUFFERREAD           (GLCD_SPIM_UDB_rxBufferRead)
#define GLCD_SPIM_UDB_RXBUFFERWRITE          (GLCD_SPIM_UDB_rxBufferWrite)

#define GLCD_SPIM_UDB_COUNTER_PERIOD         (GLCD_SPIM_UDB_COUNTER_PERIOD_REG)
#define GLCD_SPIM_UDB_COUNTER_CONTROL        (GLCD_SPIM_UDB_COUNTER_CONTROL_REG)
#define GLCD_SPIM_UDB_STATUS                 (GLCD_SPIM_UDB_TX_STATUS_REG)
#define GLCD_SPIM_UDB_CONTROL                (GLCD_SPIM_UDB_CONTROL_REG)
#define GLCD_SPIM_UDB_STATUS_MASK            (GLCD_SPIM_UDB_TX_STATUS_MASK_REG)
#define GLCD_SPIM_UDB_STATUS_ACTL            (GLCD_SPIM_UDB_TX_STATUS_ACTL_REG)

#define GLCD_SPIM_UDB_INIT_INTERRUPTS_MASK  (GLCD_SPIM_UDB_INT_ON_SPI_DONE     | \
                                                GLCD_SPIM_UDB_INT_ON_TX_EMPTY     | \
                                                GLCD_SPIM_UDB_INT_ON_TX_NOT_FULL_DEF  | \
                                                GLCD_SPIM_UDB_INT_ON_RX_FULL      | \
                                                GLCD_SPIM_UDB_INT_ON_RX_NOT_EMPTY | \
                                                GLCD_SPIM_UDB_INT_ON_RX_OVER      | \
                                                GLCD_SPIM_UDB_INT_ON_BYTE_COMP)
                                                
/* Following definitions are for version Compatibility.
*  They are obsolete in SPIM v2_40.
*  Please do not use it in new projects
*/

#define GLCD_SPIM_UDB_DataWidth                  (GLCD_SPIM_UDB_DATA_WIDTH)
#define GLCD_SPIM_UDB_InternalClockUsed          (GLCD_SPIM_UDB_INTERNAL_CLOCK)
#define GLCD_SPIM_UDB_InternalTxInterruptEnabled (GLCD_SPIM_UDB_INTERNAL_TX_INT_ENABLED)
#define GLCD_SPIM_UDB_InternalRxInterruptEnabled (GLCD_SPIM_UDB_INTERNAL_RX_INT_ENABLED)
#define GLCD_SPIM_UDB_ModeUseZero                (GLCD_SPIM_UDB_MODE_USE_ZERO)
#define GLCD_SPIM_UDB_BidirectionalMode          (GLCD_SPIM_UDB_BIDIRECTIONAL_MODE)
#define GLCD_SPIM_UDB_Mode                       (GLCD_SPIM_UDB_MODE)
#define GLCD_SPIM_UDB_DATAWIDHT                  (GLCD_SPIM_UDB_DATA_WIDTH)
#define GLCD_SPIM_UDB_InternalInterruptEnabled   (0u)

#define GLCD_SPIM_UDB_TXBUFFERSIZE   (GLCD_SPIM_UDB_TX_BUFFER_SIZE)
#define GLCD_SPIM_UDB_RXBUFFERSIZE   (GLCD_SPIM_UDB_RX_BUFFER_SIZE)

#define GLCD_SPIM_UDB_TXBUFFER       GLCD_SPIM_UDB_txBuffer
#define GLCD_SPIM_UDB_RXBUFFER       GLCD_SPIM_UDB_rxBuffer

#endif /* (CY_SPIM_GLCD_SPIM_UDB_H) */


/* [] END OF FILE */
