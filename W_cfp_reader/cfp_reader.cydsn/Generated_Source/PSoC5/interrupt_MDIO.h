/*******************************************************************************
* File Name: interrupt_MDIO.h  
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

#if !defined(CY_PINS_interrupt_MDIO_H) /* Pins interrupt_MDIO_H */
#define CY_PINS_interrupt_MDIO_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "interrupt_MDIO_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 interrupt_MDIO__PORT == 15 && ((interrupt_MDIO__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    interrupt_MDIO_Write(uint8 value);
void    interrupt_MDIO_SetDriveMode(uint8 mode);
uint8   interrupt_MDIO_ReadDataReg(void);
uint8   interrupt_MDIO_Read(void);
void    interrupt_MDIO_SetInterruptMode(uint16 position, uint16 mode);
uint8   interrupt_MDIO_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the interrupt_MDIO_SetDriveMode() function.
     *  @{
     */
        #define interrupt_MDIO_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define interrupt_MDIO_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define interrupt_MDIO_DM_RES_UP          PIN_DM_RES_UP
        #define interrupt_MDIO_DM_RES_DWN         PIN_DM_RES_DWN
        #define interrupt_MDIO_DM_OD_LO           PIN_DM_OD_LO
        #define interrupt_MDIO_DM_OD_HI           PIN_DM_OD_HI
        #define interrupt_MDIO_DM_STRONG          PIN_DM_STRONG
        #define interrupt_MDIO_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define interrupt_MDIO_MASK               interrupt_MDIO__MASK
#define interrupt_MDIO_SHIFT              interrupt_MDIO__SHIFT
#define interrupt_MDIO_WIDTH              1u

/* Interrupt constants */
#if defined(interrupt_MDIO__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in interrupt_MDIO_SetInterruptMode() function.
     *  @{
     */
        #define interrupt_MDIO_INTR_NONE      (uint16)(0x0000u)
        #define interrupt_MDIO_INTR_RISING    (uint16)(0x0001u)
        #define interrupt_MDIO_INTR_FALLING   (uint16)(0x0002u)
        #define interrupt_MDIO_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define interrupt_MDIO_INTR_MASK      (0x01u) 
#endif /* (interrupt_MDIO__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define interrupt_MDIO_PS                     (* (reg8 *) interrupt_MDIO__PS)
/* Data Register */
#define interrupt_MDIO_DR                     (* (reg8 *) interrupt_MDIO__DR)
/* Port Number */
#define interrupt_MDIO_PRT_NUM                (* (reg8 *) interrupt_MDIO__PRT) 
/* Connect to Analog Globals */                                                  
#define interrupt_MDIO_AG                     (* (reg8 *) interrupt_MDIO__AG)                       
/* Analog MUX bux enable */
#define interrupt_MDIO_AMUX                   (* (reg8 *) interrupt_MDIO__AMUX) 
/* Bidirectional Enable */                                                        
#define interrupt_MDIO_BIE                    (* (reg8 *) interrupt_MDIO__BIE)
/* Bit-mask for Aliased Register Access */
#define interrupt_MDIO_BIT_MASK               (* (reg8 *) interrupt_MDIO__BIT_MASK)
/* Bypass Enable */
#define interrupt_MDIO_BYP                    (* (reg8 *) interrupt_MDIO__BYP)
/* Port wide control signals */                                                   
#define interrupt_MDIO_CTL                    (* (reg8 *) interrupt_MDIO__CTL)
/* Drive Modes */
#define interrupt_MDIO_DM0                    (* (reg8 *) interrupt_MDIO__DM0) 
#define interrupt_MDIO_DM1                    (* (reg8 *) interrupt_MDIO__DM1)
#define interrupt_MDIO_DM2                    (* (reg8 *) interrupt_MDIO__DM2) 
/* Input Buffer Disable Override */
#define interrupt_MDIO_INP_DIS                (* (reg8 *) interrupt_MDIO__INP_DIS)
/* LCD Common or Segment Drive */
#define interrupt_MDIO_LCD_COM_SEG            (* (reg8 *) interrupt_MDIO__LCD_COM_SEG)
/* Enable Segment LCD */
#define interrupt_MDIO_LCD_EN                 (* (reg8 *) interrupt_MDIO__LCD_EN)
/* Slew Rate Control */
#define interrupt_MDIO_SLW                    (* (reg8 *) interrupt_MDIO__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define interrupt_MDIO_PRTDSI__CAPS_SEL       (* (reg8 *) interrupt_MDIO__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define interrupt_MDIO_PRTDSI__DBL_SYNC_IN    (* (reg8 *) interrupt_MDIO__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define interrupt_MDIO_PRTDSI__OE_SEL0        (* (reg8 *) interrupt_MDIO__PRTDSI__OE_SEL0) 
#define interrupt_MDIO_PRTDSI__OE_SEL1        (* (reg8 *) interrupt_MDIO__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define interrupt_MDIO_PRTDSI__OUT_SEL0       (* (reg8 *) interrupt_MDIO__PRTDSI__OUT_SEL0) 
#define interrupt_MDIO_PRTDSI__OUT_SEL1       (* (reg8 *) interrupt_MDIO__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define interrupt_MDIO_PRTDSI__SYNC_OUT       (* (reg8 *) interrupt_MDIO__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(interrupt_MDIO__SIO_CFG)
    #define interrupt_MDIO_SIO_HYST_EN        (* (reg8 *) interrupt_MDIO__SIO_HYST_EN)
    #define interrupt_MDIO_SIO_REG_HIFREQ     (* (reg8 *) interrupt_MDIO__SIO_REG_HIFREQ)
    #define interrupt_MDIO_SIO_CFG            (* (reg8 *) interrupt_MDIO__SIO_CFG)
    #define interrupt_MDIO_SIO_DIFF           (* (reg8 *) interrupt_MDIO__SIO_DIFF)
#endif /* (interrupt_MDIO__SIO_CFG) */

/* Interrupt Registers */
#if defined(interrupt_MDIO__INTSTAT)
    #define interrupt_MDIO_INTSTAT            (* (reg8 *) interrupt_MDIO__INTSTAT)
    #define interrupt_MDIO_SNAP               (* (reg8 *) interrupt_MDIO__SNAP)
    
	#define interrupt_MDIO_0_INTTYPE_REG 		(* (reg8 *) interrupt_MDIO__0__INTTYPE)
#endif /* (interrupt_MDIO__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_interrupt_MDIO_H */


/* [] END OF FILE */
