
//`#start header` -- edit after this line, do not edit this line
// ========================================
//
// Copyright YOUR COMPANY, THE YEAR
// All Rights Reserved
// UNPUBLISHED, LICENSED SOFTWARE.
//
// CONFIDENTIAL AND PROPRIETARY INFORMATION
// WHICH IS THE PROPERTY OF your company.
//
// ========================================
/*
*  Status Register Definition
*  +=======+---------+------+------+------+-----+---------+---------+---------+
*  |  Bit  |    7    |  6   |  5   |  4   |  3  |    2    |    1    |    0    |
*  +=======+---------+------+------+------+-----+---------+---------+---------+
*  | Desc  |interrupt|                unused              |  idle   |  n_full |
*  +=======+---------+------+------+------+-----+---------+---------+---------+
*
*    n_full        =>  0 = FIFO not full event has not occured 
*                      1 = FIFO not full event has occured
*
*    idle          =>  0 = Transmitter is not in the idle state
*                      1 = Transmitter is in the idle state
*/
`include "cypress.v"
//`#end` -- edit above this line, do not edit this line
// Generated on 01/10/2017 at 15:56
// Component: MDIO_host_my_v
module MDIO_host_my_v (
	output wire debug,
	output wire Interrupt,
	output reg mdc,
	output reg mdio_out,
	input wire clock,
	input wire mdio_in
);

//`#start body` -- edit after this line, do not edit this line

//        Your code goes here

    /**************************************************************************/
    /* Internal Signals                                                       */
    /**************************************************************************/
    reg [2:0] 	State;				/* 8 states requires 3-bits */
   // reg         f1_load;            /* Loads FIFO F1 from the datapath ALU */
	wire		stop_frame;		/* Stop frame pulse */
    reg         start_frame_d;      /* Delay start_frame */
  //  wire      rising_mdc;	        /* MDC rising edge detected */
  //  wire		falling_mdc;	    /* MDC falling edge detected */
  //  wire	    ta_bits;		    /* Set when turning around bits drive the MDIO */
    wire		ld_count;			/* Load the counter */
    wire		en_count;			/* Enable the counter */
    wire        synced_clock;       /* Internal clock net synchronized to bus_clk */
    wire        tc;                 /* Count7 terminal count output */
    wire	    so;			    	/* Shift out */
    wire [1:0]  ce0;		    	/* A0 == D0 */
    wire [1:0]  ce1;		    	/* A0 == D1 */
    reg  [2:0]  cfg;            	/* Datapath control store address */
    wire [6:0]  counter;            /* Count7 counter output */
    wire [7:0]  control;		    /* MDIO component control register */
    wire        nc1, nc2, nc3, nc4; /* nc bits connected to unused datapath output flags */
	
	wire f0_blk_stat;	/* Set to 1 if the FIFO is empty */
	wire f0_bus_stat;	/* Set to 1 if the FIFO is not full */
    wire f1_bus_stat;   /* Set to 1 if the FIFO is not full */
  

 	localparam MDIO_STATE_IDLE 		= 3'd0;
	localparam MDIO_STATE_START 	= 3'd1;
	localparam MDIO_STATE_SEND_PRMB = 3'd2;
	localparam MDIO_STATE_SEND_DATA = 3'd3;
    localparam MDIO_STATE_READ_DATA	= 4'd4;
	localparam MDIO_STATE_STOP 	= 3'd7;  
    
    /**************************************************************************/
    /* Clock Synchronization                                                  */
    /**************************************************************************/
    cy_psoc3_udb_clock_enable_v1_0 #(.sync_mode(`TRUE)) ClkSync
    (
        /* input  */    .clock_in(clock),
        /* input  */    .enable(1'b1),
        /* output */    .clock_out(synced_clock)
    );  
    /***************************************************************************
    *       Status Register Implementation                                      
    ***************************************************************************/   
    /*    RX Status Register bit location (bits 6-2 unused)    */
    localparam MDIO_NOT_FULL    = 3'd0;
    localparam MDIO_IDLE        = 3'd1;
	localparam MDIO_SEND_16     = 3'd2;
	localparam MDIO_CMPLT     	= 3'd3;

    wire [7:0] status_val;
    assign status_val[MDIO_NOT_FULL]	= f0_bus_stat; 
    assign status_val[MDIO_IDLE]		= (State == MDIO_STATE_IDLE);
	assign status_val[MDIO_SEND_16]		= ((State == MDIO_STATE_SEND_DATA) & (counter == 7'd31));
	assign status_val[MDIO_CMPLT]		= f1_bus_stat;
    assign status_val[7:4] = 4'b0;      /* Unused bits of status */    
	
    /**************************************************************************/
    /* General Purpose Control and Status Registers                           */
    /**************************************************************************/
    /* MDIO Status Register */
	cy_psoc3_status #(.cy_force_order(`TRUE), .cy_md_select(8'b11111111)) MdioStatusReg (
	/* input [07:00] */ .status(status_val), // Status Bits
	/* input */ .reset(1'b0), // Reset from interconnect
	/* input */ .clock(synced_clock) // Clock used for registering data
	);

	
	/**************************************************************************/
	/* MDIO Control Register */
	/**************************************************************************/
	cy_psoc3_control #(.cy_init_value (8'b00000000), .cy_force_order(`TRUE), 
					   	   .cy_ctrl_mode_1(8'h00), .cy_ctrl_mode_0(8'hFF)) MdioControlReg
    	(
		/* input          */  .clock(synced_clock),
		/* output [07:00] */  .control(control)
    	);

    wire mdio_rw = control[0];	   	/* Read = 1, Write = 0 */
    
	/**************************************************************************/
    /* Count7 block used to count bits on the MDIO frame                      */
    /**************************************************************************/
    cy_psoc3_count7 #(.cy_period(7'd63),.cy_route_ld(`TRUE),.cy_route_en(`TRUE),.cy_alt_mode(`FALSE)) MdioCounter
    (
        /*  input          */  .clock(synced_clock),
        /*  input          */  .reset(1'b0),
        /*  input          */  .load(ld_count),     /* Re-load the counter */
        /*  input          */  .enable(en_count),   	
        /*  output [06:00] */  .count(counter),
        /*  output         */  .tc(tc)
    );

	assign ld_count = (State == MDIO_STATE_IDLE);	// Load the counter
	assign en_count = ~(State == MDIO_STATE_IDLE);	// enable the counter
	
	/* Datapath Configuration addresses */
	localparam MDIO_CONFIG_IDLE   	= 3'd0;		/* IDLE */
	localparam MDIO_CONFIG_LOAD   	= 3'd1;		/* Load from the FIFO */
	localparam MDIO_CONFIG_SHIFT 	= 3'd2;		/* Shift a bit out (also used when idle) */
	localparam MDIO_CONFIG_READ 	= 3'd3;		/* Shift a bit in (also used when idle) */
	
	assign debug = ((counter < 7'd49) ? 1'b1 : 1'b0);
	
	
	/**************************************************************************/
    /* Interrupt generation logic                                             */
    /**************************************************************************/
	assign Interrupt = (State == MDIO_STATE_STOP);
	
	always @(posedge synced_clock) 
	begin
		case (State) 
			MDIO_STATE_IDLE:
				if (~f0_blk_stat) 
				begin
					State <= MDIO_STATE_START;
					cfg <= MDIO_CONFIG_LOAD;
				end
				else
					cfg <= MDIO_CONFIG_IDLE;
				
				
			MDIO_STATE_START:
				begin
					State <= MDIO_STATE_SEND_PRMB;
					cfg <= MDIO_CONFIG_IDLE;
				end
				
			MDIO_STATE_SEND_PRMB: 
				begin
					if(tc)	//32 bits
					begin
						State <= (mdio_rw == 0) ? MDIO_STATE_SEND_DATA : MDIO_STATE_READ_DATA;
					end
				end
				
			MDIO_STATE_SEND_DATA: /* write to slave*/
				begin
					if( counter == 7'd32 )
						cfg <= MDIO_CONFIG_LOAD;
					else
						begin
							cfg <= ( mdc )? MDIO_CONFIG_SHIFT : MDIO_CONFIG_IDLE;
						end
					
					if(tc)//32 bits
						State <= MDIO_STATE_STOP;
				end		
			
			MDIO_STATE_READ_DATA: /* read to slave*/
			begin
			if(counter == 7'd32)
					cfg <= MDIO_CONFIG_LOAD;
				else
					begin
						if(counter < 7'd49)
							cfg <= ( mdc )? MDIO_CONFIG_SHIFT : MDIO_CONFIG_IDLE;
						else
							cfg <= ( mdc )? MDIO_CONFIG_IDLE : MDIO_CONFIG_SHIFT;
					end
				if(tc)	//32 bits
					State <= MDIO_STATE_STOP;
			end
				
			MDIO_STATE_STOP:
				begin
					cfg <= MDIO_CONFIG_IDLE;
					if (~f0_blk_stat) 
						State <= MDIO_STATE_START;
					else 
						begin
						State <= MDIO_STATE_IDLE;
						end
				end
			
			default: 
				begin
				State <= MDIO_STATE_IDLE;
				cfg <= MDIO_CONFIG_IDLE;
				end
				
		endcase
	end
	

	always @(posedge synced_clock) begin
		case (State)
			MDIO_STATE_IDLE,
			MDIO_STATE_STOP: 
				begin
					mdio_out <= 1'b1;
					mdc <= 1'b0;
				end
				
			MDIO_STATE_START,
			MDIO_STATE_SEND_PRMB:
				begin
					mdio_out <= 1'b1;
					mdc <= ~mdc;
				end
			
			MDIO_STATE_READ_DATA,
			MDIO_STATE_SEND_DATA:
				begin
					mdio_out <= so; 
					mdc <= ~mdc;
				end
				
			default: 
				begin
					mdio_out <= 1'b1;
					mdc <= 1'b0;
				end
		endcase
	end
	
	
    /**************************************************************************/
    /* 16-bit datapath configured as MDIO shift registers and parallel to    */
    /* serial interface.                                                      */
    /*                                                                        */
    /**************************************************************************/

cy_psoc3_dp16 #(.cy_dpconfig_a(
{
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_A0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM0:  Idle*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_A0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC___F0, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM1:  Load F0 - A0*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_A0,
    `CS_SHFT_OP___SL, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM2:  Shift A0*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_A0,
    `CS_SHFT_OP___SL, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM3:  shift*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_A0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM4:                                          */
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_A0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM5:                                          */
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_A0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM6:                                          */
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_A0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM7:                                          */
    8'hFF, 8'h00,  /*CFG9:                                          */
    8'hFF, 8'hFF,  /*CFG11-10:                                       Phy Address Match*/
    `SC_CMPB_A1_D1, `SC_CMPA_A0_D1, `SC_CI_B_ARITH,
    `SC_CI_A_ARITH, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
    `SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
    `SC_SI_A_ROUTE, /*CFG13-12:                                          */
    `SC_A0_SRC_ACC, `SC_SHIFT_SL, 1'h0,
    1'h0, `SC_FIFO1_BUS, `SC_FIFO0_BUS,
    `SC_MSB_DSBL, `SC_MSB_BIT7, `SC_MSB_NOCHN,
    `SC_FB_NOCHN, `SC_CMP1_NOCHN,
    `SC_CMP0_NOCHN, /*CFG15-14:                                          */
    10'h00, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
    `SC_FIFO__EDGE,`SC_FIFO_ASYNC,`SC_EXTCRC_DSBL,
    `SC_WRK16CAT_DSBL /*CFG17-16:                                          */
}
), .cy_dpconfig_b(
{
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_A0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM0:  Idle*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_A0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC___F0, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM1:  Load F0 - A0*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_A0,
    `CS_SHFT_OP___SL, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM2:  Shift A0*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_A0,
    `CS_SHFT_OP___SL, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM3:  shift*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM4:                                          */
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM5:                                          */
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM6:                                          */
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM7:                                          */
    8'hFF, 8'h00,  /*CFG9:                                          */
    8'hFF, 8'hFF,  /*CFG11-10:                                       Phy Address Match*/
    `SC_CMPB_A1_D1, `SC_CMPA_A0_D1, `SC_CI_B_ARITH,
    `SC_CI_A_ARITH, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
    `SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
    `SC_SI_A_CHAIN, /*CFG13-12:                                          */
    `SC_A0_SRC_ACC, `SC_SHIFT_SL, 1'h0,
    1'h0, `SC_FIFO1_BUS, `SC_FIFO0_BUS,
    `SC_MSB_DSBL, `SC_MSB_BIT7, `SC_MSB_NOCHN,
    `SC_FB_NOCHN, `SC_CMP1_NOCHN,
    `SC_CMP0_NOCHN, /*CFG15-14:                                          */
    10'h00, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
    `SC_FIFO__EDGE,`SC_FIFO_ASYNC,`SC_EXTCRC_DSBL,
    `SC_WRK16CAT_DSBL /*CFG17-16:                                          */
}
)) cntrl16(
        /*  input                   */  .reset(1'b0),
        /*  input                   */  .clk(synced_clock),	//Datapath clock input
        /*  input   [02:00]         */  .cs_addr(cfg),
		/*  input                   */  .route_si(mdio_in),/* MDIO input to the shift register */
        /*  input                   */  .route_ci(1'b0),
        /*  input                   */  .f0_load(1'b0),
        /*  input                   */  .f1_load(1'b0),/* Loads FIFO 1 from A0 */
        /*  input                   */  .d0_load(1'b0),
        /*  input                   */  .d1_load(1'b0),
        /*  output  [01:00]         */  .ce0(),   /*Accumulator 0 = Data register 0 */
        /*  output  [01:00]         */  .cl0(),
        /*  output  [01:00]         */  .z0(),
        /*  output  [01:00]         */  .ff0(),
        /*  output  [01:00]         */  .ce1(), /* Accumulator [0|1] = Data register 1 */
        /*  output  [01:00]         */  .cl1(),
        /*  output  [01:00]         */  .z1(),
        /*  output  [01:00]         */  .ff1(),
        /*  output  [01:00]         */  .ov_msb(),
        /*  output  [01:00]         */  .co_msb(),
        /*  output  [01:00]         */  .cmsb(),
        /*  output  [01:00]         */  .so({so,nc2}),	//Shift Out
        /*  output  [01:00]         */  .f0_bus_stat({f0_bus_stat,nc1}),
        /*  output  [01:00]         */  .f0_blk_stat({f0_blk_stat,nc3}),
        /*  output  [01:00]         */  .f1_bus_stat({f1_bus_stat,nc4}),
        /*  output  [01:00]         */  .f1_blk_stat()
);
//`#end` -- edit above this line, do not edit this line
endmodule
//`#start footer` -- edit after this line, do not edit this line
//`#end` -- edit above this line, do not edit this line


















