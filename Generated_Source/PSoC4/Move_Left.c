/*******************************************************************************
* File Name: Move_Left.c  
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
#include "Move_Left.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        Move_Left_PC =   (Move_Left_PC & \
                                (uint32)(~(uint32)(Move_Left_DRIVE_MODE_IND_MASK << (Move_Left_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (Move_Left_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: Move_Left_Write
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
void Move_Left_Write(uint8 value) 
{
    uint8 drVal = (uint8)(Move_Left_DR & (uint8)(~Move_Left_MASK));
    drVal = (drVal | ((uint8)(value << Move_Left_SHIFT) & Move_Left_MASK));
    Move_Left_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: Move_Left_SetDriveMode
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
void Move_Left_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(Move_Left__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: Move_Left_Read
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
*  Macro Move_Left_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Move_Left_Read(void) 
{
    return (uint8)((Move_Left_PS & Move_Left_MASK) >> Move_Left_SHIFT);
}


/*******************************************************************************
* Function Name: Move_Left_ReadDataReg
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
uint8 Move_Left_ReadDataReg(void) 
{
    return (uint8)((Move_Left_DR & Move_Left_MASK) >> Move_Left_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Move_Left_INTSTAT) 

    /*******************************************************************************
    * Function Name: Move_Left_ClearInterrupt
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
    uint8 Move_Left_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(Move_Left_INTSTAT & Move_Left_MASK);
		Move_Left_INTSTAT = maskedStatus;
        return maskedStatus >> Move_Left_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
