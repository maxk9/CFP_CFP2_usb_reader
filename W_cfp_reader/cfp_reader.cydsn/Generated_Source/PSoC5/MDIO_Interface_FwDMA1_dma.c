/***************************************************************************
* File Name: MDIO_Interface_FwDMA1_dma.c  
* Version 1.70
*
*  Description:
*   Provides an API for the DMAC component. The API includes functions
*   for the DMA controller, DMA channels and Transfer Descriptors.
*
*
*   Note:
*     This module requires the developer to finish or fill in the auto
*     generated funcions and setup the dma channel and TD's.
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/
#include <CYLIB.H>
#include <CYDMAC.H>
#include <MDIO_Interface_FwDMA1_dma.H>



/****************************************************************************
* 
* The following defines are available in Cyfitter.h
* 
* 
* 
* MDIO_Interface_FwDMA1__DRQ_CTL_REG
* 
* 
* MDIO_Interface_FwDMA1__DRQ_NUMBER
* 
* Number of TD's used by this channel.
* MDIO_Interface_FwDMA1__NUMBEROF_TDS
* 
* Priority of this channel.
* MDIO_Interface_FwDMA1__PRIORITY
* 
* True if MDIO_Interface_FwDMA1_TERMIN_SEL is used.
* MDIO_Interface_FwDMA1__TERMIN_EN
* 
* TERMIN interrupt line to signal terminate.
* MDIO_Interface_FwDMA1__TERMIN_SEL
* 
* 
* True if MDIO_Interface_FwDMA1_TERMOUT0_SEL is used.
* MDIO_Interface_FwDMA1__TERMOUT0_EN
* 
* 
* TERMOUT0 interrupt line to signal completion.
* MDIO_Interface_FwDMA1__TERMOUT0_SEL
* 
* 
* True if MDIO_Interface_FwDMA1_TERMOUT1_SEL is used.
* MDIO_Interface_FwDMA1__TERMOUT1_EN
* 
* 
* TERMOUT1 interrupt line to signal completion.
* MDIO_Interface_FwDMA1__TERMOUT1_SEL
* 
****************************************************************************/


/* Zero based index of MDIO_Interface_FwDMA1 dma channel */
uint8 MDIO_Interface_FwDMA1_DmaHandle = DMA_INVALID_CHANNEL;

/*********************************************************************
* Function Name: uint8 MDIO_Interface_FwDMA1_DmaInitalize
**********************************************************************
* Summary:
*   Allocates and initialises a channel of the DMAC to be used by the
*   caller.
*
* Parameters:
*   BurstCount.
*       
*       
*   ReqestPerBurst.
*       
*       
*   UpperSrcAddress.
*       
*       
*   UpperDestAddress.
*       
*
* Return:
*   The channel that can be used by the caller for DMA activity.
*   DMA_INVALID_CHANNEL (0xFF) if there are no channels left. 
*
*
*******************************************************************/
uint8 MDIO_Interface_FwDMA1_DmaInitialize(uint8 BurstCount, uint8 ReqestPerBurst, uint16 UpperSrcAddress, uint16 UpperDestAddress) 
{

    /* Allocate a DMA channel. */
    MDIO_Interface_FwDMA1_DmaHandle = (uint8)MDIO_Interface_FwDMA1__DRQ_NUMBER;

    /* Configure the channel. */
    (void)CyDmaChSetConfiguration(MDIO_Interface_FwDMA1_DmaHandle,
                                  BurstCount,
                                  ReqestPerBurst,
                                  (uint8)MDIO_Interface_FwDMA1__TERMOUT0_SEL,
                                  (uint8)MDIO_Interface_FwDMA1__TERMOUT1_SEL,
                                  (uint8)MDIO_Interface_FwDMA1__TERMIN_SEL);

    /* Set the extended address for the transfers */
    (void)CyDmaChSetExtendedAddress(MDIO_Interface_FwDMA1_DmaHandle, UpperSrcAddress, UpperDestAddress);

    /* Set the priority for this channel */
    (void)CyDmaChPriority(MDIO_Interface_FwDMA1_DmaHandle, (uint8)MDIO_Interface_FwDMA1__PRIORITY);
    
    return MDIO_Interface_FwDMA1_DmaHandle;
}

/*********************************************************************
* Function Name: void MDIO_Interface_FwDMA1_DmaRelease
**********************************************************************
* Summary:
*   Frees the channel associated with MDIO_Interface_FwDMA1.
*
*
* Parameters:
*   void.
*
*
*
* Return:
*   void.
*
*******************************************************************/
void MDIO_Interface_FwDMA1_DmaRelease(void) 
{
    /* Disable the channel */
    (void)CyDmaChDisable(MDIO_Interface_FwDMA1_DmaHandle);
}

