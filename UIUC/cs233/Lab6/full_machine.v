// full_machine: execute a series of MIPS instructions from an instruction cache
//
// except (output) - set to 1 when an unrecognized instruction is to be executed.
// clk     (input) - the clock signal
// reset   (input) - set to 1 to set all registers to zero, set to 0 for normal execution.

module full_machine(except, clk, reset);
   output      except;
   input 	clk, reset;
   
   wire [31:0] 	inst;  
   wire [31:0] 	PC;  
   wire [31:0] 	nextPC, rsData, rtData, out, imm32, alu2_secondIn, branch_offset;
   wire [31:0] 	aluPC_w,alu_offset_offset_w; 	
   wire [4:0] 	Rdest;
   wire [2:0] 	overflow,zero,negative; //Have to capture them even if we don't read them...
   wire [2:0] 	alu_op;
   wire 	writeenable, rd_src, alu_src2,mem_read,word_we,byte_we,byte_load,lui,slt,addm;
   wire [1:0] 	control_type;   

   wire [31:0]	lui_w, mem_read_w, slt_w, byte_load_w, data_memory_w, alu_offset_w;
   wire [7:0] 	data_mux_w;	

   assign imm32 = {{16{inst[15]}}, inst[15:0]}; //Sign extender
   assign branch_offset = imm32<<2;
   
   // DO NOT comment out or rename this module
   // or the test bench will break
   register #(32) PC_reg(PC, nextPC, clk, 1, reset);
   alu32 alu1(aluPC_w, overflow[0],zero[0],negative[0],PC, 32'd4, 3'd2);
   alu32 alu_offset(alu_offset_w,overflow[2],zero[2],negative[2],aluPC_w,branch_offset,3'd2);

   mux4v mux_control(nextPC, aluPC_w,alu_offset_w,{PC[31:28],inst[25:0],2'b0},rsData,control_type);
   
   instruction_memory instrMem(inst, PC[31:2]);
   data_mem data_memory(data_memory_w, out,rtData, word_we,byte_we,clk,reset);
   
  
   
   mux2v mux_aluMain(alu2_secondIn, rtData, imm32, alu_src2);
   alu32 aluMain(out, overflow[1], zero[1], negative[1], rsData, alu2_secondIn, alu_op);
   
   mux2v #(5) mux2(Rdest,inst[15:11], inst[20:16], rd_src); 
   regfile rf (rsData, rtData, inst[25:21], inst[20:16], Rdest, lui_w, writeenable, clk, reset);

   mux4v #(8) mux_data(data_mux_w, data_memory_w[7:0],data_memory_w[15:8],data_memory_w[23:16],data_memory_w[31:24],out[1:0]);
   mux2v mux_slt(slt_w,out,{31'b0,negative[1]},slt);   
   mux2v mux_lui(lui_w,mem_read_w,{inst[15:0],16'b0},lui);
   mux2v mux_byte_load(byte_load_w, data_memory_w, {24'b0,data_mux_w},byte_load);   
   mux2v mux_mem_read(mem_read_w,slt_w,byte_load_w,mem_read);   
   
   
   mips_decode decoder(alu_op, writeenable, rd_src, alu_src2, except,control_type,mem_read,word_we,byte_we,byte_load,lui,slt,addm,inst[31:26], inst[5:0], zero[1]);
   

endmodule // full_machine
