/*******************************************************************************
* File Name: MOD_RST.h  
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

#if !defined(CY_PINS_MOD_RST_ALIASES_H) /* Pins MOD_RST_ALIASES_H */
#define CY_PINS_MOD_RST_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define MOD_RST_0			(MOD_RST__0__PC)
#define MOD_RST_0_INTR	((uint16)((uint16)0x0001u << MOD_RST__0__SHIFT))

#define MOD_RST_INTR_ALL	 ((uint16)(MOD_RST_0_INTR))

#endif /* End Pins MOD_RST_ALIASES_H */


/* [] END OF FILE */
