module mips_decode(ALUOp, RegWrite, BEQ, ALUSrc, MemRead, MemWrite, MemToReg, RegDst, LWSIN, 
		   opcode, funct);

   output [2:0] ALUOp;
   output 	RegWrite, BEQ, ALUSrc, MemRead, MemWrite, MemToReg, RegDst, LWSIN;
   input  [5:0] opcode, funct;

   wire 	RegDstTemp, ALUSrcTemp, MemToRegTemp, MemReadTemp;   

   given_decode given(ALUOp, RegWrite, BEQ, ALUSrcTemp, MemReadTemp, MemWrite, MemToRegTemp, RegDstTemp, 
		opcode, funct);

   assign LWSIN = (opcode == 6'h3b);
   mux2v #(1) regMux(RegDst, RegDstTemp, 0, LWSIN);
   mux2v #(1) ALUMux(ALUSrc, ALUSrcTemp, 1, LWSIN);
   mux2v #(1) RegMux(MemToReg, MemToRegTemp, 1, LWSIN);
   mux2v #(1) ReadMux(MemRead, MemReadTemp, 1, LWSIN);
   
endmodule // mips_decode

module machine(clk, reset);
   input        clk, reset;

   wire [31:0] 	PC;
   wire [31:2]  next_PC, next_PC_TEMP, PC_plus4, PC_plus8, PC_target;
   wire [31:0] 	inst;
   
   wire [31:0] 	imm = {{ 16{inst[15]} }, inst[15:0] };  // sign-extended immediate
   wire [4:0] 	rs = inst[25:21];
   wire [4:0] 	rt = inst[20:16];
   wire [4:0] 	rd = inst[15:11];
   wire [5:0] 	opcode = inst[31:26];
   wire [5:0] 	funct = inst[5:0];

   wire [4:0] 	wr_regnum;
   wire [2:0] 	ALUOp;

   wire         LWSIN;	
   wire 	RegWrite, BEQ, ALUSrc, MemRead, MemWrite, MemToReg, RegDst;
   wire         PCSrc, zero, negative;
   wire [31:0] 	rd1_data, rd2_data, B_data, alu_out_data, load_data, wr_data;


   register #(30, 30'h100000) PC_reg(PC[31:2], next_PC[31:2], clk, /* enable */1'b1, reset);
   assign PC[1:0] = 2'b0;  // bottom bits hard coded to 00
   adder30 next_PC_adder(PC_plus4, PC[31:2], 30'h1);
   adder30 next_PC_adder2(PC_plus8, PC[31:2], 30'h2);   
   adder30 target_PC_adder(PC_target, PC_plus4, imm[29:0]);
   mux2v #(30) branch_mux(next_PC_TEMP, PC_plus4, PC_target, PCSrc);

   assign add8 = (load_data[31] && LWSIN);   
   mux2v #(30) branch_mux2(next_PC, next_PC_TEMP, PC_plus8, add8);   
   assign PCSrc = BEQ & zero;
      
   instruction_memory imem (PC[31:2], inst);

   mips_decode decode(ALUOp, RegWrite, BEQ, ALUSrc, MemRead, MemWrite, MemToReg, RegDst, LWSIN,
		      opcode, funct);
  
   regfile rf (rs, rt, wr_regnum, 
               rd1_data, rd2_data, wr_data, 
               RegWrite, clk, reset);

   mux2v #(32) imm_mux(B_data, rd2_data, imm, ALUSrc);
   alu32 alu(alu_out_data, zero, negative, ALUOp, rd1_data, B_data);
   
   data_mem data_memory(load_data, alu_out_data, rd2_data, MemRead, MemWrite, clk, reset);
   
   mux2v #(32) wb_mux(wr_data, alu_out_data, load_data, MemToReg);
   mux2v #(5) rd_mux(wr_regnum, rt, rd, RegDst);
   
endmodule // machine
