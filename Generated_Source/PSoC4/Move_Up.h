/*******************************************************************************
* File Name: Move_Up.h  
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

#if !defined(CY_PINS_Move_Up_H) /* Pins Move_Up_H */
#define CY_PINS_Move_Up_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Move_Up_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Move_Up_Write(uint8 value) ;
void    Move_Up_SetDriveMode(uint8 mode) ;
uint8   Move_Up_ReadDataReg(void) ;
uint8   Move_Up_Read(void) ;
uint8   Move_Up_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Move_Up_DRIVE_MODE_BITS        (3)
#define Move_Up_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Move_Up_DRIVE_MODE_BITS))
#define Move_Up_DRIVE_MODE_SHIFT       (0x00u)
#define Move_Up_DRIVE_MODE_MASK        (0x07u << Move_Up_DRIVE_MODE_SHIFT)

#define Move_Up_DM_ALG_HIZ         (0x00u << Move_Up_DRIVE_MODE_SHIFT)
#define Move_Up_DM_DIG_HIZ         (0x01u << Move_Up_DRIVE_MODE_SHIFT)
#define Move_Up_DM_RES_UP          (0x02u << Move_Up_DRIVE_MODE_SHIFT)
#define Move_Up_DM_RES_DWN         (0x03u << Move_Up_DRIVE_MODE_SHIFT)
#define Move_Up_DM_OD_LO           (0x04u << Move_Up_DRIVE_MODE_SHIFT)
#define Move_Up_DM_OD_HI           (0x05u << Move_Up_DRIVE_MODE_SHIFT)
#define Move_Up_DM_STRONG          (0x06u << Move_Up_DRIVE_MODE_SHIFT)
#define Move_Up_DM_RES_UPDWN       (0x07u << Move_Up_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define Move_Up_MASK               Move_Up__MASK
#define Move_Up_SHIFT              Move_Up__SHIFT
#define Move_Up_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Move_Up_PS                     (* (reg32 *) Move_Up__PS)
/* Port Configuration */
#define Move_Up_PC                     (* (reg32 *) Move_Up__PC)
/* Data Register */
#define Move_Up_DR                     (* (reg32 *) Move_Up__DR)
/* Input Buffer Disable Override */
#define Move_Up_INP_DIS                (* (reg32 *) Move_Up__PC2)


#if defined(Move_Up__INTSTAT)  /* Interrupt Registers */

    #define Move_Up_INTSTAT                (* (reg32 *) Move_Up__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins Move_Up_H */


/* [] END OF FILE */
