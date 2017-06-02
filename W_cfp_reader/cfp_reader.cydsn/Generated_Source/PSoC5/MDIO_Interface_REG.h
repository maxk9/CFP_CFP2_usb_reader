/*******************************************************************************
* File Name: MDIO_Interface_REG.h
* Version 1.20
*
* Description:
*  This file contains CFP register declaration for the MDIO Slave component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CFP_REGISTER_SET_MDIO_Interface_H)
#define CY_CFP_REGISTER_SET_MDIO_Interface_H

#if(MDIO_Interface_ADVANCED_MODE)

/* Size of each register space */
#define MDIO_Interface_REG_PAGE_1_SIZE (512u)
#define MDIO_Interface_REG_PAGE_2_SIZE (256u)
#define MDIO_Interface_REG_PAGE_3_SIZE (256u)
#define MDIO_Interface_REG_PAGE_4_SIZE (128u)
#define MDIO_Interface_REG_PAGE_5_SIZE (256u)
#define MDIO_Interface_REG_PAGE_6_SIZE (128u)


/* Page 1 register data */
extern uint16 MDIO_Interface_registerPage_1[MDIO_Interface_REG_PAGE_1_SIZE];
/* Page 2 register data */
extern uint16 MDIO_Interface_registerPage_2[MDIO_Interface_REG_PAGE_2_SIZE];
/* Page 3 register data */
extern uint16 MDIO_Interface_registerPage_3[MDIO_Interface_REG_PAGE_3_SIZE];
/* Page 4 register data */
extern uint16 MDIO_Interface_registerPage_4[MDIO_Interface_REG_PAGE_4_SIZE];
/* Page 5 register data */
extern uint16 MDIO_Interface_registerPage_5[MDIO_Interface_REG_PAGE_5_SIZE];
/* Page 6 register data */
extern uint16 MDIO_Interface_registerPage_6[MDIO_Interface_REG_PAGE_6_SIZE];
/* Page 1 register configuration */
extern const MDIO_Interface_REG_CONFIG_STRUCT CYCODE MDIO_Interface_registerConfig_1[MDIO_Interface_REG_PAGE_1_SIZE];
/* Page 2 register configuration */
extern const MDIO_Interface_REG_CONFIG_STRUCT CYCODE MDIO_Interface_registerConfig_2[MDIO_Interface_REG_PAGE_2_SIZE];
/* Page 3 register configuration */
extern const MDIO_Interface_REG_CONFIG_STRUCT CYCODE MDIO_Interface_registerConfig_3[MDIO_Interface_REG_PAGE_3_SIZE];
/* Page 4 register configuration */
extern const MDIO_Interface_REG_CONFIG_STRUCT CYCODE MDIO_Interface_registerConfig_4[MDIO_Interface_REG_PAGE_4_SIZE];
/* Page 5 register configuration */
extern MDIO_Interface_REG_CONFIG_STRUCT MDIO_Interface_registerConfig_5[MDIO_Interface_REG_PAGE_5_SIZE];
/* Page 6 register configuration */
extern MDIO_Interface_REG_CONFIG_STRUCT MDIO_Interface_registerConfig_6[MDIO_Interface_REG_PAGE_6_SIZE];


/* Register page info list (the start address of the register space memory
*  and the start address of the register configuration associated with the
*  register space.
*/
extern const uint16 * const CYCODE MDIO_Interface_pageInfoPtr[MDIO_Interface_PAGE_INFO_SIZE];

#endif /* MDIO_Interface_ADVANCED_MODE */

#endif /* CY_CFP_REGISTER_SET_MDIO_Interface_H */

/* [] END OF FILE */
