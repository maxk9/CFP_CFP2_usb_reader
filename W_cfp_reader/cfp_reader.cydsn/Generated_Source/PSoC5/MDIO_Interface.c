/*******************************************************************************
* File Name: MDIO_Interface.c
* Version 1.20
*
* Description:
*  This file provides the source code to the API for the MDIO Slave component.
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
    #include "MDIO_Interface_StartAddrDMA_dma.h"
    #include "MDIO_Interface_EndAddrDMA_dma.h"
    #include "MDIO_Interface_AddrDMA_dma.h"
    #include "MDIO_Interface_InfoDMA_dma.h"
    #include "MDIO_Interface_RdDMA_dma.h"
    #include "MDIO_Interface_WrDMA_dma.h"
    #include "MDIO_Interface_CfgDMA1_dma.h"
    #include "MDIO_Interface_CfgDMA2_dma.h"
    #include "MDIO_Interface_FwDMA1_dma.h"
    #include "MDIO_Interface_FwDMA2_dma.h"

    /* Start addresses of register spaces */
    static uint16 MDIO_Interface_pageStartAddr[MDIO_Interface_NUMBER_OF_PAGES] =
    {
        0x8000u, 0x8400u, 0x8800u, 0xA000u, 0xA200u, 0xA400u
    };
    /* End addresses of register spaces */
    static uint16 MDIO_Interface_pageEndAddr[MDIO_Interface_NUMBER_OF_PAGES] =
    {
        0x81FFu, 0x84FFu, 0x88FFu, 0xA07Fu, 0xA2FFu, 0xA47Fu
    };

    /* Register page start address DMA */
    static uint8 MDIO_Interface_pageStartAddrDMA_Chan;
    static uint8 MDIO_Interface_pageStartAddr_TD[1u];

    /* Register page end address DMA */
    static uint8 MDIO_Interface_pageEndAddrDMA_Chan;
    static uint8 MDIO_Interface_pageEndAddr_TD[1u];

    /* Register physical memory address DMA */
    static uint8 MDIO_Interface_regAddrDMA_Chan;
    static uint8 MDIO_Interface_regAddrDMA_TD[7u];

    /* Register page info DMA */
    static uint8 MDIO_Interface_pageInfoDMA_Chan;
    static uint8 MDIO_Interface_pageInfoDMA_TD[1u];

    /* Read DMA */
    static uint8 MDIO_Interface_rdDMA_Chan;
    static uint8 MDIO_Interface_rdDMA_TD[1u];

    /* Write DMA */
    static uint8 MDIO_Interface_wrDMA_Chan;
    static uint8 MDIO_Interface_wrDMA_TD[1u];

    /* Register configuration DMA */
    static uint8 MDIO_Interface_cfgDMA1_Chan;
    static uint8 MDIO_Interface_cfgDMA1_TD[1u];
    static uint8 MDIO_Interface_cfgDMA2_Chan;
    static uint8 MDIO_Interface_cfgDMA2_TD[2u];

    /* DMA used for data transfer from APIs */
    static uint8 MDIO_Interface_fwDMA1_Chan;
    static uint8 MDIO_Interface_fwDMA1_TD[1u];
    static uint8 MDIO_Interface_fwDMA2_Chan;
    static uint8 MDIO_Interface_fwDMA2_TD[1u];

    /* List of DMA channels used by component */
    static uint8 MDIO_Interface_dmaChannelList[MDIO_Interface_NUMBER_OF_CHANNELS];

    /* Address list of all register space data and configuration arrays */
    static uint32 MDIO_Interface_pageAddrList[MDIO_Interface_NUMBER_OF_PAGES];
    static uint32 MDIO_Interface_pageInfoList[MDIO_Interface_PAGE_INFO_SIZE];

    /* Function prototype to configure/release DMA */
    static void  MDIO_Interface_DmaInit(void) ;
    static void  MDIO_Interface_DmaEnable(void) ;
    static void  MDIO_Interface_DmaDisable(void) ;
    static uint8 MDIO_Interface_DmaIsComplete(uint8 chMask) ;

#endif /* MDIO_Interface_ADVANCED_MODE */

uint8 MDIO_Interface_initVar = 0u;
static uint8 MDIO_Interface_phyAddress;
static uint8 MDIO_Interface_devAddress;


/*******************************************************************************
* Function Name: MDIO_Interface_Enable
********************************************************************************
*
* Summary:
*  Enables the MDIO Slave hardware.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void MDIO_Interface_Enable(void) 
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    /* Bit counter enabling */
    MDIO_Interface_BCNT_AUX_CTL_REG   |= MDIO_Interface_BCNT_EN;
    CyExitCriticalSection(enableInterrupts);

    #if(MDIO_Interface_ADVANCED_MODE)
        MDIO_Interface_DmaEnable();
    #endif /* MDIO_Interface_ADVANCED_MODE */

    /* Enable interrupts */
    MDIO_Interface_EnableInt();

    /* Enable component hardware */
    MDIO_Interface_CONTROL_REG |= MDIO_Interface_EN;
}


/*******************************************************************************
* Function Name: MDIO_Interface_Init
********************************************************************************
*
* Summary:
*  Initializes the component, sets the physical and device address.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void MDIO_Interface_Init(void) 
{
    #if(MDIO_Interface_ADVANCED_MODE)
        static uint8 MDIO_Interface_dmaInitDone = 0u;
    #endif /* MDIO_Interface_ADVANCED_MODE */
    uint8 enableInterrupts;

    /* Set device address */
    MDIO_Interface_SetDevAddress(MDIO_Interface_INIT_DEVADDR);
    /* Set physical address */
    MDIO_Interface_UpdatePhyAddress();

    enableInterrupts = CyEnterCriticalSection();
    /* Set Read FIFO in Single Buffer Mode */
    MDIO_Interface_FP_AUX_CTL0_REG |= MDIO_Interface_F0_CLEAR;
    MDIO_Interface_FP_AUX_CTL1_REG |= MDIO_Interface_F0_CLEAR;
    CyExitCriticalSection(enableInterrupts);

    /* Set bit counter period */
    MDIO_Interface_BCNT_PERIOD_REG = MDIO_Interface_BCNT_PER;

    #if(MDIO_Interface_ADVANCED_MODE)

        /* Set size of register page info */
        CY_SET_REG16(MDIO_Interface_INFO_INC_PTR, MDIO_Interface_PAGE_INFO_INC);
        /* Set lower 16-bit address of page info array */
        CY_SET_REG16(MDIO_Interface_INFO_BASE_PTR, LO16((uint32)MDIO_Interface_pageInfoList));
        /* Set memory type of each register page */
        MDIO_Interface_MEM_TYPE_REG   = MDIO_Interface_PAGE_MEM_TYPE;
        /* Set data width of each register page */
        MDIO_Interface_PAGE_WIDTH_REG = MDIO_Interface_PAGE_DATA_WIDTH;
        /* Initialize Address analyzer DMAs */
        if(0u == MDIO_Interface_dmaInitDone)
        {
            MDIO_Interface_DmaInit();
            MDIO_Interface_dmaInitDone = 1u;
        }

    #endif /* MDIO_Interface_ADVANCED_MODE */
}


/*******************************************************************************
* Function Name: MDIO_Interface_Start
********************************************************************************
*
* Summary:
*  Enables the component. Calls the Init() API if the component has not been
*  initialized before. Calls the Enable() API.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  MDIO_Interface_initVar - used to check initial configuration, modified on
*  first function call.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void MDIO_Interface_Start(void) 
{
    if(0u == MDIO_Interface_initVar)
    {
        MDIO_Interface_Init();
        MDIO_Interface_initVar = 1u;
    }

    MDIO_Interface_Enable();
}


/*******************************************************************************
* Function Name: MDIO_Interface_Stop
********************************************************************************
*
* Summary:
*  Disables the MDIO interface.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void MDIO_Interface_Stop(void) 
{
    uint8 enableInterrupts;

    MDIO_Interface_CONTROL_REG &= (uint8) ~MDIO_Interface_EN;

    /* Disable interrupt terminal */
    MDIO_Interface_DisableInt();

    /* Disable Address analyzer DMAs */
    #if(MDIO_Interface_ADVANCED_MODE)
        MDIO_Interface_DmaDisable();
    #endif /* MDIO_Interface_ADVANCED_MODE */

    enableInterrupts = CyEnterCriticalSection();
    /* Disable Bit counter */
    MDIO_Interface_BCNT_AUX_CTL_REG  &= (uint8) ~MDIO_Interface_BCNT_EN;

    #if(MDIO_Interface_ADVANCED_MODE)
        /* Clear start and end address FIFO buffers */
        MDIO_Interface_AC_AUX_CTL0_REG |= MDIO_Interface_FX_CLEAR;
        MDIO_Interface_AC_AUX_CTL0_REG &= (uint8) ~MDIO_Interface_FX_CLEAR;
        MDIO_Interface_AC_AUX_CTL1_REG |= MDIO_Interface_FX_CLEAR;
        MDIO_Interface_AC_AUX_CTL1_REG &= (uint8) ~MDIO_Interface_FX_CLEAR;
    #endif /* MDIO_Interface_ADVANCED_MODE */

    /* Clear Write FIFO buffer */
    MDIO_Interface_FP_AUX_CTL0_REG |= MDIO_Interface_F1_CLEAR;
    MDIO_Interface_FP_AUX_CTL0_REG &= (uint8) ~MDIO_Interface_F1_CLEAR;
    MDIO_Interface_FP_AUX_CTL1_REG |= MDIO_Interface_F1_CLEAR;
    MDIO_Interface_FP_AUX_CTL1_REG &= (uint8) ~MDIO_Interface_F1_CLEAR;
    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: MDIO_Interface_EnableInt
********************************************************************************
*
* Summary:
*  Enables the terminal output interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void MDIO_Interface_EnableInt(void) 
{
    MDIO_Interface_CONTROL_REG |= MDIO_Interface_INT_EN;
}


/*******************************************************************************
* Function Name: MDIO_Interface_DisableInt
********************************************************************************
*
* Summary:
*  Enables the terminal output interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void MDIO_Interface_DisableInt(void) 
{
    MDIO_Interface_CONTROL_REG &= (uint8) ~MDIO_Interface_INT_EN;
}


/*******************************************************************************
* Function Name: MDIO_Interface_SetDevAddress
********************************************************************************
* Summary:
*  Sets the 5-bit device address for the MDIO slave.
*
* Parameters:
*  Byte containing the constant for the MDIO device address.
*   MDIO_Interface_PMA_PMD
*   MDIO_Interface_WIS
*   MDIO_Interface_PCS
*   MDIO_Interface_PHY_XS
*   MDIO_Interface_DTE_XS
*
* Return:
*  None.
*
********************************************************************************/
void MDIO_Interface_SetDevAddress(uint8 devAddr) 
{
    /* Update the address pattern with the device address */
    CY_SET_REG16(MDIO_Interface_ADDR_PTRN_PTR, MDIO_Interface_ADDR_PATTERN |
                 (uint16)((uint16)MDIO_Interface_phyAddress << MDIO_Interface_PHYADDR_POS) | devAddr);
    MDIO_Interface_devAddress = devAddr;
}


/*******************************************************************************
* Function Name: MDIO_Interface_SetPhyAddress
********************************************************************************
* Summary:
*  Sets the 5-bit or 3-bit physical address for the MDIO slave device. When the
*  address is 3-bit, the 2 MSB bits of the physical address from an MDIO frame
*  are ignored.
*
* Parameters:
*  The physical address for the MDIO Slave.
*
* Return:
*  None.
*
********************************************************************************/
void MDIO_Interface_SetPhyAddress(uint8 phyAddr) 
{
    phyAddr &= MDIO_Interface_PHYADDR_MASK;

    /* Update the address pattern with the physical address */
    CY_SET_REG16(MDIO_Interface_ADDR_PTRN_PTR, MDIO_Interface_ADDR_PATTERN |
                 (uint16)((uint16) phyAddr << MDIO_Interface_PHYADDR_POS) | MDIO_Interface_devAddress);

    MDIO_Interface_phyAddress = phyAddr;
}


/*******************************************************************************
* Function Name: MDIO_Interface_UpdatePhyAddress
********************************************************************************
* Summary:
*  Updates the physical address based on the current phy_addr[4:0] input.
*  If the physical address mode is configured to firmware, the physical address
*  is set equal to the default value from the customizer.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  None.
*
********************************************************************************/
void MDIO_Interface_UpdatePhyAddress(void) 
{
    #if(MDIO_Interface_PHYADDR_HARDWARE)
        MDIO_Interface_SetPhyAddress(MDIO_Interface_PHYADDR_REG);
    #else
        MDIO_Interface_SetPhyAddress(MDIO_Interface_INIT_PHYADDR);
    #endif /* MDIO_Interface_PHYADDR_HARDWARE */
}

#if (MDIO_Interface_BASIC_MODE)


    /***************************************************************************
    * Function Name: MDIO_Interface_PutData
    ****************************************************************************
    * Summary:
    *  Writes the given data in the internal FIFO, which will be transmitted to
    *  the host in the next frame.
    *
    * Parameters:
    *  Data to be transmitted.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  None.
    *
    ****************************************************************************/
    void MDIO_Interface_PutData(uint16 regData) 
    {
        CY_SET_REG16(MDIO_Interface_FP_FIFO0_PTR, regData);
    }


    /***************************************************************************
    * Function Name: MDIO_Interface_ProcessFrame
    ****************************************************************************
    * Summary:
    *  Process and parse the the last frame received from the host.
    *
    * Parameters:
    *  opCode: operational code.
    *  regData: register data received.
    *
    * Return:
    *  None.
    *
    ****************************************************************************/
    void MDIO_Interface_ProcessFrame(uint8 * opCode, uint16 * regData)
                                                                     
    {
        uint16 controlBits;

        /* Get control bits */
        controlBits = CY_GET_REG16(MDIO_Interface_FP_FIFO1_PTR);

        /* Get data */
        *regData = CY_GET_REG16(MDIO_Interface_FP_FIFO1_PTR);

        /* Parse Control bits to obtain operation code */
        *opCode = (((uint8)(controlBits >> MDIO_Interface_OPCODE_POS)) & MDIO_Interface_OPCODE_MASK);
    }

#endif /* MDIO_Interface_BASIC_MODE */

#if(MDIO_Interface_ADVANCED_MODE)

    /***************************************************************************
    * Function Name: MDIO_Interface_GetAddress
    ****************************************************************************
    * Summary:
    *  Returns the last address written by the MDIO host.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  16-bit address.
    *
    ***************************************************************************/
    uint16 MDIO_Interface_GetAddress(void)    
    {
        return(CY_GET_REG16(MDIO_Interface_LAST_ADDR_PTR));
    }


    /***************************************************************************
    * Function Name: MDIO_Interface_GetData
    ****************************************************************************
    * Summary:
    *  Returns numWords values starting from the given address. If any address
    *  does not belong to the allocated register space, it returns an error.
    *
    * Parameters:
    *  address : address to be accessed.
    *  regData : array with the read data.
    *  numWords: number of words to be read.
    *
    * Return:
    *  CYRET_SUCCESS  : Operation is successful.
    *  CYRET_BAD_PARAM: One or more invalid parameters.
    *  CYRET_TIMEOUT  : Operation timed out.
    *
    * Side Effects:
    *  The word count of zero will be interpreted as a request for indefinite
    *  transfer.
    *
    ****************************************************************************/
    uint8 MDIO_Interface_GetData(uint16 address, const uint16 * regData, uint16 numWords)
                                                            
    {
        uint8  result = CYRET_BAD_PARAM;
        uint8  i;
        uint16 idx;
        uint32 memAddr;

        for(i = 0u; (i < MDIO_Interface_NUMBER_OF_PAGES) && (result != CYRET_SUCCESS); i++)
        {
            /* Check if address belongs to one of register spaces */
            if((address >= MDIO_Interface_pageStartAddr[i]) && (address <= MDIO_Interface_pageEndAddr[i]))
            {
                /* Check whether there is enough data to be read */
                #if(!MDIO_Interface_ALL_PAGES_16BIT)
                    #if(!MDIO_Interface_ALL_PAGES_8BIT)
                    if(MDIO_Interface_REG_SPACE_IS_8BIT(i))
                    #endif /* !MDIO_Interface_ALL_PAGES_8BIT */
                    {
                        numWords += numWords;
                    }
                #endif /* !MDIO_Interface_ALL_PAGES_16BIT */

                if(numWords <= ((MDIO_Interface_pageEndAddr[i] - address) + 1u))
                {
                    idx = address - MDIO_Interface_pageStartAddr[i];

                    #if(!MDIO_Interface_ALL_PAGES_8BIT)
                        #if(!MDIO_Interface_ALL_PAGES_16BIT)
                        if(MDIO_Interface_REG_SPACE_IS_16BIT(i))
                        #endif /* !MDIO_Interface_ALL_PAGES_16BIT */
                        {
                            /* If 16-bit space is accessed */
                            idx += idx;
                            numWords += numWords; /* TD_SIZE is expected in bytes */
                        }
                    #endif /* !MDIO_Interface_ALL_PAGES_8BIT */

                    memAddr = MDIO_Interface_pageAddrList[i] + idx;

                    /* Configure DMA transfer. Return values are ignored because
                    * channel number and TD handle are allocated once during the
                    * component initialization procedure and do not change in run time.
                    */
                    MDIO_Interface_fwDMA1_Chan = MDIO_Interface_FwDMA1_DmaInitialize(
                        MDIO_Interface_FW_DMA_BYTES_PER_BURST, MDIO_Interface_FW_DMA_REQUEST_PER_BURST,
                        HI16(memAddr), HI16(CYDEV_SRAM_BASE));
                    (void) CyDmaTdSetConfiguration(MDIO_Interface_fwDMA1_TD[0u], numWords,
                        DMA_INVALID_TD, MDIO_Interface_FW_DMA1_CFG);
                    (void) CyDmaTdSetAddress(MDIO_Interface_fwDMA1_TD[0u], LO16(memAddr), LO16((uint32)regData));

                    /* Clear DMA status in case if previous transfer failed */
                    MDIO_Interface_CLEAR_FW_DMA_STATUS;

                    /* Trigger DMA and wait for completion */
                    (void) CyDmaChSetRequest(MDIO_Interface_fwDMA1_Chan, CPU_REQ);
                    result = MDIO_Interface_DmaIsComplete(MDIO_Interface_FW_DMA1_MASK);
                }
            }
        }
        return(result);
    }

    #if(!MDIO_Interface_ALL_PAGES_IN_FLASH)

        /***************************************************************************
        * Function Name: MDIO_Interface_SetData
        ****************************************************************************
        * Summary:
        *  Writes numWords values starting from the given address. If any address
        *  does not belong to the allocated register space, it returns an error.
        *
        * Parameters:
        *  address : address to be accessed.
        *  regData : array with the written data.
        *  numWords: number of words to be written.
        *
        * Return:
        *  CYRET_SUCCESS  : Operation is successful.
        *  CYRET_BAD_PARAM: One or more invalid parameters.
        *  CYRET_TIMEOUT  : Operation timed out.
        *
        * Side Effects:
        *  The word count of zero will be interpreted as a request for indefinite
        *  transfer.
        *
        ***************************************************************************/
        uint8 MDIO_Interface_SetData(uint16 address, const uint16 * regData, uint16 numWords)
                                                                
        {
            uint8 result = CYRET_BAD_PARAM;
            uint8 i;
            uint16 idx;
            uint32 memAddr;

            for(i = 0u; (i < MDIO_Interface_NUMBER_OF_PAGES) && (result != CYRET_SUCCESS); i++)
            {
                /* Check if address belongs to one of register spaces */
                if((address >= MDIO_Interface_pageStartAddr[i]) && (address <= MDIO_Interface_pageEndAddr[i]))
                {
                    #if(!MDIO_Interface_ALL_PAGES_IN_SRAM)
                    /* Check whether current space is writeable */
                    if(MDIO_Interface_REG_SPACE_IS_SRAM(i))
                    #endif /* !MDIO_Interface_ALL_PAGES_IN_SRAM */
                    {
                        /* Check whether there is enough space to be written */
                        #if(!MDIO_Interface_ALL_PAGES_16BIT)
                            #if(!MDIO_Interface_ALL_PAGES_8BIT)
                            if(MDIO_Interface_REG_SPACE_IS_8BIT(i))
                            #endif /* !MDIO_Interface_ALL_PAGES_8BIT */
                            {
                                numWords += numWords;
                            }
                        #endif /* !MDIO_Interface_ALL_PAGES_16BIT */

                        if(numWords <= ((MDIO_Interface_pageEndAddr[i] - address) + 1u))
                        {
                            idx = address - MDIO_Interface_pageStartAddr[i];

                            #if(!MDIO_Interface_ALL_PAGES_8BIT)
                                #if(!MDIO_Interface_ALL_PAGES_16BIT)
                                if(MDIO_Interface_REG_SPACE_IS_16BIT(i))
                                #endif /* !MDIO_Interface_ALL_PAGES_16BIT */
                                {
                                    /* If a 16-bit space is accessed */
                                    idx += idx;
                                    numWords += numWords; /* TD_SIZE is expected in bytes */
                                }
                            #endif /* !MDIO_Interface_ALL_PAGES_8BIT */

                            memAddr = MDIO_Interface_pageAddrList[i] + idx;

                            /* Configure DMA transfer. Return values are ignored because
                            * channel number and TD handle are allocated once during the
                            * component initialization procedure and do not change in run time.
                            */
                            MDIO_Interface_fwDMA1_Chan = MDIO_Interface_FwDMA1_DmaInitialize(
                                MDIO_Interface_FW_DMA_BYTES_PER_BURST, MDIO_Interface_FW_DMA_REQUEST_PER_BURST,
                                HI16(CYDEV_SRAM_BASE), HI16(memAddr));

                            (void) CyDmaTdSetConfiguration(MDIO_Interface_fwDMA1_TD[0u], numWords,
                                DMA_INVALID_TD, MDIO_Interface_FW_DMA1_CFG);
                            (void) CyDmaTdSetAddress(MDIO_Interface_fwDMA1_TD[0u], LO16((uint32)regData),
                                                                                     LO16(memAddr));

                            /* Clear DMA status in case if previous transfer failed */
                            MDIO_Interface_CLEAR_FW_DMA_STATUS;

                            /* Trigger DMA and wait for completion */
                            (void) CyDmaChSetRequest(MDIO_Interface_fwDMA1_Chan, CPU_REQ);
                            result = MDIO_Interface_DmaIsComplete(MDIO_Interface_FW_DMA1_MASK);
                        }
                    }
                }
            }
            return(result);
        }


        /***************************************************************************
        * Function Name: MDIO_Interface_SetBits
        ****************************************************************************
        * Summary:
        *  Set at the given address only the given bits. The operation should be an
        *  OR write.
        *
        * Parameters:
        *  address: address to be accessed.
        *  regBits: bits to be set.
        *
        * Return:
        *  CYRET_SUCCESS  : Operation is successful.
        *  CYRET_BAD_PARAM: One or more invalid parameters.
        *  CYRET_TIMEOUT  : Operation timed out.
        *
        ***************************************************************************/
        uint8 MDIO_Interface_SetBits(uint16 address, uint16 regBits) 
        {
            uint8  result = CYRET_BAD_PARAM;
            uint8  i;
            uint16 idx;
            uint32 memAddr;
            /* Assuming 16-bit register space by default */
            uint8  numWords = MDIO_Interface_NUM_OF_16BIT_REGS;

            for(i = 0u; (i < MDIO_Interface_NUMBER_OF_PAGES) && (result != CYRET_SUCCESS); i++)
            {
                /* Check if address belongs to one of register spaces */
                if((address >= MDIO_Interface_pageStartAddr[i]) && (address <= MDIO_Interface_pageEndAddr[i]))
                {
                    #if(!MDIO_Interface_ALL_PAGES_IN_SRAM)
                    /* Check whether current space is writeable */
                    if(MDIO_Interface_REG_SPACE_IS_SRAM(i))
                    #endif /* !MDIO_Interface_ALL_PAGES_IN_SRAM */
                    {
                        /* Check whether there is enough space to be written */
                        #if(!MDIO_Interface_ALL_PAGES_16BIT)
                            #if(!MDIO_Interface_ALL_PAGES_8BIT)
                            if(MDIO_Interface_REG_SPACE_IS_8BIT(i))
                            #endif /* !MDIO_Interface_ALL_PAGES_8BIT */
                            {
                                numWords = MDIO_Interface_NUM_OF_8BIT_REGS;
                            }
                        #endif /* !MDIO_Interface_ALL_PAGES_16BIT */

                        if(numWords <= ((MDIO_Interface_pageEndAddr[i] - address) + 1u))
                        {
                            idx = address - MDIO_Interface_pageStartAddr[i];

                            #if(!MDIO_Interface_ALL_PAGES_8BIT)
                                #if(!MDIO_Interface_ALL_PAGES_16BIT)
                                if(MDIO_Interface_REG_SPACE_IS_16BIT(i))
                                #endif /* !MDIO_Interface_ALL_PAGES_16BIT */
                                {
                                    /* If 16-bit space is accessed */
                                    idx += idx;
                                }
                            #endif /* !MDIO_Interface_ALL_PAGES_8BIT */

                            memAddr = MDIO_Interface_pageAddrList[i] + idx;

                            /* Write bits to set to A1 reg of FwAlu datapath */
                            CY_SET_REG16(MDIO_Interface_REG_BITS_PTR, regBits);

                            /* Configure DMA transfer as follows:
                            * Two DMA channels, each channel uses one TD.
                            *  Ch1: from register memory to FwAlu;
                            *  Ch2: from FwAlu to register memory. Channel initialized
                            *       in DmaInit() API.
                            *
                            * Return values are ignored because channel number and
                            * TD handles are allocated once during the component
                            * initialization procedure and do not change in run time.
                            */
                            MDIO_Interface_fwDMA1_Chan = MDIO_Interface_FwDMA1_DmaInitialize(
                                MDIO_Interface_FW_DMA_BYTES_PER_BURST, MDIO_Interface_FW_DMA_REQUEST_PER_BURST,
                                HI16(CYDEV_SRAM_BASE), HI16(CYDEV_PERIPH_BASE));

                            /* From register memory to FwAlu datapath */
                            (void) CyDmaTdSetAddress(MDIO_Interface_fwDMA1_TD[0u], LO16(memAddr),
                                LO16((uint32)MDIO_Interface_REG_VAL_PTR));

                            /* Result of OR operation from FwAlu to register memory */
                            (void) CyDmaTdSetAddress(MDIO_Interface_fwDMA2_TD[0u],
                                LO16((uint32)MDIO_Interface_REG_VAL_PTR), LO16(memAddr));

                            /* Configure fwDMA1_TD[0u]. fwDMA2_TD[0u] configured in DmaInit() API */
                            (void) CyDmaTdSetConfiguration(MDIO_Interface_fwDMA1_TD[0u],
                                MDIO_Interface_FW_DMA_TD_SIZE, DMA_INVALID_TD,
                                TD_INC_SRC_ADR | TD_SWAP_EN | MDIO_Interface_FwDMA1__TD_TERMOUT_EN);

                            /* Clear DMA status in case if previous transfer failed */
                            MDIO_Interface_CLEAR_FW_DMA_STATUS;

                            /* Trigger DMA and wait for completion */
                            MDIO_Interface_CONTROL_REG ^= MDIO_Interface_TRIG_DMA;
                            result = MDIO_Interface_DmaIsComplete(MDIO_Interface_FW_DMA2_MASK);
                        }
                    }
                }
            }
            return(result);
        }

    #endif /* MDIO_Interface_ALL_PAGES_IN_FLASH */


    /***************************************************************************
    * Function Name: MDIO_Interface_GetConfiguration
    ****************************************************************************
    * Summary:
    *  Returns a pointer to the configuration array of the given regSpace.
    *
    * Parameters:
    *  uint8 regSpace: register space index.
    *
    * Return:
    *  Pointer to the configuration array if successful.
    *  NULL pointer if regSpace is invalid.
    *
    ***************************************************************************/
    uint8 * MDIO_Interface_GetConfiguration(uint8 regSpace)   
    {
        uint8 * config;
        config = NULL;

        if((regSpace > 0u) && (regSpace <= MDIO_Interface_NUMBER_OF_PAGES))
        {
            regSpace += regSpace;
            regSpace--;
            config = (uint8 *)MDIO_Interface_pageInfoList[regSpace];
        }
        return(config);
    }


    /***************************************************************************
    * Function Name: MDIO_Interface_DmaIsComplete
    ****************************************************************************
    *
    * Summary:
    *  Determines whether a specified DMA channel has completed the transfer.
    *
    * Parameters:
    *  channel: DMA channel to check.
    *
    * Return:
    *  CYRET_SUCCESS: transfer has completed.
    *  CYRET_TIMEOUT: transfer has not completed and 255 us timeout expired.
    *
    ***************************************************************************/
    static uint8 MDIO_Interface_DmaIsComplete(uint8 chMask)
    {
        uint8 timer;

        timer = MDIO_Interface_TIMEOUT_PERIOD;

        while(MDIO_Interface_DMA_ACTIVE(chMask) && (timer != 0u))
        {
            /* Channel is currently being serviced by DMAC and timeout period
            * is not elapsed.
            */
            timer--;
            CyDelayUs(1u);
        }
        return((timer != 0u) ? CYRET_SUCCESS : CYRET_TIMEOUT);
    }


    /***************************************************************************
    * Function Name: MDIO_Interface_DmaEnable
    ****************************************************************************
    *
    * Summary:
    *  Enables Address Analyzer DMAs.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  No.
    *
    ***************************************************************************/
    static void MDIO_Interface_DmaEnable(void)   
    {
        uint8 i;

        /* Set initial TDs and enable DMA channels */
        (void) CyDmaChSetInitialTd(MDIO_Interface_pageStartAddrDMA_Chan, MDIO_Interface_pageStartAddr_TD[0u]);
        (void) CyDmaChSetInitialTd(MDIO_Interface_pageEndAddrDMA_Chan,   MDIO_Interface_pageEndAddr_TD[0u]);
        (void) CyDmaChSetInitialTd(MDIO_Interface_pageInfoDMA_Chan,      MDIO_Interface_pageInfoDMA_TD[0u]);
        (void) CyDmaChSetInitialTd(MDIO_Interface_regAddrDMA_Chan,       MDIO_Interface_regAddrDMA_TD[0u]);
        (void) CyDmaChSetInitialTd(MDIO_Interface_rdDMA_Chan,            MDIO_Interface_rdDMA_TD[0u]);
        (void) CyDmaChSetInitialTd(MDIO_Interface_wrDMA_Chan,            MDIO_Interface_wrDMA_TD[0u]);
        (void) CyDmaChSetInitialTd(MDIO_Interface_cfgDMA1_Chan,          MDIO_Interface_cfgDMA1_TD[0u]);
        (void) CyDmaChSetInitialTd(MDIO_Interface_cfgDMA2_Chan,          MDIO_Interface_cfgDMA2_TD[0u]);
        (void) CyDmaChSetInitialTd(MDIO_Interface_fwDMA1_Chan,           MDIO_Interface_fwDMA1_TD[0u]);
        (void) CyDmaChSetInitialTd(MDIO_Interface_fwDMA2_Chan,           MDIO_Interface_fwDMA2_TD[0u]);

        for(i = 0u; i < MDIO_Interface_NUMBER_OF_CHANNELS; i++)
        {
            (void) CyDmaChEnable(MDIO_Interface_dmaChannelList[i], 1u);
        }
    }


    /***************************************************************************
    * Function Name: MDIO_Interface_DmaDisable
    ****************************************************************************
    *
    * Summary:
    *  Disable Address Analyzer DMAs.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  No.
    *
    ***************************************************************************/
    static void MDIO_Interface_DmaDisable(void)   
    {
        uint8 i;
        uint8 channel;

        for(i = 0u; i < MDIO_Interface_NUMBER_OF_CHANNELS; i++)
        {
            channel = MDIO_Interface_dmaChannelList[i];
            (void) CyDmaChDisable(channel);

            /* Clear any potential DMA requests and reset TD pointers */
            while(0u != (CY_DMA_CH_STRUCT_PTR[channel].basic_status[0u] & CY_DMA_STATUS_TD_ACTIVE))
            {
                ; /* Wait for to be cleared */
            }

            (void) CyDmaChSetRequest(channel, CY_DMA_CPU_TERM_CHAIN);
            (void) CyDmaChEnable    (channel, 1u);

            while(0u != (CY_DMA_CH_STRUCT_PTR[channel].basic_cfg[0u] & CY_DMA_STATUS_CHAIN_ACTIVE))
            {
                ; /* Wait for to be cleared */
            }
        }
    }


    /***************************************************************************
    * Function Name: MDIO_Interface_DmaInit
    ****************************************************************************
    *
    * Summary:
    *  Inits Address Analyzer DMAs.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  No.
    *
    ***************************************************************************/
    static void MDIO_Interface_DmaInit(void)      
    {
        uint8 idx;
        static uint32 MDIO_Interface_regConfig;

        /* For PSoC 3 the data is stored in the big endian ordering. However, the
        *  registers are laid out in the little endian order. The byte ordering must
        *  be considered when use a DMA to transfer between the memory and registers.
        *  The upper 16 bits of the address must be 0 for SRAM and CYDEV_FLS_BASE
        *  for Flash.
        */
        #if(CY_PSOC3)
            uint8 pageMask = 0x01u;
            for(idx = 0u; idx < MDIO_Interface_PAGE_INFO_SIZE; idx += 2u)
            {
                MDIO_Interface_pageInfoList[idx] = (uint32)MDIO_Interface_pageInfoPtr[idx] &
                                                        MDIO_Interface_LO16_ADDR_MASK;
                if(0u == (MDIO_Interface_PAGE_MEM_TYPE & pageMask))
                {
                    MDIO_Interface_pageInfoList[idx] |= CYDEV_FLS_BASE;
                }
                MDIO_Interface_pageAddrList[idx>>1u] = MDIO_Interface_pageInfoList[idx];
                MDIO_Interface_pageInfoList[idx] = CYSWAP_ENDIAN32(MDIO_Interface_pageInfoList[idx]);

                MDIO_Interface_pageInfoList[idx+1u] = (uint32)MDIO_Interface_pageInfoPtr[idx+1u] &
                                                        MDIO_Interface_LO16_ADDR_MASK;
                if(0u == (MDIO_Interface_CFG_MEM_TYPE & pageMask))
                {
                    MDIO_Interface_pageInfoList[idx+1u] |= CYDEV_FLS_BASE;
                }
                MDIO_Interface_pageInfoList[idx+1u] = CYSWAP_ENDIAN32(MDIO_Interface_pageInfoList[idx+1u]);
                pageMask = (uint8)(pageMask << 1u);
            }
        #endif /* CY_PSOC3 */

        /* 0x1FFF8000-0x1FFFFFFF needs to use alias at 0x20008000-0x2000FFFF */
        #if(CY_PSOC5)
            for(idx = 0u; idx < MDIO_Interface_PAGE_INFO_SIZE; idx += 2u)
            {
                MDIO_Interface_pageInfoList[idx] = (uint32)MDIO_Interface_pageInfoPtr[idx];
                if(MDIO_Interface_CPU_SRAM_BASE <= MDIO_Interface_pageInfoList[idx])
                {
                    MDIO_Interface_pageInfoList[idx] &= MDIO_Interface_LO16_ADDR_MASK;
                    MDIO_Interface_pageInfoList[idx] |= MDIO_Interface_DMA_SRAM_BASE;
                }

                MDIO_Interface_pageAddrList[idx>>1u] = MDIO_Interface_pageInfoList[idx];

                MDIO_Interface_pageInfoList[idx+1u] = (uint32)MDIO_Interface_pageInfoPtr[idx+1u];
                if(MDIO_Interface_CPU_SRAM_BASE <= MDIO_Interface_pageInfoList[idx+1u])
                {
                    MDIO_Interface_pageInfoList[idx+1u] &= MDIO_Interface_LO16_ADDR_MASK;
                    MDIO_Interface_pageInfoList[idx+1u] |= MDIO_Interface_DMA_SRAM_BASE;
                }
            }
        #endif /* CY_PSOC5 */


        /***********************************************************************
        *       Register space start and end address DMAs
        ***********************************************************************/

        /* Transfer register space start and end addresses from SRAM to UDB,
        *  two byte transfer, each transfer requires request.
        */
        MDIO_Interface_pageStartAddrDMA_Chan = MDIO_Interface_StartAddrDMA_DmaInitialize(
            MDIO_Interface_PAGE_ADDR_DMA_BYTES_PER_BURST, MDIO_Interface_PAGE_ADDR_DMA_REQUEST_PER_BURST,
            HI16(CYDEV_SRAM_BASE),   HI16(CYDEV_PERIPH_BASE));

        MDIO_Interface_pageEndAddrDMA_Chan   = MDIO_Interface_EndAddrDMA_DmaInitialize(
            MDIO_Interface_PAGE_ADDR_DMA_BYTES_PER_BURST, MDIO_Interface_PAGE_ADDR_DMA_REQUEST_PER_BURST,
            HI16(CYDEV_SRAM_BASE),   HI16(CYDEV_PERIPH_BASE));

        /* Update channel list with allocated channel numbers */
        MDIO_Interface_dmaChannelList[0u] = MDIO_Interface_pageStartAddrDMA_Chan;
        MDIO_Interface_dmaChannelList[1u] = MDIO_Interface_pageEndAddrDMA_Chan;

        MDIO_Interface_pageStartAddr_TD[0u] = CyDmaTdAllocate();
        MDIO_Interface_pageEndAddr_TD[0u]   = CyDmaTdAllocate();

        /* One TD looping on itself, increment source address, but not
        *  destination address.
        */
        (void) CyDmaTdSetConfiguration(MDIO_Interface_pageStartAddr_TD[0u], MDIO_Interface_PAGE_ADDR_DMA_TD_SIZE,
                                       MDIO_Interface_pageStartAddr_TD[0u], MDIO_Interface_PAGE_ADDR_DMA_CFG);
        (void) CyDmaTdSetConfiguration(MDIO_Interface_pageEndAddr_TD[0u],   MDIO_Interface_PAGE_ADDR_DMA_TD_SIZE,
                                       MDIO_Interface_pageEndAddr_TD[0u],   MDIO_Interface_PAGE_ADDR_DMA_CFG);

        /* Move register space boundaries from regPageStartAddr and
        *  regPageEndAddr arrays in SRAM to address comparison block FIFO 0
        *  and FIFO 1 correspondingly.
        */
        (void) CyDmaTdSetAddress(MDIO_Interface_pageStartAddr_TD[0u], LO16((uint32)MDIO_Interface_pageStartAddr),
                                                                        LO16((uint32)MDIO_Interface_PAGE_START_PTR));
        (void) CyDmaTdSetAddress(MDIO_Interface_pageEndAddr_TD[0u],   LO16((uint32)MDIO_Interface_pageEndAddr),
                                                                        LO16((uint32)MDIO_Interface_PAGE_END_PTR));


        /***********************************************************************
        *                   Register page info DMA
        ***********************************************************************/

        /* Transfer the register page info from SRAM to the address calculation
        *  datapath, two byte transfer, all subsequent bursts after the first
        *  burst will be automatically requested and carried out.
        */
        MDIO_Interface_pageInfoDMA_Chan = MDIO_Interface_InfoDMA_DmaInitialize(
            MDIO_Interface_PAGE_INFO_DMA_BYTES_PER_BURST,  MDIO_Interface_PAGE_INFO_DMA_REQUEST_PER_BURST,
            HI16(CYDEV_SRAM_BASE), HI16(CYDEV_PERIPH_BASE));

        /* Update channel list with allocated channel number */
        MDIO_Interface_dmaChannelList[2u] = MDIO_Interface_pageInfoDMA_Chan;

        MDIO_Interface_pageInfoDMA_TD[0u] = CyDmaTdAllocate();
        /* One TD looping on itself, increment the source address, but not the
        *  destination address.
        */
        (void) CyDmaTdSetConfiguration(MDIO_Interface_pageInfoDMA_TD[0u], MDIO_Interface_PAGE_INFO_DMA_TD_SIZE,
            MDIO_Interface_pageInfoDMA_TD[0u], TD_INC_SRC_ADR | MDIO_Interface_InfoDMA__TD_TERMOUT_EN);

        /* Move the register page info from the SRAM to the address calculation
        *  datapath FIFO 0. The source address of this TD is set to 0, since it
        *  is configured later in run-time by the AddrDMA DMA.
        */
        (void) CyDmaTdSetAddress(MDIO_Interface_pageInfoDMA_TD[0u], LO16((uint32)0u),
                                    LO16((uint32)MDIO_Interface_PAGE_INFO_PTR));


        /***********************************************************************
        *                          Read DMA
        ***********************************************************************/

        /* Transfer the register data from SRAM/Flash to FIFO 0 of the MDIO
        *  frame processing block. The source address is set to 0u, since it
        *  is updated in run-time by Address DMA.
        */
        MDIO_Interface_rdDMA_Chan = MDIO_Interface_RdDMA_DmaInitialize(
            MDIO_Interface_REG_MEM_DMA_BYTES_PER_BURST, MDIO_Interface_REG_MEM_DMA_REQUEST_PER_BURST,
            0u, HI16(CYDEV_PERIPH_BASE));

        /* Update channel list with allocated channel number */
        MDIO_Interface_dmaChannelList[3u] = MDIO_Interface_rdDMA_Chan;

        MDIO_Interface_rdDMA_TD[0u] = CyDmaTdAllocate();

        /* One TD looping on itself, increment source address, but not
        *  destination address.
        */
        (void) CyDmaTdSetConfiguration(MDIO_Interface_rdDMA_TD[0u], MDIO_Interface_REG_MEM_DMA_TD_SIZE,
                    MDIO_Interface_rdDMA_TD[0u], MDIO_Interface_RdDMA__TD_TERMOUT_EN | TD_INC_SRC_ADR | TD_SWAP_EN);

        /* Move the register data from the SRAM or Flash to the FIFO 0 register
        *  of the frame processing block. The source address of this TD is set
        *  to 0, since it is configured later in run-time by the AddrDMA DMA.
        */
        (void) CyDmaTdSetAddress(MDIO_Interface_rdDMA_TD[0u], LO16((uint32)0u),
                                                                LO16((uint32)MDIO_Interface_FP_FIFO0_PTR));


        /***********************************************************************
        *                           Write DMA
        ***********************************************************************/

        /* Transfer the register data from the FIFO 1 of the MDIO frame processing
        *  block to the register memory in SRAM.
        */
        MDIO_Interface_wrDMA_Chan = MDIO_Interface_WrDMA_DmaInitialize(
            MDIO_Interface_REG_MEM_DMA_BYTES_PER_BURST, MDIO_Interface_REG_MEM_DMA_REQUEST_PER_BURST,
            HI16(CYDEV_PERIPH_BASE), HI16(CYDEV_SRAM_BASE));

        /* Update channel list with allocated channel number */
        MDIO_Interface_dmaChannelList[4u] = MDIO_Interface_wrDMA_Chan;

        MDIO_Interface_wrDMA_TD[0u] = CyDmaTdAllocate();

        /* One TD looping on itself, increment destination address, but not
        *  source address.
        */
        (void) CyDmaTdSetConfiguration(MDIO_Interface_wrDMA_TD[0u], MDIO_Interface_REG_MEM_DMA_TD_SIZE,
                    MDIO_Interface_wrDMA_TD[0u], MDIO_Interface_WrDMA__TD_TERMOUT_EN | TD_INC_DST_ADR | TD_SWAP_EN);

        /* Move the register data from the FIFO 1 register of the frame processing
        *  block to the register memory in SRAM. The destination address of this
        *  TD is set to 0, since it is configured later in run-time by the
        *  AddrDMA DMA.
        */
        (void) CyDmaTdSetAddress(MDIO_Interface_wrDMA_TD[0u], LO16((uint32)MDIO_Interface_FP_FIFO1_PTR),
                                                                LO16((uint32)0u));


        /***********************************************************************
        *               Register configuration DMAs
        ***********************************************************************/

        /* CfgDMA1 transfers the register configuration data (mask and attributes)
        * from the configuration memory in Flash/SRAM to the fixed memory
        * location. Then the CfgDMA2 moves the configuration from this location
        * into the UDB array. The source address of CfgDMA1 is set to 0u, since
        * it is updated in run-time by Address DMA.
        */
        MDIO_Interface_cfgDMA1_Chan = MDIO_Interface_CfgDMA1_DmaInitialize(
            MDIO_Interface_CFG_DMA1_BYTES_PER_BURST, MDIO_Interface_CFG_DMA1_REQUEST_PER_BURST,
            HI16(0u), HI16(CYDEV_SRAM_BASE));

        MDIO_Interface_cfgDMA2_Chan = MDIO_Interface_CfgDMA2_DmaInitialize(
            MDIO_Interface_CFG_DMA2_BYTES_PER_BURST, MDIO_Interface_CFG_DMA2_REQUEST_PER_BURST,
            HI16(CYDEV_SRAM_BASE), HI16(CYDEV_PERIPH_BASE));

        /* Update channel list with allocated channel number */
        MDIO_Interface_dmaChannelList[5u] = MDIO_Interface_cfgDMA1_Chan;
        MDIO_Interface_dmaChannelList[6u] = MDIO_Interface_cfgDMA2_Chan;

        MDIO_Interface_cfgDMA1_TD[0u] = CyDmaTdAllocate();
        MDIO_Interface_cfgDMA2_TD[0u] = CyDmaTdAllocate();
        MDIO_Interface_cfgDMA2_TD[1u] = CyDmaTdAllocate();

        /* TD looped on itself, increment source and destination
        *  address address. Increment is required for PSoC3 if data
        *  is not aligned.
        */
        (void) CyDmaTdSetConfiguration(MDIO_Interface_cfgDMA1_TD[0u], MDIO_Interface_CFG_DMA1_TD_SIZE,
            MDIO_Interface_cfgDMA1_TD[0u], MDIO_Interface_CFG_DMA1_CFG);

        /* Two TD chain. Last TD in chain looped on first one. */
        (void) CyDmaTdSetConfiguration(MDIO_Interface_cfgDMA2_TD[0u], MDIO_Interface_CFG_DMA2_TD1_SIZE,
                                MDIO_Interface_cfgDMA2_TD[1u], TD_INC_SRC_ADR | TD_INC_DST_ADR | TD_AUTO_EXEC_NEXT);
        (void) CyDmaTdSetConfiguration(MDIO_Interface_cfgDMA2_TD[1u], MDIO_Interface_CFG_DMA2_TD2_SIZE,
                                MDIO_Interface_cfgDMA2_TD[0u], MDIO_Interface_CfgDMA2__TD_TERMOUT_EN);

        /* Move the register configuration from Flash or SRAM into the fixed
        *  memory location in SRAM. The source address of this TD is set to 0,
        *  since it is configured later in run-time by AddrDMA DMA.
        */
        (void) CyDmaTdSetAddress(MDIO_Interface_cfgDMA1_TD[0u], LO16((uint32)0u),
                                                                  LO16((uint32)&MDIO_Interface_regConfig));

        /* Move register mask from memory to D1 register of MDIO frame
        *  processing datapath.
        */
        (void) CyDmaTdSetAddress(MDIO_Interface_cfgDMA2_TD[0u], LO16((uint32)&MDIO_Interface_regConfig),
                                                                  LO16((uint32)MDIO_Interface_REG_MASK_PTR));

        /* Move register attributes from memory to regCfg control register
        *  of Address analyzer block.
        */
        (void) CyDmaTdSetAddress(MDIO_Interface_cfgDMA2_TD[1u],
                        LO16((uint32)&MDIO_Interface_regConfig + MDIO_Interface_CTRL_BITS_OFFSET),
                        LO16((uint32)MDIO_Interface_REG_ATTR_PTR));


        /***********************************************************************
        *               Register physical memory address DMA
        ***********************************************************************/

        /* Transfer data between UDB registers and DMAC config memory,
        *  two byte transfer, each transfer requires request.
        */
        MDIO_Interface_regAddrDMA_Chan  = MDIO_Interface_AddrDMA_DmaInitialize(
            MDIO_Interface_REG_MEM_DMA_BYTES_PER_BURST,  MDIO_Interface_REG_MEM_DMA_REQUEST_PER_BURST,
            HI16(CYDEV_PERIPH_BASE), HI16(CYDEV_PERIPH_BASE));

        /* Update channel list with allocated channel number */
        MDIO_Interface_dmaChannelList[7u] = MDIO_Interface_regAddrDMA_Chan;

        for(idx = 0u; idx < MDIO_Interface_REG_MEM_ADDR_DMA_TD_NUM; idx++)
        {
            MDIO_Interface_regAddrDMA_TD[idx] = CyDmaTdAllocate();
        }

        /* Configure TD chain */
        (void) CyDmaTdSetConfiguration(MDIO_Interface_regAddrDMA_TD[0u], MDIO_Interface_REG_MEM_DMA_TD_SIZE,
                                       MDIO_Interface_regAddrDMA_TD[1u], TD_AUTO_EXEC_NEXT);

        (void) CyDmaTdSetConfiguration(MDIO_Interface_regAddrDMA_TD[1u], MDIO_Interface_REG_MEM_DMA_TD_SIZE,
                                       MDIO_Interface_regAddrDMA_TD[2u], MDIO_Interface_AddrDMA__TD_TERMOUT_EN);

        (void) CyDmaTdSetConfiguration(MDIO_Interface_regAddrDMA_TD[2u], MDIO_Interface_REG_MEM_DMA_TD_SIZE,
                                       MDIO_Interface_regAddrDMA_TD[3u], TD_AUTO_EXEC_NEXT);

        (void) CyDmaTdSetConfiguration(MDIO_Interface_regAddrDMA_TD[3u], MDIO_Interface_REG_MEM_DMA_TD_SIZE,
                                       MDIO_Interface_regAddrDMA_TD[4u], MDIO_Interface_AddrDMA__TD_TERMOUT_EN);

        (void) CyDmaTdSetConfiguration(MDIO_Interface_regAddrDMA_TD[4u], MDIO_Interface_REG_MEM_DMA_TD_SIZE,
                                       MDIO_Interface_regAddrDMA_TD[5u], MDIO_Interface_AddrDMA__TD_TERMOUT_EN);

        (void) CyDmaTdSetConfiguration(MDIO_Interface_regAddrDMA_TD[5u], MDIO_Interface_REG_MEM_DMA_TD_SIZE,
                                       MDIO_Interface_regAddrDMA_TD[6u], MDIO_Interface_AddrDMA__TD_TERMOUT_EN);

        (void) CyDmaTdSetConfiguration(MDIO_Interface_regAddrDMA_TD[6u], MDIO_Interface_REG_MEM_DMA_TD_SIZE,
                                       MDIO_Interface_regAddrDMA_TD[0u], MDIO_Interface_AddrDMA__TD_TERMOUT_EN);

        /* Transfer address of register space info (register space memory
        *  base address and register space config base address) from address
        *  calculation datapath to source address of InfoDMA TD.
        */
        (void) CyDmaTdSetAddress(MDIO_Interface_regAddrDMA_TD[0u], LO16((uint32)MDIO_Interface_INFO_ADDR_PTR),
                                LO16((uint32)&CY_DMA_TDMEM_STRUCT_PTR[MDIO_Interface_pageInfoDMA_TD[0u]].TD1[0u]));

        /* Move register index from A0 register of address
        *  comparison datapath to address calculation datapath.
        */
        (void) CyDmaTdSetAddress(MDIO_Interface_regAddrDMA_TD[1u], LO16((uint32)MDIO_Interface_REG_IDX_PTR),
                                                                     LO16((uint32)MDIO_Interface_REG_OFFSET_PTR));

        /* Move lower 16 bits of register address from the A0 of
        *  address calculation datapath to source address of RdDMA TD
        *  and destination address of WrDMA TD.
        */
        (void) CyDmaTdSetAddress(MDIO_Interface_regAddrDMA_TD[2u], LO16((uint32)MDIO_Interface_REG_ADDR_PTR),
                                LO16((uint32)&CY_DMA_TDMEM_STRUCT_PTR[MDIO_Interface_rdDMA_TD[0u]].TD1[0u]));
        (void) CyDmaTdSetAddress(MDIO_Interface_regAddrDMA_TD[3u], LO16((uint32)MDIO_Interface_REG_ADDR_PTR),
                                LO16((uint32)&CY_DMA_TDMEM_STRUCT_PTR[MDIO_Interface_wrDMA_TD[0u]].TD1[2u]));

        /* Move upper 16 bits of register address from A0 of the
        *  address calculation datapath to upper 16-bit source address of
        *  RdDMA TD.
        */
        (void) CyDmaTdSetAddress(MDIO_Interface_regAddrDMA_TD[4u], LO16((uint32)MDIO_Interface_REG_ADDR_PTR),
                                LO16((uint32)&CY_DMA_CFGMEM_STRUCT_PTR[MDIO_Interface_rdDMA_Chan].CFG1[0u]));

        /* Move lower and upper 16 bits of register config address
        *  from A0 of address calculation datapath to source address
        *  of CfgDMA1 TD.
        */
        (void) CyDmaTdSetAddress(MDIO_Interface_regAddrDMA_TD[5u], LO16((uint32)MDIO_Interface_REG_ADDR_PTR),
                                LO16((uint32)&CY_DMA_TDMEM_STRUCT_PTR[MDIO_Interface_cfgDMA1_TD[0u]].TD1[0u]));
        (void) CyDmaTdSetAddress(MDIO_Interface_regAddrDMA_TD[6u], LO16((uint32)MDIO_Interface_REG_ADDR_PTR),
                                LO16((uint32)&CY_DMA_CFGMEM_STRUCT_PTR[MDIO_Interface_cfgDMA1_Chan].CFG1[0u]));


        /***********************************************************************
        *               Firmware DMA (Used from APIs)
        ***********************************************************************/

        /* Partial configuration of FwDMA1 and FwDMA2 DMA. The rest configuration is done
        *  in the SetData, GetData and SetBits APIs.
        */
        MDIO_Interface_fwDMA1_Chan = MDIO_Interface_FwDMA1_DmaInitialize(
            MDIO_Interface_FW_DMA_BYTES_PER_BURST, MDIO_Interface_FW_DMA_REQUEST_PER_BURST,
            HI16(CYDEV_SRAM_BASE), HI16(CYDEV_SRAM_BASE));

        MDIO_Interface_fwDMA1_TD[0u] = CyDmaTdAllocate();

        MDIO_Interface_fwDMA2_Chan = MDIO_Interface_FwDMA2_DmaInitialize(
            MDIO_Interface_FW_DMA_BYTES_PER_BURST, MDIO_Interface_FW_DMA_REQUEST_PER_BURST,
            HI16(CYDEV_PERIPH_BASE), HI16(CYDEV_SRAM_BASE));

        MDIO_Interface_fwDMA2_TD[0u] = CyDmaTdAllocate();
        (void) CyDmaTdSetConfiguration(MDIO_Interface_fwDMA2_TD[0u], MDIO_Interface_FW_DMA_TD_SIZE,
            DMA_INVALID_TD, TD_SWAP_EN | TD_INC_SRC_ADR | MDIO_Interface_FwDMA2__TD_TERMOUT_EN);

        /* Update channel list with allocated channel numbers */
        MDIO_Interface_dmaChannelList[8u] = MDIO_Interface_fwDMA1_Chan;
        MDIO_Interface_dmaChannelList[9u] = MDIO_Interface_fwDMA2_Chan;
    }

#endif /* MDIO_Interface_ADVANCED_MODE */


/* [] END OF FILE */
