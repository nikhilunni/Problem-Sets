class Main { main() : Int {0 }; };

class A {
      a() : Int { "sdf" + 4};
};

class B inherits A {
      attr : Int <- 12;
};

class C inherits B {
      newMethod(b : B) : Int {b@B.a("asdf")};
};

class D inherits B {
      s : String <- case attr of x:Object => "asdf"; self:SELF_TYPE => 7; x:Int => "asdf"; y:Int => "a"; esac;
};

class E inherits C {
      d() : Int {(let i : Int in let j : Int in let k : Int in "sdf")};
};
