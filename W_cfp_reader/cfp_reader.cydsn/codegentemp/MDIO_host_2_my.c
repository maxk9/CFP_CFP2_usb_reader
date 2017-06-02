/* ========================================
 *
 * Copyright FiberTreid, 2017
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

//#include <device.h>
#include <project.h>
#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "MDIO_host_2_my.h"

/*******************************************************************************
* Variables
********************************************************************************/
uint8 MDIO_host_2_initVar = 0u;

/* Data received MDIO Host */
volatile uint16 MDIO_host_2_data_bits=0u;	 

/* Internal Status Register */
volatile uint8  MDIO_host_2_StatusRegister=0u;

/*******************************************************************************
* Function Name: MDIO_host_2_Start
********************************************************************************
* Summary:
*  Initializes the MDIO Host component.
* 
* Parameters:
*  None
*
* Return:
*  None
* 
* Side Effects:
*
********************************************************************************/
void MDIO_host_2_Start(void)
{ 
    /* If not already initialized, then initialize hardware and software */
    if(MDIO_host_2_initVar == 0u)
    {
        MDIO_host_2_Init();
        MDIO_host_2_initVar = 1u;
    }
    MDIO_host_2_Enable();
}

/*******************************************************************************
* Function Name: MDIO_host_2_Stop
********************************************************************************
* Summary:
*  Disable the MDIO Host component and the internal interrupt
* 
* Parameters:
*  None
* 
* Return:
*  None
* 
* Side Effects:
*  
********************************************************************************/
void MDIO_host_2_Stop(void)
{
	/* Disable the hardware component */
 //   MDIO_host_2_CONTROL_REG = 0u;	// Set Enable and Valid bits to zero
	
	/* Disable Count7 hardware block */
    MDIO_host_2_CNT7_AUX_CTL_REG &= ~MDIO_host_2_COUNT7_EN;
	
	/* Disable Interrupt */
//	MDIO_host_2_DisableInt();
}

/*******************************************************************************
* Function Name: MDIO_host_2_Init
********************************************************************************
* Summary:
*  Initializes internal variables and resets the datapath FIFO.
* 
* Parameters:
*  None
*
* Return:
*  None
* 
* Side Effects:
*  
********************************************************************************/
void MDIO_host_2_Init(void)
{ 	
    MDIO_host_2_Enable();
	
	/* Reset Internal FIFOs */
	MDIO_host_2_ClearInternalFIFOs();

    /* Initialize interrupts */
//	MDIO_host_2_EnableInt();
}

/*******************************************************************************
* Function Name: MDIO_host_2_Enable()
********************************************************************************
* Summary:
*  Enables the hardware and internal interrupt.
* 
* Parameters:
*  None
*
* Return:
*  None
* 
* Side Effects:
*  None
********************************************************************************/
void MDIO_host_2_Enable(void) 
{
	/* Enable Count7 hardware block */
    MDIO_host_2_CNT7_AUX_CTL_REG |= MDIO_host_2_COUNT7_EN;

	/* Enable the block */
    //  MDIO_host_2_CONTROL_REG = MDIO_host_2_ENABLE;
	
    /*Reset counter */
    // MDIO_host_2_PERIOD_REG = 127;
    MDIO_host_2_COUNT_REG = 61;
    
	/* Enable the interrupt */
	//CyIntEnable(MDIO_host_2_ISR_NUMBER);   
}

/*******************************************************************************
* Function Name: MDIO_host_2_EnableInt
********************************************************************************
* Summary:
*  Enables and configure the interrupt from this component. 
* 
* Parameters:
*  None
* 
* Return:
*  None
* 
* Side Effects:
*  None
********************************************************************************/
//void MDIO_host_2_EnableInt(void)
//{   
//    /* Enable interrupt handler service routine */
//	CyIntDisable(MDIO_host_2_ISR_NUMBER);
//	CyIntSetVector(MDIO_host_2_ISR_NUMBER, MDIO_host_2_ISR_InterruptHandler);
//	CyIntSetPriority(MDIO_host_2_ISR_NUMBER, MDIO_host_2_ISR_PRIORITY);
//	CyIntEnable(MDIO_host_2_ISR_NUMBER);        
//}

/*******************************************************************************
* Function Name: MDIO_host_2_DisableInt
********************************************************************************
* Summary:
*  Disables interrupts from this component
*
* Parameters:
*  None
* 
* Return:
*  None
* 
* Side Effects:
*  None
********************************************************************************/
//void MDIO_host_2_DisableInt(void)
//{  
//    /* Disable interrupt handler service routine */
//	CyIntDisable(MDIO_host_2_ISR_NUMBER);
//}

/*******************************************************************************
* Function Name: MDIO_host_2_GetStatus
********************************************************************************
* Summary:
*  Returns the internal status of the hardware.
*
* Parameters:
*  None
* 
* Return:
*  uint8
*		b0   = Set when component is busy 
*		b1 	 = Set when PHY address matches in the right timing 
*		b7:2 = Reserved. Returns all zeros
*
* Side Effects:
*  None
********************************************************************************/
uint8 MDIO_host_2_GetStatus(void) CYREENTRANT
{
	return MDIO_host_2_StatusRegister;
}

/*******************************************************************************
* Function Name: MDIO_host_2_ClearInternalFIFOs
********************************************************************************
* Summary:
*  Clear the internal FIFOs from the data path 
*
* Parameters:
*  dataPtr: Pointer to the data buffer
* 
* Return:
*  None
*
* Side Effects:
*  The size of this buffer should be at least 32 x 16 bits (64 bytes), otherwise
*  memory violation may occurs.
*
********************************************************************************/
void MDIO_host_2_ClearInternalFIFOs(void)
{
	/* Reset F0 FIFO  */
	CY_SET_REG16(MDIO_host_2_DP_AUX_CTL_PTR, (CY_GET_REG16(MDIO_host_2_DP_AUX_CTL_PTR) |  MDIO_host_2_F0_CLR));
    CY_SET_REG16(MDIO_host_2_DP_AUX_CTL_PTR, (CY_GET_REG16(MDIO_host_2_DP_AUX_CTL_PTR) & ~MDIO_host_2_F0_CLR));
	
	/* Reset F1 FIFO  */
	CY_SET_REG16(MDIO_host_2_DP_AUX_CTL_PTR, (CY_GET_REG16(MDIO_host_2_DP_AUX_CTL_PTR) |  MDIO_host_2_F1_CLR));
    //CY_SET_REG16(MDIO_host_2_DP_AUX_CTL_PTR, (CY_GET_REG16(MDIO_host_2_DP_AUX_CTL_PTR) & ~MDIO_host_2_F1_CLR));	
}

/*******************************************************************************
*
* MDIO_host_2_SetAddr_C45()
*
*******************************************************************************/
uint8 MDIO_host_2_SetAddrC45(uint8 phy_addr, uint8 dev_addr, uint16 reg_data) // Set Addr reg
{
   	uint16 control_bits;
	uint8 status_reg;

	/* Clear and Set the control register for writing */
	MDIO_host_2_CONTROL_REG = MDIO_host_2_WRITE;
		
    /* Set the control bits and write in the fifo f0 */
     control_bits = 0x0002+(((uint16)phy_addr)<<7)+(((uint16)dev_addr)<<2);
    MDIO_host_2_FIFO_F0_REG = control_bits;
    MDIO_host_2_FIFO_F0_REG = reg_data;
//    MDIO_host_2_FIFO_F0_REG = 0x4002;
//    MDIO_host_2_FIFO_F0_REG = 0x8002;
   
	/* Clear hardware status register */
	status_reg = MDIO_host_2_STATUS_REG;
    
    return ((status_reg)? 0 : 1);
}

/*******************************************************************************
*
* MDIO_host_2_WriteData_C45()
*
*******************************************************************************/
uint8 MDIO_host_2_WriteDataC45(uint8 phy_addr, uint8 dev_addr, uint16 reg_data) // Writes data to the bus
{
   	uint16	control_bits;
	uint8   status_reg;

	/* Clear and Set the control register for writing */
	MDIO_host_2_CONTROL_REG = MDIO_host_2_WRITE;
		
    /* Set the control bits and write in the fifo f0 */
     control_bits = 0x0002+((uint16)1<<12)+(((uint16)phy_addr)<<7)+(((uint16)dev_addr)<<2);
    MDIO_host_2_FIFO_F0_REG = control_bits;
    MDIO_host_2_FIFO_F0_REG = reg_data;

   
	/* Clear hardware status register */
	status_reg = MDIO_host_2_STATUS_REG;
    
    return ((status_reg)? 0 : 1);
}


/*******************************************************************************
*
* MDIO_host_2_ReadData_C45()
*
*******************************************************************************/
uint8 MDIO_host_2_ReadDataC45(uint8 phy_addr, uint8 dev_addr, uint16 *regData) // Read data from the bus
{
   	uint16	control_bits;
	uint8 status_reg;

	/* Clear and Set the control register for reading */
	MDIO_host_2_CONTROL_REG = MDIO_host_2_READ;
	
   	/* Set the control bits and write in the fifo f0 */
   	control_bits = 0x0002+((uint16)3<<12)+(((uint16)phy_addr)<<7)+(((uint16)dev_addr)<<2);
   	MDIO_host_2_FIFO_F0_REG = control_bits;
    MDIO_host_2_FIFO_F0_REG = 0xFFFF;
    
    /* Wait till the transmission is completed */
    MDIO_host_2_StatusRegister=0u;
    
	while( !MDIO_host_2_StatusRegister );
    
   /* Get Data from FIFO f1 */
    //LED_3_Write(1);
	*regData = CY_GET_REG16(MDIO_host_2_A0_PTR);
	//LED_3_Write(0);
    /* Clear hardware status register */
	status_reg = MDIO_host_2_STATUS_REG;
	return ((status_reg)? 0 : 1);
    
}
/*******************************************************************************
*
* MDIO_host_2_PosReadData_C45()
*
*******************************************************************************/
uint8 MDIO_host_2_PosReadDataC45(uint8 phy_addr, uint8 dev_addr, uint16 *regData) // Post Read Inc Add 
{
   	uint16	control_bits;
	uint8 status_reg;

	/* Clear and Set the control register for reading */
	MDIO_host_2_CONTROL_REG = MDIO_host_2_READ;
	
   	/* Set the control bits and write in the fifo f0 */
   	control_bits = 0x0002+((uint16)2<<12)+(((uint16)phy_addr)<<7)+(((uint16)dev_addr)<<2);
   	MDIO_host_2_FIFO_F0_REG = control_bits;
    MDIO_host_2_FIFO_F0_REG = 0xFFFF;
    
    /* Wait till the transmission is completed */
    MDIO_host_2_StatusRegister=0u;
    
	while( !MDIO_host_2_StatusRegister );
    
   /* Get Data from FIFO f1 */
   // LED_3_Write(1);
	*regData = CY_GET_REG16(MDIO_host_2_A0_PTR);
	//LED_3_Write(0);
    /* Clear hardware status register */
	status_reg = MDIO_host_2_STATUS_REG;
	return ((status_reg)? 0 : 1);
    
}

/*******************************************************************************
*
* MDIO_Host__ClearStatus()
*
*******************************************************************************/
void  MDIO_host_2_ClearStatus(void)
{
	MDIO_host_2_StatusRegister = 0x00u;
}



/* [] END OF FILE */
