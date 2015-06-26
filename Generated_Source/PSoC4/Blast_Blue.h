/*******************************************************************************
* File Name: Blast_Blue.h  
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

#if !defined(CY_PINS_Blast_Blue_H) /* Pins Blast_Blue_H */
#define CY_PINS_Blast_Blue_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Blast_Blue_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Blast_Blue_Write(uint8 value) ;
void    Blast_Blue_SetDriveMode(uint8 mode) ;
uint8   Blast_Blue_ReadDataReg(void) ;
uint8   Blast_Blue_Read(void) ;
uint8   Blast_Blue_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Blast_Blue_DRIVE_MODE_BITS        (3)
#define Blast_Blue_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Blast_Blue_DRIVE_MODE_BITS))
#define Blast_Blue_DRIVE_MODE_SHIFT       (0x00u)
#define Blast_Blue_DRIVE_MODE_MASK        (0x07u << Blast_Blue_DRIVE_MODE_SHIFT)

#define Blast_Blue_DM_ALG_HIZ         (0x00u << Blast_Blue_DRIVE_MODE_SHIFT)
#define Blast_Blue_DM_DIG_HIZ         (0x01u << Blast_Blue_DRIVE_MODE_SHIFT)
#define Blast_Blue_DM_RES_UP          (0x02u << Blast_Blue_DRIVE_MODE_SHIFT)
#define Blast_Blue_DM_RES_DWN         (0x03u << Blast_Blue_DRIVE_MODE_SHIFT)
#define Blast_Blue_DM_OD_LO           (0x04u << Blast_Blue_DRIVE_MODE_SHIFT)
#define Blast_Blue_DM_OD_HI           (0x05u << Blast_Blue_DRIVE_MODE_SHIFT)
#define Blast_Blue_DM_STRONG          (0x06u << Blast_Blue_DRIVE_MODE_SHIFT)
#define Blast_Blue_DM_RES_UPDWN       (0x07u << Blast_Blue_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define Blast_Blue_MASK               Blast_Blue__MASK
#define Blast_Blue_SHIFT              Blast_Blue__SHIFT
#define Blast_Blue_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Blast_Blue_PS                     (* (reg32 *) Blast_Blue__PS)
/* Port Configuration */
#define Blast_Blue_PC                     (* (reg32 *) Blast_Blue__PC)
/* Data Register */
#define Blast_Blue_DR                     (* (reg32 *) Blast_Blue__DR)
/* Input Buffer Disable Override */
#define Blast_Blue_INP_DIS                (* (reg32 *) Blast_Blue__PC2)


#if defined(Blast_Blue__INTSTAT)  /* Interrupt Registers */

    #define Blast_Blue_INTSTAT                (* (reg32 *) Blast_Blue__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins Blast_Blue_H */


/* [] END OF FILE */
