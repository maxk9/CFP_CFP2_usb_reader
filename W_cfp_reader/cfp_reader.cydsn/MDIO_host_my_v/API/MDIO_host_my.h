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

#if !defined(`$INSTANCE_NAME`_H)
#define `$INSTANCE_NAME`_H
#include "cytypes.h"
#include "cyfitter.h"
#include "cylib.h"

/***************************************************** 
* Parameters from the Component Customizer
******************************************************/

/* PSoC5 chip */
#define `$INSTANCE_NAME`_PSOC5_CHIP  (CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_5A)

/***************************************************** 
* Constants used by the firmware APIs
******************************************************/
/* Bit field definitions for the Control Register */
#define `$INSTANCE_NAME`_ENABLE				(0x01u)
#define `$INSTANCE_NAME`_START				(0x02u)
#define `$INSTANCE_NAME`_RW					(0x04u)

/***************************************
*           API Constants               
***************************************/
#define `$INSTANCE_NAME`_NOT_FULL   (0x01u)
#define `$INSTANCE_NAME`_IDLE       (0x02u)
#define `$INSTANCE_NAME`_SEND_16    (0x04u)
#define `$INSTANCE_NAME`_CMPLT      (0x08u)

/* Bit field definitions for the UDB registers */
#define `$INSTANCE_NAME`_F0_CLR         	(0x0101u)
#define `$INSTANCE_NAME`_F1_CLR         	(0x0202u)
#define `$INSTANCE_NAME`_COUNT7_EN          (0x20u)

/* Definition for Write/Read bits */
#define	`$INSTANCE_NAME`_READ				(0x01u)
#define	`$INSTANCE_NAME`_WRITE				(0x00u)

#define `$INSTANCE_NAME`_POS_READ_PATTERN	(0x02u)
#define `$INSTANCE_NAME`_READ_PATTERN		(0x03u)
#define `$INSTANCE_NAME`_WRITE_PATTERN		(0x01u)
#define `$INSTANCE_NAME`_ADDRESS_PATTERN	(0x00u)

/* Interrupt controller constants */
//#define `$INSTANCE_NAME`_ISR_NUMBER         (`$INSTANCE_NAME`_ISR__INTC_NUMBER)
//#define `$INSTANCE_NAME`_ISR_PRIORITY       (`$INSTANCE_NAME`_ISR__INTC_PRIOR_NUM)

/* Operation Modes */
#define `$INSTANCE_NAME`_C45_ADDR		0x0
#define `$INSTANCE_NAME`_C45_READ		0x3
#define `$INSTANCE_NAME`_C45_WRITE		0x1
#define `$INSTANCE_NAME`_C45_POSR		0x2

/***************************************************** 
* UDB Registers
******************************************************/
#define `$INSTANCE_NAME`_CONTROL_REG                (*(reg8 *) 	`$INSTANCE_NAME`_MdioControlReg__CONTROL_REG)
#define `$INSTANCE_NAME`_CONTROL_PTR                ( (reg8 *) 	`$INSTANCE_NAME`_MdioControlReg__CONTROL_REG)
#define `$INSTANCE_NAME`_STATUS_REG                 (*(reg8 *) 	`$INSTANCE_NAME`_MdioStatusReg__STATUS_REG)
#define `$INSTANCE_NAME`_STATUS_PTR                 ( (reg8 *) 	`$INSTANCE_NAME`_MdioStatusReg__STATUS_REG)
#define `$INSTANCE_NAME`_CNT7_AUX_CTL_REG   		(*(reg8 *)  `$INSTANCE_NAME`_MdioCounter__CONTROL_AUX_CTL_REG)
#define `$INSTANCE_NAME`_CNT7_AUX_CTL_PTR   		( (reg8 *)  `$INSTANCE_NAME`_MdioCounter__CONTROL_AUX_CTL_REG)
#define `$INSTANCE_NAME`_DP_AUX_CTL_REG     		(*(reg16 *) `$INSTANCE_NAME`_cntrl16_u0__DP_AUX_CTL_REG)
#define `$INSTANCE_NAME`_DP_AUX_CTL_PTR     		( (reg16 *) `$INSTANCE_NAME`_cntrl16_u0__DP_AUX_CTL_REG)
#define `$INSTANCE_NAME`_FIFO_F1_REG        		(*(reg16 *)	`$INSTANCE_NAME`_cntrl16_u0__F1_REG)
#define `$INSTANCE_NAME`_FIFO_F1_PTR       	 		( (reg16 *)	`$INSTANCE_NAME`_cntrl16_u0__F1_REG)
#define `$INSTANCE_NAME`_FIFO_F0_REG        		(*(reg16 *) `$INSTANCE_NAME`_cntrl16_u0__F0_REG)
#define `$INSTANCE_NAME`_FIFO_F0_PTR        		( (reg16 *) `$INSTANCE_NAME`_cntrl16_u0__F0_REG)
#define `$INSTANCE_NAME`_PERIOD_PTR                 ( (reg8 *) 	`$INSTANCE_NAME`_MdioCounter__PERIOD_REG)
#define `$INSTANCE_NAME`_PERIOD_REG                 (*(reg8 *) 	`$INSTANCE_NAME`_MdioCounter__PERIOD_REG)
#define `$INSTANCE_NAME`_COUNT_PTR                  ( (reg8 *) 	`$INSTANCE_NAME`_MdioCounter__COUNT_REG)
#define `$INSTANCE_NAME`_COUNT_REG                  (*(reg8 *) 	`$INSTANCE_NAME`_MdioCounter__COUNT_REG)
#define `$INSTANCE_NAME`_A0_REG                     (*(reg16 *) `$INSTANCE_NAME`_cntrl16_u0__A0_REG)
#define `$INSTANCE_NAME`_A0_PTR                     ( (reg16 *) `$INSTANCE_NAME`_cntrl16_u0__A0_REG)
#define `$INSTANCE_NAME`_A1_REG                     (*(reg16 *) `$INSTANCE_NAME`_cntrl16_u0__A1_REG)
#define `$INSTANCE_NAME`_A1_PTR                     ( (reg16 *) `$INSTANCE_NAME`_cntrl16_u0__A1_REG)

/***************************************************** 
* API Function Prototypes 
******************************************************/
void    `$INSTANCE_NAME`_Start(void);
void    `$INSTANCE_NAME`_Stop(void);
void    `$INSTANCE_NAME`_Init(void);
void    `$INSTANCE_NAME`_Enable(void);
void    `$INSTANCE_NAME`_EnableInt(void);
void    `$INSTANCE_NAME`_DisableInt(void);
uint8  	`$INSTANCE_NAME`_GetStatus(void) CYREENTRANT;
void 	`$INSTANCE_NAME`_ClearInternalFIFOs(void);
uint8   `$INSTANCE_NAME`_SetAddrC45(uint8 phy_addr, uint8 dev_addr, uint16 reg_data); // Set Addr reg
uint8 	`$INSTANCE_NAME`_WriteDataC45(uint8 phy_addr, uint8 dev_addr, uint16 reg_data); // Writes data to the bus (C45)
uint8 	`$INSTANCE_NAME`_ReadDataC45(uint8 phy_addr, uint8 dev_addr, uint16 *regData);  // Reads data from the bus (C45)
uint8 	`$INSTANCE_NAME`_PosReadDataC45(uint8 phy_addr, uint8 dev_addr, uint16 *regData);  // Reads data from the bus witch increment add(C45)
void  	`$INSTANCE_NAME`_ClearStatus(void);	

/* Interrupt prototype */
//CY_ISR_PROTO(`$INSTANCE_NAME`_ISR_InterruptHandler);


#endif // header sentry


/* [] END OF FILE */
