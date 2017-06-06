/*******************************************************************************
* File Name: TMR1.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_TMR1_H)
#define CY_ISR_TMR1_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void TMR1_Start(void);
void TMR1_StartEx(cyisraddress address);
void TMR1_Stop(void);

CY_ISR_PROTO(TMR1_Interrupt);

void TMR1_SetVector(cyisraddress address);
cyisraddress TMR1_GetVector(void);

void TMR1_SetPriority(uint8 priority);
uint8 TMR1_GetPriority(void);

void TMR1_Enable(void);
uint8 TMR1_GetState(void);
void TMR1_Disable(void);

void TMR1_SetPending(void);
void TMR1_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the TMR1 ISR. */
#define TMR1_INTC_VECTOR            ((reg32 *) TMR1__INTC_VECT)

/* Address of the TMR1 ISR priority. */
#define TMR1_INTC_PRIOR             ((reg8 *) TMR1__INTC_PRIOR_REG)

/* Priority of the TMR1 interrupt. */
#define TMR1_INTC_PRIOR_NUMBER      TMR1__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable TMR1 interrupt. */
#define TMR1_INTC_SET_EN            ((reg32 *) TMR1__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the TMR1 interrupt. */
#define TMR1_INTC_CLR_EN            ((reg32 *) TMR1__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the TMR1 interrupt state to pending. */
#define TMR1_INTC_SET_PD            ((reg32 *) TMR1__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the TMR1 interrupt. */
#define TMR1_INTC_CLR_PD            ((reg32 *) TMR1__INTC_CLR_PD_REG)


#endif /* CY_ISR_TMR1_H */


/* [] END OF FILE */
