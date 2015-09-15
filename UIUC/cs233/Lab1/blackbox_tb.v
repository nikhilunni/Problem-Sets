module blackbox_test;
   reg s,l,g;
   wire b;
   blackbox bbox (b,s,l,g);
   initial begin
      $dumpfile("blackbox.vcd");
      $dumpvars(0,blackbox_test);

      s=0;
      l=0;
      g=0;
      #10;

      s=0;
      l=1;
      g=0;
      #10;

      s=0;
      l=0;
      g=1;
      #10;

      s=0;
      l=1;
      g=1;
      #10;

      s=1;
      l=0;
      g=0;
      #10;

      s=1;
      l=1;
      g=0;
      #10;

      s=1;
      l=0;
      g=1;
      #10;

      s=1;
      l=1;
      g=1;
      #10;

      $finish;
   end // initial begin

   initial
     $monitor("At time %2t, s = %d l = %d g = %d b = %d", $time, s, l, g, b);
endmodule // blackbox_test
