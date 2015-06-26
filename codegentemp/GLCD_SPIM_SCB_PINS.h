/*******************************************************************************
* File Name: GLCD_SPIM_SCB_PINS.h
* Version 1.0
*
* Description:
*  This file provides constants and parameter values for the pin components
*  buried into SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PINS_GLCD_SPIM_SCB_H)
#define CY_SCB_PINS_GLCD_SPIM_SCB_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define GLCD_SPIM_SCB_REMOVE_UART_RX_WAKE_PIN        (1u)
#define GLCD_SPIM_SCB_REMOVE_MOSI_SCL_RX_WAKE_PIN    (1u)
#define GLCD_SPIM_SCB_REMOVE_MOSI_SCL_RX_PIN         (1u)
#define GLCD_SPIM_SCB_REMOVE_MISO_SDA_TX_PIN         (1u)
#define GLCD_SPIM_SCB_REMOVE_SCLK_PIN                (1u)
#define GLCD_SPIM_SCB_REMOVE_SS0_PIN                 (1u)
#define GLCD_SPIM_SCB_REMOVE_SS1_PIN                 (1u)
#define GLCD_SPIM_SCB_REMOVE_SS2_PIN                 (1u)
#define GLCD_SPIM_SCB_REMOVE_SS3_PIN                 (1u)
#define GLCD_SPIM_SCB_REMOVE_I2C_PINS                (1u)
#define GLCD_SPIM_SCB_REMOVE_SPI_SLAVE_PINS          (1u)

#define GLCD_SPIM_SCB_UART_RX_WAKE_PIN       (0u == GLCD_SPIM_SCB_REMOVE_UART_RX_WAKE_PIN)
#define GLCD_SPIM_SCB_MOSI_SCL_RX_WAKE_PIN   (0u == GLCD_SPIM_SCB_REMOVE_MOSI_SCL_RX_WAKE_PIN)
#define GLCD_SPIM_SCB_MOSI_SCL_RX_PIN        (0u == GLCD_SPIM_SCB_REMOVE_MOSI_SCL_RX_PIN)
#define GLCD_SPIM_SCB_MISO_SDA_TX_PIN        (0u == GLCD_SPIM_SCB_REMOVE_MISO_SDA_TX_PIN)
#define GLCD_SPIM_SCB_SCLK_PIN               (0u == GLCD_SPIM_SCB_REMOVE_SCLK_PIN)
#define GLCD_SPIM_SCB_SS0_PIN                (0u == GLCD_SPIM_SCB_REMOVE_SS0_PIN)
#define GLCD_SPIM_SCB_SS1_PIN                (0u == GLCD_SPIM_SCB_REMOVE_SS1_PIN)
#define GLCD_SPIM_SCB_SS2_PIN                (0u == GLCD_SPIM_SCB_REMOVE_SS2_PIN)
#define GLCD_SPIM_SCB_SS3_PIN                (0u == GLCD_SPIM_SCB_REMOVE_SS3_PIN)
#define GLCD_SPIM_SCB_I2C_PINS               (0u == GLCD_SPIM_SCB_REMOVE_I2C_PINS)
#define GLCD_SPIM_SCB_SPI_SLAVE_PINS         (0u == GLCD_SPIM_SCB_REMOVE_SPI_SLAVE_PINS)


/***************************************
*             Includes
****************************************/

#if(GLCD_SPIM_SCB_UART_RX_WAKE_PIN)
    #include "GLCD_SPIM_SCB_rx_wake.h"
#endif /* (GLCD_SPIM_SCB_UART_RX_WAKE_PIN) */

#if(GLCD_SPIM_SCB_MOSI_SCL_RX_WAKE_PIN)
    #include "GLCD_SPIM_SCB_spi_mosi_i2c_scl_uart_rx_wake.h"
#endif /* (GLCD_SPIM_SCB_MOSI_SCL_RX_WAKE_PIN) */

#if(GLCD_SPIM_SCB_MOSI_SCL_RX_PIN)
    #include "GLCD_SPIM_SCB_spi_mosi_i2c_scl_uart_rx.h"
#endif /* (GLCD_SPIM_SCB_MOSI_SCL_RX_PIN) */

#if(GLCD_SPIM_SCB_MISO_SDA_TX_PIN)
    #include "GLCD_SPIM_SCB_spi_miso_i2c_sda_uart_tx.h"
#endif /* (GLCD_SPIM_SCB_MISO_SDA_TX_PIN_PIN) */

#if(GLCD_SPIM_SCB_SCLK_PIN)
    #include "GLCD_SPIM_SCB_spi_sclk.h"
#endif /* (GLCD_SPIM_SCB_SCLK_PIN) */

#if(GLCD_SPIM_SCB_SS0_PIN)
    #include "GLCD_SPIM_SCB_spi_ss0.h"
#endif /* (GLCD_SPIM_SCB_SS1_PIN) */

#if(GLCD_SPIM_SCB_SS1_PIN)
    #include "GLCD_SPIM_SCB_spi_ss1.h"
#endif /* (GLCD_SPIM_SCB_SS1_PIN) */

#if(GLCD_SPIM_SCB_SS2_PIN)
    #include "GLCD_SPIM_SCB_spi_ss2.h"
#endif /* (GLCD_SPIM_SCB_SS2_PIN) */

#if(GLCD_SPIM_SCB_SS3_PIN)
    #include "GLCD_SPIM_SCB_spi_ss3.h"
#endif /* (GLCD_SPIM_SCB_SS3_PIN) */

#if(GLCD_SPIM_SCB_I2C_PINS)
    #include "GLCD_SPIM_SCB_scl.h"
    #include "GLCD_SPIM_SCB_sda.h"
#endif /* (GLCD_SPIM_SCB_I2C_PINS) */


/***************************************
*              Registers
***************************************/

#if(GLCD_SPIM_SCB_MOSI_SCL_RX_WAKE_PIN)
    #define GLCD_SPIM_SCB_MOSI_SCL_RX_WAKE_HSIOM_REG  \
                                                (*(reg32 *) GLCD_SPIM_SCB_spi_mosi_i2c_scl_uart_rx_wake__0__HSIOM)
    #define GLCD_SPIM_SCB_MOSI_SCL_RX_WAKE_HSIOM_PTR  \
                                                ( (reg32 *) GLCD_SPIM_SCB_spi_mosi_i2c_scl_uart_rx_wake__0__HSIOM)
    #define GLCD_SPIM_SCB_MOSI_SCL_RX_WAKE_HSIOM_MASK \
                                                (GLCD_SPIM_SCB_spi_mosi_i2c_scl_uart_rx_wake__0__HSIOM_MASK)
    #define GLCD_SPIM_SCB_MOSI_SCL_RX_WAKE_HSIOM_POS  \
                                                (GLCD_SPIM_SCB_spi_mosi_i2c_scl_uart_rx_wake__0__HSIOM_SHIFT)

    #define GLCD_SPIM_SCB_MOSI_SCL_RX_WAKE_INTCFG_REG    (*(reg32 *) \
                                                              GLCD_SPIM_SCB_spi_mosi_i2c_scl_uart_rx_wake__0__INTCFG)
    #define GLCD_SPIM_SCB_MOSI_SCL_RX_WAKE_INTCFG_PTR    ( (reg32 *) \
                                                              GLCD_SPIM_SCB_spi_mosi_i2c_scl_uart_rx_wake__0__INTCFG)

    #define GLCD_SPIM_SCB_INTCFG_TYPE_MASK                  (0x03u)
    #define GLCD_SPIM_SCB_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS  (GLCD_SPIM_SCB_spi_mosi_i2c_scl_uart_rx_wake__SHIFT)
    #define GLCD_SPIM_SCB_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK ((uint32)                                           \
                                                                    ((uint32) GLCD_SPIM_SCB_INTCFG_TYPE_MASK << \
                                                                    GLCD_SPIM_SCB_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS))
#endif /* (GLCD_SPIM_SCB_MOSI_SCL_RX_WAKE_PIN) */

#if(GLCD_SPIM_SCB_MOSI_SCL_RX_PIN)
    #define GLCD_SPIM_SCB_MOSI_SCL_RX_HSIOM_REG      (*(reg32 *) GLCD_SPIM_SCB_spi_mosi_i2c_scl_uart_rx__0__HSIOM)
    #define GLCD_SPIM_SCB_MOSI_SCL_RX_HSIOM_PTR      ( (reg32 *) GLCD_SPIM_SCB_spi_mosi_i2c_scl_uart_rx__0__HSIOM)
    #define GLCD_SPIM_SCB_MOSI_SCL_RX_HSIOM_MASK     (GLCD_SPIM_SCB_spi_mosi_i2c_scl_uart_rx__0__HSIOM_MASK)
    #define GLCD_SPIM_SCB_MOSI_SCL_RX_HSIOM_POS      (GLCD_SPIM_SCB_spi_mosi_i2c_scl_uart_rx__0__HSIOM_SHIFT)
#endif /* (GLCD_SPIM_SCB_MOSI_SCL_RX_PIN) */

#if(GLCD_SPIM_SCB_MISO_SDA_TX_PIN)
    #define GLCD_SPIM_SCB_MISO_SDA_TX_HSIOM_REG      (*(reg32 *) GLCD_SPIM_SCB_spi_miso_i2c_sda_uart_tx__0__HSIOM)
    #define GLCD_SPIM_SCB_MISO_SDA_TX_HSIOM_PTR      ( (reg32 *) GLCD_SPIM_SCB_spi_miso_i2c_sda_uart_tx__0__HSIOM)
    #define GLCD_SPIM_SCB_MISO_SDA_TX_HSIOM_MASK     (GLCD_SPIM_SCB_spi_miso_i2c_sda_uart_tx__0__HSIOM_MASK)
    #define GLCD_SPIM_SCB_MISO_SDA_TX_HSIOM_POS      (GLCD_SPIM_SCB_spi_miso_i2c_sda_uart_tx__0__HSIOM_SHIFT)
#endif /* (GLCD_SPIM_SCB_MISO_SDA_TX_PIN_PIN) */

#if(GLCD_SPIM_SCB_SCLK_PIN)
    #define GLCD_SPIM_SCB_SCLK_HSIOM_REG     (*(reg32 *) GLCD_SPIM_SCB_spi_sclk__0__HSIOM)
    #define GLCD_SPIM_SCB_SCLK_HSIOM_PTR     ( (reg32 *) GLCD_SPIM_SCB_spi_sclk__0__HSIOM)
    #define GLCD_SPIM_SCB_SCLK_HSIOM_MASK    (GLCD_SPIM_SCB_spi_sclk__0__HSIOM_MASK)
    #define GLCD_SPIM_SCB_SCLK_HSIOM_POS     (GLCD_SPIM_SCB_spi_sclk__0__HSIOM_SHIFT)
#endif /* (GLCD_SPIM_SCB_SCLK_PIN) */

#if(GLCD_SPIM_SCB_SS0_PIN)
    #define GLCD_SPIM_SCB_SS0_HSIOM_REG      (*(reg32 *) GLCD_SPIM_SCB_spi_ss0__0__HSIOM)
    #define GLCD_SPIM_SCB_SS0_HSIOM_PTR      ( (reg32 *) GLCD_SPIM_SCB_spi_ss0__0__HSIOM)
    #define GLCD_SPIM_SCB_SS0_HSIOM_MASK     (GLCD_SPIM_SCB_spi_ss0__0__HSIOM_MASK)
    #define GLCD_SPIM_SCB_SS0_HSIOM_POS      (GLCD_SPIM_SCB_spi_ss0__0__HSIOM_SHIFT)
#endif /* (GLCD_SPIM_SCB_SS1_PIN) */

#if(GLCD_SPIM_SCB_SS1_PIN)
    #define GLCD_SPIM_SCB_SS1_HSIOM_REG      (*(reg32 *) GLCD_SPIM_SCB_spi_ss1__0__HSIOM)
    #define GLCD_SPIM_SCB_SS1_HSIOM_PTR      ( (reg32 *) GLCD_SPIM_SCB_spi_ss1__0__HSIOM)
    #define GLCD_SPIM_SCB_SS1_HSIOM_MASK     (GLCD_SPIM_SCB_spi_ss1__0__HSIOM_MASK)
    #define GLCD_SPIM_SCB_SS1_HSIOM_POS      (GLCD_SPIM_SCB_spi_ss1__0__HSIOM_SHIFT)
#endif /* (GLCD_SPIM_SCB_SS1_PIN) */

#if(GLCD_SPIM_SCB_SS2_PIN)
    #define GLCD_SPIM_SCB_SS2_HSIOM_REG     (*(reg32 *) GLCD_SPIM_SCB_spi_ss2__0__HSIOM)
    #define GLCD_SPIM_SCB_SS2_HSIOM_PTR     ( (reg32 *) GLCD_SPIM_SCB_spi_ss2__0__HSIOM)
    #define GLCD_SPIM_SCB_SS2_HSIOM_MASK    (GLCD_SPIM_SCB_spi_ss2__0__HSIOM_MASK)
    #define GLCD_SPIM_SCB_SS2_HSIOM_POS     (GLCD_SPIM_SCB_spi_ss2__0__HSIOM_SHIFT)
#endif /* (GLCD_SPIM_SCB_SS2_PIN) */

#if(GLCD_SPIM_SCB_SS3_PIN)
    #define GLCD_SPIM_SCB_SS3_HSIOM_REG     (*(reg32 *) GLCD_SPIM_SCB_spi_ss3__0__HSIOM)
    #define GLCD_SPIM_SCB_SS3_HSIOM_PTR     ( (reg32 *) GLCD_SPIM_SCB_spi_ss3__0__HSIOM)
    #define GLCD_SPIM_SCB_SS3_HSIOM_MASK    (GLCD_SPIM_SCB_spi_ss3__0__HSIOM_MASK)
    #define GLCD_SPIM_SCB_SS3_HSIOM_POS     (GLCD_SPIM_SCB_spi_ss3__0__HSIOM_SHIFT)
#endif /* (GLCD_SPIM_SCB_SS3_PIN) */

#if(GLCD_SPIM_SCB_I2C_PINS)
    #define GLCD_SPIM_SCB_SCL_HSIOM_REG     (*(reg32 *) GLCD_SPIM_SCB_scl__0__HSIOM)
    #define GLCD_SPIM_SCB_SCL_HSIOM_PTR     ( (reg32 *) GLCD_SPIM_SCB_scl__0__HSIOM)
    #define GLCD_SPIM_SCB_SCL_HSIOM_MASK    (GLCD_SPIM_SCB_scl__0__HSIOM_MASK)
    #define GLCD_SPIM_SCB_SCL_HSIOM_POS     (GLCD_SPIM_SCB_scl__0__HSIOM_SHIFT)
    
    #define GLCD_SPIM_SCB_SDA_HSIOM_REG     (*(reg32 *) GLCD_SPIM_SCB_sda__0__HSIOM)
    #define GLCD_SPIM_SCB_SDA_HSIOM_PTR     ( (reg32 *) GLCD_SPIM_SCB_sda__0__HSIOM)
    #define GLCD_SPIM_SCB_SDA_HSIOM_MASK    (GLCD_SPIM_SCB_sda__0__HSIOM_MASK)
    #define GLCD_SPIM_SCB_SDA_HSIOM_POS     (GLCD_SPIM_SCB_sda__0__HSIOM_SHIFT)
#endif /* (GLCD_SPIM_SCB_I2C_PINS) */


/***************************************
*        Registers Constants
***************************************/

/* Pins constanst */
#define GLCD_SPIM_SCB_HSIOM_DEF_SEL      (0x00u)
#define GLCD_SPIM_SCB_HSIOM_GPIO_SEL     (0x00u)
#define GLCD_SPIM_SCB_HSIOM_UART_SEL     (0x09u)
#define GLCD_SPIM_SCB_HSIOM_I2C_SEL      (0x0Eu)
#define GLCD_SPIM_SCB_HSIOM_SPI_SEL      (0x0Fu)

#define GLCD_SPIM_SCB_SCB_PINS_NUMBER            (7u)
#define GLCD_SPIM_SCB_MOSI_SCL_RX_PIN_INDEX      (0u) /* RX pins without interrupt */
#define GLCD_SPIM_SCB_MOSI_SCL_RX_WAKE_PIN_INDEX (0u) /* RX pin with interrupt     */
#define GLCD_SPIM_SCB_MISO_SDA_TX_PIN_INDEX      (1u)
#define GLCD_SPIM_SCB_SCLK_PIN_INDEX             (2u)
#define GLCD_SPIM_SCB_SS0_PIN_INDEX              (3u)
#define GLCD_SPIM_SCB_SS1_PIN_INDEX              (4u)
#define GLCD_SPIM_SCB_SS2_PIN_INDEX              (5u)
#define GLCD_SPIM_SCB_SS3_PIN_INDEX              (6u)

#define GLCD_SPIM_SCB_INTCFG_TYPE_FALLING_EDGE   (0x02u)

/* Pin DM defines */
#define GLCD_SPIM_SCB_PIN_DM_ALG_HIZ  (0u)
#define GLCD_SPIM_SCB_PIN_DM_DIG_HIZ  (1u)
#define GLCD_SPIM_SCB_PIN_DM_OD_LO    (4u)
#define GLCD_SPIM_SCB_PIN_DM_STRONG   (6u)


/***************************************
*          Macro Definitions
***************************************/

#define GLCD_SPIM_SCB_SET_REGISTER_BITS(reg, mask, pos, mode) \
                    do                                           \
                    {                                            \
                        /* Sets new bits-mask */                 \
                        (reg) = (((reg) & ((uint32) ~(uint32) (mask))) | ((uint32) ((uint32) (mode) << (pos)))); \
                    }while(0)

#define GLCD_SPIM_SCB_SET_HSIOM_SEL(reg, mask, pos, sel) GLCD_SPIM_SCB_SET_REGISTER_BITS(reg, mask, pos, sel)
#define GLCD_SPIM_SCB_SET_INCFG_TYPE(reg, mask, pos, intType) \
                                                        GLCD_SPIM_SCB_SET_REGISTER_BITS(reg, mask, pos, intType)


/* GLCD_SPIM_SCB_SET_I2C_SCL_DR(val) - Sets I2C SCL DR register.
*  GLCD_SPIM_SCB_SET_I2C_SCL_HSIOM_SEL(sel) - Sets I2C SCL HSIOM settings.
*/
/* Unconfigured SCB: scl singnal */
#if(GLCD_SPIM_SCB_MOSI_SCL_RX_WAKE_PIN)
    #define GLCD_SPIM_SCB_SET_I2C_SCL_DR(val) \
                            GLCD_SPIM_SCB_spi_mosi_i2c_scl_uart_rx_wake_Write(val)

    #define GLCD_SPIM_SCB_SET_I2C_SCL_HSIOM_SEL(sel) \
                    GLCD_SPIM_SCB_SET_HSIOM_SEL(GLCD_SPIM_SCB_MOSI_SCL_RX_WAKE_HSIOM_REG,  \
                                                   GLCD_SPIM_SCB_MOSI_SCL_RX_WAKE_HSIOM_MASK, \
                                                   GLCD_SPIM_SCB_MOSI_SCL_RX_WAKE_HSIOM_POS,  \
                                                   (sel))

#elif(GLCD_SPIM_SCB_MOSI_SCL_RX_PIN)
    #define GLCD_SPIM_SCB_SET_I2C_SCL_DR(val) \
                            GLCD_SPIM_SCB_spi_mosi_i2c_scl_uart_rx_Write(val)
                            

    #define GLCD_SPIM_SCB_SET_I2C_SCL_HSIOM_SEL(sel) \
                            GLCD_SPIM_SCB_SET_HSIOM_SEL(GLCD_SPIM_SCB_MOSI_SCL_RX_HSIOM_REG,  \
                                                           GLCD_SPIM_SCB_MOSI_SCL_RX_HSIOM_MASK, \
                                                           GLCD_SPIM_SCB_MOSI_SCL_RX_HSIOM_POS,  \
                                                           (sel))
#else
    #if(!GLCD_SPIM_SCB_I2C_PINS)
        #define GLCD_SPIM_SCB_SET_I2C_SCL_DR(val) \
                                                 do{ ; }while(0)
        #define GLCD_SPIM_SCB_SET_I2C_SCL_HSIOM_SEL(sel) \
                                                        do{ ; }while(0)
        
    #endif /* (!GLCD_SPIM_SCB_I2C_PINS) */
#endif /* (GLCD_SPIM_SCB_MOSI_SCL_RX_PIN) */

/* SCB I2C: scl singal */
#if(GLCD_SPIM_SCB_I2C_PINS)
    #define GLCD_SPIM_SCB_SET_I2C_SCL_DR(val) GLCD_SPIM_SCB_scl_Write(val)
    
    #define GLCD_SPIM_SCB_SET_I2C_SCL_HSIOM_SEL(sel) \
                          GLCD_SPIM_SCB_SET_HSIOM_SEL(GLCD_SPIM_SCB_SCL_HSIOM_REG,  \
                                                         GLCD_SPIM_SCB_SCL_HSIOM_MASK, \
                                                         GLCD_SPIM_SCB_SCL_HSIOM_POS,  \
                                                         (sel))
    
#endif /* (GLCD_SPIM_SCB_I2C_PINS) */


#endif /* (CY_SCB_PINS_GLCD_SPIM_SCB_H) */


/* [] END OF FILE */
