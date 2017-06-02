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

#if !defined(MDIO_host_2_H)
#define MDIO_host_2_H
#include "cytypes.h"
#include "cyfitter.h"
#include "cylib.h"

/***************************************************** 
* Parameters from the Component Customizer
******************************************************/

/* PSoC5 chip */
#define MDIO_host_2_PSOC5_CHIP  (CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_5A)

/***************************************************** 
* Constants used by the firmware APIs
******************************************************/
/* Bit field definitions for the Control Register */
#define MDIO_host_2_ENABLE				(0x01u)
#define MDIO_host_2_START				(0x02u)
#define MDIO_host_2_RW					(0x04u)

/***************************************
*           API Constants               
***************************************/
#define MDIO_host_2_NOT_FULL   (0x01u)
#define MDIO_host_2_IDLE       (0x02u)
#define MDIO_host_2_SEND_16    (0x04u)
#define MDIO_host_2_CMPLT      (0x08u)

/* Bit field definitions for the UDB registers */
#define MDIO_host_2_F0_CLR         	(0x0101u)
#define MDIO_host_2_F1_CLR         	(0x0202u)
#define MDIO_host_2_COUNT7_EN          (0x20u)

/* Definition for Write/Read bits */
#define	MDIO_host_2_READ				(0x01u)
#define	MDIO_host_2_WRITE				(0x00u)

#define MDIO_host_2_POS_READ_PATTERN	(0x02u)
#define MDIO_host_2_READ_PATTERN		(0x03u)
#define MDIO_host_2_WRITE_PATTERN		(0x01u)
#define MDIO_host_2_ADDRESS_PATTERN	(0x00u)

/* Interrupt controller constants */
//#define MDIO_host_2_ISR_NUMBER         (MDIO_host_2_ISR__INTC_NUMBER)
//#define MDIO_host_2_ISR_PRIORITY       (MDIO_host_2_ISR__INTC_PRIOR_NUM)

/* Operation Modes */
#define MDIO_host_2_C45_ADDR		0x0
#define MDIO_host_2_C45_READ		0x3
#define MDIO_host_2_C45_WRITE		0x1
#define MDIO_host_2_C45_POSR		0x2

/***************************************************** 
* UDB Registers
******************************************************/
#define MDIO_host_2_CONTROL_REG                (*(reg8 *) 	MDIO_host_2_MdioControlReg__CONTROL_REG)
#define MDIO_host_2_CONTROL_PTR                ( (reg8 *) 	MDIO_host_2_MdioControlReg__CONTROL_REG)
#define MDIO_host_2_STATUS_REG                 (*(reg8 *) 	MDIO_host_2_MdioStatusReg__STATUS_REG)
#define MDIO_host_2_STATUS_PTR                 ( (reg8 *) 	MDIO_host_2_MdioStatusReg__STATUS_REG)
#define MDIO_host_2_CNT7_AUX_CTL_REG   		(*(reg8 *)  MDIO_host_2_MdioCounter__CONTROL_AUX_CTL_REG)
#define MDIO_host_2_CNT7_AUX_CTL_PTR   		( (reg8 *)  MDIO_host_2_MdioCounter__CONTROL_AUX_CTL_REG)
#define MDIO_host_2_DP_AUX_CTL_REG     		(*(reg16 *) MDIO_host_2_cntrl16_u0__DP_AUX_CTL_REG)
#define MDIO_host_2_DP_AUX_CTL_PTR     		( (reg16 *) MDIO_host_2_cntrl16_u0__DP_AUX_CTL_REG)
#define MDIO_host_2_FIFO_F1_REG        		(*(reg16 *)	MDIO_host_2_cntrl16_u0__F1_REG)
#define MDIO_host_2_FIFO_F1_PTR       	 		( (reg16 *)	MDIO_host_2_cntrl16_u0__F1_REG)
#define MDIO_host_2_FIFO_F0_REG        		(*(reg16 *) MDIO_host_2_cntrl16_u0__F0_REG)
#define MDIO_host_2_FIFO_F0_PTR        		( (reg16 *) MDIO_host_2_cntrl16_u0__F0_REG)
#define MDIO_host_2_PERIOD_PTR                 ( (reg8 *) 	MDIO_host_2_MdioCounter__PERIOD_REG)
#define MDIO_host_2_PERIOD_REG                 (*(reg8 *) 	MDIO_host_2_MdioCounter__PERIOD_REG)
#define MDIO_host_2_COUNT_PTR                  ( (reg8 *) 	MDIO_host_2_MdioCounter__COUNT_REG)
#define MDIO_host_2_COUNT_REG                  (*(reg8 *) 	MDIO_host_2_MdioCounter__COUNT_REG)
#define MDIO_host_2_A0_REG                     (*(reg16 *) MDIO_host_2_cntrl16_u0__A0_REG)
#define MDIO_host_2_A0_PTR                     ( (reg16 *) MDIO_host_2_cntrl16_u0__A0_REG)
#define MDIO_host_2_A1_REG                     (*(reg16 *) MDIO_host_2_cntrl16_u0__A1_REG)
#define MDIO_host_2_A1_PTR                     ( (reg16 *) MDIO_host_2_cntrl16_u0__A1_REG)

/***************************************************** 
* API Function Prototypes 
******************************************************/
void    MDIO_host_2_Start(void);
void    MDIO_host_2_Stop(void);
void    MDIO_host_2_Init(void);
void    MDIO_host_2_Enable(void);
void    MDIO_host_2_EnableInt(void);
void    MDIO_host_2_DisableInt(void);
uint8  	MDIO_host_2_GetStatus(void) CYREENTRANT;
void 	MDIO_host_2_ClearInternalFIFOs(void);
uint8   MDIO_host_2_SetAddrC45(uint8 phy_addr, uint8 dev_addr, uint16 reg_data); // Set Addr reg
uint8 	MDIO_host_2_WriteDataC45(uint8 phy_addr, uint8 dev_addr, uint16 reg_data); // Writes data to the bus (C45)
uint8 	MDIO_host_2_ReadDataC45(uint8 phy_addr, uint8 dev_addr, uint16 *regData);  // Reads data from the bus (C45)
uint8 	MDIO_host_2_PosReadDataC45(uint8 phy_addr, uint8 dev_addr, uint16 *regData);  // Reads data from the bus witch increment add(C45)
void  	MDIO_host_2_ClearStatus(void);	

/* Interrupt prototype */
//CY_ISR_PROTO(MDIO_host_2_ISR_InterruptHandler);


#endif // header sentry


/* [] END OF FILE */
