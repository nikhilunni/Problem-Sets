class A inherits IO {

};

class B inherits A {
      coolAttr:Int <- {out_string("LOOL\n"); 2;};
      fun(a:Int, b:Int) : Object {{
      	 out_int(a);
	 out_string("\n");
      	 out_int(b);
	 out_string("\n");

      }};
};

class Other {
  j:Int <- tiny();
  tiny():Int {{false; "Hi"; 42;}};
};

class Main inherits B {
  i:Int <- 43;
  getI() : Int {i};
  setI(newI:Int) : Int {i <- newI};

  bigSelf():Object {
    let
      v : Main,             -- void
      s : Main <- self,     -- self
      t : Main <- new Main  -- another Blah
    in {
      out_string("bigSelf\n");

      if (isvoid v) then out_string("v is void\n") else out_string("WRONG\n") fi;
      if (v = s) then out_string("WRONG\n") else out_string("v neq s\n") fi;
      if (s = t) then out_string("WRONG\n") else out_string("s neq t\n") fi;
      if (v = t) then out_string("WRONG\n") else out_string("v neq t\n") fi;

      if("sdf" = "s".concat("df")) then out_string("EQUALS\n") else out_string("NOT EQUALS\n") fi;

      s.setI(3);
      t.setI(4);
      if(not s.getI() = t.getI()) then out_string("sI is different than tI\n") else out_string("WRONG\n") fi;

      t <- self;
      if(s = t) then out_string("s equals t\n") else out_string("WRONG\n") fi;

      s.setI(5);
      t.setI(6);

      if(s.getI() = t.getI()) then out_string("sI = tI\n") else out_string("WRONG\n") fi;
    }
  };
  thing : Main;
  o : Object;






  main() : Object {{
      bigSelf();	 
  }};
};