/*******************************************************************************
* File Name: MDIO_Interface.h
* Version 1.20
*
* Description:
*  This file provides constants and parameter values and API definition for the
*  MDIO Slave Component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_MDIO_SLAVE_MDIO_Interface_H)
#define CY_MDIO_SLAVE_MDIO_Interface_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"

/* Error message for removed MDIO_Interface_bMDIO_CtlReg due to the resource optimization */
#ifdef MDIO_Interface_bMDIO_CtlReg__REMOVED
    #error MDIO_Interface_v1_20 detected with a constant 0 for the enable. This will prevent the component from operating.
#endif /* MDIO_Interface_bMDIO_CtlReg__REMOVED */


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define MDIO_Interface_OP_MODE                (1u)
#define MDIO_Interface_BASIC_MODE             (0u == MDIO_Interface_OP_MODE)
#define MDIO_Interface_ADVANCED_MODE          (1u == MDIO_Interface_OP_MODE)

#define MDIO_Interface_PHYADDR_MODE           (0u)
#define MDIO_Interface_PHYADDR_FIRMWARE       (0u == MDIO_Interface_PHYADDR_MODE)
#define MDIO_Interface_PHYADDR_HARDWARE       (1u == MDIO_Interface_PHYADDR_MODE)


/***************************************
*     Data Struct Definitions
***************************************/

/* Low power Mode API Support */
typedef struct
{
    uint8 enableState;
    uint8 interruptState;
} MDIO_Interface_BACKUP_STRUCT;

/* Structure that contains configuration data for each register */
typedef struct
{
    uint16 mask;                /* 16 bit writeable mask */
    uint8  ctrlReg;             /* Control register value */
    uint8  reserved;            /* Reserved */
}
MDIO_Interface_REG_CONFIG_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void  MDIO_Interface_Start(void)                              ;
void  MDIO_Interface_Init(void)                               ;
void  MDIO_Interface_Enable(void)                             ;
void  MDIO_Interface_Stop(void)                               ;
void  MDIO_Interface_Sleep(void)                              ;
void  MDIO_Interface_Wakeup(void)                             ;
void  MDIO_Interface_SaveConfig(void)                         ;
void  MDIO_Interface_RestoreConfig(void)                      ;
void  MDIO_Interface_EnableInt(void)                          ;
void  MDIO_Interface_DisableInt(void)                         ;
void  MDIO_Interface_SetPhyAddress(uint8 phyAddr)             ;
void  MDIO_Interface_SetDevAddress(uint8 devAddr)             ;
void  MDIO_Interface_UpdatePhyAddress(void)                   ;

#if(MDIO_Interface_BASIC_MODE)

    void  MDIO_Interface_PutData(uint16 regData)              ;
    void  MDIO_Interface_ProcessFrame(uint8 * opCode, uint16 * regData)
                                                                ;
#endif /* MDIO_Interface_BASIC_MODE */

#if(MDIO_Interface_ADVANCED_MODE)

    uint8   MDIO_Interface_GetData(uint16 address, const uint16 * regData, uint16 numWords)
                                                                ;
    uint8   MDIO_Interface_SetData(uint16 address, const uint16 * regData, uint16 numWords)
                                                                ;
    uint8   MDIO_Interface_SetBits(uint16 address, uint16 regBits)
                                                                ;
    uint16  MDIO_Interface_GetAddress(void)                   ;

    uint8 * MDIO_Interface_GetConfiguration(uint8 regSpace)   ;

    /* Macros to quickly determine register page data width and memory type */
    #define MDIO_Interface_REG_SPACE_IS_SRAM(x)       (0u != ((MDIO_Interface_PAGE_MEM_TYPE   >> (x)) & 0x01u))
    #define MDIO_Interface_REG_SPACE_IS_8BIT(x)       (0u == ((MDIO_Interface_PAGE_DATA_WIDTH >> (x)) & 0x01u))
    #define MDIO_Interface_REG_SPACE_IS_16BIT(x)      (0u != ((MDIO_Interface_PAGE_DATA_WIDTH >> (x)) & 0x01u))

    /* Check if DMA channel is currently being serviced by DMAC */
    #define MDIO_Interface_DMA_ACTIVE(mask)           (0u == (MDIO_Interface_FW_DMA_STS_REG & (mask)))

    /* Clear DMA completion status */
    #define MDIO_Interface_CLEAR_FW_DMA_STATUS        ((void)MDIO_Interface_FW_DMA_STS_REG)

#endif /* MDIO_Interface_ADVANCED_MODE */


/***************************************
*   Variable with external linkage
***************************************/

extern uint8 MDIO_Interface_initVar;


/***************************************
*           API Constants
***************************************/

#define MDIO_Interface_DISABLED                   (0x00u)
#define MDIO_Interface_ENABLED                    (0x01u)
#define MDIO_Interface_ADDR_PATTERN               (0xC000u)
#define MDIO_Interface_PHYADDR_POS                (5u)
#define MDIO_Interface_PHYADDR_MASK               (31u)
#define MDIO_Interface_OPCODE_POS                 (10u)
#define MDIO_Interface_OPCODE_MASK                (0x03u)

/* Operation code */
#define MDIO_Interface_ADDRESS                    (0x00u)
#define MDIO_Interface_WRITE                      (0x01u)
#define MDIO_Interface_READ                       (0x03u)
#define MDIO_Interface_POS_READ                   (0x02u)

/* Device address (device type) */
#define MDIO_Interface_PMA_PMD                    (0x01u)
#define MDIO_Interface_WIS                        (0x02u)
#define MDIO_Interface_PCS                        (0x03u)
#define MDIO_Interface_PHY_XS                     (0x04u)
#define MDIO_Interface_DTE_XS                     (0x05u)

#if(MDIO_Interface_ADVANCED_MODE)

    /* Number of register spaces */
    #define MDIO_Interface_NUMBER_OF_PAGES        (6u)
    /* Bitmask for register spaces */
    #define MDIO_Interface_PAGE_MASK              (0xFFu >> (8u - MDIO_Interface_NUMBER_OF_PAGES))

    /* Bitmap that specifies data memory type of each register space */
    #define MDIO_Interface_PAGE_MEM_TYPE          (0x3Fu)
    #define MDIO_Interface_ALL_PAGES_IN_SRAM      (MDIO_Interface_PAGE_MASK == MDIO_Interface_PAGE_MEM_TYPE)
    #define MDIO_Interface_ALL_PAGES_IN_FLASH     (0u == MDIO_Interface_PAGE_MEM_TYPE)

    /* Bitmap that specifies the config memory type of each register space */
    #define MDIO_Interface_CFG_MEM_TYPE           (0x30u)
    #define MDIO_Interface_ALL_CFG_IN_SRAM        (MDIO_Interface_PAGE_MASK == MDIO_Interface_CFG_MEM_TYPE)
    #define MDIO_Interface_ALL_CFG_IN_FLASH       (0u == MDIO_Interface_CFG_MEM_TYPE)

    /* Bitmap that specifies data width of each register space */
    #define MDIO_Interface_PAGE_DATA_WIDTH        (0x3Fu)
    #define MDIO_Interface_ALL_PAGES_16BIT        (MDIO_Interface_PAGE_MASK == MDIO_Interface_PAGE_DATA_WIDTH)
    #define MDIO_Interface_ALL_PAGES_8BIT         (0u == MDIO_Interface_PAGE_DATA_WIDTH)

    /* Address conversion constants */
    #define MDIO_Interface_HI16_ADDR_MASK         (0xFFFF0000Lu)
    #define MDIO_Interface_LO16_ADDR_MASK         (0x0000FFFFLu)
    #define MDIO_Interface_CPU_SRAM_BASE          (0x1FFF0000Lu)
    #define MDIO_Interface_DMA_SRAM_BASE          (0x20000000Lu)

    /* Register space 1 definition */
    #define MDIO_Interface_CFP_NVR_IDX (1u)
    #define MDIO_Interface_CFP_NVR_START (0x8000u)
    #define MDIO_Interface_CFP_NVR_END (0x81FFu)
    #define MDIO_Interface_CFP_NVR_PTR MDIO_Interface_registerPage_1
    #define MDIO_Interface_CFP_NVR_CONFIG_PTR MDIO_Interface_registerConfig_1

    /* Register space 2 definition */
    #define MDIO_Interface_VENDOR_NVR_IDX (2u)
    #define MDIO_Interface_VENDOR_NVR_START (0x8400u)
    #define MDIO_Interface_VENDOR_NVR_END (0x84FFu)
    #define MDIO_Interface_VENDOR_NVR_PTR MDIO_Interface_registerPage_2
    #define MDIO_Interface_VENDOR_NVR_CONFIG_PTR MDIO_Interface_registerConfig_2

    /* Register space 3 definition */
    #define MDIO_Interface_USER_NVR_IDX (3u)
    #define MDIO_Interface_USER_NVR_START (0x8800u)
    #define MDIO_Interface_USER_NVR_END (0x88FFu)
    #define MDIO_Interface_USER_NVR_PTR MDIO_Interface_registerPage_3
    #define MDIO_Interface_USER_NVR_CONFIG_PTR MDIO_Interface_registerConfig_3

    /* Register space 4 definition */
    #define MDIO_Interface_CFP_MODULE_VR_IDX (4u)
    #define MDIO_Interface_CFP_MODULE_VR_START (0xA000u)
    #define MDIO_Interface_CFP_MODULE_VR_END (0xA07Fu)
    #define MDIO_Interface_CFP_MODULE_VR_PTR MDIO_Interface_registerPage_4
    #define MDIO_Interface_CFP_MODULE_VR_CONFIG_PTR MDIO_Interface_registerConfig_4

    /* Register space 5 definition */
    #define MDIO_Interface_NETWORK_LANE_VR_IDX (5u)
    #define MDIO_Interface_NETWORK_LANE_VR_START (0xA200u)
    #define MDIO_Interface_NETWORK_LANE_VR_END (0xA2FFu)
    #define MDIO_Interface_NETWORK_LANE_VR_PTR MDIO_Interface_registerPage_5
    #define MDIO_Interface_NETWORK_LANE_VR_CONFIG_PTR MDIO_Interface_registerConfig_5

    /* Register space 6 definition */
    #define MDIO_Interface_HOST_LANE_VR_IDX (6u)
    #define MDIO_Interface_HOST_LANE_VR_START (0xA400u)
    #define MDIO_Interface_HOST_LANE_VR_END (0xA47Fu)
    #define MDIO_Interface_HOST_LANE_VR_PTR MDIO_Interface_registerPage_6
    #define MDIO_Interface_HOST_LANE_VR_CONFIG_PTR MDIO_Interface_registerConfig_6



    /* Address analyzer DMA configuration */
    /* Register page start and end address DMAs */
    #define MDIO_Interface_PAGE_ADDR_DMA_BYTES_PER_BURST          (2u)
    #define MDIO_Interface_PAGE_ADDR_DMA_REQUEST_PER_BURST        (1u)
    #define MDIO_Interface_PAGE_ADDR_DMA_TD_SIZE                  (MDIO_Interface_NUMBER_OF_PAGES * 2u)
    #if(CY_PSOC3)
        #define MDIO_Interface_PAGE_ADDR_DMA_CFG                  (TD_INC_SRC_ADR | TD_SWAP_EN)
        #define MDIO_Interface_FW_DMA1_CFG                        (TD_INC_SRC_ADR | TD_INC_DST_ADR | \
                                                                        MDIO_Interface_FwDMA1__TD_TERMOUT_EN)
    #else
        #define MDIO_Interface_PAGE_ADDR_DMA_CFG                  (TD_INC_SRC_ADR)
        #define MDIO_Interface_FW_DMA1_CFG                        (TD_INC_SRC_ADR | TD_INC_DST_ADR | TD_SWAP_EN | \
                                                                        MDIO_Interface_FwDMA1__TD_TERMOUT_EN)
    #endif /* CY_PSOC3 */

    /* Register physical memory address DMA, Write DMA, Read DMA */
    #define MDIO_Interface_REG_MEM_DMA_BYTES_PER_BURST            (2u)
    #define MDIO_Interface_REG_MEM_DMA_REQUEST_PER_BURST          (1u)
    #define MDIO_Interface_REG_MEM_DMA_TD_SIZE                    (2u)
    #define MDIO_Interface_REG_MEM_ADDR_DMA_TD_NUM                (7u)

    /* Register page info DMA */
    #define MDIO_Interface_PAGE_INFO_DMA_BYTES_PER_BURST          (2u)
    #define MDIO_Interface_PAGE_INFO_DMA_REQUEST_PER_BURST        (0u)
    #define MDIO_Interface_PAGE_INFO_DMA_TD_SIZE                  (8u)

    /* Register configuration DMAs */
    #define MDIO_Interface_CFG_DMA1_BYTES_PER_BURST               (4u)
    #define MDIO_Interface_CFG_DMA1_REQUEST_PER_BURST             (0u)
    #define MDIO_Interface_CFG_DMA1_TD_SIZE                       (4u)
    #define MDIO_Interface_CFG_DMA2_BYTES_PER_BURST               (1u)
    #define MDIO_Interface_CFG_DMA2_REQUEST_PER_BURST             (0u)
    #define MDIO_Interface_CFG_DMA2_TD1_SIZE                      (2u)
    #define MDIO_Interface_CFG_DMA2_TD2_SIZE                      (1u)
    #if(CY_PSOC3)
        #define MDIO_Interface_CFG_DMA1_CFG                       (TD_INC_SRC_ADR | TD_INC_DST_ADR | TD_SWAP_EN | \
                                                                        MDIO_Interface_CfgDMA1__TD_TERMOUT_EN)
        #define MDIO_Interface_CTRL_BITS_OFFSET                   (3u)
    #else
        #define MDIO_Interface_CFG_DMA1_CFG                       (TD_INC_SRC_ADR | TD_INC_DST_ADR | \
                                                                        MDIO_Interface_CfgDMA1__TD_TERMOUT_EN)
        #define MDIO_Interface_CTRL_BITS_OFFSET                   (2u)
    #endif /* CY_PSOC3 */

    /* Firmware DMA */
    #define MDIO_Interface_FW_DMA_BYTES_PER_BURST                 (2u)
    #define MDIO_Interface_FW_DMA_REQUEST_PER_BURST               (0u)
    #define MDIO_Interface_FW_DMA_TD_SIZE                         (2u)
    #define MDIO_Interface_NUM_OF_8BIT_REGS                       (2u)
    #define MDIO_Interface_NUM_OF_16BIT_REGS                      (1u)

    /* The data stored for each page contains the register space memory address
    * and the memory address of the configuration array associated with the
    * register space. The number of elements of the register page info array is
    * the number of register spaces multiply by two.
    */
    #define MDIO_Interface_PAGE_INFO_SIZE             (MDIO_Interface_NUMBER_OF_PAGES * 2u)

    /* Register space info size */
    #define MDIO_Interface_PAGE_INFO_INC              (8u)

    /* Number of DMA channels */
    #define MDIO_Interface_NUMBER_OF_CHANNELS         (10u)

    #define MDIO_Interface_TIMEOUT_PERIOD             (255u)

#endif /* MDIO_Interface_ADVANCED_MODE */


/***************************************
*    Enumerated Types and Parameters
***************************************/


/***************************************
*    Initial Parameter Constants
***************************************/

#define MDIO_Interface_INIT_PHYADDR           (0u)
#define MDIO_Interface_INIT_DEVADDR           (1u)


/***************************************
*             Registers
***************************************/

/* Control register */
#define MDIO_Interface_CONTROL_REG           (* (reg8 *) MDIO_Interface_bMDIO_CtlReg__CONTROL_REG)
#define MDIO_Interface_CONTROL_PTR           (  (reg8 *) MDIO_Interface_bMDIO_CtlReg__CONTROL_REG)

/* Physical address status register */
#if(MDIO_Interface_PHYADDR_HARDWARE)
    #define MDIO_Interface_PHYADDR_REG       (* (reg8 *) MDIO_Interface_bMDIO_Hardware_PhyAddr__STATUS_REG)
    #define MDIO_Interface_PHYADDR_PTR       (  (reg8 *) MDIO_Interface_bMDIO_Hardware_PhyAddr__STATUS_REG)
#endif /* MDIO_Interface_PHYADDR_HARDWARE */

/* Bit counter control and period registers */
#define MDIO_Interface_BCNT_AUX_CTL_REG      (* (reg8 *) MDIO_Interface_bMDIO_BitCounter__CONTROL_AUX_CTL_REG)
#define MDIO_Interface_BCNT_AUX_CTL_PTR      (  (reg8 *) MDIO_Interface_bMDIO_BitCounter__CONTROL_AUX_CTL_REG)
#define MDIO_Interface_BCNT_PERIOD_REG       (* (reg8 *) MDIO_Interface_bMDIO_BitCounter__PERIOD_REG)
#define MDIO_Interface_BCNT_PERIOD_PTR       (  (reg8 *) MDIO_Interface_bMDIO_BitCounter__PERIOD_REG)

/* Physical and device address pattern register */
#if(CY_PSOC3)
    #define MDIO_Interface_ADDR_PTRN_PTR     (  (reg16 *) MDIO_Interface_bMDIO_MdioDp_u0__D0_REG)
#else
    #define MDIO_Interface_ADDR_PTRN_PTR     (  (reg16 *) MDIO_Interface_bMDIO_MdioDp_u0__16BIT_D0_REG)
#endif /* CY_PSOC3 */

/* The MDIO Frame processing block FIFO buffers. In the basic mode CPU reads/writes MDIO
*  Frame processing registers, therefore the proper address space should be
*  accessed.
*/
#if(MDIO_Interface_BASIC_MODE && CY_PSOC3)
    #define MDIO_Interface_FP_FIFO0_PTR      (  (reg16 *) MDIO_Interface_bMDIO_MdioDp_u0__F0_REG)
    #define MDIO_Interface_FP_FIFO1_PTR      (  (reg16 *) MDIO_Interface_bMDIO_MdioDp_u0__F1_REG)
#else
    #define MDIO_Interface_FP_FIFO0_PTR      (  (reg16 *) MDIO_Interface_bMDIO_MdioDp_u0__16BIT_F0_REG)
    #define MDIO_Interface_FP_FIFO1_PTR      (  (reg16 *) MDIO_Interface_bMDIO_MdioDp_u0__16BIT_F1_REG)
#endif /* MDIO_Interface_BASIC_MODE && CY_PSOC3 */

#define MDIO_Interface_FP_AUX_CTL0_REG       (* (reg8  *) MDIO_Interface_bMDIO_MdioDp_u0__DP_AUX_CTL_REG)
#define MDIO_Interface_FP_AUX_CTL1_REG       (* (reg8  *) MDIO_Interface_bMDIO_MdioDp_u1__DP_AUX_CTL_REG)

#if(MDIO_Interface_ADVANCED_MODE)

    /* Address Analyzer module registers */
    #define MDIO_Interface_PAGE_START_PTR    (  (reg16 *) MDIO_Interface_bMDIO_Advanced_AddrComp_u0__16BIT_F0_REG)
    #define MDIO_Interface_PAGE_END_PTR      (  (reg16 *) MDIO_Interface_bMDIO_Advanced_AddrComp_u0__16BIT_F1_REG)
    #define MDIO_Interface_REG_IDX_PTR       (  (reg16 *) MDIO_Interface_bMDIO_Advanced_AddrComp_u0__16BIT_A0_REG)
    #define MDIO_Interface_INFO_ADDR_PTR     (  (reg16 *) MDIO_Interface_bMDIO_Advanced_AddrCalc_u0__16BIT_A0_REG)
    #define MDIO_Interface_PAGE_INFO_PTR     (  (reg16 *) MDIO_Interface_bMDIO_Advanced_AddrCalc_u0__16BIT_F0_REG)
    #define MDIO_Interface_REG_OFFSET_PTR    (  (reg16 *) MDIO_Interface_bMDIO_Advanced_AddrCalc_u0__16BIT_A1_REG)
    #define MDIO_Interface_REG_ADDR_PTR      (  (reg16 *) MDIO_Interface_bMDIO_Advanced_AddrCalc_u0__16BIT_A0_REG)
    #define MDIO_Interface_REG_MASK_PTR      (  (reg16 *) MDIO_Interface_bMDIO_MdioDp_u0__D1_REG)
    #define MDIO_Interface_REG_VAL_PTR       (  (reg16 *) MDIO_Interface_bMDIO_Advanced_FwAlu_u0__16BIT_A0_REG)

    #define MDIO_Interface_REG_ATTR_REG      (* (reg8 *)  MDIO_Interface_bMDIO_Advanced_CfgReg__CONTROL_REG)
    #define MDIO_Interface_REG_ATTR_PTR      (  (reg8 *)  MDIO_Interface_bMDIO_Advanced_CfgReg__CONTROL_REG)
    #define MDIO_Interface_MEM_TYPE_REG      (* (reg8 *)  MDIO_Interface_bMDIO_Advanced_MemTypeCfg__CONTROL_REG)
    #define MDIO_Interface_MEM_TYPE_PTR      (  (reg8 *)  MDIO_Interface_bMDIO_Advanced_MemTypeCfg__CONTROL_REG)
    #define MDIO_Interface_PAGE_WIDTH_REG    (* (reg8 *)  MDIO_Interface_bMDIO_Advanced_DataWidthCfg__CONTROL_REG)
    #define MDIO_Interface_PAGE_WIDTH_PTR    (  (reg8 *)  MDIO_Interface_bMDIO_Advanced_DataWidthCfg__CONTROL_REG)

    #define MDIO_Interface_AC_AUX_CTL0_REG   (* (reg8  *) MDIO_Interface_bMDIO_Advanced_AddrComp_u0__DP_AUX_CTL_REG)
    #define MDIO_Interface_AC_AUX_CTL1_REG   (* (reg8  *) MDIO_Interface_bMDIO_Advanced_AddrComp_u1__DP_AUX_CTL_REG)

    #if(CY_PSOC3)
        #define MDIO_Interface_LAST_ADDR_PTR (  (reg16 *) MDIO_Interface_bMDIO_Advanced_AddrComp_u0__A1_REG)
        #define MDIO_Interface_INFO_INC_PTR  (  (reg16 *) MDIO_Interface_bMDIO_Advanced_AddrCalc_u0__D1_REG)
        #define MDIO_Interface_INFO_BASE_PTR (  (reg16 *) MDIO_Interface_bMDIO_Advanced_AddrCalc_u0__D0_REG)
        #define MDIO_Interface_REG_BITS_PTR  (  (reg16 *) MDIO_Interface_bMDIO_Advanced_FwAlu_u0__A1_REG)
    #else
        #define MDIO_Interface_LAST_ADDR_PTR (  (reg16 *) MDIO_Interface_bMDIO_Advanced_AddrComp_u0__16BIT_A1_REG)
        #define MDIO_Interface_INFO_INC_PTR  (  (reg16 *) MDIO_Interface_bMDIO_Advanced_AddrCalc_u0__16BIT_D1_REG)
        #define MDIO_Interface_INFO_BASE_PTR (  (reg16 *) MDIO_Interface_bMDIO_Advanced_AddrCalc_u0__16BIT_D0_REG)
        #define MDIO_Interface_REG_BITS_PTR  (  (reg16 *) MDIO_Interface_bMDIO_Advanced_FwAlu_u0__16BIT_A1_REG)
    #endif /* CY_PSOC3 */

    /* Firmware DMA status register */
    #define MDIO_Interface_FW_DMA_STS_REG    (* (reg8 *)  MDIO_Interface_bMDIO_Advanced_FwDmaStatus__STATUS_REG)

#endif /* MDIO_Interface_ADVANCED_MODE */


/***************************************
*       Register Constants
***************************************/

/* Enabling and interrupt generation */
#define MDIO_Interface_EN             (0x01u)
#define MDIO_Interface_INT_EN         (0x02u)
#define MDIO_Interface_TRIG_DMA       (0x04u)

/* Bit counter enabling and period */
#define MDIO_Interface_BCNT_EN        (0x20u)
#define MDIO_Interface_BCNT_PER       (0x1Eu)

/* FIFOs clear bit masks */
#define MDIO_Interface_F0_CLEAR       (0x01u)
#define MDIO_Interface_F1_CLEAR       (0x02u)
#define MDIO_Interface_FX_CLEAR       (0x03u)

/* Firmware DMA status register masks */
#define MDIO_Interface_FW_DMA1_MASK   (0x01u)
#define MDIO_Interface_FW_DMA2_MASK   (0x02u)

#endif /* CY_MDIO_SLAVE_MDIO_Interface_H */


/* [] END OF FILE */
