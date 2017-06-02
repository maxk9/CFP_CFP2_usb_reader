/*******************************************************************************
* File Name: VRef_1V2.h  
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

#if !defined(CY_PINS_VRef_1V2_H) /* Pins VRef_1V2_H */
#define CY_PINS_VRef_1V2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "VRef_1V2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 VRef_1V2__PORT == 15 && ((VRef_1V2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    VRef_1V2_Write(uint8 value);
void    VRef_1V2_SetDriveMode(uint8 mode);
uint8   VRef_1V2_ReadDataReg(void);
uint8   VRef_1V2_Read(void);
void    VRef_1V2_SetInterruptMode(uint16 position, uint16 mode);
uint8   VRef_1V2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the VRef_1V2_SetDriveMode() function.
     *  @{
     */
        #define VRef_1V2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define VRef_1V2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define VRef_1V2_DM_RES_UP          PIN_DM_RES_UP
        #define VRef_1V2_DM_RES_DWN         PIN_DM_RES_DWN
        #define VRef_1V2_DM_OD_LO           PIN_DM_OD_LO
        #define VRef_1V2_DM_OD_HI           PIN_DM_OD_HI
        #define VRef_1V2_DM_STRONG          PIN_DM_STRONG
        #define VRef_1V2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define VRef_1V2_MASK               VRef_1V2__MASK
#define VRef_1V2_SHIFT              VRef_1V2__SHIFT
#define VRef_1V2_WIDTH              1u

/* Interrupt constants */
#if defined(VRef_1V2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in VRef_1V2_SetInterruptMode() function.
     *  @{
     */
        #define VRef_1V2_INTR_NONE      (uint16)(0x0000u)
        #define VRef_1V2_INTR_RISING    (uint16)(0x0001u)
        #define VRef_1V2_INTR_FALLING   (uint16)(0x0002u)
        #define VRef_1V2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define VRef_1V2_INTR_MASK      (0x01u) 
#endif /* (VRef_1V2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define VRef_1V2_PS                     (* (reg8 *) VRef_1V2__PS)
/* Data Register */
#define VRef_1V2_DR                     (* (reg8 *) VRef_1V2__DR)
/* Port Number */
#define VRef_1V2_PRT_NUM                (* (reg8 *) VRef_1V2__PRT) 
/* Connect to Analog Globals */                                                  
#define VRef_1V2_AG                     (* (reg8 *) VRef_1V2__AG)                       
/* Analog MUX bux enable */
#define VRef_1V2_AMUX                   (* (reg8 *) VRef_1V2__AMUX) 
/* Bidirectional Enable */                                                        
#define VRef_1V2_BIE                    (* (reg8 *) VRef_1V2__BIE)
/* Bit-mask for Aliased Register Access */
#define VRef_1V2_BIT_MASK               (* (reg8 *) VRef_1V2__BIT_MASK)
/* Bypass Enable */
#define VRef_1V2_BYP                    (* (reg8 *) VRef_1V2__BYP)
/* Port wide control signals */                                                   
#define VRef_1V2_CTL                    (* (reg8 *) VRef_1V2__CTL)
/* Drive Modes */
#define VRef_1V2_DM0                    (* (reg8 *) VRef_1V2__DM0) 
#define VRef_1V2_DM1                    (* (reg8 *) VRef_1V2__DM1)
#define VRef_1V2_DM2                    (* (reg8 *) VRef_1V2__DM2) 
/* Input Buffer Disable Override */
#define VRef_1V2_INP_DIS                (* (reg8 *) VRef_1V2__INP_DIS)
/* LCD Common or Segment Drive */
#define VRef_1V2_LCD_COM_SEG            (* (reg8 *) VRef_1V2__LCD_COM_SEG)
/* Enable Segment LCD */
#define VRef_1V2_LCD_EN                 (* (reg8 *) VRef_1V2__LCD_EN)
/* Slew Rate Control */
#define VRef_1V2_SLW                    (* (reg8 *) VRef_1V2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define VRef_1V2_PRTDSI__CAPS_SEL       (* (reg8 *) VRef_1V2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define VRef_1V2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) VRef_1V2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define VRef_1V2_PRTDSI__OE_SEL0        (* (reg8 *) VRef_1V2__PRTDSI__OE_SEL0) 
#define VRef_1V2_PRTDSI__OE_SEL1        (* (reg8 *) VRef_1V2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define VRef_1V2_PRTDSI__OUT_SEL0       (* (reg8 *) VRef_1V2__PRTDSI__OUT_SEL0) 
#define VRef_1V2_PRTDSI__OUT_SEL1       (* (reg8 *) VRef_1V2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define VRef_1V2_PRTDSI__SYNC_OUT       (* (reg8 *) VRef_1V2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(VRef_1V2__SIO_CFG)
    #define VRef_1V2_SIO_HYST_EN        (* (reg8 *) VRef_1V2__SIO_HYST_EN)
    #define VRef_1V2_SIO_REG_HIFREQ     (* (reg8 *) VRef_1V2__SIO_REG_HIFREQ)
    #define VRef_1V2_SIO_CFG            (* (reg8 *) VRef_1V2__SIO_CFG)
    #define VRef_1V2_SIO_DIFF           (* (reg8 *) VRef_1V2__SIO_DIFF)
#endif /* (VRef_1V2__SIO_CFG) */

/* Interrupt Registers */
#if defined(VRef_1V2__INTSTAT)
    #define VRef_1V2_INTSTAT            (* (reg8 *) VRef_1V2__INTSTAT)
    #define VRef_1V2_SNAP               (* (reg8 *) VRef_1V2__SNAP)
    
	#define VRef_1V2_0_INTTYPE_REG 		(* (reg8 *) VRef_1V2__0__INTTYPE)
#endif /* (VRef_1V2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_VRef_1V2_H */


/* [] END OF FILE */
