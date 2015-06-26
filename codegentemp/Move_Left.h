/*******************************************************************************
* File Name: Move_Left.h  
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

#if !defined(CY_PINS_Move_Left_H) /* Pins Move_Left_H */
#define CY_PINS_Move_Left_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Move_Left_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Move_Left_Write(uint8 value) ;
void    Move_Left_SetDriveMode(uint8 mode) ;
uint8   Move_Left_ReadDataReg(void) ;
uint8   Move_Left_Read(void) ;
uint8   Move_Left_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Move_Left_DRIVE_MODE_BITS        (3)
#define Move_Left_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Move_Left_DRIVE_MODE_BITS))
#define Move_Left_DRIVE_MODE_SHIFT       (0x00u)
#define Move_Left_DRIVE_MODE_MASK        (0x07u << Move_Left_DRIVE_MODE_SHIFT)

#define Move_Left_DM_ALG_HIZ         (0x00u << Move_Left_DRIVE_MODE_SHIFT)
#define Move_Left_DM_DIG_HIZ         (0x01u << Move_Left_DRIVE_MODE_SHIFT)
#define Move_Left_DM_RES_UP          (0x02u << Move_Left_DRIVE_MODE_SHIFT)
#define Move_Left_DM_RES_DWN         (0x03u << Move_Left_DRIVE_MODE_SHIFT)
#define Move_Left_DM_OD_LO           (0x04u << Move_Left_DRIVE_MODE_SHIFT)
#define Move_Left_DM_OD_HI           (0x05u << Move_Left_DRIVE_MODE_SHIFT)
#define Move_Left_DM_STRONG          (0x06u << Move_Left_DRIVE_MODE_SHIFT)
#define Move_Left_DM_RES_UPDWN       (0x07u << Move_Left_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define Move_Left_MASK               Move_Left__MASK
#define Move_Left_SHIFT              Move_Left__SHIFT
#define Move_Left_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Move_Left_PS                     (* (reg32 *) Move_Left__PS)
/* Port Configuration */
#define Move_Left_PC                     (* (reg32 *) Move_Left__PC)
/* Data Register */
#define Move_Left_DR                     (* (reg32 *) Move_Left__DR)
/* Input Buffer Disable Override */
#define Move_Left_INP_DIS                (* (reg32 *) Move_Left__PC2)


#if defined(Move_Left__INTSTAT)  /* Interrupt Registers */

    #define Move_Left_INTSTAT                (* (reg32 *) Move_Left__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins Move_Left_H */


/* [] END OF FILE */
