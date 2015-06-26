/*******************************************************************************
* File Name: Blast_Red.h  
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

#if !defined(CY_PINS_Blast_Red_H) /* Pins Blast_Red_H */
#define CY_PINS_Blast_Red_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Blast_Red_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Blast_Red_Write(uint8 value) ;
void    Blast_Red_SetDriveMode(uint8 mode) ;
uint8   Blast_Red_ReadDataReg(void) ;
uint8   Blast_Red_Read(void) ;
uint8   Blast_Red_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Blast_Red_DRIVE_MODE_BITS        (3)
#define Blast_Red_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Blast_Red_DRIVE_MODE_BITS))
#define Blast_Red_DRIVE_MODE_SHIFT       (0x00u)
#define Blast_Red_DRIVE_MODE_MASK        (0x07u << Blast_Red_DRIVE_MODE_SHIFT)

#define Blast_Red_DM_ALG_HIZ         (0x00u << Blast_Red_DRIVE_MODE_SHIFT)
#define Blast_Red_DM_DIG_HIZ         (0x01u << Blast_Red_DRIVE_MODE_SHIFT)
#define Blast_Red_DM_RES_UP          (0x02u << Blast_Red_DRIVE_MODE_SHIFT)
#define Blast_Red_DM_RES_DWN         (0x03u << Blast_Red_DRIVE_MODE_SHIFT)
#define Blast_Red_DM_OD_LO           (0x04u << Blast_Red_DRIVE_MODE_SHIFT)
#define Blast_Red_DM_OD_HI           (0x05u << Blast_Red_DRIVE_MODE_SHIFT)
#define Blast_Red_DM_STRONG          (0x06u << Blast_Red_DRIVE_MODE_SHIFT)
#define Blast_Red_DM_RES_UPDWN       (0x07u << Blast_Red_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define Blast_Red_MASK               Blast_Red__MASK
#define Blast_Red_SHIFT              Blast_Red__SHIFT
#define Blast_Red_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Blast_Red_PS                     (* (reg32 *) Blast_Red__PS)
/* Port Configuration */
#define Blast_Red_PC                     (* (reg32 *) Blast_Red__PC)
/* Data Register */
#define Blast_Red_DR                     (* (reg32 *) Blast_Red__DR)
/* Input Buffer Disable Override */
#define Blast_Red_INP_DIS                (* (reg32 *) Blast_Red__PC2)


#if defined(Blast_Red__INTSTAT)  /* Interrupt Registers */

    #define Blast_Red_INTSTAT                (* (reg32 *) Blast_Red__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins Blast_Red_H */


/* [] END OF FILE */
