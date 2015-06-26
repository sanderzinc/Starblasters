/*******************************************************************************
* File Name: Menu_Up.c  
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
#include "Menu_Up.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        Menu_Up_PC =   (Menu_Up_PC & \
                                (uint32)(~(uint32)(Menu_Up_DRIVE_MODE_IND_MASK << (Menu_Up_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (Menu_Up_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: Menu_Up_Write
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
void Menu_Up_Write(uint8 value) 
{
    uint8 drVal = (uint8)(Menu_Up_DR & (uint8)(~Menu_Up_MASK));
    drVal = (drVal | ((uint8)(value << Menu_Up_SHIFT) & Menu_Up_MASK));
    Menu_Up_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: Menu_Up_SetDriveMode
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
void Menu_Up_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(Menu_Up__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: Menu_Up_Read
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
*  Macro Menu_Up_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Menu_Up_Read(void) 
{
    return (uint8)((Menu_Up_PS & Menu_Up_MASK) >> Menu_Up_SHIFT);
}


/*******************************************************************************
* Function Name: Menu_Up_ReadDataReg
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
uint8 Menu_Up_ReadDataReg(void) 
{
    return (uint8)((Menu_Up_DR & Menu_Up_MASK) >> Menu_Up_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Menu_Up_INTSTAT) 

    /*******************************************************************************
    * Function Name: Menu_Up_ClearInterrupt
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
    uint8 Menu_Up_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(Menu_Up_INTSTAT & Menu_Up_MASK);
		Menu_Up_INTSTAT = maskedStatus;
        return maskedStatus >> Menu_Up_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
