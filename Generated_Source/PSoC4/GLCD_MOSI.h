/*******************************************************************************
* File Name: GLCD_MOSI.h  
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

#if !defined(CY_PINS_GLCD_MOSI_H) /* Pins GLCD_MOSI_H */
#define CY_PINS_GLCD_MOSI_H

#include "cytypes.h"
#include "cyfitter.h"
#include "GLCD_MOSI_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    GLCD_MOSI_Write(uint8 value) ;
void    GLCD_MOSI_SetDriveMode(uint8 mode) ;
uint8   GLCD_MOSI_ReadDataReg(void) ;
uint8   GLCD_MOSI_Read(void) ;
uint8   GLCD_MOSI_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define GLCD_MOSI_DRIVE_MODE_BITS        (3)
#define GLCD_MOSI_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - GLCD_MOSI_DRIVE_MODE_BITS))
#define GLCD_MOSI_DRIVE_MODE_SHIFT       (0x00u)
#define GLCD_MOSI_DRIVE_MODE_MASK        (0x07u << GLCD_MOSI_DRIVE_MODE_SHIFT)

#define GLCD_MOSI_DM_ALG_HIZ         (0x00u << GLCD_MOSI_DRIVE_MODE_SHIFT)
#define GLCD_MOSI_DM_DIG_HIZ         (0x01u << GLCD_MOSI_DRIVE_MODE_SHIFT)
#define GLCD_MOSI_DM_RES_UP          (0x02u << GLCD_MOSI_DRIVE_MODE_SHIFT)
#define GLCD_MOSI_DM_RES_DWN         (0x03u << GLCD_MOSI_DRIVE_MODE_SHIFT)
#define GLCD_MOSI_DM_OD_LO           (0x04u << GLCD_MOSI_DRIVE_MODE_SHIFT)
#define GLCD_MOSI_DM_OD_HI           (0x05u << GLCD_MOSI_DRIVE_MODE_SHIFT)
#define GLCD_MOSI_DM_STRONG          (0x06u << GLCD_MOSI_DRIVE_MODE_SHIFT)
#define GLCD_MOSI_DM_RES_UPDWN       (0x07u << GLCD_MOSI_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define GLCD_MOSI_MASK               GLCD_MOSI__MASK
#define GLCD_MOSI_SHIFT              GLCD_MOSI__SHIFT
#define GLCD_MOSI_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define GLCD_MOSI_PS                     (* (reg32 *) GLCD_MOSI__PS)
/* Port Configuration */
#define GLCD_MOSI_PC                     (* (reg32 *) GLCD_MOSI__PC)
/* Data Register */
#define GLCD_MOSI_DR                     (* (reg32 *) GLCD_MOSI__DR)
/* Input Buffer Disable Override */
#define GLCD_MOSI_INP_DIS                (* (reg32 *) GLCD_MOSI__PC2)


#if defined(GLCD_MOSI__INTSTAT)  /* Interrupt Registers */

    #define GLCD_MOSI_INTSTAT                (* (reg32 *) GLCD_MOSI__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins GLCD_MOSI_H */


/* [] END OF FILE */
