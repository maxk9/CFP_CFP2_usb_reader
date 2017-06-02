/*******************************************************************************
* File Name: MOD_ABS.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_MOD_ABS_H) /* Pins MOD_ABS_H */
#define CY_PINS_MOD_ABS_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "MOD_ABS_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 MOD_ABS__PORT == 15 && ((MOD_ABS__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    MOD_ABS_Write(uint8 value);
void    MOD_ABS_SetDriveMode(uint8 mode);
uint8   MOD_ABS_ReadDataReg(void);
uint8   MOD_ABS_Read(void);
void    MOD_ABS_SetInterruptMode(uint16 position, uint16 mode);
uint8   MOD_ABS_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the MOD_ABS_SetDriveMode() function.
     *  @{
     */
        #define MOD_ABS_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define MOD_ABS_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define MOD_ABS_DM_RES_UP          PIN_DM_RES_UP
        #define MOD_ABS_DM_RES_DWN         PIN_DM_RES_DWN
        #define MOD_ABS_DM_OD_LO           PIN_DM_OD_LO
        #define MOD_ABS_DM_OD_HI           PIN_DM_OD_HI
        #define MOD_ABS_DM_STRONG          PIN_DM_STRONG
        #define MOD_ABS_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define MOD_ABS_MASK               MOD_ABS__MASK
#define MOD_ABS_SHIFT              MOD_ABS__SHIFT
#define MOD_ABS_WIDTH              1u

/* Interrupt constants */
#if defined(MOD_ABS__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in MOD_ABS_SetInterruptMode() function.
     *  @{
     */
        #define MOD_ABS_INTR_NONE      (uint16)(0x0000u)
        #define MOD_ABS_INTR_RISING    (uint16)(0x0001u)
        #define MOD_ABS_INTR_FALLING   (uint16)(0x0002u)
        #define MOD_ABS_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define MOD_ABS_INTR_MASK      (0x01u) 
#endif /* (MOD_ABS__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MOD_ABS_PS                     (* (reg8 *) MOD_ABS__PS)
/* Data Register */
#define MOD_ABS_DR                     (* (reg8 *) MOD_ABS__DR)
/* Port Number */
#define MOD_ABS_PRT_NUM                (* (reg8 *) MOD_ABS__PRT) 
/* Connect to Analog Globals */                                                  
#define MOD_ABS_AG                     (* (reg8 *) MOD_ABS__AG)                       
/* Analog MUX bux enable */
#define MOD_ABS_AMUX                   (* (reg8 *) MOD_ABS__AMUX) 
/* Bidirectional Enable */                                                        
#define MOD_ABS_BIE                    (* (reg8 *) MOD_ABS__BIE)
/* Bit-mask for Aliased Register Access */
#define MOD_ABS_BIT_MASK               (* (reg8 *) MOD_ABS__BIT_MASK)
/* Bypass Enable */
#define MOD_ABS_BYP                    (* (reg8 *) MOD_ABS__BYP)
/* Port wide control signals */                                                   
#define MOD_ABS_CTL                    (* (reg8 *) MOD_ABS__CTL)
/* Drive Modes */
#define MOD_ABS_DM0                    (* (reg8 *) MOD_ABS__DM0) 
#define MOD_ABS_DM1                    (* (reg8 *) MOD_ABS__DM1)
#define MOD_ABS_DM2                    (* (reg8 *) MOD_ABS__DM2) 
/* Input Buffer Disable Override */
#define MOD_ABS_INP_DIS                (* (reg8 *) MOD_ABS__INP_DIS)
/* LCD Common or Segment Drive */
#define MOD_ABS_LCD_COM_SEG            (* (reg8 *) MOD_ABS__LCD_COM_SEG)
/* Enable Segment LCD */
#define MOD_ABS_LCD_EN                 (* (reg8 *) MOD_ABS__LCD_EN)
/* Slew Rate Control */
#define MOD_ABS_SLW                    (* (reg8 *) MOD_ABS__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define MOD_ABS_PRTDSI__CAPS_SEL       (* (reg8 *) MOD_ABS__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define MOD_ABS_PRTDSI__DBL_SYNC_IN    (* (reg8 *) MOD_ABS__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define MOD_ABS_PRTDSI__OE_SEL0        (* (reg8 *) MOD_ABS__PRTDSI__OE_SEL0) 
#define MOD_ABS_PRTDSI__OE_SEL1        (* (reg8 *) MOD_ABS__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define MOD_ABS_PRTDSI__OUT_SEL0       (* (reg8 *) MOD_ABS__PRTDSI__OUT_SEL0) 
#define MOD_ABS_PRTDSI__OUT_SEL1       (* (reg8 *) MOD_ABS__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define MOD_ABS_PRTDSI__SYNC_OUT       (* (reg8 *) MOD_ABS__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(MOD_ABS__SIO_CFG)
    #define MOD_ABS_SIO_HYST_EN        (* (reg8 *) MOD_ABS__SIO_HYST_EN)
    #define MOD_ABS_SIO_REG_HIFREQ     (* (reg8 *) MOD_ABS__SIO_REG_HIFREQ)
    #define MOD_ABS_SIO_CFG            (* (reg8 *) MOD_ABS__SIO_CFG)
    #define MOD_ABS_SIO_DIFF           (* (reg8 *) MOD_ABS__SIO_DIFF)
#endif /* (MOD_ABS__SIO_CFG) */

/* Interrupt Registers */
#if defined(MOD_ABS__INTSTAT)
    #define MOD_ABS_INTSTAT            (* (reg8 *) MOD_ABS__INTSTAT)
    #define MOD_ABS_SNAP               (* (reg8 *) MOD_ABS__SNAP)
    
	#define MOD_ABS_0_INTTYPE_REG 		(* (reg8 *) MOD_ABS__0__INTTYPE)
#endif /* (MOD_ABS__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_MOD_ABS_H */


/* [] END OF FILE */
