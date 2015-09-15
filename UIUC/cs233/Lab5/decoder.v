// mips_decode: a decoder for MIPS arithmetic instructions
//
// alu_op      (output) - control signal to be sent to the ALU
// writeenable (output) - should a new value be captured by the register file
// rd_src      (output) - should the destination register be rd (0) or rt (1)
// alu_src2    (output) - should the 2nd ALU source be a register (0) or an immediate (1)
// except      (output) - set to 1 when the opcode/funct combination is unrecognized
// opcode      (input)  - the opcode field from the instruction
// funct       (input)  - the function field from the instruction
//

module mips_decode(alu_op, writeenable, rd_src, alu_src2, except, opcode, funct);
   output [2:0] alu_op;
   output       writeenable, rd_src, alu_src2, except;
   input [5:0] 	opcode, funct;
   wire 	addW,subW,andW,orW,norW,xorW,addiW,andiW,oriW,xoriW;
 	
   assign addW = (opcode == 6'b000000) & (funct == 6'b100000);  
   assign subW = (opcode == 6'b000000) & (funct == 6'b100010);   
   assign andW = (opcode == 6'b000000) &  (funct == 6'b100100);   
   assign orW = (opcode == 6'b000000) & (funct == 6'b100101);   
   assign norW = (opcode == 6'b000000) & (funct == 6'b100111);   
   assign xorW  = (opcode == 6'b000000) & (funct == 6'b100110);
   assign addiW = (opcode == 6'b001000);
   assign andiW = (opcode == 6'b001100); 
   assign oriW = (opcode == 6'b001101);
   assign xoriW = (opcode == 6'b001110);
   
   assign except = ~(addW | subW | andW | orW | norW | xorW | addiW | andiW | oriW | xoriW);

   assign alu_op[2] = (andW | orW | norW | xorW | andiW | oriW | xoriW);
   assign alu_op[1] = (addW | subW | norW | xorW | addiW | xoriW);
   assign alu_op[0] = (subW | orW | xorW | oriW | xoriW);   
   
   assign rd_src = addiW | andiW | oriW | xoriW;
   assign writeenable = ~except;
   assign alu_src2 = rd_src;
   
   
endmodule // mips_decode
