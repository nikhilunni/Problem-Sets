class A inherits IO {

};

class B inherits A {
      fun(a:Int, b:Int) : Object {{
      	 out_int(a);
	 out_string("\n");
      	 out_int(b);
	 out_string("\n");

      }};
};


class Main inherits B {
  main : Int <- 33;
  main() : Object
  {
	(new B).fun({out_string("first arg\n"); 0;}, {out_string("second arg\n"); 1;})
  };
};