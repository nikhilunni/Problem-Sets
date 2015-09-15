// dffe: D-type flip-flop with enable
//
// q      (output) - Current value of flip flop
// d      (input)  - Next value of flip flop
// clk    (input)  - Clock (positive edge-sensitive)
// enable (input)  - Load new value? (yes = 1, no = 0)
// reset  (input)  - Asynchronous reset   (reset =  1)
//
module dffe(q, d, clk, enable, reset);
   output q;
   reg    q;
   input  d;
   input  clk, enable, reset;
   
   always@(reset)
     if (reset == 1'b1)
       q <= 0;
   
   always@(posedge clk)
     if ((reset == 1'b0) && (enable == 1'b1))
       q <= d;
endmodule // dffe


module l_reader(L, bits, clk, restart);
   output      L;
   input [2:0] bits;
   input       restart, clk;
   wire        A,B,C,D,E,A_next,B_next,C_next,D_next,E_next;
   
   dffe A_flip(A,A_next,clk,1,0);
   assign A_next = (A & bits != 3'b000) | restart |
       (B & (bits != 3'b111 | bits != 3'b000)) |
       (C & (bits != 3'b001 | bits != 3'b000)) |
       (D & bits != 3'b000) |
       (E & (bits != 3'b111 | bits != 3'b000));

   dffe B_flip(B,B_next,clk,1,0);
   assign B_next = (A & bits==3'b000) | (B & bits==3'b000) |
       (C & bits==3'b000) | (E & bits==3'b000);	

   dffe C_flip(C,C_next,clk,1,0);
   assign C_next = (B & bits==3'b111) | (E & bits==3'b111);

   dffe D_flip(D,D_next,clk,1,0);
   assign D_next = (C & bits==3'b001);

   dffe E_flip(E,E_next,clk,1,0);
   assign E_next = (D & bits==3'b000);

   assign L = (E & bits==3'b000); 
endmodule // l_reader
