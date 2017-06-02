/*******************************************************************************
* File Name: I_PRG_CNTL.h  
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

#if !defined(CY_PINS_I_PRG_CNTL_ALIASES_H) /* Pins I_PRG_CNTL_ALIASES_H */
#define CY_PINS_I_PRG_CNTL_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define I_PRG_CNTL_0			(I_PRG_CNTL__0__PC)
#define I_PRG_CNTL_0_INTR	((uint16)((uint16)0x0001u << I_PRG_CNTL__0__SHIFT))

#define I_PRG_CNTL_1			(I_PRG_CNTL__1__PC)
#define I_PRG_CNTL_1_INTR	((uint16)((uint16)0x0001u << I_PRG_CNTL__1__SHIFT))

#define I_PRG_CNTL_2			(I_PRG_CNTL__2__PC)
#define I_PRG_CNTL_2_INTR	((uint16)((uint16)0x0001u << I_PRG_CNTL__2__SHIFT))

#define I_PRG_CNTL_INTR_ALL	 ((uint16)(I_PRG_CNTL_0_INTR| I_PRG_CNTL_1_INTR| I_PRG_CNTL_2_INTR))

#endif /* End Pins I_PRG_CNTL_ALIASES_H */


/* [] END OF FILE */
