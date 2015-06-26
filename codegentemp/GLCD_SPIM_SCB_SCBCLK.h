/*******************************************************************************
* File Name: GLCD_SPIM_SCB_SCBCLK.h
* Version 2.0
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

#if !defined(CY_CLOCK_GLCD_SPIM_SCB_SCBCLK_H)
#define CY_CLOCK_GLCD_SPIM_SCB_SCBCLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/

void GLCD_SPIM_SCB_SCBCLK_Start(void);
void GLCD_SPIM_SCB_SCBCLK_Stop(void);

void GLCD_SPIM_SCB_SCBCLK_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 GLCD_SPIM_SCB_SCBCLK_GetDividerRegister(void);
uint8  GLCD_SPIM_SCB_SCBCLK_GetFractionalDividerRegister(void);

#define GLCD_SPIM_SCB_SCBCLK_Enable()                         GLCD_SPIM_SCB_SCBCLK_Start()
#define GLCD_SPIM_SCB_SCBCLK_Disable()                        GLCD_SPIM_SCB_SCBCLK_Stop()
#define GLCD_SPIM_SCB_SCBCLK_SetDividerRegister(clkDivider, reset)  \
                        GLCD_SPIM_SCB_SCBCLK_SetFractionalDividerRegister((clkDivider), 0)
#define GLCD_SPIM_SCB_SCBCLK_SetDivider(clkDivider)           GLCD_SPIM_SCB_SCBCLK_SetDividerRegister((clkDivider), 1)
#define GLCD_SPIM_SCB_SCBCLK_SetDividerValue(clkDivider)      GLCD_SPIM_SCB_SCBCLK_SetDividerRegister((clkDivider) - 1, 1)


/***************************************
*             Registers
***************************************/

#define GLCD_SPIM_SCB_SCBCLK_DIV_REG    (*(reg32 *)GLCD_SPIM_SCB_SCBCLK__REGISTER)
#define GLCD_SPIM_SCB_SCBCLK_ENABLE_REG GLCD_SPIM_SCB_SCBCLK_DIV_REG

#endif /* !defined(CY_CLOCK_GLCD_SPIM_SCB_SCBCLK_H) */

/* [] END OF FILE */
