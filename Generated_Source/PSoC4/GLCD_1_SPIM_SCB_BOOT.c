/*******************************************************************************
* File Name: GLCD_1_SPIM_SCB_BOOT.c
* Version 1.0
*
* Description:
*  This file provides the source code to the API for the bootloader
*  communication support in SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "GLCD_1_SPIM_SCB.h"

#if(GLCD_1_SPIM_SCB_SCB_MODE_I2C_INC)
    #include "GLCD_1_SPIM_SCB_I2C.h"
#endif /* (GLCD_1_SPIM_SCB_SCB_MODE_I2C_INC) */

#if(GLCD_1_SPIM_SCB_SCB_MODE_SPI_INC || GLCD_1_SPIM_SCB_SCB_MODE_UART_INC)
    #include "GLCD_1_SPIM_SCB_SPI_UART.h"
#endif /* (GLCD_1_SPIM_SCB_SCB_MODE_SPI_INC || GLCD_1_SPIM_SCB_SCB_MODE_UART_INC) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_GLCD_1_SPIM_SCB) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/*******************************************************************************
* Function Name: GLCD_1_SPIM_SCB_CyBtldrCommStart
********************************************************************************
*
* Summary:
*  Calls Start function fucntion of the bootloader communication component for
*  selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void GLCD_1_SPIM_SCB_CyBtldrCommStart(void)
{
    #if(GLCD_1_SPIM_SCB_SCB_MODE_UNCONFIG_CONST_CFG)
        if(GLCD_1_SPIM_SCB_SCB_MODE_I2C_RUNTM_CFG)
        {
            GLCD_1_SPIM_SCB_I2CCyBtldrCommStart();
        }
        else if(GLCD_1_SPIM_SCB_SCB_MODE_SPI_RUNTM_CFG)
        {
            GLCD_1_SPIM_SCB_SpiCyBtldrCommStart();
        }
        else if(GLCD_1_SPIM_SCB_SCB_MODE_UART_RUNTM_CFG)
        {
            GLCD_1_SPIM_SCB_UartCyBtldrCommStart();
        }
        else
        {
            /* Unknown mode: do nothing */
        }
    #elif(GLCD_1_SPIM_SCB_SCB_MODE_I2C_CONST_CFG)
        GLCD_1_SPIM_SCB_I2CCyBtldrCommStart();

    #elif(GLCD_1_SPIM_SCB_SCB_MODE_SPI_CONST_CFG)
        GLCD_1_SPIM_SCB_SpiCyBtldrCommStart();

    #elif(GLCD_1_SPIM_SCB_SCB_MODE_UART_CONST_CFG)
        GLCD_1_SPIM_SCB_UartCyBtldrCommStart();

    #else
        /* Do nothing */

    #endif /* (GLCD_1_SPIM_SCB_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: GLCD_1_SPIM_SCB_CyBtldrCommStop
********************************************************************************
*
* Summary:
*  Calls Stop function fucntion of the bootloader communication component for
*  selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void GLCD_1_SPIM_SCB_CyBtldrCommStop(void)
{
    #if(GLCD_1_SPIM_SCB_SCB_MODE_UNCONFIG_CONST_CFG)
        if(GLCD_1_SPIM_SCB_SCB_MODE_I2C_RUNTM_CFG)
        {
            GLCD_1_SPIM_SCB_I2CCyBtldrCommStop();
        }
        else if(GLCD_1_SPIM_SCB_SCB_MODE_SPI_RUNTM_CFG)
        {
            GLCD_1_SPIM_SCB_SpiCyBtldrCommStop();
        }
        else if(GLCD_1_SPIM_SCB_SCB_MODE_UART_RUNTM_CFG)
        {
            GLCD_1_SPIM_SCB_UartCyBtldrCommStop();
        }
        else
        {
            /* Unknown mode: do nothing */
        }
    #elif(GLCD_1_SPIM_SCB_SCB_MODE_I2C_CONST_CFG)
        GLCD_1_SPIM_SCB_I2CCyBtldrCommStop();

    #elif(GLCD_1_SPIM_SCB_SCB_MODE_SPI_CONST_CFG)
        GLCD_1_SPIM_SCB_SpiCyBtldrCommStop();

    #elif(GLCD_1_SPIM_SCB_SCB_MODE_UART_CONST_CFG)
        GLCD_1_SPIM_SCB_UartCyBtldrCommStop();

    #else
        /* Do nothing */

    #endif /* (GLCD_1_SPIM_SCB_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: GLCD_1_SPIM_SCB_CyBtldrCommReset
********************************************************************************
*
* Summary:
*  Calls reset function fucntion of the bootloader communication component for
*  selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void GLCD_1_SPIM_SCB_CyBtldrCommReset(void)
{
    #if(GLCD_1_SPIM_SCB_SCB_MODE_UNCONFIG_CONST_CFG)
        if(GLCD_1_SPIM_SCB_SCB_MODE_I2C_RUNTM_CFG)
        {
            GLCD_1_SPIM_SCB_I2CCyBtldrCommReset();
        }
        else if(GLCD_1_SPIM_SCB_SCB_MODE_SPI_RUNTM_CFG)
        {
            GLCD_1_SPIM_SCB_SpiCyBtldrCommReset();
        }
        else if(GLCD_1_SPIM_SCB_SCB_MODE_UART_RUNTM_CFG)
        {
            GLCD_1_SPIM_SCB_UartCyBtldrCommReset();
        }
        else
        {
            /* Unknown mode: do nothing */
        }
    #elif(GLCD_1_SPIM_SCB_SCB_MODE_I2C_CONST_CFG)
        GLCD_1_SPIM_SCB_I2CCyBtldrCommReset();

    #elif(GLCD_1_SPIM_SCB_SCB_MODE_SPI_CONST_CFG)
        GLCD_1_SPIM_SCB_SpiCyBtldrCommReset();

    #elif(GLCD_1_SPIM_SCB_SCB_MODE_UART_CONST_CFG)
        GLCD_1_SPIM_SCB_UartCyBtldrCommReset();

    #else
        /* Do nothing */

    #endif /* (GLCD_1_SPIM_SCB_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: GLCD_1_SPIM_SCB_CyBtldrCommRead
********************************************************************************
*
* Summary:
*  Calls read fucntion of the bootloader communication component for selected
*  mode.
*
* Parameters:
*  pData:    Pointer to storage for the block of data to be read from the
*            bootloader host
*  size:     Number of bytes to be read.
*  count:    Pointer to the variable to write the number of bytes actually
*            read.
*  timeOut:  Number of units in 10 ms to wait before returning because of a
*            timeout.
*
* Return:
*  Returns CYRET_SUCCESS if no problem was encountered or returns the value
*  that best describes the problem.
*
*******************************************************************************/
cystatus GLCD_1_SPIM_SCB_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    #if(GLCD_1_SPIM_SCB_SCB_MODE_UNCONFIG_CONST_CFG)
        if(GLCD_1_SPIM_SCB_SCB_MODE_I2C_RUNTM_CFG)
        {
            status = GLCD_1_SPIM_SCB_I2CCyBtldrCommRead(pData, size, count, timeOut);
        }
        else if(GLCD_1_SPIM_SCB_SCB_MODE_SPI_RUNTM_CFG)
        {
            status = GLCD_1_SPIM_SCB_SpiCyBtldrCommRead(pData, size, count, timeOut);
        }
        else if(GLCD_1_SPIM_SCB_SCB_MODE_UART_RUNTM_CFG)
        {
            status = GLCD_1_SPIM_SCB_UartCyBtldrCommRead(pData, size, count, timeOut);
        }
        else
        {
            status = CYRET_INVALID_STATE; /* Unknown mode: return status */
        }

    #elif(GLCD_1_SPIM_SCB_SCB_MODE_I2C_CONST_CFG)
        status = GLCD_1_SPIM_SCB_I2CCyBtldrCommRead(pData, size, count, timeOut);

    #elif(GLCD_1_SPIM_SCB_SCB_MODE_SPI_CONST_CFG)
        status = GLCD_1_SPIM_SCB_SpiCyBtldrCommRead(pData, size, count, timeOut);

    #elif(GLCD_1_SPIM_SCB_SCB_MODE_UART_CONST_CFG)
        status = GLCD_1_SPIM_SCB_UartCyBtldrCommRead(pData, size, count, timeOut);

    #else
        status = CYRET_INVALID_STATE; /* Unknown mode: return status */

    #endif /* (GLCD_1_SPIM_SCB_SCB_MODE_UNCONFIG_CONST_CFG) */

    return(status);
}


/*******************************************************************************
* Function Name: GLCD_1_SPIM_SCB_CyBtldrCommWrite
********************************************************************************
*
* Summary:
*  Calls write fucntion of the bootloader communication component for selected
*  mode.
*
* Parameters:
*  pData:    Pointer to the block of data to be written to the bootloader host.
*  size:     Number of bytes to be written.
*  count:    Pointer to the variable to write the number of bytes actually
*            written.
*  timeOut:  Number of units in 10 ms to wait before returning because of a
*            timeout.
*
* Return:
*  Returns CYRET_SUCCESS if no problem was encountered or returns the value
*  that best describes the problem.
*
*******************************************************************************/
cystatus GLCD_1_SPIM_SCB_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    #if(GLCD_1_SPIM_SCB_SCB_MODE_UNCONFIG_CONST_CFG)
        if(GLCD_1_SPIM_SCB_SCB_MODE_I2C_RUNTM_CFG)
        {
            status = GLCD_1_SPIM_SCB_I2CCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else if(GLCD_1_SPIM_SCB_SCB_MODE_SPI_RUNTM_CFG)
        {
            status = GLCD_1_SPIM_SCB_SpiCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else if(GLCD_1_SPIM_SCB_SCB_MODE_UART_RUNTM_CFG)
        {
            status = GLCD_1_SPIM_SCB_UartCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else
        {
            status = CYRET_INVALID_STATE; /* Unknown mode: return status */
        }
    #elif(GLCD_1_SPIM_SCB_SCB_MODE_I2C_CONST_CFG)
        status = GLCD_1_SPIM_SCB_I2CCyBtldrCommWrite(pData, size, count, timeOut);

    #elif(GLCD_1_SPIM_SCB_SCB_MODE_SPI_CONST_CFG)
        status = GLCD_1_SPIM_SCB_SpiCyBtldrCommWrite(pData, size, count, timeOut);

    #elif(GLCD_1_SPIM_SCB_SCB_MODE_UART_CONST_CFG)
        status = GLCD_1_SPIM_SCB_UartCyBtldrCommWrite(pData, size, count, timeOut);

    #else
        status = CYRET_INVALID_STATE; /* Unknown mode: return status */

    #endif /* (GLCD_1_SPIM_SCB_SCB_MODE_UNCONFIG_CONST_CFG) */

    return(status);
}

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_GLCD_1_SPIM_SCB) || \
                                                    (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface)) */


/* [] END OF FILE */
