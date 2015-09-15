// arith_machine: execute a series of arithmetic instructions from an instruction cache
//
// except (output) - set to 1 when an unrecognized instruction is to be executed.
// clk    (input)  - the clock signal
// reset  (input)  - set to 1 to set all registers to zero, set to 0 for normal execution.

module arith_machine(except, clk, reset);
    output      except;
    input       clk, reset;

    wire [31:0] inst;  
    wire [31:0] PC;  
	wire [31:0] nextPC, rsData, rtData, out, imm32, alu2_secondIn;
	wire [4:0] Rdest;
	wire [1:0] overflow,zero,negative; //Have to capture them even if we don't read them...
	wire [2:0] alu_op;
	wire writeenable, rd_src, alu_src2;
    // DO NOT comment out or rename this module
    // or the test bench will break
    register #(32) PC_reg(PC, nextPC, clk, 1, reset);
	alu32 alu1(nextPC, overflow[0],zero[0],negative[0],PC, 32'd4, 3'd2);

	instruction_memory instrMem(inst, PC[31:2]);

	assign imm32 = {{16{inst[15]}}, inst[15:0]}; //Sign extender 
	mux2v mux1(alu2_secondIn, rtData, imm32, alu_src2);
	alu32 alu2(out, overflow[1], zero[1], negative[1], rsData, alu2_secondIn, alu_op);

    mux2v mux2(Rdest,inst[15:11], inst[20:16], rd_src); 
    regfile rf (rsData, rtData, inst[25:21], inst[20:16], Rdest, out, writeenable, clk, reset);

	mips_decode decoder(alu_op, writeenable, rd_src, alu_src2, except, inst[31:26], inst[5:0]);

    /* add other modules */
   
endmodule // arith_machine
