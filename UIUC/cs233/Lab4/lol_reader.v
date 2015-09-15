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


module lol_reader(L, O, Y, bits, clk, restart);
   output      L, O, Y;
   input [2:0] bits;
   input       restart, clk;
   wire        A,B,C,D,E,A_next,B_next,C_next,D_next,E_next;

   dffe A_flip(A,A_next,clk,1,0);
   assign A_next = 
		  ((A & bits != 3'b000) |
		   (B & (bits != 3'b111 & bits != 3'b000)) |
		   (C & (bits != 3'b001 & bits != 3'b000)) |
		   (D & bits != 3'b000) |
		   (E & (bits != 3'b111 & bits != 3'b000))) & ~restart;

   dffe B_flip(B,B_next,clk,1,0);
   assign B_next = ((A & bits==3'b000) | (B & bits==3'b000) |
		   (C & bits==3'b000) | (E & bits==3'b000)) | restart;

   dffe C_flip(C,C_next,clk,1,0);
   assign C_next = ((B & bits==3'b111) | (E & bits==3'b111)) & ~restart;

   dffe D_flip(D,D_next,clk,1,0);
   assign D_next = (C & bits==3'b001) & ~restart;

   dffe E_flip(E,E_next,clk,1,0);
   assign E_next = (D & bits==3'b000) & ~restart;
   
   assign L = (E); 

   wire        garbage,w1,w2,o1,o2,o3,
               garbage_next,w1_next,w2_next,o1_next,o2_next,o3_next;
   dffe garbage_flip(garbage,garbage_next,clk,1,0);
   assign garbage_next = 
		    ((garbage & bits != 3'b000) |
			 (w1 & (bits != 3'b111 & bits != 3'b000)) |
			 (o1 & (bits != 3'b101 & bits != 3'b000)) |
			 (o2 & (bits != 3'b111 & bits != 3'b000)) |
			 (o3 & (bits != 3'b000)) |
			 (w2 & (bits != 3'b111 & bits != 3'b000))) & ~restart;

   dffe w1_flip(w1,w1_next,clk,1,0);
   assign w1_next = ((garbage & bits==3'b000) | (w1 & bits==3'b000) |
		    (o1 & bits==3'b000) | (o2 & bits==3'b000) |
		    (w2 & bits==3'b000)) | restart;

   dffe o1_flip(o1,o1_next,clk,1,0);
   assign o1_next = ((w1 & bits==3'b111) | (w2 & bits==3'b111)) & ~restart;

   dffe o2_flip(o2,o2_next,clk,1,0);
   assign o2_next = (o1 & bits==3'b101) & ~restart;

   dffe o3_flip(o3,o3_next,clk,1,0);
   assign o3_next = (o2 & bits==3'b111) & ~restart;

   dffe w2_flip(w2,w2_next,clk,1,0);
   assign w2_next = (o3 & bits==3'b000) & ~restart;

   assign O = (w2);


   wire        garbage2,w3,w4,y1,y2,y3,
	       garbage2_next,w3_next,w4_next,y1_next,y2_next,y3_next;

   dffe garbage2_flip(garbage2,garbage2_next,clk,1,0);
   assign garbage2_next = 
		    ((garbage2 & bits != 3'b000) |
			 (w3 & (bits != 3'b100 & bits != 3'b000)) |
			 (y1 & (bits != 3'b011 & bits != 3'b000)) |
			 (y2 & (bits != 3'b100 & bits != 3'b000)) |
			 (y3 & (bits != 3'b000)) |
			 (w4 & (bits != 3'b100 & bits != 3'b000))) & ~restart;
   
   dffe w3_flip(w3,w3_next,clk,1,0);
   assign w3_next = ((garbage2 & bits==3'b000) | (w3 & bits==3'b000) |
		    (y1 & bits==3'b000) | (y2 & bits==3'b000) |
		    (w4 & bits==3'b000)) | restart;

   dffe y1_flip(y1,y1_next,clk,1,0);
   assign y1_next = ((w3 & bits==3'b100) | (w4 & bits==3'b100)) & ~restart;

   dffe y2_flip(y2,y2_next,clk,1,0);
   assign y2_next = (y1 & bits==3'b011) & ~restart;

   dffe y3_flip(y3,y3_next,clk,1,0);
   assign y3_next = (y2 & bits==3'b100) & ~restart;

   dffe w4_flip(w4,w4_next,clk,1,0);
   assign w4_next = (y3 & bits==3'b000) & ~restart;

   assign Y = (w4);

   
endmodule // lol_reader
