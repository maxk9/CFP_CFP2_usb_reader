/*******************************************************************************
* File Name: MOD_RX_LOS.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_MOD_RX_LOS_ALIASES_H) /* Pins MOD_RX_LOS_ALIASES_H */
#define CY_PINS_MOD_RX_LOS_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define MOD_RX_LOS_0			(MOD_RX_LOS__0__PC)
#define MOD_RX_LOS_0_INTR	((uint16)((uint16)0x0001u << MOD_RX_LOS__0__SHIFT))

#define MOD_RX_LOS_INTR_ALL	 ((uint16)(MOD_RX_LOS_0_INTR))

#endif /* End Pins MOD_RX_LOS_ALIASES_H */


/* [] END OF FILE */
