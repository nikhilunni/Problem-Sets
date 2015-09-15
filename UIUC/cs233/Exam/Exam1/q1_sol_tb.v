module test;

   // these are inputs to "circuit under test"
   reg       L;
   reg       R;
   reg       C;
   reg       S;

  // wires for the outputs of "circuit under test"
   wire [1:0] bin;

  // the circuit under test
   widget w(bin, L, R, C, S);  
    
   initial begin               // initial = run at beginning of simulation
                               // begin/end = associate block with initial
      
      $dumpfile("test.vcd");  // name of dump file to create
      $dumpvars(0, test);     // record all signals of module "test" and sub-modules
                              // remember to change "test" to the correct
                              // module name when writing your own test benches
        
      // test all input combinations
      L = 0; R = 0; C = 0; S = 0; #10;
      L = 0; R = 0; C = 0; S = 1; #10;
      L = 0; R = 0; C = 1; S = 0; #10;
      L = 0; R = 0; C = 1; S = 1; #10;
      L = 0; R = 1; C = 0; S = 0; #10;
      L = 0; R = 1; C = 0; S = 1; #10;
      L = 0; R = 1; C = 1; S = 0; #10;
      L = 0; R = 1; C = 1; S = 1; #10;
      L = 1; R = 0; C = 0; S = 0; #10;
      L = 1; R = 0; C = 0; S = 1; #10;
      L = 1; R = 0; C = 1; S = 0; #10;
      L = 1; R = 0; C = 1; S = 1; #10;
      L = 1; R = 1; C = 0; S = 0; #10;
      L = 1; R = 1; C = 0; S = 1; #10;
      L = 1; R = 1; C = 1; S = 0; #10;
      L = 1; R = 1; C = 1; S = 1; #10;
      
      $finish;        // end the simulation
   end                      
   
   initial begin
     $display("inputs = L, R, C, S  outputs = bin");
     $monitor("inputs = %d  %d  %d  %d  outputs = %d   time = %2t",
              L, R, C, S, bin, $time);
   end
endmodule // test
