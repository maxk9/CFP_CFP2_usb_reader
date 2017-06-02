/* ==============================================
 *
 * Copyright Cypress Semiconductor, 2010
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF CYPRESS SEMICONDUCTOR
 *
 * ==============================================
*/
//#include <device.h>
#include <project.h>
#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "MDIO_Host_1.h"

/*******************************************************************************
* Variables
********************************************************************************/
uint8 MDIO_Host_1_initVar = 0u;

/* Data received MDIO Host */
extern volatile uint16 MDIO_Host_1_data_bits;	 

/* Internal Status Register */
extern volatile uint8  MDIO_Host_1_StatusRegister;

/*******************************************************************************
* Function Name: MDIO_Host_1_Start
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
void MDIO_Host_1_Start(void)
{ 
    /* If not already initialized, then initialize hardware and software */
    if(MDIO_Host_1_initVar == 0u)
    {
        MDIO_Host_1_Init();
        MDIO_Host_1_initVar = 1u;
    }
    MDIO_Host_1_Enable();
}

/*******************************************************************************
* Function Name: MDIO_Host_1_Stop
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
void MDIO_Host_1_Stop(void)
{
	/* Disable the hardware component */
    MDIO_Host_1_CONTROL_REG = 0u;	// Set Enable and Valid bits to zero
	
	/* Disable Count7 hardware block */
    MDIO_Host_1_CNT7_AUX_CTL_REG &= ~MDIO_Host_1_COUNT7_EN;
	
	/* Disable Interrupt */
	MDIO_Host_1_DisableInt();
}

/*******************************************************************************
* Function Name: MDIO_Host_1_Init
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
void MDIO_Host_1_Init(void)
{ 	
    /* Initialize the UDB control register */
    MDIO_Host_1_CONTROL_REG = 0u;
	
	/* Reset Internal FIFOs */
	MDIO_Host_1_ClearInternalFIFOs();

    /* Initialize interrupts */
	MDIO_Host_1_EnableInt();
}

/*******************************************************************************
* Function Name: MDIO_Host_1_Enable()
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
void MDIO_Host_1_Enable(void) 
{
	/* Enable Count7 hardware block */
    MDIO_Host_1_CNT7_AUX_CTL_REG |= MDIO_Host_1_COUNT7_EN;

	/* Enable the block */
    MDIO_Host_1_CONTROL_REG |= MDIO_Host_1_ENABLE;
	
	/* Enable the interrupt */
	CyIntEnable(MDIO_Host_1_ISR_NUMBER);   
}

/*******************************************************************************
* Function Name: MDIO_Host_1_EnableInt
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
void MDIO_Host_1_EnableInt(void)
{   
    /* Enable interrupt handler service routine */
	CyIntDisable(MDIO_Host_1_ISR_NUMBER);
	CyIntSetVector(MDIO_Host_1_ISR_NUMBER, MDIO_Host_1_ISR_InterruptHandler);
	CyIntSetPriority(MDIO_Host_1_ISR_NUMBER, MDIO_Host_1_ISR_PRIORITY);
	CyIntEnable(MDIO_Host_1_ISR_NUMBER);        
}

/*******************************************************************************
* Function Name: MDIO_Host_1_DisableInt
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
void MDIO_Host_1_DisableInt(void)
{  
    /* Disable interrupt handler service routine */
	CyIntDisable(MDIO_Host_1_ISR_NUMBER);
}

/*******************************************************************************
* Function Name: MDIO_Host_1_GetStatus
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
uint8 MDIO_Host_1_GetStatus(void) CYREENTRANT
{
	return MDIO_Host_1_StatusRegister;
}

/*******************************************************************************
* Function Name: MDIO_Host_1_ClearInternalFIFOs
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
void MDIO_Host_1_ClearInternalFIFOs(void)
{
	/* Reset F0 FIFO  */
	CY_SET_REG16(MDIO_Host_1_DP_AUX_CTL_PTR, (CY_GET_REG16(MDIO_Host_1_DP_AUX_CTL_PTR) |  MDIO_Host_1_F0_CLR));
    CY_SET_REG16(MDIO_Host_1_DP_AUX_CTL_PTR, (CY_GET_REG16(MDIO_Host_1_DP_AUX_CTL_PTR) & ~MDIO_Host_1_F0_CLR));
	
	/* Reset F1 FIFO  */
	CY_SET_REG16(MDIO_Host_1_DP_AUX_CTL_PTR, (CY_GET_REG16(MDIO_Host_1_DP_AUX_CTL_PTR) |  MDIO_Host_1_F1_CLR));
    //CY_SET_REG16(MDIO_Host_1_DP_AUX_CTL_PTR, (CY_GET_REG16(MDIO_Host_1_DP_AUX_CTL_PTR) & ~MDIO_Host_1_F1_CLR));	
}

/*******************************************************************************
*
* MDIO_Host_1_WriteData_C45()
*
*******************************************************************************/
uint8 MDIO_Host_1_WriteDataC45(uint8 op_mode, uint8 phy_addr, uint8 dev_addr, uint16 reg_data) // Writes data to the bus
{
   	uint16	control_bits;
	uint8   status_reg;

	/* Clear and Set the control register for writing */
	MDIO_Host_1_CONTROL_REG &= MDIO_Host_1_ENABLE;
	MDIO_Host_1_CONTROL_REG |= MDIO_Host_1_WRITE;
	
   	/* Set the control bits and write in the fifo f0 */
   	control_bits = 0x0002+((uint16)op_mode<<12)+(((uint16)phy_addr)<<7)+(((uint16)dev_addr)<<2);
   	CY_SET_REG16(MDIO_Host_1_FIFO_F0_PTR, control_bits);
   
   	/* Write data bits in the fifo f0 */
   	CY_SET_REG16(MDIO_Host_1_FIFO_F0_PTR, reg_data);
    
   	/* Start Transmission */
   	MDIO_Host_1_CONTROL_REG |= MDIO_Host_1_START;
	
	/* Wait till the transmission is completed */
	while ( MDIO_Host_1_StatusRegister != MDIO_Host_1_MDIO_STS_CMPLT );
	
	/* Clear hardware status register */
	status_reg = MDIO_Host_1_STATUS_REG;
	
	/* Clear software status register */
	MDIO_Host_1_StatusRegister = 0x00u;
    
    return ((status_reg)? 0 : 1);
}

/*******************************************************************************
*
* MDIO_Host_1_ReadData_C45()
*
*******************************************************************************/
uint8 MDIO_Host_1_ReadDataC45(uint8 op_mode, uint8 phy_addr, uint8 dev_addr, uint16 *regData) // Read data from the bus
{
   	uint16	control_bits;
	uint8 status_reg;

	/* Clear and Set the control register for writing */
	MDIO_Host_1_CONTROL_REG &= MDIO_Host_1_ENABLE;
	MDIO_Host_1_CONTROL_REG |= MDIO_Host_1_READ;
	
   	/* Set the control bits and write in the fifo f0 */
   	control_bits = 0x0003+((uint16)op_mode<<12)+(((uint16)phy_addr)<<7)+(((uint16)dev_addr)<<2);
   	CY_SET_REG16(MDIO_Host_1_FIFO_F0_PTR, control_bits);
    
   	/* Start Transmission */
   	MDIO_Host_1_CONTROL_REG |= MDIO_Host_1_START;
	
	/* Wait till the transmission is completed */
	while ( MDIO_Host_1_StatusRegister != MDIO_Host_1_MDIO_STS_CMPLT );
	
	/* Check if device acked */
	status_reg = MDIO_Host_1_STATUS_REG;
	
	MDIO_Host_1_StatusRegister = 0x00u;
	
	*regData = MDIO_Host_1_data_bits;
	
	return ((status_reg)? 0 : 1);
}

/*******************************************************************************
*
* MDIO_Host_WriteData_C22()
*
*******************************************************************************/
void 	MDIO_Host_1_WriteDataC22(uint8 phy_addr, uint8 dev_addr, uint16 reg_data)
{
   	uint16	control_bits;

	/* Clear and Set the control register for writing */
	MDIO_Host_1_CONTROL_REG &= MDIO_Host_1_ENABLE;
	MDIO_Host_1_CONTROL_REG |= MDIO_Host_1_WRITE;
	
   	/* Set the control bits and write in the fifo f0 */
   	control_bits = 0x5002+(((uint16)phy_addr)<<7)+(((uint16)dev_addr)<<2);
   	CY_SET_REG16(MDIO_Host_1_FIFO_F0_PTR, control_bits);
   
   	/* Write data bits in the fifo f0 */
   	CY_SET_REG16(MDIO_Host_1_FIFO_F0_PTR, reg_data);
    
   	/* Start Transmission */
   	MDIO_Host_1_CONTROL_REG |= MDIO_Host_1_START;
}

/*******************************************************************************
*
* MDIO_Host_ReadData_C22()
*
*******************************************************************************/
uint16 	MDIO_Host_1_ReadDataC22(uint8 phy_addr, uint8 dev_addr)
{
   	uint16	control_bits;

	/* Clear and Set the control register for writing */
	MDIO_Host_1_CONTROL_REG &= MDIO_Host_1_ENABLE;
	MDIO_Host_1_CONTROL_REG |= MDIO_Host_1_READ;
	
   	/* Set the control bits and write in the fifo f0 */
   	control_bits = 0x6003+(((uint16)phy_addr)<<7)+(((uint16)dev_addr)<<2);
   	CY_SET_REG16(MDIO_Host_1_FIFO_F0_PTR, control_bits);
    
   	/* Start Transmission */
   	MDIO_Host_1_CONTROL_REG |= MDIO_Host_1_START;
	
	while ( MDIO_Host_1_StatusRegister != MDIO_Host_1_MDIO_STS_CMPLT );
	
	MDIO_Host_1_StatusRegister = 0x00u;
	
	return MDIO_Host_1_data_bits;
}

/*******************************************************************************
*
* MDIO_Host__ClearStatus()
*
*******************************************************************************/
void  MDIO_Host_1_ClearStatus(void)
{
	MDIO_Host_1_StatusRegister = 0x00u;
}

/* [] END OF FILE */
