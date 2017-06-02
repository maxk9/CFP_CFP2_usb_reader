/*******************************************************************************
* File Name: I_PRG_CNTL.h  
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

#if !defined(CY_PINS_I_PRG_CNTL_H) /* Pins I_PRG_CNTL_H */
#define CY_PINS_I_PRG_CNTL_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "I_PRG_CNTL_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 I_PRG_CNTL__PORT == 15 && ((I_PRG_CNTL__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    I_PRG_CNTL_Write(uint8 value);
void    I_PRG_CNTL_SetDriveMode(uint8 mode);
uint8   I_PRG_CNTL_ReadDataReg(void);
uint8   I_PRG_CNTL_Read(void);
void    I_PRG_CNTL_SetInterruptMode(uint16 position, uint16 mode);
uint8   I_PRG_CNTL_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the I_PRG_CNTL_SetDriveMode() function.
     *  @{
     */
        #define I_PRG_CNTL_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define I_PRG_CNTL_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define I_PRG_CNTL_DM_RES_UP          PIN_DM_RES_UP
        #define I_PRG_CNTL_DM_RES_DWN         PIN_DM_RES_DWN
        #define I_PRG_CNTL_DM_OD_LO           PIN_DM_OD_LO
        #define I_PRG_CNTL_DM_OD_HI           PIN_DM_OD_HI
        #define I_PRG_CNTL_DM_STRONG          PIN_DM_STRONG
        #define I_PRG_CNTL_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define I_PRG_CNTL_MASK               I_PRG_CNTL__MASK
#define I_PRG_CNTL_SHIFT              I_PRG_CNTL__SHIFT
#define I_PRG_CNTL_WIDTH              3u

/* Interrupt constants */
#if defined(I_PRG_CNTL__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in I_PRG_CNTL_SetInterruptMode() function.
     *  @{
     */
        #define I_PRG_CNTL_INTR_NONE      (uint16)(0x0000u)
        #define I_PRG_CNTL_INTR_RISING    (uint16)(0x0001u)
        #define I_PRG_CNTL_INTR_FALLING   (uint16)(0x0002u)
        #define I_PRG_CNTL_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define I_PRG_CNTL_INTR_MASK      (0x01u) 
#endif /* (I_PRG_CNTL__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define I_PRG_CNTL_PS                     (* (reg8 *) I_PRG_CNTL__PS)
/* Data Register */
#define I_PRG_CNTL_DR                     (* (reg8 *) I_PRG_CNTL__DR)
/* Port Number */
#define I_PRG_CNTL_PRT_NUM                (* (reg8 *) I_PRG_CNTL__PRT) 
/* Connect to Analog Globals */                                                  
#define I_PRG_CNTL_AG                     (* (reg8 *) I_PRG_CNTL__AG)                       
/* Analog MUX bux enable */
#define I_PRG_CNTL_AMUX                   (* (reg8 *) I_PRG_CNTL__AMUX) 
/* Bidirectional Enable */                                                        
#define I_PRG_CNTL_BIE                    (* (reg8 *) I_PRG_CNTL__BIE)
/* Bit-mask for Aliased Register Access */
#define I_PRG_CNTL_BIT_MASK               (* (reg8 *) I_PRG_CNTL__BIT_MASK)
/* Bypass Enable */
#define I_PRG_CNTL_BYP                    (* (reg8 *) I_PRG_CNTL__BYP)
/* Port wide control signals */                                                   
#define I_PRG_CNTL_CTL                    (* (reg8 *) I_PRG_CNTL__CTL)
/* Drive Modes */
#define I_PRG_CNTL_DM0                    (* (reg8 *) I_PRG_CNTL__DM0) 
#define I_PRG_CNTL_DM1                    (* (reg8 *) I_PRG_CNTL__DM1)
#define I_PRG_CNTL_DM2                    (* (reg8 *) I_PRG_CNTL__DM2) 
/* Input Buffer Disable Override */
#define I_PRG_CNTL_INP_DIS                (* (reg8 *) I_PRG_CNTL__INP_DIS)
/* LCD Common or Segment Drive */
#define I_PRG_CNTL_LCD_COM_SEG            (* (reg8 *) I_PRG_CNTL__LCD_COM_SEG)
/* Enable Segment LCD */
#define I_PRG_CNTL_LCD_EN                 (* (reg8 *) I_PRG_CNTL__LCD_EN)
/* Slew Rate Control */
#define I_PRG_CNTL_SLW                    (* (reg8 *) I_PRG_CNTL__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define I_PRG_CNTL_PRTDSI__CAPS_SEL       (* (reg8 *) I_PRG_CNTL__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define I_PRG_CNTL_PRTDSI__DBL_SYNC_IN    (* (reg8 *) I_PRG_CNTL__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define I_PRG_CNTL_PRTDSI__OE_SEL0        (* (reg8 *) I_PRG_CNTL__PRTDSI__OE_SEL0) 
#define I_PRG_CNTL_PRTDSI__OE_SEL1        (* (reg8 *) I_PRG_CNTL__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define I_PRG_CNTL_PRTDSI__OUT_SEL0       (* (reg8 *) I_PRG_CNTL__PRTDSI__OUT_SEL0) 
#define I_PRG_CNTL_PRTDSI__OUT_SEL1       (* (reg8 *) I_PRG_CNTL__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define I_PRG_CNTL_PRTDSI__SYNC_OUT       (* (reg8 *) I_PRG_CNTL__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(I_PRG_CNTL__SIO_CFG)
    #define I_PRG_CNTL_SIO_HYST_EN        (* (reg8 *) I_PRG_CNTL__SIO_HYST_EN)
    #define I_PRG_CNTL_SIO_REG_HIFREQ     (* (reg8 *) I_PRG_CNTL__SIO_REG_HIFREQ)
    #define I_PRG_CNTL_SIO_CFG            (* (reg8 *) I_PRG_CNTL__SIO_CFG)
    #define I_PRG_CNTL_SIO_DIFF           (* (reg8 *) I_PRG_CNTL__SIO_DIFF)
#endif /* (I_PRG_CNTL__SIO_CFG) */

/* Interrupt Registers */
#if defined(I_PRG_CNTL__INTSTAT)
    #define I_PRG_CNTL_INTSTAT            (* (reg8 *) I_PRG_CNTL__INTSTAT)
    #define I_PRG_CNTL_SNAP               (* (reg8 *) I_PRG_CNTL__SNAP)
    
	#define I_PRG_CNTL_0_INTTYPE_REG 		(* (reg8 *) I_PRG_CNTL__0__INTTYPE)
	#define I_PRG_CNTL_1_INTTYPE_REG 		(* (reg8 *) I_PRG_CNTL__1__INTTYPE)
	#define I_PRG_CNTL_2_INTTYPE_REG 		(* (reg8 *) I_PRG_CNTL__2__INTTYPE)
#endif /* (I_PRG_CNTL__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_I_PRG_CNTL_H */


/* [] END OF FILE */
