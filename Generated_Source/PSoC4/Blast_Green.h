/*******************************************************************************
* File Name: Blast_Green.h  
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

#if !defined(CY_PINS_Blast_Green_H) /* Pins Blast_Green_H */
#define CY_PINS_Blast_Green_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Blast_Green_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Blast_Green_Write(uint8 value) ;
void    Blast_Green_SetDriveMode(uint8 mode) ;
uint8   Blast_Green_ReadDataReg(void) ;
uint8   Blast_Green_Read(void) ;
uint8   Blast_Green_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Blast_Green_DRIVE_MODE_BITS        (3)
#define Blast_Green_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Blast_Green_DRIVE_MODE_BITS))
#define Blast_Green_DRIVE_MODE_SHIFT       (0x00u)
#define Blast_Green_DRIVE_MODE_MASK        (0x07u << Blast_Green_DRIVE_MODE_SHIFT)

#define Blast_Green_DM_ALG_HIZ         (0x00u << Blast_Green_DRIVE_MODE_SHIFT)
#define Blast_Green_DM_DIG_HIZ         (0x01u << Blast_Green_DRIVE_MODE_SHIFT)
#define Blast_Green_DM_RES_UP          (0x02u << Blast_Green_DRIVE_MODE_SHIFT)
#define Blast_Green_DM_RES_DWN         (0x03u << Blast_Green_DRIVE_MODE_SHIFT)
#define Blast_Green_DM_OD_LO           (0x04u << Blast_Green_DRIVE_MODE_SHIFT)
#define Blast_Green_DM_OD_HI           (0x05u << Blast_Green_DRIVE_MODE_SHIFT)
#define Blast_Green_DM_STRONG          (0x06u << Blast_Green_DRIVE_MODE_SHIFT)
#define Blast_Green_DM_RES_UPDWN       (0x07u << Blast_Green_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define Blast_Green_MASK               Blast_Green__MASK
#define Blast_Green_SHIFT              Blast_Green__SHIFT
#define Blast_Green_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Blast_Green_PS                     (* (reg32 *) Blast_Green__PS)
/* Port Configuration */
#define Blast_Green_PC                     (* (reg32 *) Blast_Green__PC)
/* Data Register */
#define Blast_Green_DR                     (* (reg32 *) Blast_Green__DR)
/* Input Buffer Disable Override */
#define Blast_Green_INP_DIS                (* (reg32 *) Blast_Green__PC2)


#if defined(Blast_Green__INTSTAT)  /* Interrupt Registers */

    #define Blast_Green_INTSTAT                (* (reg32 *) Blast_Green__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins Blast_Green_H */


/* [] END OF FILE */
