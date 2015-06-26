/*******************************************************************************
* File Name: Blast.h  
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

#if !defined(CY_PINS_Blast_H) /* Pins Blast_H */
#define CY_PINS_Blast_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Blast_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Blast_Write(uint8 value) ;
void    Blast_SetDriveMode(uint8 mode) ;
uint8   Blast_ReadDataReg(void) ;
uint8   Blast_Read(void) ;
uint8   Blast_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Blast_DRIVE_MODE_BITS        (3)
#define Blast_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Blast_DRIVE_MODE_BITS))
#define Blast_DRIVE_MODE_SHIFT       (0x00u)
#define Blast_DRIVE_MODE_MASK        (0x07u << Blast_DRIVE_MODE_SHIFT)

#define Blast_DM_ALG_HIZ         (0x00u << Blast_DRIVE_MODE_SHIFT)
#define Blast_DM_DIG_HIZ         (0x01u << Blast_DRIVE_MODE_SHIFT)
#define Blast_DM_RES_UP          (0x02u << Blast_DRIVE_MODE_SHIFT)
#define Blast_DM_RES_DWN         (0x03u << Blast_DRIVE_MODE_SHIFT)
#define Blast_DM_OD_LO           (0x04u << Blast_DRIVE_MODE_SHIFT)
#define Blast_DM_OD_HI           (0x05u << Blast_DRIVE_MODE_SHIFT)
#define Blast_DM_STRONG          (0x06u << Blast_DRIVE_MODE_SHIFT)
#define Blast_DM_RES_UPDWN       (0x07u << Blast_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define Blast_MASK               Blast__MASK
#define Blast_SHIFT              Blast__SHIFT
#define Blast_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Blast_PS                     (* (reg32 *) Blast__PS)
/* Port Configuration */
#define Blast_PC                     (* (reg32 *) Blast__PC)
/* Data Register */
#define Blast_DR                     (* (reg32 *) Blast__DR)
/* Input Buffer Disable Override */
#define Blast_INP_DIS                (* (reg32 *) Blast__PC2)


#if defined(Blast__INTSTAT)  /* Interrupt Registers */

    #define Blast_INTSTAT                (* (reg32 *) Blast__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins Blast_H */


/* [] END OF FILE */
