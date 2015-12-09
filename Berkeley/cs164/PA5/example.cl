class A inherits IO {
  a : Int <- 77;    
};

class B inherits A {
  b : Int <- 44;
  b() : Int {b};
  print() : Object {out_int(b)};
};


class Test inherits IO {
      fun() : Object {{
      	    let foo:Int <-73, foo:Int <- ~43, foo:Bool in if not foo then
	    	let foo:Int in out_int(foo+94) else
		out_int(5)
		fi;
      }};
};

class Main inherits B {
      main : Int <- 56;
      main() : Object {{
      	     (new Test).fun();
      }};
};