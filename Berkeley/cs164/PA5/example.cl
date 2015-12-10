class A inherits IO {

};

class B inherits A {

};


class Test inherits IO {

};


class Main inherits B {
  main : Int <- 33;
  main() : Object
  {
      case (4432) of
	i : B => out_string("B!\n");
	b : A => out_string("A!\n");
	c : Int => out_int(c);
	d : Bool => out_string("Bool!\n");
      esac
  };
};

class Extension inherits Main {

};

class ExtExtension inherits Extension {

};

class Extension2 inherits Main {

};

