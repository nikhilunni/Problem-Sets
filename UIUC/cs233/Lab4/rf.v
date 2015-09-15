// register: A register which may be reset to an arbirary value
//
// q      (output) - Current value of register
// d      (input)  - Next value of register
// clk    (input)  - Clock (positive edge-sensitive)
// enable (input)  - Load new value? (yes = 1, no = 0)
// reset  (input)  - Asynchronous reset    (reset = 1)
//
module register(q, d, clk, enable, reset);

    parameter
        width = 32,
        reset_value = 0;
 
    output [(width-1):0] q;
    reg    [(width-1):0] q;
    input  [(width-1):0] d;
    input                clk, enable, reset;
 
    always@(reset)
      if (reset == 1'b1)
        q <= reset_value;
 
    always@(posedge clk)
      if ((reset == 1'b0) && (enable == 1'b1))
        q <= d;

endmodule // register

module decoder2 (out, in, enable);
    input     in;
    input     enable;
    output [1:0] out;
 
    and a0(out[0], enable, ~in);
    and a1(out[1], enable, in);
endmodule // decoder2

module decoder4 (out, in, enable);
    input [1:0]    in;
    input     enable;
    output [3:0]   out;
    wire [1:0]    w_enable;
	decoder2 d1(w_enable[1:0],in[1],enable);
   	decoder2 d2(out[1:0],in[0],w_enable[0]);
	decoder2 d3(out[3:2],in[0],w_enable[1]);
 
endmodule // decoder4

module decoder8 (out, in, enable);
    input [2:0]    in;
    input     enable;
    output [7:0]   out;
    wire [1:0]    w_enable;

	decoder2 d1(w_enable,in[2],enable);
	decoder4 d2(out[3:0],in[1:0],w_enable[0]);
	decoder4 d3(out[7:4],in[1:0],w_enable[1]);
 
endmodule // decoder8

module decoder16 (out, in, enable);
    input [3:0]    in;
    input     enable;
    output [15:0]  out;
    wire [1:0]    w_enable;

	decoder2 d1(w_enable,in[3],enable);
	decoder8 d2(out[7:0],in[2:0],w_enable[0]);
	decoder8 d3(out[15:8],in[2:0],w_enable[1]); 
 
endmodule // decoder16

module decoder32 (out, in, enable);
    input [4:0]    in;
    input     enable;
    output [31:0]  out;
    wire [1:0]    w_enable;
 
	decoder2 	d1(w_enable,in[4],enable);
	decoder16 	d2(out[15:0],in[3:0],w_enable[0]);
	decoder16	d3(out[31:16],in[3:0],w_enable[1]);	
 
endmodule // decoder32

module mips_regfile (rd1_data, rd2_data, rd1_regnum, rd2_regnum, 
             wr_regnum, wr_data, writeenable, 
             clock, reset);

    output [31:0]  rd1_data, rd2_data;
    input   [4:0]  rd1_regnum, rd2_regnum, wr_regnum;
    input  [31:0]  wr_data;
    input          writeenable, clock, reset;

	wire [31:0] decoder_filter;
	wire [31:0] out [31:0];	

	decoder32 d1(decoder_filter,wr_regnum,writeenable);

	register r0(out[0],0,clock,decoder_filter[0],reset);
	register r1(out[1],wr_data,clock,decoder_filter[1],reset);
	register r2(out[2],wr_data,clock,decoder_filter[2],reset);
	register r3(out[3],wr_data,clock,decoder_filter[3],reset);
	register r4(out[4],wr_data,clock,decoder_filter[4],reset);
	register r5(out[5],wr_data,clock,decoder_filter[5],reset);
	register r6(out[6],wr_data,clock,decoder_filter[6],reset);
	register r7(out[7],wr_data,clock,decoder_filter[7],reset);
	register r8(out[8],wr_data,clock,decoder_filter[8],reset);
	register r9(out[9],wr_data,clock,decoder_filter[9],reset);
	register r10(out[10],wr_data,clock,decoder_filter[10],reset);
	register r11(out[11],wr_data,clock,decoder_filter[11],reset);
	register r12(out[12],wr_data,clock,decoder_filter[12],reset);
	register r13(out[13],wr_data,clock,decoder_filter[13],reset);
	register r14(out[14],wr_data,clock,decoder_filter[14],reset);
	register r15(out[15],wr_data,clock,decoder_filter[15],reset);
	register r16(out[16],wr_data,clock,decoder_filter[16],reset);
	register r17(out[17],wr_data,clock,decoder_filter[17],reset);
	register r18(out[18],wr_data,clock,decoder_filter[18],reset);
	register r19(out[19],wr_data,clock,decoder_filter[19],reset);
	register r20(out[20],wr_data,clock,decoder_filter[20],reset);
	register r21(out[21],wr_data,clock,decoder_filter[21],reset);
	register r22(out[22],wr_data,clock,decoder_filter[22],reset);
	register r23(out[23],wr_data,clock,decoder_filter[23],reset);
	register r24(out[24],wr_data,clock,decoder_filter[24],reset);
	register r25(out[25],wr_data,clock,decoder_filter[25],reset);
	register r26(out[26],wr_data,clock,decoder_filter[26],reset);
	register r27(out[27],wr_data,clock,decoder_filter[27],reset);
	register r28(out[28],wr_data,clock,decoder_filter[28],reset);
	register r29(out[29],wr_data,clock,decoder_filter[29],reset);
	register r30(out[30],wr_data,clock,decoder_filter[30],reset);
	register r31(out[31],wr_data,clock,decoder_filter[31],reset);
 
	mux32v mux1(rd1_data,0,out[1],out[2],out[3],out[4],out[5],out[6],out[7],out[8],out[9],out[10],out[11],out[12],out[13],out[14],out[15],out[16],out[17],out[18],out[19],out[20],out[21],out[22],out[23],out[24],out[25],out[26],out[27],out[28],out[29],out[30],out[31],rd1_regnum);

	mux32v mux2(rd2_data,0,out[1],out[2],out[3],out[4],out[5],out[6],out[7],out[8],out[9],out[10],out[11],out[12],out[13],out[14],out[15],out[16],out[17],out[18],out[19],out[20],out[21],out[22],out[23],out[24],out[25],out[26],out[27],out[28],out[29],out[30],out[31],rd2_regnum);

endmodule // mips_regfile

