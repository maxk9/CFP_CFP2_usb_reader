/*******************************************************************************
* File Name: MDIO_S.h  
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

#if !defined(CY_PINS_MDIO_S_H) /* Pins MDIO_S_H */
#define CY_PINS_MDIO_S_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "MDIO_S_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 MDIO_S__PORT == 15 && ((MDIO_S__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    MDIO_S_Write(uint8 value);
void    MDIO_S_SetDriveMode(uint8 mode);
uint8   MDIO_S_ReadDataReg(void);
uint8   MDIO_S_Read(void);
void    MDIO_S_SetInterruptMode(uint16 position, uint16 mode);
uint8   MDIO_S_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the MDIO_S_SetDriveMode() function.
     *  @{
     */
        #define MDIO_S_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define MDIO_S_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define MDIO_S_DM_RES_UP          PIN_DM_RES_UP
        #define MDIO_S_DM_RES_DWN         PIN_DM_RES_DWN
        #define MDIO_S_DM_OD_LO           PIN_DM_OD_LO
        #define MDIO_S_DM_OD_HI           PIN_DM_OD_HI
        #define MDIO_S_DM_STRONG          PIN_DM_STRONG
        #define MDIO_S_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define MDIO_S_MASK               MDIO_S__MASK
#define MDIO_S_SHIFT              MDIO_S__SHIFT
#define MDIO_S_WIDTH              1u

/* Interrupt constants */
#if defined(MDIO_S__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in MDIO_S_SetInterruptMode() function.
     *  @{
     */
        #define MDIO_S_INTR_NONE      (uint16)(0x0000u)
        #define MDIO_S_INTR_RISING    (uint16)(0x0001u)
        #define MDIO_S_INTR_FALLING   (uint16)(0x0002u)
        #define MDIO_S_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define MDIO_S_INTR_MASK      (0x01u) 
#endif /* (MDIO_S__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MDIO_S_PS                     (* (reg8 *) MDIO_S__PS)
/* Data Register */
#define MDIO_S_DR                     (* (reg8 *) MDIO_S__DR)
/* Port Number */
#define MDIO_S_PRT_NUM                (* (reg8 *) MDIO_S__PRT) 
/* Connect to Analog Globals */                                                  
#define MDIO_S_AG                     (* (reg8 *) MDIO_S__AG)                       
/* Analog MUX bux enable */
#define MDIO_S_AMUX                   (* (reg8 *) MDIO_S__AMUX) 
/* Bidirectional Enable */                                                        
#define MDIO_S_BIE                    (* (reg8 *) MDIO_S__BIE)
/* Bit-mask for Aliased Register Access */
#define MDIO_S_BIT_MASK               (* (reg8 *) MDIO_S__BIT_MASK)
/* Bypass Enable */
#define MDIO_S_BYP                    (* (reg8 *) MDIO_S__BYP)
/* Port wide control signals */                                                   
#define MDIO_S_CTL                    (* (reg8 *) MDIO_S__CTL)
/* Drive Modes */
#define MDIO_S_DM0                    (* (reg8 *) MDIO_S__DM0) 
#define MDIO_S_DM1                    (* (reg8 *) MDIO_S__DM1)
#define MDIO_S_DM2                    (* (reg8 *) MDIO_S__DM2) 
/* Input Buffer Disable Override */
#define MDIO_S_INP_DIS                (* (reg8 *) MDIO_S__INP_DIS)
/* LCD Common or Segment Drive */
#define MDIO_S_LCD_COM_SEG            (* (reg8 *) MDIO_S__LCD_COM_SEG)
/* Enable Segment LCD */
#define MDIO_S_LCD_EN                 (* (reg8 *) MDIO_S__LCD_EN)
/* Slew Rate Control */
#define MDIO_S_SLW                    (* (reg8 *) MDIO_S__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define MDIO_S_PRTDSI__CAPS_SEL       (* (reg8 *) MDIO_S__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define MDIO_S_PRTDSI__DBL_SYNC_IN    (* (reg8 *) MDIO_S__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define MDIO_S_PRTDSI__OE_SEL0        (* (reg8 *) MDIO_S__PRTDSI__OE_SEL0) 
#define MDIO_S_PRTDSI__OE_SEL1        (* (reg8 *) MDIO_S__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define MDIO_S_PRTDSI__OUT_SEL0       (* (reg8 *) MDIO_S__PRTDSI__OUT_SEL0) 
#define MDIO_S_PRTDSI__OUT_SEL1       (* (reg8 *) MDIO_S__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define MDIO_S_PRTDSI__SYNC_OUT       (* (reg8 *) MDIO_S__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(MDIO_S__SIO_CFG)
    #define MDIO_S_SIO_HYST_EN        (* (reg8 *) MDIO_S__SIO_HYST_EN)
    #define MDIO_S_SIO_REG_HIFREQ     (* (reg8 *) MDIO_S__SIO_REG_HIFREQ)
    #define MDIO_S_SIO_CFG            (* (reg8 *) MDIO_S__SIO_CFG)
    #define MDIO_S_SIO_DIFF           (* (reg8 *) MDIO_S__SIO_DIFF)
#endif /* (MDIO_S__SIO_CFG) */

/* Interrupt Registers */
#if defined(MDIO_S__INTSTAT)
    #define MDIO_S_INTSTAT            (* (reg8 *) MDIO_S__INTSTAT)
    #define MDIO_S_SNAP               (* (reg8 *) MDIO_S__SNAP)
    
	#define MDIO_S_0_INTTYPE_REG 		(* (reg8 *) MDIO_S__0__INTTYPE)
#endif /* (MDIO_S__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_MDIO_S_H */


/* [] END OF FILE */
