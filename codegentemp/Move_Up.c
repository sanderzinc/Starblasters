/*******************************************************************************
* File Name: Move_Up.c  
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
#include "Move_Up.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        Move_Up_PC =   (Move_Up_PC & \
                                (uint32)(~(uint32)(Move_Up_DRIVE_MODE_IND_MASK << (Move_Up_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (Move_Up_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: Move_Up_Write
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
void Move_Up_Write(uint8 value) 
{
    uint8 drVal = (uint8)(Move_Up_DR & (uint8)(~Move_Up_MASK));
    drVal = (drVal | ((uint8)(value << Move_Up_SHIFT) & Move_Up_MASK));
    Move_Up_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: Move_Up_SetDriveMode
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
void Move_Up_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(Move_Up__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: Move_Up_Read
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
*  Macro Move_Up_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Move_Up_Read(void) 
{
    return (uint8)((Move_Up_PS & Move_Up_MASK) >> Move_Up_SHIFT);
}


/*******************************************************************************
* Function Name: Move_Up_ReadDataReg
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
uint8 Move_Up_ReadDataReg(void) 
{
    return (uint8)((Move_Up_DR & Move_Up_MASK) >> Move_Up_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Move_Up_INTSTAT) 

    /*******************************************************************************
    * Function Name: Move_Up_ClearInterrupt
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
    uint8 Move_Up_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(Move_Up_INTSTAT & Move_Up_MASK);
		Move_Up_INTSTAT = maskedStatus;
        return maskedStatus >> Move_Up_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
