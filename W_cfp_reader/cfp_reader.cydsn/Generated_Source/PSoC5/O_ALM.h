/*******************************************************************************
* File Name: O_ALM.h  
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

#if !defined(CY_PINS_O_ALM_H) /* Pins O_ALM_H */
#define CY_PINS_O_ALM_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "O_ALM_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 O_ALM__PORT == 15 && ((O_ALM__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    O_ALM_Write(uint8 value);
void    O_ALM_SetDriveMode(uint8 mode);
uint8   O_ALM_ReadDataReg(void);
uint8   O_ALM_Read(void);
void    O_ALM_SetInterruptMode(uint16 position, uint16 mode);
uint8   O_ALM_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the O_ALM_SetDriveMode() function.
     *  @{
     */
        #define O_ALM_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define O_ALM_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define O_ALM_DM_RES_UP          PIN_DM_RES_UP
        #define O_ALM_DM_RES_DWN         PIN_DM_RES_DWN
        #define O_ALM_DM_OD_LO           PIN_DM_OD_LO
        #define O_ALM_DM_OD_HI           PIN_DM_OD_HI
        #define O_ALM_DM_STRONG          PIN_DM_STRONG
        #define O_ALM_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define O_ALM_MASK               O_ALM__MASK
#define O_ALM_SHIFT              O_ALM__SHIFT
#define O_ALM_WIDTH              3u

/* Interrupt constants */
#if defined(O_ALM__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in O_ALM_SetInterruptMode() function.
     *  @{
     */
        #define O_ALM_INTR_NONE      (uint16)(0x0000u)
        #define O_ALM_INTR_RISING    (uint16)(0x0001u)
        #define O_ALM_INTR_FALLING   (uint16)(0x0002u)
        #define O_ALM_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define O_ALM_INTR_MASK      (0x01u) 
#endif /* (O_ALM__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define O_ALM_PS                     (* (reg8 *) O_ALM__PS)
/* Data Register */
#define O_ALM_DR                     (* (reg8 *) O_ALM__DR)
/* Port Number */
#define O_ALM_PRT_NUM                (* (reg8 *) O_ALM__PRT) 
/* Connect to Analog Globals */                                                  
#define O_ALM_AG                     (* (reg8 *) O_ALM__AG)                       
/* Analog MUX bux enable */
#define O_ALM_AMUX                   (* (reg8 *) O_ALM__AMUX) 
/* Bidirectional Enable */                                                        
#define O_ALM_BIE                    (* (reg8 *) O_ALM__BIE)
/* Bit-mask for Aliased Register Access */
#define O_ALM_BIT_MASK               (* (reg8 *) O_ALM__BIT_MASK)
/* Bypass Enable */
#define O_ALM_BYP                    (* (reg8 *) O_ALM__BYP)
/* Port wide control signals */                                                   
#define O_ALM_CTL                    (* (reg8 *) O_ALM__CTL)
/* Drive Modes */
#define O_ALM_DM0                    (* (reg8 *) O_ALM__DM0) 
#define O_ALM_DM1                    (* (reg8 *) O_ALM__DM1)
#define O_ALM_DM2                    (* (reg8 *) O_ALM__DM2) 
/* Input Buffer Disable Override */
#define O_ALM_INP_DIS                (* (reg8 *) O_ALM__INP_DIS)
/* LCD Common or Segment Drive */
#define O_ALM_LCD_COM_SEG            (* (reg8 *) O_ALM__LCD_COM_SEG)
/* Enable Segment LCD */
#define O_ALM_LCD_EN                 (* (reg8 *) O_ALM__LCD_EN)
/* Slew Rate Control */
#define O_ALM_SLW                    (* (reg8 *) O_ALM__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define O_ALM_PRTDSI__CAPS_SEL       (* (reg8 *) O_ALM__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define O_ALM_PRTDSI__DBL_SYNC_IN    (* (reg8 *) O_ALM__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define O_ALM_PRTDSI__OE_SEL0        (* (reg8 *) O_ALM__PRTDSI__OE_SEL0) 
#define O_ALM_PRTDSI__OE_SEL1        (* (reg8 *) O_ALM__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define O_ALM_PRTDSI__OUT_SEL0       (* (reg8 *) O_ALM__PRTDSI__OUT_SEL0) 
#define O_ALM_PRTDSI__OUT_SEL1       (* (reg8 *) O_ALM__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define O_ALM_PRTDSI__SYNC_OUT       (* (reg8 *) O_ALM__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(O_ALM__SIO_CFG)
    #define O_ALM_SIO_HYST_EN        (* (reg8 *) O_ALM__SIO_HYST_EN)
    #define O_ALM_SIO_REG_HIFREQ     (* (reg8 *) O_ALM__SIO_REG_HIFREQ)
    #define O_ALM_SIO_CFG            (* (reg8 *) O_ALM__SIO_CFG)
    #define O_ALM_SIO_DIFF           (* (reg8 *) O_ALM__SIO_DIFF)
#endif /* (O_ALM__SIO_CFG) */

/* Interrupt Registers */
#if defined(O_ALM__INTSTAT)
    #define O_ALM_INTSTAT            (* (reg8 *) O_ALM__INTSTAT)
    #define O_ALM_SNAP               (* (reg8 *) O_ALM__SNAP)
    
	#define O_ALM_0_INTTYPE_REG 		(* (reg8 *) O_ALM__0__INTTYPE)
	#define O_ALM_1_INTTYPE_REG 		(* (reg8 *) O_ALM__1__INTTYPE)
	#define O_ALM_2_INTTYPE_REG 		(* (reg8 *) O_ALM__2__INTTYPE)
#endif /* (O_ALM__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_O_ALM_H */


/* [] END OF FILE */
