/* ========================================
 *
 * Copyright FiberTreid, 2016
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF FiberTreid.
 *
 * ========================================
*/
#include "project.h"
#include "stdio.h"



/* Firmware Constants */
#define SPECIAL_COR_REGISTER    0xA000  /* Special COR Register address */
#define SPECIAL_COR_MODIFIER    0xA200  /* Special address to modify the COR Register */
#define BASE_MDIO_ADDRESS       0x8000  /* Start address for the incremental address variable */
#define MAX_MDIO_ADDRESS        0xA500  /* Maximum address supported in this firmware */
#define INC_ADDRESS             0x0100  /* Incremental value for the adddress */
#define RANDOM_CONST            0xDEAD  /* Random value to generate write/read data */
//#define RANDOM_CONST            0x1  /* Random value to generate write/read data */
#define ENABLE_MDIO             0x20    /* Enable bit for the MDIO Component */


#define USBFS_DEVICE    (0u)
/* The buffer size is equal to the maximum packet size of the IN and OUT bulk
* endpoints.
*/
#define USBUART_BUFFER_SIZE (64u)
#define LINE_STR_LENGTH     (20u)


uint16 cur_psw[2];//,read_MDIO[133];

/* MDIO Host Variables */
uint16 HostAddress    = BASE_MDIO_ADDRESS;    /* Address data for the MDIO frames */
uint16 HostData       = 0x0000;               /* Read data for the MDIO frames */


/* State Constants */
#define STATE_WRITE 0
#define STATE_READ  1


/* Device Address of MDIO Interface (constant) */
static uint8  MdioDevAddr = 0x01; //PMA/PMD
static uint8  MdioPhyAddr = 0x00;

/* Local prototypes */
uint8_t analiz_rx_data(uint8_t *rx_buffer);



/* Internal Status Register */
extern uint8  MDIO_host_2_StatusRegister;

uint16 read_MDIO_data=0;



/* Interrupt Prototypes */
CY_ISR_PROTO(ISR_TMR1);
CY_ISR_PROTO(ISR_MDIO);

int main(void)
{
    CYBIT  first_enter = 0;
    //CYBIT test=0;
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    uint16 count=0,count_rx=0;
    uint8 buffer[USBUART_BUFFER_SIZE];//, strk[10];
    

    uint8 state;

    CyGlobalIntEnable;

    
     /* Start USBFS operation with 5-V operation. */
    USBUART_1_Start(USBFS_DEVICE, USBUART_1_5V_OPERATION);  
    MDIO_host_2_Init(); 	

    
   /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    Clock_2_Enable();
    Clock_1_Enable();
//    Clock_3_Enable();
    PWM_1_Start();
    PWM_2_Start();

         ISR_MDIO_Start();
    ISR_TMR1_Start();
    
        /* Start ISRs */
    ISR_TMR1_StartEx (ISR_TMR1);
    ISR_MDIO_StartEx (ISR_MDIO);

    LED_1_Write(1);
    LED_2_Write(1);
    LED_3_Write(1);
    LED_4_data_Write(1);
    
    Timer_1_Start();
    
    for(;;)
    {      
        /* Host can send double SET_INTERFACE request. */
        if (0u != USBUART_1_IsConfigurationChanged())
        {
            /* Initialize IN endpoints when device is configured. */
            if (0u != USBUART_1_GetConfiguration())
            {
                /* Enumeration is done, enable OUT endpoint to receive data 
                 * from host. */
                USBUART_1_CDC_Init();
            }
        }

        /* Service USB CDC when device is configured. */
        if (0u != USBUART_1_GetConfiguration())
        {
            /* Check for input data from host. */
            if (0u != USBUART_1_DataIsReady())
            {
                /* Read received data and re-enable OUT endpoint. */
                count = USBUART_1_GetAll(buffer);

               // if (0u != count)
                 if (count)
                {
                    /* Wait until component is ready to send data to host. */
                    while (0u == USBUART_1_CDCIsReady())
                    {
                    }
                    
                    count_rx += count;
                    
                    if(count_rx>2)
                    {
                        count_rx=0;
                        LED_4_data_Write(0);
                        /* Send data back to host. */
                        analiz_rx_data(buffer);
                    }
                        
                    
                    /* If the last sent packet is exactly the maximum packet 
                    *  size, it is followed by a zero-length packet to assure
                    *  that the end of the segment is properly identified by 
                    *  the terminal.
                    */
                    if (USBUART_BUFFER_SIZE == count)
                    {
                        /* Wait until component is ready to send data to PC. */
                        while (0u == USBUART_1_CDCIsReady())
                        {
                        }

                        /* Send zero-length packet to PC. */
                        USBUART_1_PutData(NULL, 0u);
                    }
                }
            }


            /* Check for Line settings change. */
            state = USBUART_1_IsLineChanged();
            if (0u != state)
            {
                /* Output on LCD Line Control settings. */
                if (0u != (state & USBUART_1_LINE_CONTROL_CHANGED))
                {                   
                    /* Get string to output. */
                    state = USBUART_1_GetLineControl();
                    
                    if(0u != (state & USBUART_1_LINE_CONTROL_DTR))//connect terminal
                    {
                       if(!first_enter)
                        {
                          first_enter = 1;  
                          USBUART_1_PutString("Hello from Cypress!");
                          LED_3_Write(0);
                        }
                    }
                    else    //disconnect terminal
                    {
                        first_enter = 0;
                        LED_3_Write(1);
                    }
                }
            }
        }
        //        CyDelayUs(10);
    }
}

/*******************************************************************************
* Function Name: analiz_rx_data
********************************************************************************
* Summary:
*  Analiz rx packet and send acknowledg
*  
* 
* Parameters:
*  None
*
* Return:
*  None
*
********************************************************************************/
uint8_t analiz_rx_data(uint8_t *rx_buffer)
{
    uint8_t tx_data[3],strk[10];//,tmp_byte=0;
    uint16_t count_word =0;
    CYBIT is_word=1;
    
    
    switch(rx_buffer[0])
    {
//        case 'D'://set MdioDevAddr
//         //    Debug_MDIO_1_Write(1);
//            MdioDevAddr = rx_buffer[2];
//            USBUART_1_PutString("DOK");
//           //  Debug_MDIO_1_Write(0);
//            break;
//        
//        case 'H'://set MdioPhyAddr
//          //  Debug_MDIO_1_Write(1);
//            MdioPhyAddr = rx_buffer[2];
//            USBUART_1_PutString("HOK");
//            //Debug_MDIO_1_Write(0);
//            break;
            
        case 'A'://set addr reg
           // Debug_MDIO_1_Write(1);
            HostAddress = (rx_buffer[1]<<8)|rx_buffer[2];
            MDIO_host_2_SetAddrC45( MdioPhyAddr, MdioDevAddr, HostAddress );
            USBUART_1_PutString("AOK");
            //Debug_MDIO_1_Write(0);
            break;
            
        case 'W'://write one word
            HostData = (rx_buffer[1]<<8)|rx_buffer[2];
            MDIO_host_2_WriteDataC45(MdioPhyAddr, MdioDevAddr, HostData);
            USBUART_1_PutString("WOK");
             break;
            
        case 'R'://read one word
                MDIO_host_2_ReadDataC45( MdioPhyAddr, MdioDevAddr, &read_MDIO_data );
                tx_data[0]=(read_MDIO_data>>8)&0xFF;
                tx_data[1]=(read_MDIO_data)&0xFF;
                USBUART_1_PutData(tx_data,2);
            break;
            
        case 'C'://read one BYTE with increment
                count_word = ((rx_buffer[1]<<8)|rx_buffer[2])+1;
                //count_word = 132;
            //    MDIO_host_2_SetAddrC45( MdioPhyAddr, MdioDevAddr, 0x8000 );
                while(count_word)
                {
                    MDIO_host_2_PosReadDataC45( MdioPhyAddr, MdioDevAddr, &read_MDIO_data );
                    if(is_word)
                    {
                        is_word = 0;
                        tx_data[0]=(read_MDIO_data>>8)&0xFF;
                        tx_data[1]=(read_MDIO_data)&0xFF;
                         
                        USBUART_1_PutData(tx_data,2);
                        --count_word;
                         
                        /* Wait until component is ready to send data to PC. */
                        while (0u == USBUART_1_CDCIsReady())
                        {
                        }
                    }
                    else
                    {
                        is_word = 1;
                    }
                }
            break;
                
        case 'V'://read one WORD with increment
                count_word = ((rx_buffer[1]<<8)|rx_buffer[2])+1;
                //count_word = 132;
            //    MDIO_host_2_SetAddrC45( MdioPhyAddr, MdioDevAddr, 0x8000 );
                while(count_word)
                {
                    MDIO_host_2_PosReadDataC45( MdioPhyAddr, MdioDevAddr, &read_MDIO_data );
                    tx_data[0]=(read_MDIO_data>>8)&0xFF;
                    tx_data[1]=(read_MDIO_data)&0xFF;
                    USBUART_1_PutData(tx_data,2);
                    --count_word;
                     /* Wait until component is ready to send data to PC. */
                    while (0u == USBUART_1_CDCIsReady())
                    {
                    }
                    //CyDelayUs(10);
                }
            break;
            
        case 'P'://reset mod
                MOD_RST_Write(0);
                CyDelay(100);
                MOD_RST_Write(1);
                USBUART_1_PutString("POK");
            break;
                
        case 'S'://mod abs
                if(MOD_ABS_Read())
                    USBUART_1_PutString("S00");
                else
                    USBUART_1_PutString("S01");
            break;
                
                
        default:
            USBUART_1_PutString("RX:unknown data");
             return 0;
            break;
    }
    
    
    
  
//     if(rx_buffer[0] == 'a')/* Send address frame */                    
//        {
//            USBUART_1_PutString("SET MDIO address: 0x8000\n\r");
//            MDIO_host_2_SetAddrC45( MdioPhyAddr, MdioDevAddr, 0x8000u );
//        }
//        else
//        if(rx_buffer[0] == 'a')/* Send address frame */                    
//        {
//            USBUART_1_PutString("SET MDIO address: 0x8000\n\r");
//            MDIO_host_2_SetAddrC45( MdioPhyAddr, MdioDevAddr, 0x8000u );
//        }
//        else
//        if(rx_buffer[0] == 'q')/* Send address frame */                    
//        {
//            USBUART_1_PutString("SET MDIO address: 0x8201\n\r");
//            MDIO_host_2_SetAddrC45( MdioPhyAddr, MdioDevAddr, 0x8201u );
//        }
//        else
//        if(rx_buffer[0] == 'w')/* Send address frame */                    
//        {
//            USBUART_1_PutString("Read MDIO:");
//            MDIO_host_2_ReadDataC45( MdioPhyAddr, MdioDevAddr, &read_MDIO_data );
//
//            sprintf((char *)strk,"0x%04X\n\r",read_MDIO_data);
//            USBUART_1_PutString((const char *)strk);
//        }
//        else
//        {
//             USBUART_1_PutString("RX:unknown data");
//        }
               
    return 1;
}

CY_ISR(ISR_TMR1)    //200ms
{
     /*200 ms*/
    LED_4_data_Write(1);
}


CY_ISR(ISR_MDIO)
{
   MDIO_host_2_StatusRegister=1; 
}



/* [] END OF FILE */
