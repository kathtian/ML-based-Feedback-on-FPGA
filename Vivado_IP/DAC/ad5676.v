`timescale 1ns / 1ps
module ad5676(
	//100MHz clock
	input clk,
	input reset,
	input [15:0] dac1,
	input [15:0] dac2,
	input [15:0] dac3,
	input [15:0] dac4,
	input [15:0] dac5,
	input [15:0] dac6,
	input [15:0] dac7,
	input [15:0] dac8,

	output reg convertEnd,
		
	//Interface with DAC 
	output reg sdin,
	output reg sclk,	
	output reg sync_,
	output clr_,
	input sdo,	
	output ldac_,
	output reg reset_,
	output [63:0] tp
    );


/**** Parameters  ****/
//spi word length: 8'h16 --> 24 bit
parameter SHIFT_COUNTER=8'h16;
//Delay time between control registers write at bootup
parameter DELAY_TIME = 16'hF;

/**** Registers ****/
reg [15:0] delayCounter;
reg convertStartReg,convertStartRegReg;
reg [5:0] sclkCounter;
reg sclkReg;
reg [7:0] shiftCounter;
reg [23:0] shiftReg;
reg [15:0] dac1Reg,dac1RegReg;
reg [15:0] dac2Reg,dac2RegReg;
reg [15:0] dac3Reg,dac3RegReg;
reg [15:0] dac4Reg,dac4RegReg;
reg [15:0] dac5Reg,dac5RegReg;
reg [15:0] dac6Reg,dac6RegReg;
reg [15:0] dac7Reg,dac7RegReg;
reg [15:0] dac8Reg,dac8RegReg;

//state machine
reg [5:0] state, nextState;
parameter RESET_STATE=6'h0,W_REG1_1=6'h1,W_REG1_2=6'h2,W_REG1_3=6'h3;
parameter W_REG2_1=6'h4,W_REG2_2=6'h5,W_REG2_3=6'h6;
parameter W_REG3_1=6'h7,W_REG3_2=6'h8,W_REG3_3=6'h9;
parameter W_REG4_1=6'hA,W_REG4_2=6'hB,W_REG4_3=6'hC;
parameter W_DAC1_1=6'hD,W_DAC1_2=6'hE,W_DAC1_3=6'hF;
parameter W_DAC2_1=6'h10,W_DAC2_2=6'h11,W_DAC2_3=6'h12;
parameter W_DAC3_1=6'h13,W_DAC3_2=6'h14,W_DAC3_3=6'h15;
parameter W_DAC4_1=6'h16,W_DAC4_2=6'h17,W_DAC4_3=6'h18;
parameter W_DAC5_1=6'h19,W_DAC5_2=6'h1A,W_DAC5_3=6'h1B;
parameter W_DAC6_1=6'h1C,W_DAC6_2=6'h1D,W_DAC6_3=6'h1E;
parameter W_DAC7_1=6'h1F,W_DAC7_2=6'h20,W_DAC7_3=6'h21;
parameter W_DAC8_1=6'h22,W_DAC8_2=6'h23,W_DAC8_3=6'h24;
parameter DELAY1=6'h25,DELAY2=6'h26,DELAY3=6'h27,DELAY4=6'h28,DELAY5=6'h29;
parameter DELAY_DAC1=6'h2A,DELAY_DAC2=6'h2B,DELAY_DAC3=6'h2C,DELAY_DAC4=6'h2D;
parameter DELAY_DAC5=6'h2E,DELAY_DAC6=6'h2F,DELAY_DAC7=6'h30,DELAY_DAC8=6'h31;
parameter IDLE=6'h32;

/**** Logics ****/
//Not clear the chip.  Instead, set a DAC setpoint to all four channels at state@W_REG2_1
assign clr_ = 1'b1;
//Only use sync_ rising edge to latch dac register data
assign ldac_ = 1'b0;
//reset to clear all the DAC output to zero: PCB connect this to the chip RESET (active high).  Make it reverse
/*
always @(posedge clk)
begin
    if(reset) 
		reset_ <= 1'b0;
	else if((sclkReg==1'b0)&&(sclk==1'b1)&&(state==W_REG1_1))
		reset_ <= 1'b0;	
	else reset_ <= 1'b1;
end 
*/
always @(posedge clk) reset_ <= (~reset);	//used VCCIO_EN to reset: power on, VCCIO_EN = 0; then goes to high.
	
	
//input buffer
always @(posedge clk)
begin
	dac1Reg <= dac1;
	dac2Reg <= dac2;
	dac3Reg <= dac3;
	dac4Reg <= dac4;
	dac5Reg <= dac5;
	dac6Reg <= dac6;
	dac7Reg <= dac7;
	dac8Reg <= dac8;
end

always @(posedge clk)
begin
    if(reset) dac1RegReg <= 16'h0;
	else if((sclkReg==1'b0)&&(sclk==1'b1)&&(state==W_DAC1_1)) 
		dac1RegReg <= dac1Reg;	
	else dac1RegReg <= dac1RegReg;
end
always @(posedge clk)
begin
    if(reset) dac2RegReg <= 16'h0;
    else if((sclkReg==1'b0)&&(sclk==1'b1)&&(state==W_DAC2_1)) 
		dac2RegReg <= dac2Reg;	
	else dac2RegReg <= dac2RegReg;
end
always @(posedge clk)
begin
    if(reset) 
        dac3RegReg <= 16'h0;
	else if((sclkReg==1'b0)&&(sclk==1'b1)&&(state==W_DAC3_1)) 
		dac3RegReg <= dac3Reg;	
	else dac3RegReg <= dac3RegReg;
end
always @(posedge clk)
begin
    if(reset) dac4RegReg <= 16'h0;
    else if((sclkReg==1'b0)&&(sclk==1'b1)&&(state==W_DAC4_1)) 
		dac4RegReg <= dac4Reg;	
	else dac4RegReg <= dac4RegReg;
end

always @(posedge clk)
begin
    if(reset) dac5RegReg <= 16'h0;
	else if((sclkReg==1'b0)&&(sclk==1'b1)&&(state==W_DAC5_1)) 
		dac5RegReg <= dac5Reg;	
	else dac5RegReg <= dac5RegReg;
end
always @(posedge clk)
begin
    if(reset) dac6RegReg <= 16'h0;
	else if((sclkReg==1'b0)&&(sclk==1'b1)&&(state==W_DAC6_1)) 
		dac6RegReg <= dac6Reg;	
	else dac6RegReg <= dac6RegReg;
end
always @(posedge clk)
begin
    if(reset) dac7RegReg <= 16'h0;
	else if((sclkReg==1'b0)&&(sclk==1'b1)&&(state==W_DAC7_1)) 
		dac7RegReg <= dac7Reg;	
	else dac7RegReg <= dac7RegReg;
end
always @(posedge clk)
begin
    if(reset) dac8RegReg <= 16'h0;
	else if((sclkReg==1'b0)&&(sclk==1'b1)&&(state==W_DAC8_1)) 
		dac8RegReg <= dac8Reg;	
	else dac8RegReg <= dac8RegReg;
end
//sclk clock: desimation of fast clk to slower spi sclk clock
always @(posedge clk)
begin
	if(reset)
	sclkCounter <= 6'h0;
	else
	sclkCounter <= sclkCounter + 6'h1;	
end

always @(posedge clk)
	sclk <= sclkCounter[5];	

always @(posedge clk)
sclkReg <= sclk;

//convertEnd
always @(posedge clk)
begin
	if((state==RESET_STATE)||(state==IDLE))
	convertEnd <= 1'b1;
	else if((state==W_DAC1_1)||(state==W_DAC2_1)||(state==W_DAC3_1)||(state==W_DAC4_1)||(state==W_DAC5_1)||(state==W_DAC6_1)||(state==W_DAC7_1)||(state==W_DAC8_1))
	convertEnd <= 1'b0;
	else
	convertEnd <= convertEnd;
end

	
//sync_: @rising edge sclk. Falls before first spi bit, rise after last bit. 
always @(posedge clk)
begin
	if(reset)
	sync_ <= 1'h1;	
	else if((sclkReg==1'b0)&&(sclk==1'b1))
		begin
			if((state==W_REG1_1)||(state==W_REG2_1)||(state==W_REG3_1)||(state==W_REG4_1)||
			   (state==W_REG1_2)||(state==W_REG2_2)||(state==W_REG3_2)||(state==W_REG4_2)||
			   (state==W_DAC1_1)||(state==W_DAC2_1)||(state==W_DAC3_1)||(state==W_DAC4_1)||
			   (state==W_DAC1_2)||(state==W_DAC2_2)||(state==W_DAC3_2)||(state==W_DAC4_2)||
			   (state==W_DAC5_1)||(state==W_DAC6_1)||(state==W_DAC7_1)||(state==W_DAC8_1)||
			   (state==W_DAC5_2)||(state==W_DAC6_2)||(state==W_DAC7_2)||(state==W_DAC8_2))
			   
			sync_ <= 1'h0;
			else
			sync_ <= 1'h1;
		end
	else
	sync_ <= sync_;
end

//shiftReg	@rising edge of sclk.  Reserved 4 control registers for initial setup. For AD5754, we only need two: one for range setup, one for all DAC initial to 0V.
always @(posedge clk)
begin
	if(reset)
	shiftReg <= 24'h0;	
	else if((sclkReg==1'b0)&&(sclk==1'b1))
	begin
		if(state==W_REG1_1)
			shiftReg <= 24'h300000;  //range is 10V
		else if (state==W_REG2_1)
			shiftReg <= 24'h310000;  //All 4 DAC goes to zero
		else if (state==W_REG3_1)
				shiftReg <= 24'h320000;  //repeat range register							
		else if (state==W_REG4_1)			
				shiftReg <= 24'h330000;  //repeat range register				
		else if (state==W_DAC1_1) 
				shiftReg <= {8'h30,dac1Reg}; 
		else if (state==W_DAC2_1) 
				shiftReg <= {8'h31,dac2Reg};  
		else if (state==W_DAC3_1) 
				shiftReg <= {8'h32,dac3Reg};  
		else if (state==W_DAC4_1) 
				shiftReg <= {8'h33,dac4Reg}; 
		else if (state==W_DAC5_1) 
				shiftReg <= {8'h34,dac5Reg}; 
		else if (state==W_DAC6_1) 
				shiftReg <= {8'h35,dac6Reg}; 
		else if (state==W_DAC7_1) 
				shiftReg <= {8'h36,dac7Reg}; 
		else if (state==W_DAC8_1) 
				shiftReg <= {8'h37,dac8Reg}; 				
		else if((state==W_REG1_2)||(state==W_REG2_2)||(state==W_REG3_2)||(state==W_REG4_2)||(state==W_DAC1_2)||(state==W_DAC2_2)||(state==W_DAC3_2)||(state==W_DAC4_2)||
				(state==W_DAC5_2)||(state==W_DAC6_2)||(state==W_DAC7_2)||(state==W_DAC8_2))	
			shiftReg <= {shiftReg[23:0],1'b0};
		else if((state==W_REG1_3)||(state==W_REG2_3)||(state==W_REG3_3)||(state==W_REG4_3)||(state==W_DAC1_3)||(state==W_DAC2_3)||(state==W_DAC3_3)||(state==W_DAC4_3)||
				(state==W_DAC5_3)||(state==W_DAC6_3)||(state==W_DAC7_3)||(state==W_DAC8_3))
			shiftReg <= 24'h0;
		else
			shiftReg <= shiftReg;
	end
	else
			shiftReg <= shiftReg;
end

//shiftCounter @rising edge of sclk
always @(posedge clk)
begin
	if(reset)
	shiftCounter <= 8'h0;	
	else if((sclkReg==1'b0)&&(sclk==1'b1))
	begin
		if     ((state==W_REG1_1)||(state==W_REG2_1)||(state==W_REG3_1)||(state==W_REG4_1)||(state==W_DAC1_1)||(state==W_DAC2_1)||(state==W_DAC3_1)||(state==W_DAC4_1)||
		        (state==W_DAC5_1)||(state==W_DAC6_1)||(state==W_DAC7_1)||(state==W_DAC8_1))
		shiftCounter <= 8'h0;	
		else if((state==W_REG1_2)||(state==W_REG2_2)||(state==W_REG3_2)||(state==W_REG4_2)||(state==W_DAC1_2)||(state==W_DAC2_2)||(state==W_DAC3_2)||(state==W_DAC4_2)||
				(state==W_DAC5_2)||(state==W_DAC6_2)||(state==W_DAC7_2)||(state==W_DAC8_2))	
		shiftCounter <= shiftCounter + 8'h1;	
		else
			shiftCounter <= shiftCounter;	
	end
	else
			shiftCounter <= shiftCounter;	
end		

//sdin: alwasy MSB of shiftReg.  It will be latched at the @falling edge of sclk by SPI slave device.
always @(posedge clk)
sdin <= shiftReg[23];

//delay between register write
always @(posedge clk)
begin
	if(reset)
	delayCounter <= 16'h0;
	else if((sclkReg==1'b0)&&(sclk==1'b1))
	begin
		if((state==DELAY1)||(state==DELAY2)||(state==DELAY3)||(state==DELAY4)||(state==DELAY5)||(state==DELAY_DAC1)||(state==DELAY_DAC2)||(state==DELAY_DAC3)||(state==DELAY_DAC4)||
		   (state==DELAY_DAC5)||(state==DELAY_DAC6)||(state==DELAY_DAC7)||(state==DELAY_DAC8))
		delayCounter <= delayCounter + 16'h1;
		else
		delayCounter <= 16'h0;
	end
	else
	delayCounter <= delayCounter;
end	

//state machine
always @(posedge clk)
begin
	if(reset)
	state <= RESET_STATE;
	else
	begin
		//riding edge
		if((sclkReg==1'b0)&&(sclk==1'b1))
		state <= nextState;
		else
		state <= state;
	end
end


always @(*)
begin
	case(state)
	RESET_STATE:
		begin
			if(reset)
			nextState <= RESET_STATE;
			else
			nextState <= W_REG1_1;			
		end
	W_REG1_1:
			nextState <= W_REG1_2;
	W_REG1_2:
		begin
			if(shiftCounter!=SHIFT_COUNTER)  //24bit
			nextState <= W_REG1_2;
 			else
			nextState <= W_REG1_3;
		end
	W_REG1_3:
			nextState <= DELAY1;
	DELAY1: 
		begin
			if(delayCounter==DELAY_TIME)
			nextState <= W_REG2_1;
			else
			nextState <= DELAY1;
		end
	
	W_REG2_1:
			nextState <= W_REG2_2;
	W_REG2_2:
		begin
			if(shiftCounter!=SHIFT_COUNTER)  //24bit
			nextState <= W_REG2_2;
 			else
			nextState <= W_REG2_3;
		end
	W_REG2_3:
			nextState <= DELAY2;
	DELAY2: 
		begin
			if(delayCounter==DELAY_TIME)
			nextState <= W_REG3_1;
			else
			nextState <= DELAY2;
		end
	
	W_REG3_1:
			nextState <= W_REG3_2;
	W_REG3_2:
		begin
			if(shiftCounter!=SHIFT_COUNTER)  //24bit
			nextState <= W_REG3_2;
 			else
			nextState <= W_REG3_3;
		end
	W_REG3_3:
			nextState <= DELAY3;			
	DELAY3: 
		begin
			if(delayCounter==DELAY_TIME)
			nextState <= W_REG4_1;
			else
			nextState <= DELAY3;
		end		
	W_REG4_1:
			nextState <= W_REG4_2;
	W_REG4_2:
		begin
			if(shiftCounter!=SHIFT_COUNTER)  //24bit
			nextState <= W_REG4_2;
 			else
			nextState <= W_REG4_3;
		end
	W_REG4_3:
			nextState <= DELAY4;
	DELAY4: 
		begin
			if(delayCounter==DELAY_TIME)
			nextState <= IDLE;
			else
			nextState <= DELAY4;
		end	
	IDLE:  //decide which DAC has new value
		begin
			if(dac1RegReg!=dac1Reg)
			nextState <= W_DAC1_1;
			else if (dac2RegReg!=dac2Reg)
			nextState <= W_DAC2_1;
			else if (dac3RegReg!=dac3Reg)
			nextState <= W_DAC3_1;
			else if (dac4RegReg!=dac4Reg)
			nextState <= W_DAC4_1;
			else if (dac5RegReg!=dac5Reg)
			nextState <= W_DAC5_1;
			else if (dac6RegReg!=dac6Reg)
			nextState <= W_DAC6_1;
			else if (dac7RegReg!=dac7Reg)
			nextState <= W_DAC7_1;
			else if (dac8RegReg!=dac8Reg)
			nextState <= W_DAC8_1;
			else
			nextState <= IDLE;
		end
	W_DAC1_1:	
		nextState <= W_DAC1_2;
	W_DAC1_2:
		begin
			if(shiftCounter!=SHIFT_COUNTER)  //24bit
			nextState <= W_DAC1_2;
 			else
			nextState <= W_DAC1_3; 
		end
	W_DAC1_3:
			nextState <= DELAY_DAC1;
	DELAY_DAC1:		
		begin
			if(delayCounter==DELAY_TIME)
			nextState <= IDLE;
			else
			nextState <= DELAY_DAC1;
		end
	W_DAC2_1:	
		nextState <= W_DAC2_2;
	W_DAC2_2:
		begin
			if(shiftCounter!=SHIFT_COUNTER)  //24bit
			nextState <= W_DAC2_2;
 			else
			nextState <= W_DAC2_3; 
		end
	W_DAC2_3:
			nextState <= DELAY_DAC2;
	DELAY_DAC2:		
		begin
			if(delayCounter==DELAY_TIME)
			nextState <= IDLE;
			else
			nextState <= DELAY_DAC2;
		end	
	W_DAC3_1:	
		nextState <= W_DAC3_2;
	W_DAC3_2:
		begin
			if(shiftCounter!=SHIFT_COUNTER)  //24bit
			nextState <= W_DAC3_2;
 			else
			nextState <= W_DAC3_3; 
		end
	W_DAC3_3:
			nextState <= DELAY_DAC3;
	DELAY_DAC3:		
		begin
			if(delayCounter==DELAY_TIME)
			nextState <= IDLE;
			else
			nextState <= DELAY_DAC3;
		end
	W_DAC4_1:	
		nextState <= W_DAC4_2;
	W_DAC4_2:
		begin
			if(shiftCounter!=SHIFT_COUNTER)  //24bit
			nextState <= W_DAC4_2;
 			else
			nextState <= W_DAC4_3; 
		end
	W_DAC4_3:
			nextState <= DELAY_DAC4;
	DELAY_DAC4:		
		begin
			if(delayCounter==DELAY_TIME)
			nextState <= IDLE;
			else
			nextState <= DELAY_DAC4;
		end		
	W_DAC5_1:	
		nextState <= W_DAC5_2;
	W_DAC5_2:
		begin
			if(shiftCounter!=SHIFT_COUNTER)  //24bit
			nextState <= W_DAC5_2;
 			else
			nextState <= W_DAC5_3; 
		end
	W_DAC5_3:
			nextState <= DELAY_DAC5;
	DELAY_DAC5:		
		begin
			if(delayCounter==DELAY_TIME)
			nextState <= IDLE;
			else
			nextState <= DELAY_DAC5;
		end		
	W_DAC6_1:	
		nextState <= W_DAC6_2;
	W_DAC6_2:
		begin
			if(shiftCounter!=SHIFT_COUNTER)  //24bit
			nextState <= W_DAC6_2;
 			else
			nextState <= W_DAC6_3; 
		end
	W_DAC6_3:
			nextState <= DELAY_DAC6;
	DELAY_DAC6:		
		begin
			if(delayCounter==DELAY_TIME)
			nextState <= IDLE;
			else
			nextState <= DELAY_DAC6;
		end		
	W_DAC7_1:	
		nextState <= W_DAC7_2;
	W_DAC7_2:
		begin
			if(shiftCounter!=SHIFT_COUNTER)  //24bit
			nextState <= W_DAC7_2;
 			else
			nextState <= W_DAC7_3; 
		end
	W_DAC7_3:
			nextState <= DELAY_DAC7;
	DELAY_DAC7:		
		begin
			if(delayCounter==DELAY_TIME)
			nextState <= IDLE;
			else
			nextState <= DELAY_DAC7;
		end		
	W_DAC8_1:	
		nextState <= W_DAC8_2;
	W_DAC8_2:
		begin
			if(shiftCounter!=SHIFT_COUNTER)  //24bit
			nextState <= W_DAC8_2;
 			else
			nextState <= W_DAC8_3; 
		end
	W_DAC8_3:
			nextState <= DELAY_DAC8;
	DELAY_DAC8:		
		begin
			if(delayCounter==DELAY_TIME)
			nextState <= IDLE;
			else
			nextState <= DELAY_DAC8;
		end		
	default:
			nextState <= IDLE;
	endcase
end

assign tp = {dac3[15:0], dac2[15:0], dac1[15:0], 
            3'h7,reset_,ldac_,clr_,sync_,sclk,sdin,convertEnd,state[5:0]};
	
endmodule
