// 00 - AND, 01 - OR, 10 - NOR, 11 - XOR
module logicunit(out, A, B, control);
    output      out;
    input       A, B;
    input [1:0] control;
	wire out0,out1,out2,out3;
	and a1(out0,A,B);
	or o1(out1,A,B);
	nor no1(out2,A,B);
	xor xo1(out3,A,B);
	mux4 mux(out,out0,out1,out2,out3,control);
endmodule // logicunit
