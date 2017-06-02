/*******************************************************************************
* File Name: MDIO_Interface_PM.c
* Version 1.20
*
* Description:
*  This file contains the setup, control and status commands to support
*  component operations in low power mode.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "MDIO_Interface.h"

#if(MDIO_Interface_ADVANCED_MODE)
    #include "MDIO_Interface_REG.h"
#endif /* MDIO_Interface_ADVANCED_MODE */

static MDIO_Interface_BACKUP_STRUCT MDIO_Interface_backup =
{
    /* By default the component and interrupts are disabled */
    MDIO_Interface_DISABLED,
    MDIO_Interface_DISABLED
};


/*******************************************************************************
* Function Name: MDIO_Interface_SaveConfig
********************************************************************************
*
* Summary:
*  Saves MDIO_Interface configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  MDIO_Interface_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void MDIO_Interface_SaveConfig(void) 
{
    MDIO_Interface_backup.interruptState = MDIO_Interface_CONTROL_REG & MDIO_Interface_INT_EN;
}


/*******************************************************************************
* Function Name: MDIO_Interface_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores MDIO_Interface configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  MDIO_Interface_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void MDIO_Interface_RestoreConfig(void) 
{
    #if(MDIO_Interface_ADVANCED_MODE)
        /* Set memory type of each register page */
        MDIO_Interface_MEM_TYPE_REG   = MDIO_Interface_PAGE_MEM_TYPE;
        /* Set data width of each register page */
        MDIO_Interface_PAGE_WIDTH_REG = MDIO_Interface_PAGE_DATA_WIDTH;
    #endif /* MDIO_Interface_ADVANCED_MODE */

    /* Restore interrupt state */
    MDIO_Interface_CONTROL_REG = MDIO_Interface_backup.interruptState;
}


/*******************************************************************************
* Function Name: MDIO_Interface_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves its configuration. Should be called
*  prior to entering low power mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  MDIO_Interface_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void MDIO_Interface_Sleep(void) 
{
    if(MDIO_Interface_DISABLED != (MDIO_Interface_CONTROL_REG & MDIO_Interface_EN))
    {
        MDIO_Interface_backup.enableState = MDIO_Interface_ENABLED;
    }
    else /* Component is disabled */
    {
        MDIO_Interface_backup.enableState = MDIO_Interface_DISABLED;
    }

    /* Save registers configuration */
    MDIO_Interface_SaveConfig();

    /* Stop component */
    MDIO_Interface_Stop();
}


/*******************************************************************************
* Function Name: MDIO_Interface_Wakeup
********************************************************************************
*
* Summary:
*  Enables block's operation and restores its configuration. Should be called
*  after awaking from low power mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  MDIO_Interface_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void MDIO_Interface_Wakeup(void)  
{
    /* Restore registers values */
    MDIO_Interface_RestoreConfig();

    if(MDIO_Interface_DISABLED != MDIO_Interface_backup.enableState)
    {
        /* Enable component's operation */
        MDIO_Interface_Enable();

    } /* Do nothing if component's block was disabled before */
}


/* [] END OF FILE */
