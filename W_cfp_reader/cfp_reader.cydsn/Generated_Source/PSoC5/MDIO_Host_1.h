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
#if !defined(MDIO_Host_1_H)
#define MDIO_Host_1_H
#include "cytypes.h"
#include "cyfitter.h"
#include "cylib.h"

/***************************************************** 
* Parameters from the Component Customizer
******************************************************/

/* PSoC5 chip */
#define MDIO_Host_1_PSOC5_CHIP  (CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_5A)

/***************************************************** 
* Constants used by the firmware APIs
******************************************************/
/* Bit field definitions for the Control Register */
#define MDIO_Host_1_ENABLE				(0x01u)
#define MDIO_Host_1_START				(0x02u)
#define MDIO_Host_1_RW					(0x04u)

/* Bit field definitions for the Status Register */
#define MDIO_Host_1_MDIO_STS_CMPLT		0x08

/* Bit field definitions for the UDB registers */
#define MDIO_Host_1_F0_CLR         	(0x0101u)
#define MDIO_Host_1_F1_CLR         	(0x0202u)
#define MDIO_Host_1_COUNT7_EN          (0x20u)

/* Definition for Write/Read bits */
#define	MDIO_Host_1_READ				(0x04u)
#define	MDIO_Host_1_WRITE				(0x00u)

#define MDIO_Host_1_POS_READ_PATTERN	(0x02u)
#define MDIO_Host_1_READ_PATTERN		(0x03u)
#define MDIO_Host_1_WRITE_PATTERN		(0x01u)
#define MDIO_Host_1_ADDRESS_PATTERN	(0x00u)

/* Interrupt controller constants */
#define MDIO_Host_1_ISR_NUMBER         (MDIO_Host_1_ISR__INTC_NUMBER)
#define MDIO_Host_1_ISR_PRIORITY       (MDIO_Host_1_ISR__INTC_PRIOR_NUM)

/* Operation Modes */
#define MDIO_Host_1_C45_ADDR		0x0
#define MDIO_Host_1_C45_READ		0x3
#define MDIO_Host_1_C45_WRITE		0x1
#define MDIO_Host_1_C45_POSR		0x2

/***************************************************** 
* UDB Registers
******************************************************/
#define MDIO_Host_1_CONTROL_REG                (*(reg8 *) 	MDIO_Host_1_B_MDIO_Host_AsyncCtl_MdioControlReg__CONTROL_REG)
#define MDIO_Host_1_CONTROL_PTR                ( (reg8 *) 	MDIO_Host_1_B_MDIO_Host_AsyncCtl_MdioControlReg__CONTROL_REG)
#define MDIO_Host_1_STATUS_REG                 (*(reg8 *) 	MDIO_Host_1_B_MDIO_Host_MdioStatusReg__STATUS_REG)
#define MDIO_Host_1_STATUS_PTR                 ( (reg8 *) 	MDIO_Host_1_B_MDIO_Host_MdioStatusReg__STATUS_REG)
#define MDIO_Host_1_CNT7_AUX_CTL_REG   		(*(reg8 *)  MDIO_Host_1_B_MDIO_Host_MdioCounter__CONTROL_AUX_CTL_REG)
#define MDIO_Host_1_CNT7_AUX_CTL_PTR   		( (reg8 *)  MDIO_Host_1_B_MDIO_Host_MdioCounter__CONTROL_AUX_CTL_REG)
#define MDIO_Host_1_DP_AUX_CTL_REG     		(*(reg16 *) MDIO_Host_1_B_MDIO_Host_MdioDataPath_u0__DP_AUX_CTL_REG)
#define MDIO_Host_1_DP_AUX_CTL_PTR     		( (reg16 *) MDIO_Host_1_B_MDIO_Host_MdioDataPath_u0__DP_AUX_CTL_REG)
#define MDIO_Host_1_FIFO_F1_REG        		(*(reg16 *)	MDIO_Host_1_B_MDIO_Host_MdioDataPath_u0__F1_REG)
#define MDIO_Host_1_FIFO_F1_PTR       	 		( (reg16 *)	MDIO_Host_1_B_MDIO_Host_MdioDataPath_u0__F1_REG)
#define MDIO_Host_1_FIFO_F0_REG        		(*(reg16 *) MDIO_Host_1_B_MDIO_Host_MdioDataPath_u0__F0_REG)
#define MDIO_Host_1_FIFO_F0_PTR        		( (reg16 *) MDIO_Host_1_B_MDIO_Host_MdioDataPath_u0__F0_REG)

/***************************************************** 
* API Function Prototypes 
******************************************************/
void    MDIO_Host_1_Start(void);
void    MDIO_Host_1_Stop(void);
void    MDIO_Host_1_Init(void);
void    MDIO_Host_1_Enable(void);
void    MDIO_Host_1_EnableInt(void);
void    MDIO_Host_1_DisableInt(void);
uint8  	MDIO_Host_1_GetStatus(void) CYREENTRANT;
void 	MDIO_Host_1_ClearInternalFIFOs(void);
uint8 	MDIO_Host_1_WriteDataC45(uint8 op_mode, uint8 phy_addr, uint8 dev_addr, uint16 reg_data); // Writes data to the bus (C45)
uint8 	MDIO_Host_1_ReadDataC45(uint8 op_mode, uint8 phy_addr, uint8 dev_addr, uint16 *regData);  // Reads data from the bus (C45)
void 	MDIO_Host_1_WriteDataC22(uint8 phy_addr, uint8 dev_addr, uint16 reg_data); // Writes data to the bus (C22)
uint16 	MDIO_Host_1_ReadDataC22(uint8 phy_addr, uint8 dev_addr); // Read data from the bus (C22)
void  	MDIO_Host_1_ClearStatus(void);	

/* Interrupt prototype */
CY_ISR_PROTO(MDIO_Host_1_ISR_InterruptHandler);


#endif // header sentry

//[] END OF FILE
