/*******************************************************************************
* File Name: GLCD_SPIM_SCB_SPI_UART.h
* Version 1.0
*
* Description:
*  This file provides constants and parameter values for the SCB Component in
*  SPI and UART modes.
*
* Note:
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_SPI_UART_GLCD_SPIM_SCB_H)
#define CY_SCB_SPI_UART_GLCD_SPIM_SCB_H

#include "GLCD_SPIM_SCB.h"


/***************************************
*   SPI Initial Parameter Constants
****************************************/

#define GLCD_SPIM_SCB_SPI_MODE                   (1u)
#define GLCD_SPIM_SCB_SPI_SUB_MODE               (0u)
#define GLCD_SPIM_SCB_SPI_CLOCK_MODE             (0u)
#define GLCD_SPIM_SCB_SPI_OVS_FACTOR             (4u)
#define GLCD_SPIM_SCB_SPI_MEDIAN_FILTER_ENABLE   (1u)
#define GLCD_SPIM_SCB_SPI_LATE_MISO_SAMPLE_ENABLE (1u)
#define GLCD_SPIM_SCB_SPI_RX_DATA_BITS_NUM       (9u)
#define GLCD_SPIM_SCB_SPI_TX_DATA_BITS_NUM       (9u)
#define GLCD_SPIM_SCB_SPI_WAKE_ENABLE            (0u)
#define GLCD_SPIM_SCB_SPI_BITS_ORDER             (1u)
#define GLCD_SPIM_SCB_SPI_TRANSFER_SEPARATION    (0u)
#define GLCD_SPIM_SCB_SPI_NUMBER_OF_SS_LINES     (4u)
#define GLCD_SPIM_SCB_SPI_RX_BUFFER_SIZE         (8u)
#define GLCD_SPIM_SCB_SPI_TX_BUFFER_SIZE         (8u)

#define GLCD_SPIM_SCB_SPI_INTERRUPT_MODE         (0u)

#define GLCD_SPIM_SCB_SPI_INTR_RX_MASK           (0u)
#define GLCD_SPIM_SCB_SPI_INTR_TX_MASK           (0u)

#define GLCD_SPIM_SCB_SPI_RX_TRIGGER_LEVEL       (7u)
#define GLCD_SPIM_SCB_SPI_TX_TRIGGER_LEVEL       (0u)


/***************************************
*   UART Initial Parameter Constants
****************************************/

#define GLCD_SPIM_SCB_UART_SUB_MODE              (0u)
#define GLCD_SPIM_SCB_UART_DIRECTION             (3u)
#define GLCD_SPIM_SCB_UART_DATA_BITS_NUM         (8u)
#define GLCD_SPIM_SCB_UART_PARITY_TYPE           (2u)
#define GLCD_SPIM_SCB_UART_STOP_BITS_NUM         (2u)
#define GLCD_SPIM_SCB_UART_OVS_FACTOR            (12u)
#define GLCD_SPIM_SCB_UART_IRDA_LOW_POWER        (0u)
#define GLCD_SPIM_SCB_UART_MEDIAN_FILTER_ENABLE  (0u)
#define GLCD_SPIM_SCB_UART_RETRY_ON_NACK         (0u)
#define GLCD_SPIM_SCB_UART_IRDA_POLARITY         (0u)
#define GLCD_SPIM_SCB_UART_DROP_ON_FRAME_ERR     (0u)
#define GLCD_SPIM_SCB_UART_DROP_ON_PARITY_ERR    (0u)
#define GLCD_SPIM_SCB_UART_WAKE_ENABLE           (0u)
#define GLCD_SPIM_SCB_UART_RX_BUFFER_SIZE        (8u)
#define GLCD_SPIM_SCB_UART_TX_BUFFER_SIZE        (8u)
#define GLCD_SPIM_SCB_UART_MP_MODE_ENABLE        (0u)
#define GLCD_SPIM_SCB_UART_MP_ACCEPT_ADDRESS     (0u)
#define GLCD_SPIM_SCB_UART_MP_RX_ADDRESS         (2u)
#define GLCD_SPIM_SCB_UART_MP_RX_ADDRESS_MASK    (255u)

#define GLCD_SPIM_SCB_UART_INTERRUPT_MODE        (0u)

#define GLCD_SPIM_SCB_UART_INTR_RX_MASK          (0u)
#define GLCD_SPIM_SCB_UART_INTR_TX_MASK          (0u)

#define GLCD_SPIM_SCB_UART_RX_TRIGGER_LEVEL      (7u)
#define GLCD_SPIM_SCB_UART_TX_TRIGGER_LEVEL      (0u)

/* Sources of RX errors */
#define GLCD_SPIM_SCB_INTR_RX_ERR        (GLCD_SPIM_SCB_INTR_RX_OVERFLOW    | \
                                             GLCD_SPIM_SCB_INTR_RX_UNDERFLOW   | \
                                             GLCD_SPIM_SCB_INTR_RX_FRAME_ERROR | \
                                             GLCD_SPIM_SCB_INTR_RX_PARITY_ERROR)

/* UART direction enum */
#define GLCD_SPIM_SCB_UART_RX    (1u)
#define GLCD_SPIM_SCB_UART_TX    (2u)
#define GLCD_SPIM_SCB_UART_TX_RX (3u)


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* Enable SPI mode interrupt */
#define GLCD_SPIM_SCB_SPI_INTERRUPT_ENABLE   ((GLCD_SPIM_SCB_SPI_INTERRUPT_MODE == \
                                                    GLCD_SPIM_SCB_SCB_INTR_MODE_INTERNAL) ? (1u) : (0u))

/* Enable UART mode interrupt */
#define GLCD_SPIM_SCB_UART_INTERRUPT_ENABLE  ((GLCD_SPIM_SCB_UART_INTERRUPT_MODE == \
                                                    GLCD_SPIM_SCB_SCB_INTR_MODE_INTERNAL) ? (1u) : (0u))

#if(GLCD_SPIM_SCB_SCB_MODE_UNCONFIG_CONST_CFG)

    /* Direction */
    #define GLCD_SPIM_SCB_RX_DIRECTION           (1u)
    #define GLCD_SPIM_SCB_TX_DIRECTION           (1u)
    #define GLCD_SPIM_SCB_UART_RX_DIRECTION      (1u)
    #define GLCD_SPIM_SCB_UART_TX_DIRECTION      (1u)

    /* Only external RX and TX buffer for uncofigured mode */
    #define GLCD_SPIM_SCB_INTERNAL_RX_SW_BUFFER   (0u)
    #define GLCD_SPIM_SCB_INTERNAL_TX_SW_BUFFER   (0u)

    /* Get RX and TX buffer size */
    #define GLCD_SPIM_SCB_RX_BUFFER_SIZE (GLCD_SPIM_SCB_rxBufferSize)
    #define GLCD_SPIM_SCB_TX_BUFFER_SIZE (GLCD_SPIM_SCB_txBufferSize)

    /* Return true if buffer is provided */
    #define GLCD_SPIM_SCB_CHECK_RX_SW_BUFFER (NULL != GLCD_SPIM_SCB_rxBuffer)
    #define GLCD_SPIM_SCB_CHECK_TX_SW_BUFFER (NULL != GLCD_SPIM_SCB_txBuffer)

    /* Alwasy provde global variables to support RX and TX buffers */
    #define GLCD_SPIM_SCB_INTERNAL_RX_SW_BUFFER_CONST    (1u)
    #define GLCD_SPIM_SCB_INTERNAL_TX_SW_BUFFER_CONST    (1u)

    /* Get wakeup enable option */
    #define GLCD_SPIM_SCB_CHECK_SPI_WAKE_ENABLE  (0u != GLCD_SPIM_SCB_scbEnableWake)
    #define GLCD_SPIM_SCB_CHECK_UART_WAKE_ENABLE (0u != GLCD_SPIM_SCB_scbEnableWake)

#else

    /* SPI internal RX and TX buffers */
    #define GLCD_SPIM_SCB_INTERNAL_SPI_RX_SW_BUFFER  (GLCD_SPIM_SCB_SPI_RX_BUFFER_SIZE > \
                                                                                            GLCD_SPIM_SCB_FIFO_SIZE)
    #define GLCD_SPIM_SCB_INTERNAL_SPI_TX_SW_BUFFER  (GLCD_SPIM_SCB_SPI_TX_BUFFER_SIZE > \
                                                                                            GLCD_SPIM_SCB_FIFO_SIZE)

    /* UART internal RX and TX buffers */
    #define GLCD_SPIM_SCB_INTERNAL_UART_RX_SW_BUFFER  (GLCD_SPIM_SCB_UART_RX_BUFFER_SIZE > \
                                                                                            GLCD_SPIM_SCB_FIFO_SIZE)
    #define GLCD_SPIM_SCB_INTERNAL_UART_TX_SW_BUFFER  (GLCD_SPIM_SCB_UART_TX_BUFFER_SIZE > \
                                                                                            GLCD_SPIM_SCB_FIFO_SIZE)

    /* SPI Direction */
    #define GLCD_SPIM_SCB_SPI_RX_DIRECTION (1u)
    #define GLCD_SPIM_SCB_SPI_TX_DIRECTION (1u)

    /* UART Direction */
    #define GLCD_SPIM_SCB_UART_RX_DIRECTION (0u != (GLCD_SPIM_SCB_UART_DIRECTION & GLCD_SPIM_SCB_UART_RX))
    #define GLCD_SPIM_SCB_UART_TX_DIRECTION (0u != (GLCD_SPIM_SCB_UART_DIRECTION & GLCD_SPIM_SCB_UART_TX))

    /* Direction */
    #define GLCD_SPIM_SCB_RX_DIRECTION ((GLCD_SPIM_SCB_SCB_MODE_SPI_CONST_CFG) ? \
                                            (GLCD_SPIM_SCB_SPI_RX_DIRECTION) : (GLCD_SPIM_SCB_UART_RX_DIRECTION))

    #define GLCD_SPIM_SCB_TX_DIRECTION ((GLCD_SPIM_SCB_SCB_MODE_SPI_CONST_CFG) ? \
                                            (GLCD_SPIM_SCB_SPI_TX_DIRECTION) : (GLCD_SPIM_SCB_UART_TX_DIRECTION))

    /* Internal RX and TX buffer: for SPI or UART */
    #if(GLCD_SPIM_SCB_SCB_MODE_SPI_CONST_CFG)

        /* Internal SPI RX and TX buffer */
        #define GLCD_SPIM_SCB_INTERNAL_RX_SW_BUFFER  (GLCD_SPIM_SCB_INTERNAL_SPI_RX_SW_BUFFER)
        #define GLCD_SPIM_SCB_INTERNAL_TX_SW_BUFFER  (GLCD_SPIM_SCB_INTERNAL_SPI_TX_SW_BUFFER)

        /* Internal SPI RX and TX buffer size */
        #define GLCD_SPIM_SCB_RX_BUFFER_SIZE         (GLCD_SPIM_SCB_SPI_RX_BUFFER_SIZE + 1u)
        #define GLCD_SPIM_SCB_TX_BUFFER_SIZE         (GLCD_SPIM_SCB_SPI_TX_BUFFER_SIZE)

    #else

        /* Internal UART RX and TX buffer */
        #define GLCD_SPIM_SCB_INTERNAL_RX_SW_BUFFER  (GLCD_SPIM_SCB_INTERNAL_UART_RX_SW_BUFFER)
        #define GLCD_SPIM_SCB_INTERNAL_TX_SW_BUFFER  (GLCD_SPIM_SCB_INTERNAL_UART_TX_SW_BUFFER)

        /* Internal UART RX and TX buffer size */
        #define GLCD_SPIM_SCB_RX_BUFFER_SIZE         (GLCD_SPIM_SCB_UART_RX_BUFFER_SIZE + 1u)
        #define GLCD_SPIM_SCB_TX_BUFFER_SIZE         (GLCD_SPIM_SCB_UART_TX_BUFFER_SIZE)

    #endif /* (GLCD_SPIM_SCB_SCB_MODE_SPI_CONST_CFG) */

    /* Internal RX and TX buffer: for SPI or UART. Used in conditional compilation check */
    #define GLCD_SPIM_SCB_CHECK_RX_SW_BUFFER (GLCD_SPIM_SCB_INTERNAL_RX_SW_BUFFER)
    #define GLCD_SPIM_SCB_CHECK_TX_SW_BUFFER (GLCD_SPIM_SCB_INTERNAL_TX_SW_BUFFER)

    /* Provide global variables to support RX and TX buffers */
    #define GLCD_SPIM_SCB_INTERNAL_RX_SW_BUFFER_CONST    (GLCD_SPIM_SCB_INTERNAL_RX_SW_BUFFER)
    #define GLCD_SPIM_SCB_INTERNAL_TX_SW_BUFFER_CONST    (GLCD_SPIM_SCB_INTERNAL_TX_SW_BUFFER)

    /* Get wakeup enable option */
    #define GLCD_SPIM_SCB_CHECK_SPI_WAKE_ENABLE  (0u != GLCD_SPIM_SCB_SPI_WAKE_ENABLE)
    #define GLCD_SPIM_SCB_CHECK_UART_WAKE_ENABLE (0u != GLCD_SPIM_SCB_UART_WAKE_ENABLE)

#endif /* End (GLCD_SPIM_SCB_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Bootloader communication interface enable: NOT supported yet */
#define GLCD_SPIM_SCB_SPI_BTLDR_COMM_ENABLED   ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_GLCD_SPIM_SCB) || \
                                                    (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

#define GLCD_SPIM_SCB_UART_BTLDR_COMM_ENABLED   ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_GLCD_SPIM_SCB) || \
                                                    (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))


/***************************************
*       Type Definitions
***************************************/

/* GLCD_SPIM_SCB_SPI_INIT_STRUCT */
typedef struct
{
    uint32 mode;
    uint32 submode;
    uint32 sclkMode;
    uint32 oversample;
    uint32 enableMedianFilter;
    uint32 enableLateSampling;
    uint32 enableWake;
    uint32 rxDataBits;
    uint32 txDataBits;
    uint32 bitOrder;
    uint32 transferSeperation;
    uint32 rxBufferSize;
    uint8* rxBuffer;
    uint32 txBufferSize;
    uint8* txBuffer;
    uint32 enableInterrupt;
    uint32 rxInterruptMask;
    uint32 rxTriggerLevel;
    uint32 txInterruptMask;
    uint32 txTriggerLevel;
} GLCD_SPIM_SCB_SPI_INIT_STRUCT;

/* GLCD_SPIM_SCB_UART_INIT_STRUCT */
typedef struct
{
    uint32 mode;
    uint32 direction;
    uint32 dataBits;
    uint32 parity;
    uint32 stopBits;
    uint32 oversample;
    uint32 enableIrdaLowPower;
    uint32 enableMedianFilter;
    uint32 enableRetryNack;
    uint32 enableInvertedRx;
    uint32 dropOnParityErr;
    uint32 dropOnFrameErr;
    uint32 enableWake;
    uint32 rxBufferSize;
    uint8* rxBuffer;
    uint32 txBufferSize;
    uint8* txBuffer;
    uint32 enableMultiproc;
    uint32 multiprocAcceptAddr;
    uint32 multiprocAddr;
    uint32 multiprocAddrMask;
    uint32 enableInterrupt;
    uint32 rxInterruptMask;
    uint32 rxTriggerLevel;
    uint32 txInterruptMask;
    uint32 txTriggerLevel;
} GLCD_SPIM_SCB_UART_INIT_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

/* SPI specific functions */
#if(GLCD_SPIM_SCB_SCB_MODE_UNCONFIG_CONST_CFG)
    void GLCD_SPIM_SCB_SpiInit(const GLCD_SPIM_SCB_SPI_INIT_STRUCT *config);
#endif /* (GLCD_SPIM_SCB_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(GLCD_SPIM_SCB_SCB_MODE_SPI_INC)
    void GLCD_SPIM_SCB_SpiSetActiveSlaveSelect(uint32 activeSelect);
#endif /* (GLCD_SPIM_SCB_SCB_MODE_SPI_INC) */

/* UART specific functions */
#if(GLCD_SPIM_SCB_SCB_MODE_UNCONFIG_CONST_CFG)
    void GLCD_SPIM_SCB_UartInit(const GLCD_SPIM_SCB_UART_INIT_STRUCT *config);
#endif /* (GLCD_SPIM_SCB_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(GLCD_SPIM_SCB_SCB_MODE_UART_INC)
    void GLCD_SPIM_SCB_UartSetRxAddress(uint32 address);
    void GLCD_SPIM_SCB_UartSetRxAddressMask(uint32 addressMask);
#endif /* (GLCD_SPIM_SCB_SCB_MODE_UART_INC) */

/* UART RX direction APIs */
#if(GLCD_SPIM_SCB_UART_RX_DIRECTION)
    uint32 GLCD_SPIM_SCB_UartGetChar(void);
    uint32 GLCD_SPIM_SCB_UartGetByte(void);
#endif /* (GLCD_SPIM_SCB_UART_RX_DIRECTION) */

/* UART TX direction APIs */
#if(GLCD_SPIM_SCB_UART_TX_DIRECTION)
    #define GLCD_SPIM_SCB_UartPutChar(ch)    GLCD_SPIM_SCB_SpiUartWriteTxData((uint32)(ch))
    void GLCD_SPIM_SCB_UartPutString(const char8 string[]);
    void GLCD_SPIM_SCB_UartPutCRLF(uint32 txDataByte);
#endif /* (GLCD_SPIM_SCB_UART_TX_DIRECTION) */

/* Common APIs Rx direction */
#if(GLCD_SPIM_SCB_RX_DIRECTION)
    uint32 GLCD_SPIM_SCB_SpiUartReadRxData(void);
    uint32 GLCD_SPIM_SCB_SpiUartGetRxBufferSize(void);
    void   GLCD_SPIM_SCB_SpiUartClearRxBuffer(void);
#endif /* (GLCD_SPIM_SCB_RX_DIRECTION) */

/* Common APIs Tx direction */
#if(GLCD_SPIM_SCB_TX_DIRECTION)
    void   GLCD_SPIM_SCB_SpiUartWriteTxData(uint32 txDataByte);
    void   GLCD_SPIM_SCB_SpiUartPutArray(const uint16 wrBuf[], uint32 count);
    void   GLCD_SPIM_SCB_SpiUartClearTxBuffer(void);
    uint32 GLCD_SPIM_SCB_SpiUartGetTxBufferSize(void);
#endif /* (GLCD_SPIM_SCB_TX_DIRECTION) */

CY_ISR_PROTO(GLCD_SPIM_SCB_SPI_UART_ISR);

#if(GLCD_SPIM_SCB_UART_RX_WAKEUP_IRQ)
    CY_ISR_PROTO(GLCD_SPIM_SCB_UART_WAKEUP_ISR);
#endif /* (GLCD_SPIM_SCB_UART_RX_WAKEUP_IRQ) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (GLCD_SPIM_SCB_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void GLCD_SPIM_SCB_SpiCyBtldrCommStart(void);
    void GLCD_SPIM_SCB_SpiCyBtldrCommStop (void);
    void GLCD_SPIM_SCB_SpiCyBtldrCommReset(void);
    cystatus GLCD_SPIM_SCB_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus GLCD_SPIM_SCB_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (GLCD_SPIM_SCB_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (GLCD_SPIM_SCB_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void GLCD_SPIM_SCB_UartCyBtldrCommStart(void);
    void GLCD_SPIM_SCB_UartCyBtldrCommStop (void);
    void GLCD_SPIM_SCB_UartCyBtldrCommReset(void);
    cystatus GLCD_SPIM_SCB_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus GLCD_SPIM_SCB_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (GLCD_SPIM_SCB_UART_BTLDR_COMM_ENABLED) */


/***************************************
*     Buffer Access Macro Definitions
***************************************/

#if(GLCD_SPIM_SCB_SCB_MODE_UNCONFIG_CONST_CFG)
    /* RX direction */
    void   GLCD_SPIM_SCB_PutWordInRxBuffer  (uint32 idx, uint32 rxDataByte);
    uint32 GLCD_SPIM_SCB_GetWordFromRxBuffer(uint32 idx);

    /* TX direction */
    void   GLCD_SPIM_SCB_PutWordInTxBuffer  (uint32 idx, uint32 txDataByte);
    uint32 GLCD_SPIM_SCB_GetWordFromTxBuffer(uint32 idx);

#else

    /* RX direction */
    #if(GLCD_SPIM_SCB_INTERNAL_RX_SW_BUFFER_CONST)
        #define GLCD_SPIM_SCB_PutWordInRxBuffer(idx, rxDataByte) \
                do{                                                 \
                    GLCD_SPIM_SCB_rxBufferInternal[(idx)] = ((uint16) (rxDataByte)); \
                }while(0)

        #define GLCD_SPIM_SCB_GetWordFromRxBuffer(idx) GLCD_SPIM_SCB_rxBufferInternal[(idx)]

    #endif /* (GLCD_SPIM_SCB_INTERNAL_RX_SW_BUFFER_CONST) */

    /* TX direction */
    #if(GLCD_SPIM_SCB_INTERNAL_TX_SW_BUFFER_CONST)
        #define GLCD_SPIM_SCB_PutWordInTxBuffer(idx, txDataByte) \
                    do{                                             \
                        GLCD_SPIM_SCB_txBufferInternal[(idx)] = ((uint16) (txDataByte)); \
                    }while(0)

        #define GLCD_SPIM_SCB_GetWordFromTxBuffer(idx) GLCD_SPIM_SCB_txBufferInternal[(idx)]

    #endif /* (GLCD_SPIM_SCB_INTERNAL_TX_SW_BUFFER_CONST) */

#endif /* (GLCD_SPIM_SCB_TX_SW_BUFFER_ENABLE) */


/***************************************
*         SPI API Constants
***************************************/

/* SPI mode enum */
#define GLCD_SPIM_SCB_SPI_SLAVE  (0u)
#define GLCD_SPIM_SCB_SPI_MASTER (1u)

/* SPI sub mode enum */
#define GLCD_SPIM_SCB_SPI_MODE_MOTOROLA      (0x00u)
#define GLCD_SPIM_SCB_SPI_MODE_TI_COINCIDES  (0x01u)
#define GLCD_SPIM_SCB_SPI_MODE_TI_PRECEDES   (0x11u)
#define GLCD_SPIM_SCB_SPI_MODE_NATIONAL      (0x02u)
#define GLCD_SPIM_SCB_SPI_MODE_MASK          (0x03u)
#define GLCD_SPIM_SCB_SPI_MODE_TI_PRECEDES_MASK  (0x10u)

/* SPI phase and polarity mode enum */
#define GLCD_SPIM_SCB_SPI_SCLK_CPHA0_CPOL0   (0x00u)
#define GLCD_SPIM_SCB_SPI_SCLK_CPHA0_CPOL1   (0x02u)
#define GLCD_SPIM_SCB_SPI_SCLK_CPHA1_CPOL0   (0x01u)
#define GLCD_SPIM_SCB_SPI_SCLK_CPHA1_CPOL1   (0x03u)

/* SPI bits order enum */
#define GLCD_SPIM_SCB_BITS_ORDER_LSB_FIRST   (0u)
#define GLCD_SPIM_SCB_BITS_ORDER_MSB_FIRST   (1u)

/* SPI transfer separation enum */
#define GLCD_SPIM_SCB_SPI_TRANSFER_SEPARATED     (0u)
#define GLCD_SPIM_SCB_SPI_TRANSFER_CONTINUOUS    (1u)

/* "activeSS" constants for SpiSetActiveSlaveSelect() function */
#define GLCD_SPIM_SCB_SPIM_ACTIVE_SS0    (0x00u)
#define GLCD_SPIM_SCB_SPIM_ACTIVE_SS1    (0x01u)
#define GLCD_SPIM_SCB_SPIM_ACTIVE_SS2    (0x02u)
#define GLCD_SPIM_SCB_SPIM_ACTIVE_SS3    (0x03u)


/***************************************
*         UART API Constants
***************************************/

/* UART sub-modes enum */
#define GLCD_SPIM_SCB_UART_MODE_STD          (0u)
#define GLCD_SPIM_SCB_UART_MODE_SMARTCARD    (1u)
#define GLCD_SPIM_SCB_UART_MODE_IRDA         (2u)

/* UART direction enum */
#define GLCD_SPIM_SCB_UART_RX    (1u)
#define GLCD_SPIM_SCB_UART_TX    (2u)
#define GLCD_SPIM_SCB_UART_TX_RX (3u)

/* UART parity enum */
#define GLCD_SPIM_SCB_UART_PARITY_EVEN   (0u)
#define GLCD_SPIM_SCB_UART_PARITY_ODD    (1u)
#define GLCD_SPIM_SCB_UART_PARITY_NONE   (2u)

/* UART stop bits enum */
#define GLCD_SPIM_SCB_UART_STOP_BITS_1   (1u)
#define GLCD_SPIM_SCB_UART_STOP_BITS_1_5 (2u)
#define GLCD_SPIM_SCB_UART_STOP_BITS_2   (3u)

/* UART IrDA low power OVS enum */
#define GLCD_SPIM_SCB_UART_IRDA_LP_OVS16     (16u)
#define GLCD_SPIM_SCB_UART_IRDA_LP_OVS32     (32u)
#define GLCD_SPIM_SCB_UART_IRDA_LP_OVS48     (48u)
#define GLCD_SPIM_SCB_UART_IRDA_LP_OVS96     (96u)
#define GLCD_SPIM_SCB_UART_IRDA_LP_OVS192    (192u)
#define GLCD_SPIM_SCB_UART_IRDA_LP_OVS768    (768u)
#define GLCD_SPIM_SCB_UART_IRDA_LP_OVS1536   (1536u)

/* Uart MP: mark (address) and space (data) bit definitions */
#define GLCD_SPIM_SCB_UART_MP_MARK       (0x100u)
#define GLCD_SPIM_SCB_UART_MP_SPACE      (0x000u)


/***************************************
*     Vars with External Linkage
***************************************/

#if(GLCD_SPIM_SCB_SCB_MODE_UNCONFIG_CONST_CFG)
    extern const GLCD_SPIM_SCB_SPI_INIT_STRUCT  GLCD_SPIM_SCB_configSpi;
    extern const GLCD_SPIM_SCB_UART_INIT_STRUCT GLCD_SPIM_SCB_configUart;
#endif /* (GLCD_SPIM_SCB_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*    Specific SPI Macro Definitions
***************************************/

#define GLCD_SPIM_SCB_GET_SPI_INTR_SLAVE_MASK(sourceMask)  ((sourceMask) & GLCD_SPIM_SCB_INTR_SLAVE_SPI_BUS_ERROR)
#define GLCD_SPIM_SCB_GET_SPI_INTR_MASTER_MASK(sourceMask) ((sourceMask) & GLCD_SPIM_SCB_INTR_MASTER_SPI_DONE)
#define GLCD_SPIM_SCB_GET_SPI_INTR_RX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~GLCD_SPIM_SCB_INTR_SLAVE_SPI_BUS_ERROR)

#define GLCD_SPIM_SCB_GET_SPI_INTR_TX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~GLCD_SPIM_SCB_INTR_MASTER_SPI_DONE)


/***************************************
*    Specific UART Macro Definitions
***************************************/

#define GLCD_SPIM_SCB_UART_GET_CTRL_OVS_IRDA_LP(oversample) \
        ((GLCD_SPIM_SCB_UART_IRDA_LP_OVS16   == (oversample)) ? GLCD_SPIM_SCB_CTRL_OVS_IRDA_LP_OVS16 : \
         ((GLCD_SPIM_SCB_UART_IRDA_LP_OVS32   == (oversample)) ? GLCD_SPIM_SCB_CTRL_OVS_IRDA_LP_OVS32 : \
          ((GLCD_SPIM_SCB_UART_IRDA_LP_OVS48   == (oversample)) ? GLCD_SPIM_SCB_CTRL_OVS_IRDA_LP_OVS48 : \
           ((GLCD_SPIM_SCB_UART_IRDA_LP_OVS96   == (oversample)) ? GLCD_SPIM_SCB_CTRL_OVS_IRDA_LP_OVS96 : \
            ((GLCD_SPIM_SCB_UART_IRDA_LP_OVS192  == (oversample)) ? GLCD_SPIM_SCB_CTRL_OVS_IRDA_LP_OVS192 : \
             ((GLCD_SPIM_SCB_UART_IRDA_LP_OVS768  == (oversample)) ? GLCD_SPIM_SCB_CTRL_OVS_IRDA_LP_OVS768 : \
              ((GLCD_SPIM_SCB_UART_IRDA_LP_OVS1536 == (oversample)) ? GLCD_SPIM_SCB_CTRL_OVS_IRDA_LP_OVS1536 : \
                                                                          GLCD_SPIM_SCB_CTRL_OVS_IRDA_LP_OVS16)))))))

#define GLCD_SPIM_SCB_GET_UART_RX_CTRL_ENABLED(direction) ((0u != (GLCD_SPIM_SCB_UART_RX & (direction))) ? \
                                                                    (GLCD_SPIM_SCB_RX_CTRL_ENABLED) : (0u))

#define GLCD_SPIM_SCB_GET_UART_TX_CTRL_ENABLED(direction) ((0u != (GLCD_SPIM_SCB_UART_TX & (direction))) ? \
                                                                    (GLCD_SPIM_SCB_TX_CTRL_ENABLED) : (0u))


/***************************************
*        SPI Register Settings
***************************************/

#define GLCD_SPIM_SCB_CTRL_SPI      (GLCD_SPIM_SCB_CTRL_MODE_SPI)
#define GLCD_SPIM_SCB_SPI_RX_CTRL   (GLCD_SPIM_SCB_RX_CTRL_ENABLED)
#define GLCD_SPIM_SCB_SPI_TX_CTRL   (GLCD_SPIM_SCB_TX_CTRL_ENABLED)


/***************************************
*       SPI Init Register Settings
***************************************/

#if(GLCD_SPIM_SCB_SCB_MODE_SPI_CONST_CFG)

    /* SPI Configuration */
    #define GLCD_SPIM_SCB_SPI_DEFAULT_CTRL \
                    (GLCD_SPIM_SCB_GET_CTRL_OVS(GLCD_SPIM_SCB_SPI_OVS_FACTOR)         | \
                     GLCD_SPIM_SCB_GET_CTRL_EC_AM_MODE(GLCD_SPIM_SCB_SPI_WAKE_ENABLE) | \
                     GLCD_SPIM_SCB_CTRL_SPI)

    #define GLCD_SPIM_SCB_SPI_DEFAULT_SPI_CTRL \
                    (GLCD_SPIM_SCB_GET_SPI_CTRL_CONTINUOUS    (GLCD_SPIM_SCB_SPI_TRANSFER_SEPARATION)       | \
                     GLCD_SPIM_SCB_GET_SPI_CTRL_SELECT_PRECEDE(GLCD_SPIM_SCB_SPI_SUB_MODE &                   \
                                                                  GLCD_SPIM_SCB_SPI_MODE_TI_PRECEDES_MASK)     | \
                     GLCD_SPIM_SCB_GET_SPI_CTRL_SCLK_MODE     (GLCD_SPIM_SCB_SPI_CLOCK_MODE)                | \
                     GLCD_SPIM_SCB_GET_SPI_CTRL_LATE_MISO_SAMPLE(GLCD_SPIM_SCB_SPI_LATE_MISO_SAMPLE_ENABLE) | \
                     GLCD_SPIM_SCB_GET_SPI_CTRL_SUB_MODE      (GLCD_SPIM_SCB_SPI_SUB_MODE)                  | \
                     GLCD_SPIM_SCB_GET_SPI_CTRL_MASTER_MODE   (GLCD_SPIM_SCB_SPI_MODE))

    /* RX direction */
    #define GLCD_SPIM_SCB_SPI_DEFAULT_RX_CTRL \
                    (GLCD_SPIM_SCB_GET_RX_CTRL_DATA_WIDTH(GLCD_SPIM_SCB_SPI_RX_DATA_BITS_NUM)     | \
                     GLCD_SPIM_SCB_GET_RX_CTRL_BIT_ORDER (GLCD_SPIM_SCB_SPI_BITS_ORDER)           | \
                     GLCD_SPIM_SCB_GET_RX_CTRL_MEDIAN    (GLCD_SPIM_SCB_SPI_MEDIAN_FILTER_ENABLE) | \
                     GLCD_SPIM_SCB_SPI_RX_CTRL)

    #define GLCD_SPIM_SCB_SPI_DEFAULT_RX_FIFO_CTRL \
                    GLCD_SPIM_SCB_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(GLCD_SPIM_SCB_SPI_RX_TRIGGER_LEVEL)

    /* TX direction */
    #define GLCD_SPIM_SCB_SPI_DEFAULT_TX_CTRL \
                    (GLCD_SPIM_SCB_GET_TX_CTRL_DATA_WIDTH(GLCD_SPIM_SCB_SPI_TX_DATA_BITS_NUM) | \
                     GLCD_SPIM_SCB_GET_TX_CTRL_BIT_ORDER (GLCD_SPIM_SCB_SPI_BITS_ORDER)       | \
                     GLCD_SPIM_SCB_SPI_TX_CTRL)

    #define GLCD_SPIM_SCB_SPI_DEFAULT_TX_FIFO_CTRL \
                    GLCD_SPIM_SCB_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(GLCD_SPIM_SCB_SPI_TX_TRIGGER_LEVEL)

    /* Interrupt sources */
    #define GLCD_SPIM_SCB_SPI_INTERRUPT_DISABLE          (0u == GLCD_SPIM_SCB_SPI_INTERRUPT_ENABLE)

    #define GLCD_SPIM_SCB_SPI_DEFAULT_INTR_SPI_EC_MASK   (GLCD_SPIM_SCB_NO_INTR_SOURCES)

    #define GLCD_SPIM_SCB_SPI_DEFAULT_INTR_I2C_EC_MASK   (GLCD_SPIM_SCB_NO_INTR_SOURCES)
    #define GLCD_SPIM_SCB_SPI_DEFAULT_INTR_SLAVE_MASK \
                    (GLCD_SPIM_SCB_SPI_INTR_RX_MASK & GLCD_SPIM_SCB_INTR_SLAVE_SPI_BUS_ERROR)

    #define GLCD_SPIM_SCB_SPI_DEFAULT_INTR_MASTER_MASK \
                    (GLCD_SPIM_SCB_SPI_INTR_TX_MASK & GLCD_SPIM_SCB_INTR_MASTER_SPI_DONE)

    #define GLCD_SPIM_SCB_SPI_DEFAULT_INTR_RX_MASK \
                    (GLCD_SPIM_SCB_SPI_INTR_RX_MASK & (uint32) ~GLCD_SPIM_SCB_INTR_SLAVE_SPI_BUS_ERROR)

    #define GLCD_SPIM_SCB_SPI_DEFAULT_INTR_TX_MASK \
                    (GLCD_SPIM_SCB_SPI_INTR_TX_MASK & (uint32) ~GLCD_SPIM_SCB_INTR_MASTER_SPI_DONE)

#endif /* (GLCD_SPIM_SCB_SCB_MODE_SPI_CONST_CFG) */


/***************************************
*        UART Register Settings
***************************************/

#define GLCD_SPIM_SCB_CTRL_UART      (GLCD_SPIM_SCB_CTRL_MODE_UART)
#define GLCD_SPIM_SCB_UART_RX_CTRL   (GLCD_SPIM_SCB_RX_CTRL_LSB_FIRST) /* LSB for UART goes first */
#define GLCD_SPIM_SCB_UART_TX_CTRL   (GLCD_SPIM_SCB_TX_CTRL_LSB_FIRST) /* LSB for UART goes first */


/***************************************
*      UART Init Register Settings
***************************************/

#if(GLCD_SPIM_SCB_SCB_MODE_UART_CONST_CFG)

    /* UART configuration */
    #if(GLCD_SPIM_SCB_UART_MODE_IRDA == GLCD_SPIM_SCB_UART_SUB_MODE)

        #define GLCD_SPIM_SCB_DEFAULT_CTRL_OVS   ((0u != GLCD_SPIM_SCB_UART_IRDA_LOW_POWER) ?              \
                                (GLCD_SPIM_SCB_UART_GET_CTRL_OVS_IRDA_LP(GLCD_SPIM_SCB_UART_OVS_FACTOR)) : \
                                (GLCD_SPIM_SCB_CTRL_OVS_IRDA_OVS16))

    #else

        #define GLCD_SPIM_SCB_DEFAULT_CTRL_OVS   GLCD_SPIM_SCB_GET_CTRL_OVS(GLCD_SPIM_SCB_UART_OVS_FACTOR)

    #endif /* (GLCD_SPIM_SCB_UART_MODE_IRDA == GLCD_SPIM_SCB_UART_SUB_MODE) */

    #define GLCD_SPIM_SCB_UART_DEFAULT_CTRL \
                                (GLCD_SPIM_SCB_GET_CTRL_ADDR_ACCEPT(GLCD_SPIM_SCB_UART_MP_ACCEPT_ADDRESS) | \
                                 GLCD_SPIM_SCB_DEFAULT_CTRL_OVS                                              | \
                                 GLCD_SPIM_SCB_CTRL_UART)

    #define GLCD_SPIM_SCB_UART_DEFAULT_UART_CTRL \
                                    (GLCD_SPIM_SCB_GET_UART_CTRL_MODE(GLCD_SPIM_SCB_UART_SUB_MODE))

    /* RX direction */
    #define GLCD_SPIM_SCB_UART_DEFAULT_RX_CTRL_PARITY \
                                ((GLCD_SPIM_SCB_UART_PARITY_NONE != GLCD_SPIM_SCB_UART_PARITY_TYPE) ?      \
                                  (GLCD_SPIM_SCB_GET_UART_RX_CTRL_PARITY(GLCD_SPIM_SCB_UART_PARITY_TYPE) | \
                                   GLCD_SPIM_SCB_UART_RX_CTRL_PARITY_ENABLED) : (0u))

    #define GLCD_SPIM_SCB_UART_DEFAULT_UART_RX_CTRL \
                    (GLCD_SPIM_SCB_GET_UART_RX_CTRL_MODE(GLCD_SPIM_SCB_UART_STOP_BITS_NUM)                    | \
                     GLCD_SPIM_SCB_GET_UART_RX_CTRL_POLARITY(GLCD_SPIM_SCB_UART_IRDA_POLARITY)                | \
                     GLCD_SPIM_SCB_GET_UART_RX_CTRL_MP_MODE(GLCD_SPIM_SCB_UART_MP_MODE_ENABLE)                | \
                     GLCD_SPIM_SCB_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(GLCD_SPIM_SCB_UART_DROP_ON_PARITY_ERR) | \
                     GLCD_SPIM_SCB_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(GLCD_SPIM_SCB_UART_DROP_ON_FRAME_ERR)   | \
                     GLCD_SPIM_SCB_UART_DEFAULT_RX_CTRL_PARITY)

    #define GLCD_SPIM_SCB_UART_DEFAULT_RX_CTRL \
                                (GLCD_SPIM_SCB_GET_RX_CTRL_DATA_WIDTH(GLCD_SPIM_SCB_UART_DATA_BITS_NUM)        | \
                                 GLCD_SPIM_SCB_GET_RX_CTRL_MEDIAN    (GLCD_SPIM_SCB_UART_MEDIAN_FILTER_ENABLE) | \
                                 GLCD_SPIM_SCB_GET_UART_RX_CTRL_ENABLED(GLCD_SPIM_SCB_UART_DIRECTION))

    #define GLCD_SPIM_SCB_UART_DEFAULT_RX_FIFO_CTRL \
                                GLCD_SPIM_SCB_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(GLCD_SPIM_SCB_UART_RX_TRIGGER_LEVEL)

    #define GLCD_SPIM_SCB_UART_DEFAULT_RX_MATCH_REG  ((0u != GLCD_SPIM_SCB_UART_MP_MODE_ENABLE) ?          \
                                (GLCD_SPIM_SCB_GET_RX_MATCH_ADDR(GLCD_SPIM_SCB_UART_MP_RX_ADDRESS) | \
                                 GLCD_SPIM_SCB_GET_RX_MATCH_MASK(GLCD_SPIM_SCB_UART_MP_RX_ADDRESS_MASK)) : (0u))

    /* TX direction */
    #define GLCD_SPIM_SCB_UART_DEFAULT_TX_CTRL_PARITY (GLCD_SPIM_SCB_UART_DEFAULT_RX_CTRL_PARITY)

    #define GLCD_SPIM_SCB_UART_DEFAULT_UART_TX_CTRL \
                                (GLCD_SPIM_SCB_GET_UART_TX_CTRL_MODE(GLCD_SPIM_SCB_UART_STOP_BITS_NUM)       | \
                                 GLCD_SPIM_SCB_GET_UART_TX_CTRL_RETRY_NACK(GLCD_SPIM_SCB_UART_RETRY_ON_NACK) | \
                                 GLCD_SPIM_SCB_UART_DEFAULT_TX_CTRL_PARITY)

    #define GLCD_SPIM_SCB_UART_DEFAULT_TX_CTRL \
                                (GLCD_SPIM_SCB_GET_TX_CTRL_DATA_WIDTH(GLCD_SPIM_SCB_UART_DATA_BITS_NUM) | \
                                 GLCD_SPIM_SCB_GET_UART_TX_CTRL_ENABLED(GLCD_SPIM_SCB_UART_DIRECTION))

    #define GLCD_SPIM_SCB_UART_DEFAULT_TX_FIFO_CTRL \
                                GLCD_SPIM_SCB_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(GLCD_SPIM_SCB_UART_TX_TRIGGER_LEVEL)

    /* Interrupt sources */
    #define GLCD_SPIM_SCB_UART_INTERRUPT_DISABLE         (0u == GLCD_SPIM_SCB_UART_INTERRUPT_ENABLE)
    #define GLCD_SPIM_SCB_UART_DEFAULT_INTR_I2C_EC_MASK  (GLCD_SPIM_SCB_NO_INTR_SOURCES)
    #define GLCD_SPIM_SCB_UART_DEFAULT_INTR_SPI_EC_MASK  (GLCD_SPIM_SCB_NO_INTR_SOURCES)
    #define GLCD_SPIM_SCB_UART_DEFAULT_INTR_SLAVE_MASK   (GLCD_SPIM_SCB_NO_INTR_SOURCES)
    #define GLCD_SPIM_SCB_UART_DEFAULT_INTR_MASTER_MASK  (GLCD_SPIM_SCB_NO_INTR_SOURCES)
    #define GLCD_SPIM_SCB_UART_DEFAULT_INTR_RX_MASK      (GLCD_SPIM_SCB_UART_INTR_RX_MASK)
    #define GLCD_SPIM_SCB_UART_DEFAULT_INTR_TX_MASK      (GLCD_SPIM_SCB_UART_INTR_TX_MASK)

#endif /* (GLCD_SPIM_SCB_SCB_MODE_UART_CONST_CFG) */

#endif /* CY_SCB_SPI_UART_GLCD_SPIM_SCB_H */


/* [] END OF FILE */
