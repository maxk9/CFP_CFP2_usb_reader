/*******************************************************************************
* File Name: O_ALM.h  
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

#if !defined(CY_PINS_O_ALM_ALIASES_H) /* Pins O_ALM_ALIASES_H */
#define CY_PINS_O_ALM_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define O_ALM_0			(O_ALM__0__PC)
#define O_ALM_0_INTR	((uint16)((uint16)0x0001u << O_ALM__0__SHIFT))

#define O_ALM_1			(O_ALM__1__PC)
#define O_ALM_1_INTR	((uint16)((uint16)0x0001u << O_ALM__1__SHIFT))

#define O_ALM_2			(O_ALM__2__PC)
#define O_ALM_2_INTR	((uint16)((uint16)0x0001u << O_ALM__2__SHIFT))

#define O_ALM_INTR_ALL	 ((uint16)(O_ALM_0_INTR| O_ALM_1_INTR| O_ALM_2_INTR))

#endif /* End Pins O_ALM_ALIASES_H */


/* [] END OF FILE */
