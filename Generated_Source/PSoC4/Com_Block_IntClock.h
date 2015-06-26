/*******************************************************************************
* File Name: Com_Block_IntClock.h
* Version 2.10
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_Com_Block_IntClock_H)
#define CY_CLOCK_Com_Block_IntClock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/

void Com_Block_IntClock_Start(void);
void Com_Block_IntClock_Stop(void);

void Com_Block_IntClock_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 Com_Block_IntClock_GetDividerRegister(void);
uint8  Com_Block_IntClock_GetFractionalDividerRegister(void);

#define Com_Block_IntClock_Enable()                         Com_Block_IntClock_Start()
#define Com_Block_IntClock_Disable()                        Com_Block_IntClock_Stop()
#define Com_Block_IntClock_SetDividerRegister(clkDivider, reset)  \
                        Com_Block_IntClock_SetFractionalDividerRegister((clkDivider), 0u)
#define Com_Block_IntClock_SetDivider(clkDivider)           Com_Block_IntClock_SetDividerRegister((clkDivider), 1u)
#define Com_Block_IntClock_SetDividerValue(clkDivider)      Com_Block_IntClock_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/

#define Com_Block_IntClock_DIV_REG    (*(reg32 *)Com_Block_IntClock__REGISTER)
#define Com_Block_IntClock_ENABLE_REG Com_Block_IntClock_DIV_REG

#endif /* !defined(CY_CLOCK_Com_Block_IntClock_H) */

/* [] END OF FILE */
