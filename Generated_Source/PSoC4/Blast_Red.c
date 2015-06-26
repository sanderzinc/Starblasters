/*******************************************************************************
* File Name: Blast_Red.c  
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
#include "Blast_Red.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        Blast_Red_PC =   (Blast_Red_PC & \
                                (uint32)(~(uint32)(Blast_Red_DRIVE_MODE_IND_MASK << (Blast_Red_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (Blast_Red_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: Blast_Red_Write
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
void Blast_Red_Write(uint8 value) 
{
    uint8 drVal = (uint8)(Blast_Red_DR & (uint8)(~Blast_Red_MASK));
    drVal = (drVal | ((uint8)(value << Blast_Red_SHIFT) & Blast_Red_MASK));
    Blast_Red_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: Blast_Red_SetDriveMode
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
void Blast_Red_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(Blast_Red__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: Blast_Red_Read
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
*  Macro Blast_Red_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Blast_Red_Read(void) 
{
    return (uint8)((Blast_Red_PS & Blast_Red_MASK) >> Blast_Red_SHIFT);
}


/*******************************************************************************
* Function Name: Blast_Red_ReadDataReg
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
uint8 Blast_Red_ReadDataReg(void) 
{
    return (uint8)((Blast_Red_DR & Blast_Red_MASK) >> Blast_Red_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Blast_Red_INTSTAT) 

    /*******************************************************************************
    * Function Name: Blast_Red_ClearInterrupt
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
    uint8 Blast_Red_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(Blast_Red_INTSTAT & Blast_Red_MASK);
		Blast_Red_INTSTAT = maskedStatus;
        return maskedStatus >> Blast_Red_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
