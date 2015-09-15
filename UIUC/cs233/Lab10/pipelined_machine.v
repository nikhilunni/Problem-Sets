module pipelined_machine(clk, reset);
   input        clk, reset;

   wire [31:0] 	PC;
   wire [29:0] 	next_PC, PC_plus4_ORIGINAL, PC_target;
   wire [29:0] 	PC_plus4; 	
   wire [31:0] 	inst;
   
   wire [31:0] 	imm_ORIGINAL = {{ 16{inst[15]} }, inst[15:0] };  // sign-extended immediate
   wire [31:0] 	imm;
   wire [4:0] 	rs_ORIGINAL = inst[25:21];
   wire [4:0] 	rt_ORIGINAL = inst[20:16];
   wire [4:0] 	rd_ORIGINAL = inst[15:11];
   wire [4:0] 	rs, rt, rd;
   wire [5:0] 	opcode_ORIGINAL = inst[31:26];
   wire [5:0] 	opcode; 	
   wire [5:0] 	funct_ORIGINAL = inst[5:0];
   wire [5:0] 	funct;

   wire [4:0] 	wr_regnum_ORIGINAL, wr_regnum;
   wire [2:0] 	ALUOp;

   wire 	RegWrite, RegWrite_ORIGINAL, BEQ, ALUSrc, MemRead, MemWrite, MemToReg, RegDst;
   wire         PCSrc, zero, flush;
   wire [31:0] 	rd1_data, rd1_data_ORIGINAL, rd2_data, rd2_data_ORIGINAL, B_data, alu_out_data, load_data, wr_data, wr_data_ORIGINAL;
   wire [31:0] 	alu_in_1, alu_in_2;
  
   register #(30, 30'h100000) PC_reg(PC[31:2], next_PC[29:0], clk, /* enable */1'b1, reset);
   assign PC[1:0] = 2'b0;  // bottom bits hard coded to 00
   adder30 next_PC_adder(PC_plus4_ORIGINAL, PC[31:2], 30'h1);
   adder30 target_PC_adder(PC_target, PC_plus4, imm[29:0]);
   mux2v #(30) branch_mux(next_PC, PC_plus4_ORIGINAL, PC_target, PCSrc);
   assign PCSrc = BEQ & zero;
   assign Flush = PCSrc | reset;
   assign ForwardA = (rs == wr_regnum) & RegWrite;
   assign ForwardB = (rt == wr_regnum) & RegWrite;
   
   register #(30,30'd0) PC_plus4_pipe(PC_plus4, PC_plus4_ORIGINAL, clk, 1, Flush); //CHANGE reset to flush!!!
   register #(6,6'd0) opcode_pipe(opcode, opcode_ORIGINAL, clk, 1, Flush);
   register #(6,6'd0) funct_pipe(funct, funct_ORIGINAL, clk, 1, Flush);
   register #(32,32'd0) rd1_data_pipe(rd1_data, rd1_data_ORIGINAL, clk, 1, Flush);
   register #(32,32'd0) rd2_data_pipe(rd2_data, rd2_data_ORIGINAL, clk, 1, Flush);
   register #(32,32'd0) imm_pipe(imm, imm_ORIGINAL, clk, 1, Flush);
   register #(5,5'd0) rt_pipe(rt, rt_ORIGINAL, clk, 1, Flush);
   register #(5,5'd0) rd_pipe(rd, rd_ORIGINAL, clk, 1, Flush);
   register #(5,5'd0) rs_pipe(rs, rs_ORIGINAL, clk, 1, Flush);


   register #(5) wr_regnum_pipe(wr_regnum, wr_regnum_ORIGINAL, clk, 1, Flush);
   register #(32) wr_data_pipe(wr_data, wr_data_ORIGINAL, clk, 1, Flush);
   register #(1) RegWrite_pipe(RegWrite, RegWrite_ORIGINAL, clk, 1, Flush);

   mux2v #(32) ForwardA_mux(alu_in_1, rd1_data, wr_data, ForwardA);
   mux2v #(32) ForwardB_mux(alu_in_2, rd2_data, wr_data, ForwardB);
   
   
   
   instruction_memory imem (PC[31:2], inst);

   mips_decode decode(ALUOp, RegWrite_ORIGINAL, BEQ, ALUSrc, MemRead, MemWrite, MemToReg, RegDst, 
		      opcode, funct);
   
   regfile rf (rs_ORIGINAL, rt_ORIGINAL, wr_regnum_ORIGINAL, 
               rd1_data_ORIGINAL, rd2_data_ORIGINAL, wr_data_ORIGINAL, 
               RegWrite_ORIGINAL, clk, reset);

   mux2v #(32) imm_mux(B_data, alu_in_2, imm, ALUSrc);
   alu32 alu(alu_out_data, zero, ALUOp, alu_in_1, B_data);
   
   data_mem data_memory(load_data, alu_out_data, rd2_data, MemRead, MemWrite, clk, reset);
   
   mux2v #(32) wb_mux(wr_data_ORIGINAL, alu_out_data, load_data, MemToReg);
   mux2v #(5) rd_mux(wr_regnum_ORIGINAL, rt, rd, RegDst);
   
endmodule // pipelined_machine
