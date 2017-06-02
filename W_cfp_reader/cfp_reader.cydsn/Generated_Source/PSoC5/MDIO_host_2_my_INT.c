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

#include "MDIO_host_2.h"
//#include <device.h>
#include <project.h>

/* Data received MDIO Host */
volatile uint16 MDIO_host_2_data_bits;

/* Internal Status Register */
volatile uint8  MDIO_host_2_StatusRegister;

CY_ISR(MDIO_host_2_ISR_InterruptHandler)
{
	/* Get Data from FIFO f1 */
	MDIO_host_2_data_bits = CY_GET_REG16(MDIO_host_2_FIFO_F1_PTR);
	
	/* Clear control register */
	MDIO_host_2_CONTROL_REG &= MDIO_host_2_ENABLE;
	
	/* Set complete status bit */
	MDIO_host_2_StatusRegister = MDIO_host_2_MDIO_STS_CMPLT;
	
    /*  Place your Interrupt code here. */
    /* `#START CounterISR_Interrupt` */

    /* `#END` */
}




/* [] END OF FILE */
