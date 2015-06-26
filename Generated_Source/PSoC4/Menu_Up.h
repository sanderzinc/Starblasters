/*******************************************************************************
* File Name: Menu_Up.h  
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

#if !defined(CY_PINS_Menu_Up_H) /* Pins Menu_Up_H */
#define CY_PINS_Menu_Up_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Menu_Up_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Menu_Up_Write(uint8 value) ;
void    Menu_Up_SetDriveMode(uint8 mode) ;
uint8   Menu_Up_ReadDataReg(void) ;
uint8   Menu_Up_Read(void) ;
uint8   Menu_Up_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Menu_Up_DRIVE_MODE_BITS        (3)
#define Menu_Up_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Menu_Up_DRIVE_MODE_BITS))
#define Menu_Up_DRIVE_MODE_SHIFT       (0x00u)
#define Menu_Up_DRIVE_MODE_MASK        (0x07u << Menu_Up_DRIVE_MODE_SHIFT)

#define Menu_Up_DM_ALG_HIZ         (0x00u << Menu_Up_DRIVE_MODE_SHIFT)
#define Menu_Up_DM_DIG_HIZ         (0x01u << Menu_Up_DRIVE_MODE_SHIFT)
#define Menu_Up_DM_RES_UP          (0x02u << Menu_Up_DRIVE_MODE_SHIFT)
#define Menu_Up_DM_RES_DWN         (0x03u << Menu_Up_DRIVE_MODE_SHIFT)
#define Menu_Up_DM_OD_LO           (0x04u << Menu_Up_DRIVE_MODE_SHIFT)
#define Menu_Up_DM_OD_HI           (0x05u << Menu_Up_DRIVE_MODE_SHIFT)
#define Menu_Up_DM_STRONG          (0x06u << Menu_Up_DRIVE_MODE_SHIFT)
#define Menu_Up_DM_RES_UPDWN       (0x07u << Menu_Up_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define Menu_Up_MASK               Menu_Up__MASK
#define Menu_Up_SHIFT              Menu_Up__SHIFT
#define Menu_Up_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Menu_Up_PS                     (* (reg32 *) Menu_Up__PS)
/* Port Configuration */
#define Menu_Up_PC                     (* (reg32 *) Menu_Up__PC)
/* Data Register */
#define Menu_Up_DR                     (* (reg32 *) Menu_Up__DR)
/* Input Buffer Disable Override */
#define Menu_Up_INP_DIS                (* (reg32 *) Menu_Up__PC2)


#if defined(Menu_Up__INTSTAT)  /* Interrupt Registers */

    #define Menu_Up_INTSTAT                (* (reg32 *) Menu_Up__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins Menu_Up_H */


/* [] END OF FILE */
