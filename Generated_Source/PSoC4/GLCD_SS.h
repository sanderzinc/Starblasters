/*******************************************************************************
* File Name: GLCD_SS.h  
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

#if !defined(CY_PINS_GLCD_SS_H) /* Pins GLCD_SS_H */
#define CY_PINS_GLCD_SS_H

#include "cytypes.h"
#include "cyfitter.h"
#include "GLCD_SS_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    GLCD_SS_Write(uint8 value) ;
void    GLCD_SS_SetDriveMode(uint8 mode) ;
uint8   GLCD_SS_ReadDataReg(void) ;
uint8   GLCD_SS_Read(void) ;
uint8   GLCD_SS_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define GLCD_SS_DRIVE_MODE_BITS        (3)
#define GLCD_SS_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - GLCD_SS_DRIVE_MODE_BITS))
#define GLCD_SS_DRIVE_MODE_SHIFT       (0x00u)
#define GLCD_SS_DRIVE_MODE_MASK        (0x07u << GLCD_SS_DRIVE_MODE_SHIFT)

#define GLCD_SS_DM_ALG_HIZ         (0x00u << GLCD_SS_DRIVE_MODE_SHIFT)
#define GLCD_SS_DM_DIG_HIZ         (0x01u << GLCD_SS_DRIVE_MODE_SHIFT)
#define GLCD_SS_DM_RES_UP          (0x02u << GLCD_SS_DRIVE_MODE_SHIFT)
#define GLCD_SS_DM_RES_DWN         (0x03u << GLCD_SS_DRIVE_MODE_SHIFT)
#define GLCD_SS_DM_OD_LO           (0x04u << GLCD_SS_DRIVE_MODE_SHIFT)
#define GLCD_SS_DM_OD_HI           (0x05u << GLCD_SS_DRIVE_MODE_SHIFT)
#define GLCD_SS_DM_STRONG          (0x06u << GLCD_SS_DRIVE_MODE_SHIFT)
#define GLCD_SS_DM_RES_UPDWN       (0x07u << GLCD_SS_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define GLCD_SS_MASK               GLCD_SS__MASK
#define GLCD_SS_SHIFT              GLCD_SS__SHIFT
#define GLCD_SS_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define GLCD_SS_PS                     (* (reg32 *) GLCD_SS__PS)
/* Port Configuration */
#define GLCD_SS_PC                     (* (reg32 *) GLCD_SS__PC)
/* Data Register */
#define GLCD_SS_DR                     (* (reg32 *) GLCD_SS__DR)
/* Input Buffer Disable Override */
#define GLCD_SS_INP_DIS                (* (reg32 *) GLCD_SS__PC2)


#if defined(GLCD_SS__INTSTAT)  /* Interrupt Registers */

    #define GLCD_SS_INTSTAT                (* (reg32 *) GLCD_SS__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins GLCD_SS_H */


/* [] END OF FILE */
