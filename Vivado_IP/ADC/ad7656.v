module ad7656(
    //interface with PSI_controller
	 input reset,
	 input clk,
	 input convert_start,
	 output reg convert_end,
	 output reg [15:0] ADC_data_v1,
	 output reg [15:0] ADC_data_v2,
	 output reg [15:0] ADC_data_v3,
	 output reg [15:0] ADC_data_v4,
	 output reg [15:0] ADC_data_v5,
	 output reg [15:0] ADC_data_v6,
	 output reg [15:0] ADC_data_v1_AVG,
	 output reg [15:0] ADC_data_v2_AVG,
	 output reg [15:0] ADC_data_v3_AVG,
	 output reg [15:0] ADC_data_v4_AVG,
	 output reg [15:0] ADC_data_v5_AVG,
	 output reg [15:0] ADC_data_v6_AVG,
	 //Inteface with AD7656
	 output reg ADC_reset,
	 output reg ADC_convst,
	 input ADC_busy,
	 output reg ADC_cs,
	 output reg ADC_sclk,
	 input ADC_dout_a,
	 input ADC_dout_b,
	 input ADC_dout_c,
	 output ADC_Stby,
	 output ADC_Rd,
	 output [79:0] tp,
	 output reg [31:0] adc1_2,
     output reg [31:0] adc3_4,
     output reg adcReady
    );

//input register:
reg convert_start_reg,convert_start_reg_reg;
reg ADC_busy_reg,ADC_busy_reg_reg;
reg ADC_sclk_reg;
reg [5:0] ADC_read_counter;

reg [3:0] sadc_reset_count,sadc_reset_done_count;

parameter IDLE=5'h0,START_CONVERT=5'h1,CONVERT_DONE=5'h2,READ_START=5'h3,READ_LOAD=5'h4,READ_DONE=5'h5, SADC_RESET=5'h6,SADC_RESET_DONE=5'h7;
parameter START_CONVERT1=5'h8,START_CONVERT2=5'h9,START_CONVERT3=5'hA,START_CONVERT4=5'hB,START_CONVERT5=5'hC;
parameter START_CONVERT4_1=5'hD,START_CONVERT4_2=5'hE,SUM_AVERAGE=5'hF,SUM_AVERAGE_1=5'h10,SUM_AVERAGE_2=5'h11;
parameter SUM_AVERAGE_3=5'h12;

reg [4:0] next_state, state;

reg ADC_cs_reg;

assign ADC_Stby = 1'b1;  //active low
assign ADC_Rd = 1'b0;  //active low

//1. input register: Double register to make it more reliable.
always @(posedge clk)
begin
	convert_start_reg <= convert_start;
	convert_start_reg_reg <= convert_start_reg;
	ADC_busy_reg <= ADC_busy;
	ADC_busy_reg_reg <= ADC_busy_reg;
	ADC_sclk_reg <= ADC_sclk;
	ADC_cs_reg <= ADC_cs;
	adc1_2 <= {ADC_data_v1,ADC_data_v2};
	adc3_4 <= {ADC_data_v3,ADC_data_v4};
	adcReady <= convert_end;
end

//2. ADC_clk: always running
//parameter ADC_SCLK_HALF_CYCLE=5'h3;  //Fsclk < 18MHz
parameter ADC_SCLK_HALF_CYCLE=5'h1F;  //Fsclk < 18MHz
reg [5:0] ADC_sclk_counter;

//3.
always @(posedge clk)
begin
	if(reset==1'b1)
	ADC_reset <= 1'b1;
	else if(state==SADC_RESET)
	ADC_reset <= 1'b1;
	else
	ADC_reset <= 1'b0;
end

always @(posedge clk)
begin
	if((reset==1'b1)||(ADC_sclk_counter==ADC_SCLK_HALF_CYCLE))
	ADC_sclk_counter <= 6'h0;
	else if(ADC_cs==1'b0)
	ADC_sclk_counter <= ADC_sclk_counter + 6'h1;
	else
	ADC_sclk_counter <= ADC_sclk_counter;

end

reg ADC_cs_reg_reg_reg,ADC_cs_reg_reg;
always @(posedge clk)
begin
	ADC_cs_reg_reg_reg <= ADC_cs_reg_reg;
	ADC_cs_reg_reg <= ADC_cs_reg;
end

always @(posedge clk)
begin
	if(reset==1'b1)
	ADC_sclk <= 1'h1;
	else if ((ADC_cs_reg_reg_reg==1'b1)&&(ADC_cs_reg_reg==1'b0))
	ADC_sclk <= 1'h1;
	else if (ADC_sclk_counter==ADC_SCLK_HALF_CYCLE)
	ADC_sclk <= ~ADC_sclk;
	else
	ADC_sclk <= ADC_sclk;
end


reg [11:0] adcConvtCounter;
always @(posedge clk)
begin
	if(state==START_CONVERT5)
	   adcConvtCounter <= adcConvtCounter + 12'h1;
	else adcConvtCounter <= 12'h0;
end
always @(posedge clk)
begin
	if((reset==1'b1)||(state==IDLE))
	ADC_read_counter <= 6'h0;
	else if(state==READ_START)
		begin
			if((ADC_sclk_reg==1'b0)&&(ADC_sclk==1'b1))
			ADC_read_counter <= ADC_read_counter + 6'h1;
			else
			ADC_read_counter <= ADC_read_counter;
		end
	else
			ADC_read_counter <= ADC_read_counter;
end

always @(posedge clk)
begin
	if(reset==1'b1)
	state <= IDLE;
	else
	state <= next_state;
end

always @(state or convert_start_reg or convert_start_reg_reg or ADC_busy_reg_reg or ADC_busy_reg or ADC_sclk_counter
        or ADC_read_counter or ADC_sclk or ADC_sclk_reg)
begin
	case(state)
		IDLE:
			begin
				if((convert_start_reg_reg==1'b0)&&(convert_start_reg==1'b1))
				next_state <= START_CONVERT;
				else
				next_state <= IDLE;
			end
		START_CONVERT:
			next_state <= START_CONVERT1;
		START_CONVERT1:
			next_state <= START_CONVERT2;
		START_CONVERT2:
			next_state <= START_CONVERT3;
		START_CONVERT3:
			next_state <= START_CONVERT4;
		START_CONVERT4:
			next_state <= START_CONVERT4_1;
		START_CONVERT4_1:
			next_state <= START_CONVERT4_2;
		START_CONVERT4_2:
			next_state <= START_CONVERT5;
		START_CONVERT5:
		/* To save IO, use counter. It take 3us to finish.  Now the counter reseerve 10us, enough to finish ADC conversion */
		  begin
		          if(adcConvtCounter==10'hFFF) next_state <= CONVERT_DONE;
		          else next_state <= START_CONVERT5;
		  end
		/*
			begin
				if((ADC_busy_reg_reg==1'b1)&&(ADC_busy_reg==1'b0))
				next_state <= CONVERT_DONE;
				else
				next_state <= START_CONVERT5;
			end		*/
		CONVERT_DONE:
			begin
				if(ADC_cs==1'b0)
				next_state <= READ_START;
				else
				next_state <= READ_START;
			end
		READ_START:
			begin
				if(ADC_read_counter==6'h20)
				next_state <= READ_LOAD;
				else
				next_state <= READ_START;
			end
		READ_LOAD:
				next_state <= SUM_AVERAGE;
		SUM_AVERAGE:
		        next_state <= SUM_AVERAGE_1;
		SUM_AVERAGE_1:
		        next_state <= SUM_AVERAGE_2;
	    SUM_AVERAGE_2:
		        next_state <= SUM_AVERAGE_3;
		SUM_AVERAGE_3:
		        next_state <= READ_DONE;
		READ_DONE:
			//begin
			//	if((ADC_sclk_reg==1'b1)&&(ADC_sclk==1'b0))
				next_state <= IDLE;
			//	else
			//	next_state <= READ_DONE;
			//end
		SADC_RESET:
			begin
				if(sadc_reset_count==4'hB)
				next_state <= SADC_RESET_DONE;
				else
				next_state <= SADC_RESET;
			end
		SADC_RESET_DONE:
			begin
				if(sadc_reset_done_count==4'hF)
				next_state <= IDLE;
				else
				next_state <= SADC_RESET_DONE;
			end
		default:
				next_state <= IDLE;
		endcase
end

always @(posedge clk)
begin
	if(reset==1'b1)
	sadc_reset_count <= 4'h0;
	else if(state==SADC_RESET)
	sadc_reset_count <= sadc_reset_count + 4'h1;
	else
	sadc_reset_count <= 4'h0;
end

always @(posedge clk)
begin
	if(reset==1'b1)
	sadc_reset_done_count <= 4'h0;
	else if(state==SADC_RESET_DONE)
	sadc_reset_done_count <= sadc_reset_done_count + 4'h1;
	else
	sadc_reset_done_count <= 4'h0;
end

always @(posedge clk)
begin
	if(reset==1'b1)
	convert_end <= 1'b1;
	else if((convert_start_reg_reg==1'b0)&&(convert_start_reg==1'b1))
	convert_end <= 1'b0;
	else if(state==READ_DONE)
	convert_end <= 1'b1;
	else
	convert_end <= convert_end;
end

always @(posedge clk)
begin
	if(reset==1'b1)
	ADC_convst <= 1'b1;
	else if(state==START_CONVERT)
	ADC_convst <= 1'b0;
	else if(state==START_CONVERT5)
	ADC_convst <= 1'b1;
	else if(state==IDLE)
	ADC_convst <= 1'b1;
	else
	ADC_convst <= ADC_convst;
end

always @(posedge clk)
begin
	if(reset==1'b1)
	ADC_cs <= 1'b1;
	else if(state==READ_START)
	ADC_cs <= 1'b0;
	else if(state==READ_DONE)
	ADC_cs <= 1'b1;
	else
	ADC_cs <= ADC_cs;
end

reg [31:0] Data_v1_v2, Data_v3_v4, Data_v5_v6;

always @(posedge clk)
begin
	if(reset==1'b1)
	Data_v1_v2 <= 32'h0;
	else if(state==START_CONVERT)
	Data_v1_v2 <= 32'h0;
	else if((ADC_sclk_reg==1'b1)&&(ADC_sclk==1'b0)&&(state==READ_START))  //ltach at falling edge
	Data_v1_v2 <= {Data_v1_v2[30:0],ADC_dout_a};
	else
	Data_v1_v2 <= Data_v1_v2;
end

always @(posedge clk)
begin
	if(reset==1'b1)
	Data_v3_v4 <= 32'h0;
	else if(state==START_CONVERT)
	Data_v3_v4 <= 32'h0;
	else if((ADC_sclk_reg==1'b1)&&(ADC_sclk==1'b0)&&(state==READ_START))
	Data_v3_v4 <= {Data_v3_v4[30:0],ADC_dout_b};
	else
	Data_v3_v4 <= Data_v3_v4;
end

always @(posedge clk)
begin
	if(reset==1'b1)
	Data_v5_v6 <= 32'h0;
	else if(state==START_CONVERT)
	Data_v5_v6 <= 32'h0;
	else if((ADC_sclk_reg==1'b1)&&(ADC_sclk==1'b0)&&(state==READ_START))
	Data_v5_v6 <= {Data_v5_v6[30:0],ADC_dout_c};
	else
	Data_v5_v6 <= Data_v5_v6;
end

reg [31:0] ADC_data_v1_SUM,ADC_data_v2_SUM,ADC_data_v3_SUM,ADC_data_v4_SUM,ADC_data_v5_SUM,ADC_data_v6_SUM;
reg [15:0] ADC_data_v1_AVG,ADC_data_v2_AVG,ADC_data_v3_AVG,ADC_data_v4_AVG,ADC_data_v5_AVG,ADC_data_v6_AVG;
reg [15:0] ADC_data_v1_CNT,ADC_data_v2_CNT,ADC_data_v3_CNT,ADC_data_v4_CNT,ADC_data_v5_CNT,ADC_data_v6_CNT;

parameter AVG_NUMBER=16'h1000;
parameter AVG_SHIFT = 12;

always @(posedge clk)
begin
	if(reset==1'b1) ADC_data_v1_SUM <= 32'h0;
	else if(state==SUM_AVERAGE) begin
	   if(ADC_data_v1[15]!=1) //skip negtive voltage
	       ADC_data_v1_SUM <= ADC_data_v1_SUM + {16'h0,ADC_data_v1};
	   end
	else if(state==SUM_AVERAGE_3) begin
	   if(ADC_data_v1_CNT==AVG_NUMBER) ADC_data_v1_SUM  <= (ADC_data_v1_SUM >>AVG_SHIFT);
     end
    else ADC_data_v1_SUM <= ADC_data_v1_SUM;
end

always @(posedge clk)
begin
	if(reset==1'b1) ADC_data_v1_CNT <= 16'h0;
	else if(state==SUM_AVERAGE) begin
	   if(ADC_data_v1[15]!=1) //skip negtive voltage
        ADC_data_v1_CNT <= ADC_data_v1_CNT + 16'h1;
	   end
  else if(state==READ_DONE) begin
    if(ADC_data_v1_CNT==AVG_NUMBER) ADC_data_v1_CNT <= 16'h0;
    end
  else ADC_data_v1_CNT <= ADC_data_v1_CNT;
end

  always @(posedge clk)
  begin
  	if(reset==1'b1) ADC_data_v1_AVG <= 16'h0;
    else if(state==READ_DONE) begin
      if(ADC_data_v1_CNT==AVG_NUMBER) ADC_data_v1_AVG <= ADC_data_v1_SUM[15:0];
      end
    else ADC_data_v1_AVG <= ADC_data_v1_AVG;
  end

  always @(posedge clk)
  begin
  	if(reset==1'b1) ADC_data_v2_SUM <= 32'h0;
  	else if(state==SUM_AVERAGE) begin
  	   if(ADC_data_v2[15]!=1) //skip negtive voltage
  	       ADC_data_v2_SUM <= ADC_data_v2_SUM + {16'h0,ADC_data_v2};
  	   end
  	else if(state==SUM_AVERAGE_3) begin
  	   if(ADC_data_v2_CNT==AVG_NUMBER) ADC_data_v2_SUM  <= (ADC_data_v2_SUM >>AVG_SHIFT);
       end
      else ADC_data_v2_SUM <= ADC_data_v2_SUM;
  end

  always @(posedge clk)
  begin
  	if(reset==1'b1) ADC_data_v2_CNT <= 16'h0;
  	else if(state==SUM_AVERAGE) begin
  	   if(ADC_data_v2[15]!=1) //skip negtive voltage
          ADC_data_v2_CNT <= ADC_data_v2_CNT + 16'h1;
  	   end
    else if(state==READ_DONE) begin
      if(ADC_data_v2_CNT==AVG_NUMBER) ADC_data_v2_CNT <= 16'h0;
      end
    else ADC_data_v2_CNT <= ADC_data_v2_CNT;
  end

    always @(posedge clk)
    begin
    	if(reset==1'b1) ADC_data_v2_AVG <= 16'h0;
      else if(state==READ_DONE) begin
        if(ADC_data_v2_CNT==AVG_NUMBER) ADC_data_v2_AVG <= ADC_data_v2_SUM[15:0];
        end
      else ADC_data_v2_AVG <= ADC_data_v2_AVG;
    end

always @(posedge clk)
begin
	if(reset==1'b1) ADC_data_v3_SUM <= 32'h0;
	else if(state==SUM_AVERAGE) begin
	   if(ADC_data_v3[15]!=1) //skip negtive voltage
	       ADC_data_v3_SUM <= ADC_data_v3_SUM + {16'h0,ADC_data_v3};
	   end
	else if(state==SUM_AVERAGE_3) begin
	   if(ADC_data_v3_CNT==AVG_NUMBER) ADC_data_v3_SUM  <= (ADC_data_v3_SUM >>AVG_SHIFT);
     end
    else ADC_data_v3_SUM <= ADC_data_v3_SUM;
end

always @(posedge clk)
begin
	if(reset==1'b1) ADC_data_v3_CNT <= 16'h0;
	else if(state==SUM_AVERAGE) begin
	   if(ADC_data_v3[15]!=1) //skip negtive voltage
        ADC_data_v3_CNT <= ADC_data_v3_CNT + 16'h1;
	   end
  else if(state==READ_DONE) begin
    if(ADC_data_v3_CNT==AVG_NUMBER) ADC_data_v3_CNT <= 16'h0;
    end
  else ADC_data_v3_CNT <= ADC_data_v3_CNT;
end

  always @(posedge clk)
  begin
  	if(reset==1'b1) ADC_data_v3_AVG <= 16'h0;
    else if(state==READ_DONE) begin
      if(ADC_data_v3_CNT==AVG_NUMBER) ADC_data_v3_AVG <= ADC_data_v3_SUM[15:0];
      end
    else ADC_data_v3_AVG <= ADC_data_v3_AVG;
  end


always @(posedge clk)
begin
	if(reset==1'b1) ADC_data_v4_SUM <= 32'h0;
	else if(state==SUM_AVERAGE) begin
	   if(ADC_data_v4[15]!=1) //skip negtive voltage
	       ADC_data_v4_SUM <= ADC_data_v4_SUM + {16'h0,ADC_data_v4};
	   end
	else if(state==SUM_AVERAGE_3) begin
	   if(ADC_data_v4_CNT==AVG_NUMBER) ADC_data_v4_SUM  <= (ADC_data_v4_SUM >>AVG_SHIFT);
     end
    else ADC_data_v4_SUM <= ADC_data_v4_SUM;
end

always @(posedge clk)
begin
	if(reset==1'b1) ADC_data_v4_CNT <= 16'h0;
	else if(state==SUM_AVERAGE) begin
	   if(ADC_data_v4[15]!=1) //skip negtive voltage
        ADC_data_v4_CNT <= ADC_data_v4_CNT + 16'h1;
	   end
  else if(state==READ_DONE) begin
    if(ADC_data_v4_CNT==AVG_NUMBER) ADC_data_v4_CNT <= 16'h0;
    end
  else ADC_data_v4_CNT <= ADC_data_v4_CNT;
end

  always @(posedge clk)
  begin
  	if(reset==1'b1) ADC_data_v4_AVG <= 16'h0;
    else if(state==READ_DONE) begin
      if(ADC_data_v4_CNT==AVG_NUMBER) ADC_data_v4_AVG <= ADC_data_v4_SUM[15:0];
      end
    else ADC_data_v4_AVG <= ADC_data_v4_AVG;
  end



always @(posedge clk)
begin
	if(reset==1'b1) ADC_data_v5_SUM <= 32'h0;
	else if(state==SUM_AVERAGE) begin
	   if(ADC_data_v5[15]!=1) //skip negtive voltage
	       ADC_data_v5_SUM <= ADC_data_v5_SUM + {16'h0,ADC_data_v5};
	   end
	else if(state==SUM_AVERAGE_3) begin
	   if(ADC_data_v5_CNT==AVG_NUMBER) ADC_data_v5_SUM  <= (ADC_data_v5_SUM >>AVG_SHIFT);
     end
    else ADC_data_v5_SUM <= ADC_data_v5_SUM;
end

always @(posedge clk)
begin
	if(reset==1'b1) ADC_data_v5_CNT <= 16'h0;
	else if(state==SUM_AVERAGE) begin
	   if(ADC_data_v5[15]!=1) //skip negtive voltage
        ADC_data_v5_CNT <= ADC_data_v5_CNT + 16'h1;
	   end
  else if(state==READ_DONE) begin
    if(ADC_data_v5_CNT==AVG_NUMBER) ADC_data_v5_CNT <= 16'h0;
    end
  else ADC_data_v5_CNT <= ADC_data_v5_CNT;
end

  always @(posedge clk)
  begin
  	if(reset==1'b1) ADC_data_v5_AVG <= 16'h0;
    else if(state==READ_DONE) begin
      if(ADC_data_v5_CNT==AVG_NUMBER) ADC_data_v5_AVG <= ADC_data_v5_SUM[15:0];
      end
    else ADC_data_v5_AVG <= ADC_data_v5_AVG;
  end


always @(posedge clk)
begin
	if(reset==1'b1) ADC_data_v6_SUM <= 32'h0;
	else if(state==SUM_AVERAGE) begin
	   if(ADC_data_v6[15]!=1) //skip negtive voltage
	       ADC_data_v6_SUM <= ADC_data_v6_SUM + {16'h0,ADC_data_v6};
	   end
	else if(state==SUM_AVERAGE_3) begin
	   if(ADC_data_v6_CNT==AVG_NUMBER) ADC_data_v6_SUM  <= (ADC_data_v6_SUM >>AVG_SHIFT);
     end
    else ADC_data_v6_SUM <= ADC_data_v6_SUM;
end

always @(posedge clk)
begin
	if(reset==1'b1) ADC_data_v6_CNT <= 16'h0;
	else if(state==SUM_AVERAGE) begin
	   if(ADC_data_v6[15]!=1) //skip negtive voltage
        ADC_data_v6_CNT <= ADC_data_v6_CNT + 16'h1;
	   end
  else if(state==READ_DONE) begin
    if(ADC_data_v6_CNT==AVG_NUMBER) ADC_data_v6_CNT <= 16'h0;
    end
  else ADC_data_v6_CNT <= ADC_data_v6_CNT;
end

  always @(posedge clk)
  begin
  	if(reset==1'b1) ADC_data_v6_AVG <= 16'h0;
    else if(state==READ_DONE) begin
      if(ADC_data_v6_CNT==AVG_NUMBER) ADC_data_v6_AVG <= ADC_data_v6_SUM[15:0];
      end
    else ADC_data_v6_AVG <= ADC_data_v6_AVG;
  end

////////////////////


always @(posedge clk)
begin
	if(reset==1'b1)
	ADC_data_v1 <= 16'h0;
	//else if(state==START_CONVERT)
	//ADC_data_v1 <= 16'h0;
	else if (state==READ_LOAD)
	ADC_data_v1 <= {Data_v1_v2[31:24],Data_v1_v2[23:16]};
	else
	ADC_data_v1 <= ADC_data_v1;
end

always @(posedge clk)
begin
	if(reset==1'b1)
	ADC_data_v2 <= 16'h0;
	//else if(state==START_CONVERT)
	//ADC_data_v2 <= 16'h0;
	else if (state==READ_LOAD)
	ADC_data_v2 <= {Data_v1_v2[15:8],Data_v1_v2[7:0]};
	else
	ADC_data_v2 <= ADC_data_v2;
end

always @(posedge clk)
begin
	if(reset==1'b1)
	ADC_data_v3 <= 16'h0;
	//else if(state==START_CONVERT)
	//ADC_data_v3 <= 16'h0;
	else if (state==READ_LOAD)
	//ADC_data_v3 <= Data_v3_v4[15:0];
	ADC_data_v3 <= {Data_v3_v4[31:24],Data_v3_v4[23:16]};
	else
	ADC_data_v3 <= ADC_data_v3;
end

always @(posedge clk)
begin
	if(reset==1'b1)
	ADC_data_v4 <= 16'h0;
	//else if(state==START_CONVERT)
	//ADC_data_v4 <= 16'h0;
	else if (state==READ_LOAD)
	//ADC_data_v4 <= Data_v3_v4[31:16];
	ADC_data_v4 <= {Data_v3_v4[15:8],Data_v3_v4[7:0]};
	else
	ADC_data_v4 <= ADC_data_v4;
end

always @(posedge clk)
begin
	if(reset==1'b1)
	ADC_data_v5 <= 16'h0;
	//else if(state==START_CONVERT)
	//ADC_data_v5 <= 16'h0;
	else if (state==READ_LOAD)
	//ADC_data_v5 <= Data_v5_v6[15:0];
	ADC_data_v5 <= {Data_v5_v6[31:24],Data_v5_v6[23:16]};
	else
	ADC_data_v5 <= ADC_data_v5;
end

always @(posedge clk)
begin
	if(reset==1'b1)
	ADC_data_v6 <= 16'h0;
	//else if(state==START_CONVERT)
	//ADC_data_v6 <= 16'h0;
	else if (state==READ_LOAD)
	ADC_data_v6 <= {Data_v5_v6[15:8],Data_v5_v6[7:0]};
	else
	ADC_data_v6 <= ADC_data_v6;
end

assign tp = {ADC_data_v2[15:0],ADC_data_v2_AVG[15:0],ADC_data_v3[15:0],ADC_data_v3_AVG[15:0], 
             4'hC, convert_end, ADC_dout_b,ADC_dout_a,ADC_sclk,ADC_cs,  ADC_convst,convert_start,state[4:0]};
endmodule	
