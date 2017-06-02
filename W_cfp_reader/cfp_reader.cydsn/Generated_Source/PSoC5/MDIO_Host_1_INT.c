/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "MDIO_Host_1.h"
//#include <device.h>
#include <project.h>

/* Data received MDIO Host */
volatile uint16 MDIO_Host_1_data_bits;

/* Internal Status Register */
volatile uint8  MDIO_Host_1_StatusRegister;

CY_ISR(MDIO_Host_1_ISR_InterruptHandler)
{
	/* Get Data from FIFO f1 */
	MDIO_Host_1_data_bits = CY_GET_REG16(MDIO_Host_1_FIFO_F1_PTR);
	
	/* Clear control register */
	MDIO_Host_1_CONTROL_REG &= MDIO_Host_1_ENABLE;
	
	/* Set complete status bit */
	MDIO_Host_1_StatusRegister = MDIO_Host_1_MDIO_STS_CMPLT;
	
    /*  Place your Interrupt code here. */
    /* `#START CounterISR_Interrupt` */

    /* `#END` */
}


/* [] END OF FILE */
