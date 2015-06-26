/*******************************************************************************
* File Name: GLCD_SS.c  
* Version 1.90
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "GLCD_SS.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        GLCD_SS_PC =   (GLCD_SS_PC & \
                                (uint32)(~(uint32)(GLCD_SS_DRIVE_MODE_IND_MASK << (GLCD_SS_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (GLCD_SS_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: GLCD_SS_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None 
*  
*******************************************************************************/
void GLCD_SS_Write(uint8 value) 
{
    uint8 drVal = (uint8)(GLCD_SS_DR & (uint8)(~GLCD_SS_MASK));
    drVal = (drVal | ((uint8)(value << GLCD_SS_SHIFT) & GLCD_SS_MASK));
    GLCD_SS_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: GLCD_SS_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to this drive mode.
*
* Return: 
*  None
*
*******************************************************************************/
void GLCD_SS_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(GLCD_SS__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: GLCD_SS_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro GLCD_SS_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 GLCD_SS_Read(void) 
{
    return (uint8)((GLCD_SS_PS & GLCD_SS_MASK) >> GLCD_SS_SHIFT);
}


/*******************************************************************************
* Function Name: GLCD_SS_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 GLCD_SS_ReadDataReg(void) 
{
    return (uint8)((GLCD_SS_DR & GLCD_SS_MASK) >> GLCD_SS_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(GLCD_SS_INTSTAT) 

    /*******************************************************************************
    * Function Name: GLCD_SS_ClearInterrupt
    ********************************************************************************
    *
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 GLCD_SS_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(GLCD_SS_INTSTAT & GLCD_SS_MASK);
		GLCD_SS_INTSTAT = maskedStatus;
        return maskedStatus >> GLCD_SS_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
