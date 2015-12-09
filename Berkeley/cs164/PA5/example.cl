class A inherits IO {
  a : Int <- 11;
  print() : Object {{out_int(a); out_string("\n");}};
};

class B inherits A {
  b : Int <- 22;
  b() : Int {b};
  print() : Object {{out_int(b); out_string("\n");}};
};


class Test inherits IO {
      fun() : Object {{
      	    let a:Int in out_int(a);
      }};
};

class Main inherits B {
      main : Int <- 33;
      print() : Object {{out_int(main); out_string("\n");}};
      main() : Object {{
      	     (new B).print();  
      }};
};