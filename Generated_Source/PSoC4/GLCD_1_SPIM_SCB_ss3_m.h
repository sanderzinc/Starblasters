/*******************************************************************************
* File Name: GLCD_1_SPIM_SCB_ss3_m.h  
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

#if !defined(CY_PINS_GLCD_1_SPIM_SCB_ss3_m_H) /* Pins GLCD_1_SPIM_SCB_ss3_m_H */
#define CY_PINS_GLCD_1_SPIM_SCB_ss3_m_H

#include "cytypes.h"
#include "cyfitter.h"
#include "GLCD_1_SPIM_SCB_ss3_m_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    GLCD_1_SPIM_SCB_ss3_m_Write(uint8 value) ;
void    GLCD_1_SPIM_SCB_ss3_m_SetDriveMode(uint8 mode) ;
uint8   GLCD_1_SPIM_SCB_ss3_m_ReadDataReg(void) ;
uint8   GLCD_1_SPIM_SCB_ss3_m_Read(void) ;
uint8   GLCD_1_SPIM_SCB_ss3_m_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define GLCD_1_SPIM_SCB_ss3_m_DRIVE_MODE_BITS        (3)
#define GLCD_1_SPIM_SCB_ss3_m_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - GLCD_1_SPIM_SCB_ss3_m_DRIVE_MODE_BITS))
#define GLCD_1_SPIM_SCB_ss3_m_DRIVE_MODE_SHIFT       (0x00u)
#define GLCD_1_SPIM_SCB_ss3_m_DRIVE_MODE_MASK        (0x07u << GLCD_1_SPIM_SCB_ss3_m_DRIVE_MODE_SHIFT)

#define GLCD_1_SPIM_SCB_ss3_m_DM_ALG_HIZ         (0x00u << GLCD_1_SPIM_SCB_ss3_m_DRIVE_MODE_SHIFT)
#define GLCD_1_SPIM_SCB_ss3_m_DM_DIG_HIZ         (0x01u << GLCD_1_SPIM_SCB_ss3_m_DRIVE_MODE_SHIFT)
#define GLCD_1_SPIM_SCB_ss3_m_DM_RES_UP          (0x02u << GLCD_1_SPIM_SCB_ss3_m_DRIVE_MODE_SHIFT)
#define GLCD_1_SPIM_SCB_ss3_m_DM_RES_DWN         (0x03u << GLCD_1_SPIM_SCB_ss3_m_DRIVE_MODE_SHIFT)
#define GLCD_1_SPIM_SCB_ss3_m_DM_OD_LO           (0x04u << GLCD_1_SPIM_SCB_ss3_m_DRIVE_MODE_SHIFT)
#define GLCD_1_SPIM_SCB_ss3_m_DM_OD_HI           (0x05u << GLCD_1_SPIM_SCB_ss3_m_DRIVE_MODE_SHIFT)
#define GLCD_1_SPIM_SCB_ss3_m_DM_STRONG          (0x06u << GLCD_1_SPIM_SCB_ss3_m_DRIVE_MODE_SHIFT)
#define GLCD_1_SPIM_SCB_ss3_m_DM_RES_UPDWN       (0x07u << GLCD_1_SPIM_SCB_ss3_m_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define GLCD_1_SPIM_SCB_ss3_m_MASK               GLCD_1_SPIM_SCB_ss3_m__MASK
#define GLCD_1_SPIM_SCB_ss3_m_SHIFT              GLCD_1_SPIM_SCB_ss3_m__SHIFT
#define GLCD_1_SPIM_SCB_ss3_m_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define GLCD_1_SPIM_SCB_ss3_m_PS                     (* (reg32 *) GLCD_1_SPIM_SCB_ss3_m__PS)
/* Port Configuration */
#define GLCD_1_SPIM_SCB_ss3_m_PC                     (* (reg32 *) GLCD_1_SPIM_SCB_ss3_m__PC)
/* Data Register */
#define GLCD_1_SPIM_SCB_ss3_m_DR                     (* (reg32 *) GLCD_1_SPIM_SCB_ss3_m__DR)
/* Input Buffer Disable Override */
#define GLCD_1_SPIM_SCB_ss3_m_INP_DIS                (* (reg32 *) GLCD_1_SPIM_SCB_ss3_m__PC2)


#if defined(GLCD_1_SPIM_SCB_ss3_m__INTSTAT)  /* Interrupt Registers */

    #define GLCD_1_SPIM_SCB_ss3_m_INTSTAT                (* (reg32 *) GLCD_1_SPIM_SCB_ss3_m__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins GLCD_1_SPIM_SCB_ss3_m_H */


/* [] END OF FILE */
