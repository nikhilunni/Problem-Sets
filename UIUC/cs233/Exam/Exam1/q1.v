// Widgets Incorporated has hired you to build a widget sorter for its
// production line.  The widgets they produce are either red or blue,
// large or small, cube or spherical, and steel or plastic.

// Your widget sorter has 4 sensors:
// A scale that weighs the widget (L = 1, when the widget is large; otherwise L = 0)
// A camera that measures the color (R = 1, when the widget is red; otherwise R = 0) and
//   shape (C = 1, when the widget is cube-shaped; otherwise C = 0)
// A magnet that senses metallic objects (S = 1, when the widget is steel; otherwise S = 0)

// You need to sort the widgets into 4 bins based on their characteristics:
// Small blue plastic and large spherical steel widgets should go in bin 0.
// Small blue steel and large blue cube-shaped widgets should go in bin 1.
// Large spherical plastic and small red spherical widgets should go in bin 3.
// All other widgets should go in bin 2.

module widget(bin, L, R, C, S);
   output [1:0] bin;
   input  	L, R, C, S;

   assign bin[0] = (~L&~R&S | L&~R&C | L&~C&~S | ~L&R&~C) & !(~L&~R&~S | L&~C&S);   
   assign bin[1] = (L&~C&~S | ~L&R&~C | ~bin[0]) & !(~L&~R&~S | L&~C&S);
   

endmodule // widget

