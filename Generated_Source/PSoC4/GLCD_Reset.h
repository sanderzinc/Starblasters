/*******************************************************************************
* File Name: GLCD_Reset.h  
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

#if !defined(CY_PINS_GLCD_Reset_H) /* Pins GLCD_Reset_H */
#define CY_PINS_GLCD_Reset_H

#include "cytypes.h"
#include "cyfitter.h"
#include "GLCD_Reset_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    GLCD_Reset_Write(uint8 value) ;
void    GLCD_Reset_SetDriveMode(uint8 mode) ;
uint8   GLCD_Reset_ReadDataReg(void) ;
uint8   GLCD_Reset_Read(void) ;
uint8   GLCD_Reset_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define GLCD_Reset_DRIVE_MODE_BITS        (3)
#define GLCD_Reset_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - GLCD_Reset_DRIVE_MODE_BITS))
#define GLCD_Reset_DRIVE_MODE_SHIFT       (0x00u)
#define GLCD_Reset_DRIVE_MODE_MASK        (0x07u << GLCD_Reset_DRIVE_MODE_SHIFT)

#define GLCD_Reset_DM_ALG_HIZ         (0x00u << GLCD_Reset_DRIVE_MODE_SHIFT)
#define GLCD_Reset_DM_DIG_HIZ         (0x01u << GLCD_Reset_DRIVE_MODE_SHIFT)
#define GLCD_Reset_DM_RES_UP          (0x02u << GLCD_Reset_DRIVE_MODE_SHIFT)
#define GLCD_Reset_DM_RES_DWN         (0x03u << GLCD_Reset_DRIVE_MODE_SHIFT)
#define GLCD_Reset_DM_OD_LO           (0x04u << GLCD_Reset_DRIVE_MODE_SHIFT)
#define GLCD_Reset_DM_OD_HI           (0x05u << GLCD_Reset_DRIVE_MODE_SHIFT)
#define GLCD_Reset_DM_STRONG          (0x06u << GLCD_Reset_DRIVE_MODE_SHIFT)
#define GLCD_Reset_DM_RES_UPDWN       (0x07u << GLCD_Reset_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define GLCD_Reset_MASK               GLCD_Reset__MASK
#define GLCD_Reset_SHIFT              GLCD_Reset__SHIFT
#define GLCD_Reset_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define GLCD_Reset_PS                     (* (reg32 *) GLCD_Reset__PS)
/* Port Configuration */
#define GLCD_Reset_PC                     (* (reg32 *) GLCD_Reset__PC)
/* Data Register */
#define GLCD_Reset_DR                     (* (reg32 *) GLCD_Reset__DR)
/* Input Buffer Disable Override */
#define GLCD_Reset_INP_DIS                (* (reg32 *) GLCD_Reset__PC2)


#if defined(GLCD_Reset__INTSTAT)  /* Interrupt Registers */

    #define GLCD_Reset_INTSTAT                (* (reg32 *) GLCD_Reset__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins GLCD_Reset_H */


/* [] END OF FILE */
