/*******************************************************************************
* File Name: Com_Block.h
* Version 2.60
*
* Description:
*  Contains the function prototypes, constants and register definition
*  of the SPI Slave Component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SPIS_Com_Block_H)
#define CY_SPIS_Com_Block_H

#include "cytypes.h"
#include "CyLib.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component SPI_Slave_v2_60 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define Com_Block_DATA_WIDTH                  (16u)
#define Com_Block_INTERNAL_TX_INT_ENABLED     (0u)
#define Com_Block_INTERNAL_RX_INT_ENABLED     (0u)
#define Com_Block_MODE_USE_ZERO               (1u)
#define Com_Block_BIDIRECTIONAL_MODE          (0u)
#define Com_Block_MODE                        (0u)

#define Com_Block_FIFO_SIZE                  (4u)
/* Internal interrupt handling */
#define Com_Block_TX_BUFFER_SIZE             (4u)
#define Com_Block_RX_BUFFER_SIZE             (4u)
#define Com_Block_INTERNAL_TX_INT_ENABLED    (0u)
#define Com_Block_INTERNAL_RX_INT_ENABLED    (0u)

#define Com_Block_TX_SOFTWARE_BUF_ENABLED    ((0u != Com_Block_INTERNAL_TX_INT_ENABLED) && \
                                                     (Com_Block_TX_BUFFER_SIZE > Com_Block_FIFO_SIZE))

#define Com_Block_RX_SOFTWARE_BUF_ENABLED    ((0u != Com_Block_INTERNAL_RX_INT_ENABLED) && \
                                                     (Com_Block_RX_BUFFER_SIZE > Com_Block_FIFO_SIZE))

/* Following definitions are for version Compatibility, they are obsolete.
*  Please do not use it in new projects
*/
#define Com_Block_InternalInterruptEnabled (0u)


/***************************************
*        Data Struct Definition
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
    uint8 cntrPeriod;

    #if(CY_UDB_V0) /* CY_UDB_V0 */

        uint16 saveSrTxIntMask;
        uint16 saveSrRxIntMask;

    #endif /* CY_UDB_V0 */

} Com_Block_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void  Com_Block_Init(void) ;
void  Com_Block_Enable(void) ;
void  Com_Block_Start(void) ;
void  Com_Block_Stop(void) ;
void  Com_Block_EnableTxInt(void) ;
void  Com_Block_EnableRxInt(void) ;
void  Com_Block_DisableTxInt(void) ;
void  Com_Block_DisableRxInt(void) ;
void  Com_Block_SetTxInterruptMode(uint8 intSrc) ;
void  Com_Block_SetRxInterruptMode(uint8 intSrc) ;
uint8 Com_Block_ReadTxStatus(void) ;
uint8 Com_Block_ReadRxStatus(void) ;
void  Com_Block_WriteTxData(uint16 txData);

#if(Com_Block_MODE_USE_ZERO != 0u)
    void  Com_Block_WriteTxDataZero(uint16 txDataByte) \
                                              ;
#endif /* (Com_Block_MODE_USE_ZERO != 0u) */

uint16 Com_Block_ReadRxData(void) ;
uint8 Com_Block_GetRxBufferSize(void) ;
uint8 Com_Block_GetTxBufferSize(void) ;
void  Com_Block_ClearRxBuffer(void) ;
void  Com_Block_ClearTxBuffer(void) ;

#if (Com_Block_BIDIRECTIONAL_MODE != 0u)
    void  Com_Block_TxEnable(void) ;
    void  Com_Block_TxDisable(void) ;
#endif /* Com_Block_BIDIRECTIONAL_MODE != 0u */

void  Com_Block_PutArray(const uint16 buffer[], uint8 byteCount) ;
void  Com_Block_ClearFIFO(void) ;
void  Com_Block_Sleep(void) ;
void  Com_Block_Wakeup(void) ;
void  Com_Block_SaveConfig(void) ;
void  Com_Block_RestoreConfig(void) ;

/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Com_Block) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    Com_Block_CyBtldrCommStart(void) CYSMALL ;
    void    Com_Block_CyBtldrCommStop(void) CYSMALL ;
    void    Com_Block_CyBtldrCommReset(void) CYSMALL ;
    cystatus Com_Block_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus Com_Block_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Com_Block)
        #define CyBtldrCommStart    Com_Block_CyBtldrCommStart
        #define CyBtldrCommStop     Com_Block_CyBtldrCommStop
        #define CyBtldrCommReset    Com_Block_CyBtldrCommReset
        #define CyBtldrCommWrite    Com_Block_CyBtldrCommWrite
        #define CyBtldrCommRead     Com_Block_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Com_Block) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define Com_Block_BYTE2BYTE_TIME_OUT (1u)

#endif /* (CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Com_Block) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface)) */


CY_ISR_PROTO(Com_Block_TX_ISR);
CY_ISR_PROTO(Com_Block_RX_ISR);

/* Macros for getting software status of SPIS Statusi Register */
#define Com_Block_GET_STATUS_TX(swTxSts) ( (uint8)(Com_Block_TX_STATUS_REG | \
                                                       ((swTxSts) & Com_Block_STS_CLR_ON_RD_BYTES_MASK)) )
#define Com_Block_GET_STATUS_RX(swRxSts) ( (uint8)(Com_Block_RX_STATUS_REG | \
                                                       ((swRxSts) & Com_Block_STS_CLR_ON_RD_BYTES_MASK)) )

/* Following definitions are for version Compatibility, they are obsolete.
*  Please do not use it in new projects
*/
#define Com_Block_WriteByte      (Com_Block_WriteTxData)
#define Com_Block_ReadByte       (Com_Block_ReadRxData)
#define Com_Block_WriteByteZero  (Com_Block_WriteTxDataZero)
void  Com_Block_SetInterruptMode(uint8 intSrc) ;
uint8 Com_Block_ReadStatus(void) ;
void  Com_Block_EnableInt(void) ;
void  Com_Block_DisableInt(void) ;


/**********************************
*   Variable with external linkage
**********************************/

extern uint8 Com_Block_initVar;


/***************************************
*           API Constants
***************************************/

#define Com_Block_TX_ISR_NUMBER     ((uint8)Com_Block_TxInternalInterrupt__INTC_NUMBER)
#define Com_Block_RX_ISR_NUMBER     ((uint8)Com_Block_RxInternalInterrupt__INTC_NUMBER)
#define Com_Block_TX_ISR_PRIORITY   ((uint8)Com_Block_TxInternalInterrupt__INTC_PRIOR_NUM)
#define Com_Block_RX_ISR_PRIORITY   ((uint8)Com_Block_RxInternalInterrupt__INTC_PRIOR_NUM)


/***************************************
*    Initial Parameter Constants
***************************************/

#define Com_Block_INT_ON_SPI_DONE    (uint8)(0u << Com_Block_STS_SPI_DONE_SHIFT)
#define Com_Block_INT_ON_TX_EMPTY    (uint8)(0u << Com_Block_STS_TX_FIFO_EMPTY_SHIFT)
#define Com_Block_INT_ON_TX_NOT_FULL (uint8)(0u << Com_Block_STS_TX_FIFO_NOT_FULL_SHIFT)
#define Com_Block_INT_ON_BYTE_COMP   (uint8)(0u << Com_Block_STS_BYTE_COMPLETE_SHIFT)

#define Com_Block_TX_INIT_INTERRUPTS_MASK  (Com_Block_INT_ON_SPI_DONE | \
                                            Com_Block_INT_ON_TX_EMPTY | Com_Block_INT_ON_TX_NOT_FULL | \
                                            Com_Block_INT_ON_BYTE_COMP)

#define Com_Block_INT_ON_RX_EMPTY     (uint8)(0u << Com_Block_STS_RX_FIFO_EMPTY_SHIFT)
#define Com_Block_INT_ON_RX_NOT_EMPTY (uint8)(0u << Com_Block_STS_RX_FIFO_NOT_EMPTY_SHIFT)
#define Com_Block_INT_ON_RX_OVER      (uint8)(0u << Com_Block_STS_RX_FIFO_OVERRUN_SHIFT)
#define Com_Block_INT_ON_RX_FULL      (uint8)(0u << Com_Block_STS_RX_FIFO_FULL_SHIFT)

#define Com_Block_RX_INIT_INTERRUPTS_MASK (Com_Block_INT_ON_RX_EMPTY | \
                                            Com_Block_INT_ON_RX_NOT_EMPTY | Com_Block_INT_ON_RX_OVER | \
                                            Com_Block_INT_ON_RX_FULL)

#define Com_Block_BITCTR_INIT           (Com_Block_DATA_WIDTH - 1u)

#define Com_Block__MODE_00 0
#define Com_Block__MODE_01 1
#define Com_Block__MODE_10 2
#define Com_Block__MODE_11 3


#define Com_Block_TX_BUFFER_SIZE         (4u)
#define Com_Block_RX_BUFFER_SIZE         (4u)

/* Following definitions are for version Compatibility, they are obsolete.
*  Please do not use it in new projects
*/
#define Com_Block_INIT_INTERRUPTS_MASK  (Com_Block_INT_ON_SPI_DONE | Com_Block_INT_ON_TX_EMPTY | \
                                            Com_Block_INT_ON_TX_NOT_FULL | Com_Block_INT_ON_RX_EMPTY | \
                                            Com_Block_INT_ON_RX_NOT_EMPTY | Com_Block_INT_ON_RX_OVER | \
                                            Com_Block_INT_ON_BYTE_COMP)


/***************************************
*             Registers
***************************************/

#if(CY_UDB_V0)

    #define Com_Block_TXDATA_ZERO_REG           (* (reg16  *) \
            Com_Block_BSPIS_es2_SPISlave_sR16_DpMISO_u0__A0_REG)

    #define Com_Block_TXDATA_ZERO_PTR           (  (reg16  *) \
            Com_Block_BSPIS_es2_SPISlave_sR16_DpMISO_u0__A0_REG)

    #define Com_Block_RXDATA_ZERO_REG           (* (reg16  *) \
            Com_Block_BSPIS_es2_SPISlave_sR16_DpMOSI_u0__A0_REG)

    #define Com_Block_RXDATA_ZERO_PTR           (  (reg16  *) \
            Com_Block_BSPIS_es2_SPISlave_sR16_DpMOSI_u0__A0_REG)

    #define Com_Block_TXDATA_REG                (* (reg16  *) \
            Com_Block_BSPIS_es2_SPISlave_sR16_DpMISO_u0__F0_REG)

    #define Com_Block_TXDATA_PTR                (  (reg16  *) \
            Com_Block_BSPIS_es2_SPISlave_sR16_DpMISO_u0__F0_REG)

    #define Com_Block_RXDATA_REG                (* (reg16  *) \
            Com_Block_BSPIS_es2_SPISlave_sR16_DpMOSI_u0__F0_REG)

    #define Com_Block_RXDATA_PTR                (  (reg16  *) \
            Com_Block_BSPIS_es2_SPISlave_sR16_DpMOSI_u0__F0_REG)

    #define Com_Block_TX_AUX_CONTROL_DP0_REG       (* (reg8 *) \
            Com_Block_BSPIS_es2_SPISlave_sR16_DpMISO_u0__DP_AUX_CTL_REG)
    #define Com_Block_TX_AUX_CONTROL_DP0_PTR       (  (reg8 *) \
            Com_Block_BSPIS_es2_SPISlave_sR16_DpMISO_u0__DP_AUX_CTL_REG)

    #if(Com_Block_DATA_WIDTH > 8u)

        #define Com_Block_TX_AUX_CONTROL_DP1_REG   (* (reg8 *) \
                Com_Block_BSPIS_es2_SPISlave_sR16_DpMISO_u1__DP_AUX_CTL_REG)
        #define Com_Block_TX_AUX_CONTROL_DP1_PTR   (  (reg8 *) \
                Com_Block_BSPIS_es2_SPISlave_sR16_DpMISO_u1__DP_AUX_CTL_REG)

    #endif /* Com_Block_DATA_WIDTH > 8u */

#else /* CY_UDB_V0 */
    #if(CY_PSOC3 || CY_PSOC5)
        #define Com_Block_TXDATA_ZERO_REG          (* (reg16  *) \
                Com_Block_BSPIS_es3_SPISlave_sR16_Dp_u0__A0_REG)

        #define Com_Block_TXDATA_ZERO_PTR           (  (reg16  *) \
                Com_Block_BSPIS_es3_SPISlave_sR16_Dp_u0__A0_REG)

        #define Com_Block_RXDATA_ZERO_REG           (* (reg16  *) \
                Com_Block_BSPIS_es3_SPISlave_sR16_Dp_u0__A0_REG)

        #define Com_Block_RXDATA_ZERO_PTR           (  (reg16  *) \
                Com_Block_BSPIS_es3_SPISlave_sR16_Dp_u0__A0_REG)

        #define Com_Block_TXDATA_REG                (* (reg16  *) \
                Com_Block_BSPIS_es3_SPISlave_sR16_Dp_u0__F0_REG)

        #define Com_Block_TXDATA_PTR                (  (reg16  *) \
                Com_Block_BSPIS_es3_SPISlave_sR16_Dp_u0__F0_REG)

        #define Com_Block_RXDATA_REG                (* (reg16  *) \
                Com_Block_BSPIS_es3_SPISlave_sR16_Dp_u0__F1_REG)

        #define Com_Block_RXDATA_PTR                (  (reg16  *) \
                Com_Block_BSPIS_es3_SPISlave_sR16_Dp_u0__F1_REG)
    #else
        #if(Com_Block_DATA_WIDTH <= 8u) /* 8bit - SPIS */
            #define Com_Block_TXDATA_ZERO_REG           (* (reg8 *) \
                    Com_Block_BSPIS_es3_SPISlave_sR16_Dp_u0__A0_REG)

            #define Com_Block_TXDATA_ZERO_PTR           (  (reg8  *) \
                    Com_Block_BSPIS_es3_SPISlave_sR16_Dp_u0__A0_REG)

            #define Com_Block_RXDATA_ZERO_REG           (* (reg8  *) \
                    Com_Block_BSPIS_es3_SPISlave_sR16_Dp_u0__A0_REG)

            #define Com_Block_RXDATA_ZERO_PTR           (  (reg8 *) \
                    Com_Block_BSPIS_es3_SPISlave_sR16_Dp_u0__A0_REG)

            #define Com_Block_TXDATA_REG                (* (reg8  *) \
                    Com_Block_BSPIS_es3_SPISlave_sR16_Dp_u0__F0_REG)

            #define Com_Block_TXDATA_PTR                (  (reg8  *) \
                    Com_Block_BSPIS_es3_SPISlave_sR16_Dp_u0__F0_REG)

            #define Com_Block_RXDATA_REG                (* (reg8  *) \
                    Com_Block_BSPIS_es3_SPISlave_sR16_Dp_u0__F1_REG)

            #define Com_Block_RXDATA_PTR                (  (reg8  *) \
                    Com_Block_BSPIS_es3_SPISlave_sR16_Dp_u0__F1_REG)
        #else /* 16bit - SPIS */
            #define Com_Block_TXDATA_ZERO_REG           (* (reg16  *) \
                    Com_Block_BSPIS_es3_SPISlave_sR16_Dp_u0__16BIT_A0_REG)

            #define Com_Block_TXDATA_ZERO_PTR           (  (reg16  *) \
                    Com_Block_BSPIS_es3_SPISlave_sR16_Dp_u0__16BIT_A0_REG)

            #define Com_Block_RXDATA_ZERO_REG           (* (reg16  *) \
                    Com_Block_BSPIS_es3_SPISlave_sR16_Dp_u0__16BIT_A0_REG)

            #define Com_Block_RXDATA_ZERO_PTR           (  (reg16  *) \
                    Com_Block_BSPIS_es3_SPISlave_sR16_Dp_u0__16BIT_A0_REG)

            #define Com_Block_TXDATA_REG                (* (reg16  *) \
                    Com_Block_BSPIS_es3_SPISlave_sR16_Dp_u0__16BIT_F0_REG)

            #define Com_Block_TXDATA_PTR                (  (reg16  *) \
                    Com_Block_BSPIS_es3_SPISlave_sR16_Dp_u0__16BIT_F0_REG)

            #define Com_Block_RXDATA_REG                (* (reg16  *) \
                    Com_Block_BSPIS_es3_SPISlave_sR16_Dp_u0__16BIT_F1_REG)

            #define Com_Block_RXDATA_PTR                (  (reg16 *) \
                    Com_Block_BSPIS_es3_SPISlave_sR16_Dp_u0__16BIT_F1_REG)
        #endif /* (Com_Block_DATA_WIDTH <= 8u) */
    #endif     /* (CY_PSOC3 || CY_PSOC5) */

    #define Com_Block_TX_AUX_CONTROL_DP0_REG       (* (reg8 *) \
            Com_Block_BSPIS_es3_SPISlave_sR16_Dp_u0__DP_AUX_CTL_REG)
    #define Com_Block_TX_AUX_CONTROL_DP0_PTR       (  (reg8 *) \
            Com_Block_BSPIS_es3_SPISlave_sR16_Dp_u0__DP_AUX_CTL_REG)

    #define Com_Block_RX_AUX_CONTROL_DP0_REG       (* (reg8 *) \
            Com_Block_BSPIS_es3_SPISlave_sR16_Dp_u0__DP_AUX_CTL_REG)
    #define Com_Block_RX_AUX_CONTROL_DP0_PTR       (  (reg8 *) \
            Com_Block_BSPIS_es3_SPISlave_sR16_Dp_u0__DP_AUX_CTL_REG)

    #if(Com_Block_DATA_WIDTH > 8u)

        #define Com_Block_TX_AUX_CONTROL_DP1_REG   (* (reg8 *) \
                Com_Block_BSPIS_es3_SPISlave_sR16_Dp_u1__DP_AUX_CTL_REG)
        #define Com_Block_TX_AUX_CONTROL_DP1_PTR   (  (reg8 *) \
                Com_Block_BSPIS_es3_SPISlave_sR16_Dp_u1__DP_AUX_CTL_REG)

        #define Com_Block_RX_AUX_CONTROL_DP1_REG   (* (reg8 *) \
                Com_Block_BSPIS_es3_SPISlave_sR16_Dp_u1__DP_AUX_CTL_REG)
        #define Com_Block_RX_AUX_CONTROL_DP1_PTR   (  (reg8 *) \
                Com_Block_BSPIS_es3_SPISlave_sR16_Dp_u1__DP_AUX_CTL_REG)

    #endif /* Com_Block_DATA_WIDTH > 8u */

#endif /* CY_UDB_V0 */

#define Com_Block_COUNTER_PERIOD_REG    (* (reg8 *) \
        Com_Block_BSPIS_es3_SPISlave_BitCounter__PERIOD_REG)
#define Com_Block_COUNTER_PERIOD_PTR    (  (reg8 *) \
        Com_Block_BSPIS_es3_SPISlave_BitCounter__PERIOD_REG)

#define Com_Block_TX_STATUS_MASK_REG    (* (reg8 *) \
        Com_Block_BSPIS_es3_SPISlave_TxStsReg__MASK_REG)
#define Com_Block_TX_STATUS_MASK_PTR    (  (reg8 *) \
        Com_Block_BSPIS_es3_SPISlave_TxStsReg__MASK_REG)

#define Com_Block_RX_STATUS_MASK_REG    (* (reg8 *) \
        Com_Block_BSPIS_es3_SPISlave_RxStsReg__MASK_REG)
#define Com_Block_RX_STATUS_MASK_PTR    (  (reg8 *) \
        Com_Block_BSPIS_es3_SPISlave_RxStsReg__MASK_REG)

#define Com_Block_ONE_REG               (* (reg8 *) \
        Com_Block_BSPIS_es3_SPISlave_dpCounter_u0__D1_REG)
#define Com_Block_ONE_PTR               (  (reg8 *) \
        Com_Block_BSPIS_es3_SPISlave_dpCounter_u0__D1_REG)

#define Com_Block_TX_STATUS_REG         (* (reg8 *) \
        Com_Block_BSPIS_es3_SPISlave_TxStsReg__STATUS_REG)
#define Com_Block_TX_STATUS_PTR         (  (reg8 *) \
        Com_Block_BSPIS_es3_SPISlave_TxStsReg__STATUS_REG)

#define Com_Block_RX_STATUS_REG         (* (reg8 *) \
        Com_Block_BSPIS_es3_SPISlave_RxStsReg__STATUS_REG)
#define Com_Block_RX_STATUS_PTR         (  (reg8 *) \
        Com_Block_BSPIS_es3_SPISlave_RxStsReg__STATUS_REG)

#define Com_Block_COUNTER_CONTROL_REG   (* (reg8 *) \
        Com_Block_BSPIS_es3_SPISlave_BitCounter__CONTROL_AUX_CTL_REG)
#define Com_Block_COUNTER_CONTROL_PTR   (  (reg8 *) \
        Com_Block_BSPIS_es3_SPISlave_BitCounter__CONTROL_AUX_CTL_REG)

#define Com_Block_TX_STATUS_ACTL_REG    (* (reg8 *) \
        Com_Block_BSPIS_es3_SPISlave_TxStsReg__STATUS_AUX_CTL_REG)
#define Com_Block_TX_STATUS_ACTL_PTR    (  (reg8 *) \
        Com_Block_TX_BSPIS_es3_SPISlave_TxStsReg__STATUS_AUX_CTL_REG)

#define Com_Block_RX_STATUS_ACTL_REG    (* (reg8 *) \
        Com_Block_BSPIS_es3_SPISlave_RxStsReg__STATUS_AUX_CTL_REG)
#define Com_Block_RX_STATUS_ACTL_PTR    (  (reg8 *) \
        Com_Block_RX_BSPIS_es3_SPISlave_RxStsReg__STATUS_AUX_CTL_REG)

#if(Com_Block_BIDIRECTIONAL_MODE)

    #define Com_Block_CONTROL_REG       (* (reg8 *) \
   Com_Block_BSPIS_es3_SPISlave_SyncCtl_CtrlReg__CONTROL_REG)
    #define Com_Block_CONTROL_PTR       (  (reg8 *) \
   Com_Block_BSPIS_es3_SPISlave_SyncCtl_CtrlReg__CONTROL_REG)

#endif /* Com_Block_BIDIRECTIONAL_MODE */

/* Obsolete register names. Not to be used in new designs */
#define Com_Block_TXDATA_ZERO               (Com_Block_TXDATA_ZERO_REG)
#define Com_Block_TXDATA                    (Com_Block_TXDATA_REG)
#define Com_Block_RXDATA                    (Com_Block_RXDATA_REG)
#define Com_Block_MISO_AUX_CONTROLDP0       (Com_Block_MISO_AUX_CTRL_DP0_REG)
#define Com_Block_MOSI_AUX_CONTROLDP0       (Com_Block_MOSI_AUX_CTRL_DP0_REG)
#define Com_Block_TXBUFFERREAD              (Com_Block_txBufferRead)
#define Com_Block_TXBUFFERWRITE             (Com_Block_txBufferWrite)
#define Com_Block_RXBUFFERREAD              (Com_Block_rxBufferRead)
#define Com_Block_RXBUFFERWRITE             (Com_Block_rxBufferWrite)

#if(Com_Block_DATA_WIDTH > 8u)

    #define Com_Block_MISO_AUX_CONTROLDP1   (Com_Block_MISO_AUX_CTRL_DP1_REG)
    #define Com_Block_MOSI_AUX_CONTROLDP1   (Com_Block_MOSI_AUX_CTRL_DP0_REG)

#endif /* Com_Block_DATA_WIDTH > 8u */

#define Com_Block_COUNTER_PERIOD            (Com_Block_COUNTER_PERIOD_REG)
#define Com_Block_COUNTER_CONTROL           (Com_Block_COUNTER_CONTROL_REG)
#define Com_Block_ONE                       (Com_Block_ONE_REG)
#define Com_Block_STATUS                    (Com_Block_TX_STATUS_REG)
#define Com_Block_STATUS_MASK               (Com_Block_TX_STATUS_MASK_REG)
#define Com_Block_STATUS_ACTL               (Com_Block_TX_STATUS_ACTL_REG)


/***************************************
*       Register Constants
***************************************/

/* Status Register Definitions */
#define Com_Block_STS_SPI_DONE_SHIFT             (0x00u)
#define Com_Block_STS_TX_FIFO_NOT_FULL_SHIFT     (0x01u)
#define Com_Block_STS_TX_FIFO_EMPTY_SHIFT        (0x02u)
#define Com_Block_STS_RX_FIFO_NOT_EMPTY_SHIFT    (0x03u)
#define Com_Block_STS_RX_FIFO_EMPTY_SHIFT        (0x04u)
#define Com_Block_STS_RX_FIFO_OVERRUN_SHIFT      (0x05u)
#define Com_Block_STS_RX_FIFO_FULL_SHIFT         (0x06u)
#define Com_Block_STS_BYTE_COMPLETE_SHIFT        (0x06u)

#define Com_Block_STS_SPI_DONE                   ((uint8)(0x01u << Com_Block_STS_SPI_DONE_SHIFT))
#define Com_Block_STS_TX_FIFO_EMPTY              ((uint8)(0x01u << Com_Block_STS_TX_FIFO_EMPTY_SHIFT))
#define Com_Block_STS_TX_FIFO_NOT_FULL           ((uint8)(0x01u << Com_Block_STS_TX_FIFO_NOT_FULL_SHIFT))
#define Com_Block_STS_RX_FIFO_EMPTY              ((uint8)(0x01u << Com_Block_STS_RX_FIFO_EMPTY_SHIFT))
#define Com_Block_STS_RX_FIFO_NOT_EMPTY          ((uint8)(0x01u << Com_Block_STS_RX_FIFO_NOT_EMPTY_SHIFT))
#define Com_Block_STS_RX_FIFO_OVERRUN            ((uint8)(0x01u << Com_Block_STS_RX_FIFO_OVERRUN_SHIFT))
#define Com_Block_STS_RX_FIFO_FULL               ((uint8)(0x01u << Com_Block_STS_RX_FIFO_FULL_SHIFT))
#define Com_Block_STS_BYTE_COMPLETE              ((uint8)(0x01u << Com_Block_STS_BYTE_COMPLETE_SHIFT))

#define Com_Block_STS_CLR_ON_RD_BYTES_MASK       (0x61u)

/* StatusI Register Interrupt Enable Control Bits */
/* As defined by the Register map for the AUX Control Register */
#define Com_Block_INT_ENABLE                     (0x10u)
#define Com_Block_TX_FIFO_CLR    (0x01u) /* F0 - TX FIFO */
#define Com_Block_RX_FIFO_CLR    (0x02u) /* F1 - RX FIFO */
#define Com_Block_FIFO_CLR       (Com_Block_TX_FIFO_CLR | Com_Block_RX_FIFO_CLR)

/* Bit Counter (7-bit) Control Register Bit Definitions */
/* As defined by the Register map for the AUX Control Register */
#define Com_Block_CNTR_ENABLE                    (0x20u)

/* Bi-Directional mode control bit */
#define Com_Block_CTRL_TX_SIGNAL_EN              (0x01u)

/* Datapath Auxillary Control Register definitions */
#define Com_Block_AUX_CTRL_FIFO0_CLR             (0x00u)
#define Com_Block_AUX_CTRL_FIFO1_CLR             (0x00u)
#define Com_Block_AUX_CTRL_FIFO0_LVL             (0x00u)
#define Com_Block_AUX_CTRL_FIFO1_LVL             (0x00u)
#define Com_Block_STATUS_ACTL_INT_EN_MASK        (0x10u)

/* Component disabled */
#define Com_Block_DISABLED   (0u)

/* Obosolete Status Register Definitions *DO NOT USE IN NEW DESIGNS* */
#define Com_Block_STS_TX_BUF_NOT_FULL_SHIFT      (0x01u)
#define Com_Block_STS_TX_BUF_FULL_SHIFT          (0x02u)
#define Com_Block_STS_RX_BUF_NOT_EMPTY_SHIFT     (0x03u)
#define Com_Block_STS_RX_BUF_EMPTY_SHIFT         (0x04u)
#define Com_Block_STS_RX_BUF_OVERRUN_SHIFT       (0x05u)

#define Com_Block_STS_TX_BUF_NOT_FULL            ((uint8)(0x01u << Com_Block_STS_TX_BUF_NOT_FULL_SHIFT))
#define Com_Block_STS_TX_BUF_FULL                ((uint8)(0x01u << Com_Block_STS_TX_BUF_FULL_SHIFT))
#define Com_Block_STS_RX_BUF_NOT_EMPTY           ((uint8)(0x01u << Com_Block_STS_RX_BUF_NOT_EMPTY_SHIFT))
#define Com_Block_STS_RX_BUF_EMPTY               ((uint8)(0x01u << Com_Block_STS_RX_BUF_EMPTY_SHIFT))
#define Com_Block_STS_RX_BUF_OVERRUN             ((uint8)(0x01u << Com_Block_STS_RX_BUF_OVERRUN_SHIFT))

/* Following definitions are for version Compatibility.
*  They are obsolete in SPIS v2_60.
*  Please do not use it in new projects
*/
#define Com_Block_DataWidth                  (Com_Block_DATA_WIDTH)
#define Com_Block_InternalClockUsed          (Com_Block_INTERNAL_CLOCK)
#define Com_Block_InternalTxInterruptEnabled (Com_Block_INTERNAL_TX_INT_ENABLED)
#define Com_Block_InternalRxInterruptEnabled (Com_Block_INTERNAL_RX_INT_ENABLED)
#define Com_Block_ModeUseZero                (Com_Block_MODE_USE_ZERO)
#define Com_Block_BidirectionalMode          (Com_Block_BIDIRECTIONAL_MODE)
#define Com_Block_Mode                       (Com_Block_MODE)
#define Com_Block_DATAWIDHT                  (Com_Block_DATA_WIDTH)
#define Com_Block_InternalInterruptEnabled   (0u)

#define Com_Block_TXBUFFERSIZE   (Com_Block_TX_BUFFER_SIZE)
#define Com_Block_RXBUFFERSIZE   (Com_Block_RX_BUFFER_SIZE)

#define Com_Block_TXBUFFER       Com_Block_txBuffer
#define Com_Block_RXBUFFER       Com_Block_rxBuffer


#endif  /* CY_SPIS_Com_Block_H */


/* [] END OF FILE */
