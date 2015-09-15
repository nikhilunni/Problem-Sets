// mips_decode: a decoder for MIPS arithmetic instructions
//
// alu_op       (output) - control signal to be sent to the ALU
// writeenable  (output) - should a new value be captured by the register file
// rd_src       (output) - should the destination register be rd (0) or rt (1)
// alu_src2     (output) - should the 2nd ALU source be a register (0) or an immediate (1)
// except       (output) - set to 1 when we don't recognize an opdcode & funct combination
// control_type (output) - 00 = fallthrough, 01 = branch_target, 10 = jump_target, 11 = jump_register 
// mem_read     (output) - the register value written is coming from the memory
// word_we      (output) - we're writing a word's worth of data
// byte_we      (output) - we're only writing a byte's worth of data
// byte_load    (output) - we're doing a byte load
// lui          (output) - the instruction is a lui
// slt          (output) - the instruction is an slt
// opcode        (input) - the opcode field from the instruction
// funct         (input) - the function field from the instruction
// zero          (input) - from the ALU
//

module mips_decode(alu_op, writeenable, rd_src, alu_src2, except, control_type,
                   mem_read, word_we, byte_we, byte_load, lui, slt, 
                   opcode, funct, zero);
   output [2:0] alu_op;
   output       writeenable, rd_src, alu_src2, except;
   output [1:0] control_type;
   output       mem_read, word_we, byte_we, byte_load, lui, slt;
   input [5:0] 	opcode, funct;
   input        zero;
   
   wire 	addW,subW,andW,orW,norW,xorW,addiW,andiW,oriW,xoriW;
   wire         beqW,bneW,jW,jrW,luiW,sltW,lwW,lbuW,swW,sbW;
   
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

   assign beqW = (opcode == `OP_BEQ);
   assign bneW = (opcode == `OP_BNE);
   assign jW = (opcode == `OP_J);
   assign jrW = (opcode == 6'b000000) & (funct == `OP0_JR);
   assign luiW = (opcode == `OP_LUI);
   assign sltW = (opcode == 6'b000000) & (funct == `OP0_SLT);
   assign lwW = (opcode == `OP_LW);
   assign lbuW = (opcode == `OP_LBU);
   assign swW = (opcode == `OP_SW);
   assign sbW = (opcode == `OP_SB);


   assign alu_op[2] = (andW | orW | norW | xorW | andiW | oriW | xoriW);
   assign alu_op[1] = (addW | subW | norW | xorW | addiW | xoriW | beqW | lwW | bneW | sltW | lbuW | swW | sbW); //Sub for the ZERO
   assign alu_op[0] = (subW | orW | xorW | oriW | xoriW | beqW | bneW | sltW); 
   
   assign except = ~(addW|subW|andW|orW|norW|xorW|addiW|andiW|oriW|xoriW|beqW|bneW|jW|jrW|luiW|sltW|lwW|lbuW|swW|sbW);
   assign writeenable = (addW|subW|andW|orW|norW|xorW|addiW|andiW|oriW|xoriW|luiW|sltW|lwW|lbuW);
   assign rd_src = addiW | andiW | oriW | xoriW | luiW | lwW | lbuW | swW | sbW;
   assign mem_read = (lwW | lbuW);
   assign alu_src2 = rd_src;   
   assign byte_we = sbW;   
   assign word_we = swW;
   assign byte_load = lbuW;
   assign lui = luiW;
   assign slt = sltW;
   assign control_type[0] = (beqW & zero | bneW & ~zero | jrW); //We "sub"d
   assign control_type[1] = (jW | jrW);   
   

endmodule // mips_decode
