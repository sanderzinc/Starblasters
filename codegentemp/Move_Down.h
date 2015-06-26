/*******************************************************************************
* File Name: Move_Down.h  
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

#if !defined(CY_PINS_Move_Down_H) /* Pins Move_Down_H */
#define CY_PINS_Move_Down_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Move_Down_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Move_Down_Write(uint8 value) ;
void    Move_Down_SetDriveMode(uint8 mode) ;
uint8   Move_Down_ReadDataReg(void) ;
uint8   Move_Down_Read(void) ;
uint8   Move_Down_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Move_Down_DRIVE_MODE_BITS        (3)
#define Move_Down_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Move_Down_DRIVE_MODE_BITS))
#define Move_Down_DRIVE_MODE_SHIFT       (0x00u)
#define Move_Down_DRIVE_MODE_MASK        (0x07u << Move_Down_DRIVE_MODE_SHIFT)

#define Move_Down_DM_ALG_HIZ         (0x00u << Move_Down_DRIVE_MODE_SHIFT)
#define Move_Down_DM_DIG_HIZ         (0x01u << Move_Down_DRIVE_MODE_SHIFT)
#define Move_Down_DM_RES_UP          (0x02u << Move_Down_DRIVE_MODE_SHIFT)
#define Move_Down_DM_RES_DWN         (0x03u << Move_Down_DRIVE_MODE_SHIFT)
#define Move_Down_DM_OD_LO           (0x04u << Move_Down_DRIVE_MODE_SHIFT)
#define Move_Down_DM_OD_HI           (0x05u << Move_Down_DRIVE_MODE_SHIFT)
#define Move_Down_DM_STRONG          (0x06u << Move_Down_DRIVE_MODE_SHIFT)
#define Move_Down_DM_RES_UPDWN       (0x07u << Move_Down_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define Move_Down_MASK               Move_Down__MASK
#define Move_Down_SHIFT              Move_Down__SHIFT
#define Move_Down_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Move_Down_PS                     (* (reg32 *) Move_Down__PS)
/* Port Configuration */
#define Move_Down_PC                     (* (reg32 *) Move_Down__PC)
/* Data Register */
#define Move_Down_DR                     (* (reg32 *) Move_Down__DR)
/* Input Buffer Disable Override */
#define Move_Down_INP_DIS                (* (reg32 *) Move_Down__PC2)


#if defined(Move_Down__INTSTAT)  /* Interrupt Registers */

    #define Move_Down_INTSTAT                (* (reg32 *) Move_Down__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins Move_Down_H */


/* [] END OF FILE */
