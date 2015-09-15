module alu32_test;
   reg [31:0] A = 0, B = 0;
   reg [2:0]  control = 0;

   initial begin
      $dumpfile("alu32.vcd");
      $dumpvars(0, alu32_test);
      
      A = 8; B = 4; control = `ALU_ADD; // try adding 8 and 4
      #16 A = 32'h7FFFFFFF; B=32'h7FFFFFFF; control = `ALU_ADD; //-2 + overflow     
	  #16 A = -1; B=1; control = `ALU_ADD; //0 + overflow
      #16 A = 2; B = 5; control = `ALU_SUB; // -3 + negative
      #16 A = 32'h80000000; B = 32'h0FFFFFFF; control = `ALU_SUB;
      #16 A = 32'hFFFFFFFF; B=1; control = `ALU_AND; //1111... ^ 000...01
      #16 A = 32'hFFFF0000; B=32'h0000FFFF; control = `ALU_OR;
      #16 A = 32'h0000FFFF; B=32'hFFFF0000; control = `ALU_NOR;
      #16 A = 32'hF0F0F0F0; B=32'hFF00FF00; control = `ALU_XOR;
      
      

      # 10 $finish;
   end

   wire [31:0] out;
   wire        overflow, zero, negative;
   alu32 a(out, overflow, zero, negative, A, B, control);  
endmodule // alu32_test
