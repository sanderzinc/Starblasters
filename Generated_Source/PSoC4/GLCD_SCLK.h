/*******************************************************************************
* File Name: GLCD_SCLK.h  
* Version 1.90
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_GLCD_SCLK_H) /* Pins GLCD_SCLK_H */
#define CY_PINS_GLCD_SCLK_H

#include "cytypes.h"
#include "cyfitter.h"
#include "GLCD_SCLK_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    GLCD_SCLK_Write(uint8 value) ;
void    GLCD_SCLK_SetDriveMode(uint8 mode) ;
uint8   GLCD_SCLK_ReadDataReg(void) ;
uint8   GLCD_SCLK_Read(void) ;
uint8   GLCD_SCLK_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define GLCD_SCLK_DRIVE_MODE_BITS        (3)
#define GLCD_SCLK_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - GLCD_SCLK_DRIVE_MODE_BITS))
#define GLCD_SCLK_DRIVE_MODE_SHIFT       (0x00u)
#define GLCD_SCLK_DRIVE_MODE_MASK        (0x07u << GLCD_SCLK_DRIVE_MODE_SHIFT)

#define GLCD_SCLK_DM_ALG_HIZ         (0x00u << GLCD_SCLK_DRIVE_MODE_SHIFT)
#define GLCD_SCLK_DM_DIG_HIZ         (0x01u << GLCD_SCLK_DRIVE_MODE_SHIFT)
#define GLCD_SCLK_DM_RES_UP          (0x02u << GLCD_SCLK_DRIVE_MODE_SHIFT)
#define GLCD_SCLK_DM_RES_DWN         (0x03u << GLCD_SCLK_DRIVE_MODE_SHIFT)
#define GLCD_SCLK_DM_OD_LO           (0x04u << GLCD_SCLK_DRIVE_MODE_SHIFT)
#define GLCD_SCLK_DM_OD_HI           (0x05u << GLCD_SCLK_DRIVE_MODE_SHIFT)
#define GLCD_SCLK_DM_STRONG          (0x06u << GLCD_SCLK_DRIVE_MODE_SHIFT)
#define GLCD_SCLK_DM_RES_UPDWN       (0x07u << GLCD_SCLK_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define GLCD_SCLK_MASK               GLCD_SCLK__MASK
#define GLCD_SCLK_SHIFT              GLCD_SCLK__SHIFT
#define GLCD_SCLK_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define GLCD_SCLK_PS                     (* (reg32 *) GLCD_SCLK__PS)
/* Port Configuration */
#define GLCD_SCLK_PC                     (* (reg32 *) GLCD_SCLK__PC)
/* Data Register */
#define GLCD_SCLK_DR                     (* (reg32 *) GLCD_SCLK__DR)
/* Input Buffer Disable Override */
#define GLCD_SCLK_INP_DIS                (* (reg32 *) GLCD_SCLK__PC2)


#if defined(GLCD_SCLK__INTSTAT)  /* Interrupt Registers */

    #define GLCD_SCLK_INTSTAT                (* (reg32 *) GLCD_SCLK__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins GLCD_SCLK_H */


/* [] END OF FILE */
