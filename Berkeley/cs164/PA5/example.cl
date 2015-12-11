(*
   The class A2I provides integer-to-string and string-to-integer
conversion routines.  To use these routines, either inherit them
in the class where needed, have a dummy variable bound to
something of type A2I, or simpl write (new A2I).method(argument).
*)


(*
   c2i   Converts a 1-character string to an integer.  Aborts
         if the string is not "0" through "9"
*)
class A2I {

     c2i(char : String) : Int {
        if char = "0" then 0 else
        if char = "1" then 1 else
        if char = "2" then 2 else
        if char = "3" then 3 else
        if char = "4" then 4 else
        if char = "5" then 5 else
        if char = "6" then 6 else
        if char = "7" then 7 else
        if char = "8" then 8 else
        if char = "9" then 9 else
        { abort(); 0; }  (* the 0 is needed to satisfy the
                                  typchecker *)
        fi fi fi fi fi fi fi fi fi fi
     };

(*
   i2c is the inverse of c2i.
*)
     i2c(i : Int) : String {
        if i = 0 then "0" else
        if i = 1 then "1" else
        if i = 2 then "2" else
        if i = 3 then "3" else
        if i = 4 then "4" else
        if i = 5 then "5" else
        if i = 6 then "6" else
        if i = 7 then "7" else
        if i = 8 then "8" else
        if i = 9 then "9" else
        { abort(); ""; }  -- the "" is needed to satisfy the typchecker
        fi fi fi fi fi fi fi fi fi fi
     };

(*
   a2i converts an ASCII string into an integer.  The empty string
is converted to 0.  Signed and unsigned strings are handled.  The
method aborts if the string does not represent an integer.  Very
long strings of digits produce strange answers because of arithmetic 
overflow.

*)
     a2i(s : String) : Int {
        if s.length() = 0 then 0 else
        if s.substr(0,1) = "-" then ~a2i_aux(s.substr(1,s.length()-1)) else
        if s.substr(0,1) = "+" then a2i_aux(s.substr(1,s.length()-1)) else
           a2i_aux(s)
        fi fi fi
     };

(* a2i_aux converts the usigned portion of the string.  As a
   programming example, this method is written iteratively.  *)


     a2i_aux(s : String) : Int {
        (let int : Int <- 0 in        
           {        
               (let j : Int <- s.length() in
                  (let i : Int <- 0 in
                    while i < j loop
                        {
                            int <- int * 10 + c2i(s.substr(i,1));
                            i <- i + 1;
                        }
                    pool
                  )
               );
              int;
            }
        )
     };

(* i2a converts an integer to a string.  Positive and negative 
   numbers are handled correctly.  *)

    i2a(i : Int) : String {
        if i = 0 then "0" else 
        if 0 < i then i2a_aux(i) else
          "-".concat(i2a_aux(i * ~1)) 
        fi fi
    };
        
(* i2a_aux is an example using recursion.  *)                

    i2a_aux(i : Int) : String {
        if i = 0 then "" else 
            (let next : Int <- i / 10 in
                i2a_aux(next).concat(i2c(i - next * 10))
            )
        fi
    };

};

class Main0 inherits IO {
    main(): Object {
        let numString: String,
        	num: Int,
        	resultString: String,
        	result: Int,
        	a2i: A2I <- new A2I
        in {
            numString <- "1234";
            num <- a2i.a2i(numString);
            result <- num * num;
            resultString <- a2i.i2a(result);
            out_string(numString.concat(" * ".concat(numString.concat(" is ".concat(resultString.concat("\n"))))));
        }
    };
};

-- example of static and dynamic type differing for a dispatch

Class Book inherits IO {
    title : String;
    author : String;

    initBook(title_p : String, author_p : String) : Book {
        {
            title <- title_p;
            author <- author_p;
            self;
        }
    };

    print() : Book {
        {
            out_string("title:      ").out_string(title).out_string("\n");
            out_string("author:     ").out_string(author).out_string("\n");
            self;
        }
    };
};

Class Article inherits Book {
    per_title : String;

    initArticle(title_p : String, author_p : String,
        per_title_p : String) : Article {
        {
            initBook(title_p, author_p);
            per_title <- per_title_p;
            self;
        }
    };

    print() : Book {
        {
        self@Book.print();
            out_string("periodical:  ").out_string(per_title).out_string("\n");
            self;
        }
    };
};

Class BookList inherits IO { 
    (* Since abort "returns" type Object, we have to add
       an expression of type Bool here to satisfy the typechecker.
       This code is unreachable, since abort() halts the program.
    *)
    isNil() : Bool { { abort(); true; } };
    
    cons(hd : Book) : Cons {
        (let new_cell : Cons <- new Cons in
            new_cell.init(hd,self)
        )
    };

    (* Since abort "returns" type Object, we have to add
       an expression of type Book here to satisfy the typechecker.
       This code is unreachable, since abort() halts the program.
    *)
    car() : Book { { abort(); new Book; } };
    
    (* Since abort "returns" type Object, we have to add
       an expression of type BookList here to satisfy the typechecker.
       This code is unreachable, since abort() halts the program.
    *)
    cdr() : BookList { { abort(); new BookList; } };
    
    print_list() : Object { abort() };
};

Class Cons inherits BookList {
    xcar : Book;  -- We keep the car and cdr in attributes.
    xcdr : BookList; -- Because methods and features must have different names,
    -- we use xcar and xcdr for the attributes and reserve
    -- car and cdr for the features.
    
    isNil() : Bool { false };
    
    init(hd : Book, tl : BookList) : Cons {
        {
            xcar <- hd;
            xcdr <- tl;
            self;
        }
    };

    car() : Book { xcar };

    cdr() : BookList { xcdr };
    
    print_list() : Object {
        {
            case xcar.print() of
                dummy : Book => out_string("- dynamic type was Book -\n");
                dummy : Article => out_string("- dynamic type was Article -\n");
            esac;
            xcdr.print_list();
        }
    };
};

Class Nil inherits BookList {
    isNil() : Bool { true };

    print_list() : Object { true };
};


Class Main1 {

    books : BookList;

    main() : Object {
        (let a_book : Book <-
            (new Book).initBook("Compilers, Principles, Techniques, and Tools",
                                "Aho, Sethi, and Ullman")
        in
            (let an_article : Article <-
                (new Article).initArticle("The Top 100 CD_ROMs",
                                          "Ulanoff",
                                          "PC Magazine")
            in
                {
                    books <- (new Nil).cons(a_book).cons(an_article);
                    books.print_list();
                }
            )  -- end let an_article
        )  -- end let a_book
    };
};

(* models one-dimensional cellular automaton on a circle of finite radius
   arrays are faked as Strings,
   X's respresent live cells, dots represent dead cells,
   no error checking is done *)
class CellularAutomaton inherits IO {
    population_map : String;
   
    init(map : String) : SELF_TYPE {
        {
            population_map <- map;
            self;
        }
    };
   
    print() : SELF_TYPE {
        {
            out_string(population_map.concat("\n"));
            self;
        }
    };
   
    num_cells() : Int {
        population_map.length()
    };
   
    cell(position : Int) : String {
        population_map.substr(position, 1)
    };
   
    cell_left_neighbor(position : Int) : String {
        if position = 0 then
            cell(num_cells() - 1)
        else
            cell(position - 1)
        fi
    };
   
    cell_right_neighbor(position : Int) : String {
        if position = num_cells() - 1 then
            cell(0)
        else
            cell(position + 1)
        fi
    };
   
    (* a cell will live if exactly 1 of itself and it's immediate
       neighbors are alive *)
    cell_at_next_evolution(position : Int) : String {
        if (if cell(position) = "X" then 1 else 0 fi
            + if cell_left_neighbor(position) = "X" then 1 else 0 fi
            + if cell_right_neighbor(position) = "X" then 1 else 0 fi
            = 1)
        then
            "X"
        else
            "."
        fi
    };
   
    evolve() : SELF_TYPE {
        (let position : Int in
        (let num : Int <- num_cells() in
        (let temp : String in
            {
                while position < num loop
                    {
                        temp <- temp.concat(cell_at_next_evolution(position));
                        position <- position + 1;
                    }
                pool;
                population_map <- temp;
                self;
            }
        ) ) )
    };
};

class Main2 {
    cells : CellularAutomaton;
   
    main() : SELF_TYPE {
        {
            cells <- (new CellularAutomaton).init("         X         ");
            cells.print();
            (let countdown : Int <- 20 in
                while 0 < countdown loop
                    {
                        cells.evolve();
                        cells.print();
                        countdown <- countdown - 1;
                    }
                pool
            );
            self;
        }
    };
};

class Main3 inherits IO {
 main() : SELF_TYPE {
	(let c : Complex <- (new Complex).init(1, 1) in
	 if c.reflect_X().reflect_Y() = c.reflect_0()
	 then out_string("=)\n")
	 else out_string("=(\n")
	 fi
	)
 };
};

class Complex inherits IO {
 x : Int;
 y : Int;

 init(a : Int, b : Int) : Complex {
	{
	 x = a;
	 y = b;
	 self;
	}
 };

 print() : Object {
	if y = 0
	then out_int(x)
	else out_int(x).out_string("+").out_int(y).out_string("I")
	fi
 };

 reflect_0() : Complex {
	{
	 x = ~x;
	 y = ~y;
	 self;
	}
 };

 reflect_X() : Complex {
	{
	 y = ~y;
	 self;
	}
 };

 reflect_Y() : Complex {
	{
	 x = ~x;
	 self;
	}
 };
};


class Main4 inherits IO {
 main() : SELF_TYPE {
 {
 out_string((new Object).type_name().substr(4,1)).
 out_string((isvoid self).type_name().substr(1,3));
 out_string("\n");
 out_string("\"");
 out_string(self.type_name().concat(" is my name!"));
 out_string("\" has length : ");
 out_int(self.type_name().concat(" is my name!").length());
 out_string("\n");
 }
 };
};

(* hairy . . .*)

class Bazz inherits IO {

 h : Int <- 1;

 g : Foo <- case self of
		 	n : Bazz => (new Foo);
		 	n : Razz => (new Bar);
			n : Foo => (new Razz);
			n : Bar => n;
		 esac;

 i : Object <- printh();

 printh() : Int { { out_int(h); 0; } };

 doh() : Int { (let i: Int <- h in { h <- h + 1; i; } ) };
};

class Foo inherits Bazz {
 a : Razz <- case self of
		 n : Razz => (new Bar);
		 n : Foo => (new Razz);
		 n : Bar => n;
 	 esac;

 b : Int <- a.doh() + g.doh() + doh() + printh();

 doh() : Int { (let i : Int <- h in { h <- h + 2; i; } ) };

};

class Razz inherits Foo {

 e : Bar <- case self of
		 n : Razz => (new Bar);
		 n : Bar => n;
		esac;

 f : Int <- a@Bazz.doh() + g.doh() + e.doh() + doh() + printh();

};

class Bar inherits Razz {

 c : Int <- doh();

 d : Object <- printh();
};

(* scary . . . *)
class Main5 inherits IO {
 a : Bazz <- new Bazz;
 b : Foo <- new Foo;
 c : Razz <- new Razz;
 d : Bar <- new Bar;

 main(): String { { out_string("\n") ; "do nothing" ; } };

};


(* A program for
   1. Representing lambda terms
   2. Interpreting lambda terms
   3. Compiling lambda calculus programs to Cool
   The lambda calculus is described by the following grammar:
   e ::= x	       a variable
      |  \x.e	       a function with argument x
      |  e1@e2	       apply function e1 to argument e2
  Jeff Foster (jfoster@cs.berkeley.edu)
  March 24, 2000
*)

(*
 * A list of variables.  We use this to do de Bruijn numbering
 *
 *)
class VarList inherits IO {
  isNil() : Bool { true };
  head()  : Variable { { abort(); new Variable; } };
  tail()  : VarList { { abort(); new VarList; } };
  add(x : Variable) : VarList { (new VarListNE).init(x, self) };
  print() : SELF_TYPE { out_string("\n") };
};

class VarListNE inherits VarList {
  x : Variable;
  rest : VarList;
  isNil() : Bool { false };
  head()  : Variable { x };
  tail()  : VarList { rest };
  init(y : Variable, r : VarList) : VarListNE { { x <- y; rest <- r; self; } };
  print() : SELF_TYPE { { x.print_self(); out_string(" ");
	                  rest.print(); self; } };
};

(*
 * A list of closures we need to build.  We need to number (well, name)
 * the closures uniquely.
 *)
class LambdaList {
  isNil() : Bool { true };
  headE() : VarList { { abort(); new VarList; } };
  headC() : Lambda { { abort(); new Lambda; } };
  headN() : Int { { abort(); 0; } };
  tail()  : LambdaList { { abort(); new LambdaList; } };
  add(e : VarList, x : Lambda, n : Int) : LambdaList {
    (new LambdaListNE).init(e, x, n, self)
  };
};

class LambdaListNE inherits LambdaList {
  lam : Lambda;
  num : Int;
  env : VarList;
  rest : LambdaList;
  isNil() : Bool { false };
  headE() : VarList { env };
  headC() : Lambda { lam };
  headN() : Int { num };
  tail()  : LambdaList { rest };
  init(e : VarList, l : Lambda, n : Int, r : LambdaList) : LambdaListNE {
    {
      env <- e;
      lam <- l;
      num <- n;
      rest <- r;
      self;
    }
  };
};

class LambdaListRef {
  nextNum : Int <- 0;
  l : LambdaList;
  isNil() : Bool { l.isNil() };
  headE() : VarList { l.headE() };
  headC() : Lambda { l.headC() };
  headN() : Int { l.headN() };
  reset() : SELF_TYPE {
    {
      nextNum <- 0;
      l <- new LambdaList;
      self;
    }
  };
  add(env : VarList, c : Lambda) : Int {
    {
      l <- l.add(env, c, nextNum);
      nextNum <- nextNum + 1;
      nextNum - 1;
    }
  };
  removeHead() : SELF_TYPE {
    {
      l <- l.tail();
      self;
    }
  };
};

(*
 * Lambda expressions
 *
 *)

-- A pure virtual class representing any expression
class Expr inherits IO {

  -- Print this lambda term
  print_self() : SELF_TYPE {
    {
      out_string("\nError: Expr is pure virtual; can't print self\n");
      abort();
      self;
    }
  };

  -- Do one step of (outermost) beta reduction to this term
  beta() : Expr {
    {
      out_string("\nError: Expr is pure virtual; can't beta-reduce\n");
      abort();
      self;
    }
  };

  -- Replace all occurrences of x by e
  substitute(x : Variable, e : Expr) : Expr {
    {
      out_string("\nError: Expr is pure virtual; can't substitute\n");
      abort();
      self;
    }
  };

  -- Generate Cool code to evaluate this expression
  gen_code(env : VarList, closures : LambdaListRef) : SELF_TYPE {
    {
      out_string("\nError: Expr is pure virtual; can't gen_code\n");
      abort();
      self;
    }
  };
};

(*
 * Variables
 *)
class Variable inherits Expr {
  name : String;

  init(n:String) : Variable {
    {
      name <- n;
      self;
    }
  };

  print_self() : SELF_TYPE {
    out_string(name)
  };

  beta() : Expr { self };
  
  substitute(x : Variable, e : Expr) : Expr {
    if x = self then e else self fi
  };

  gen_code(env : VarList, closures : LambdaListRef) : SELF_TYPE {
    let cur_env : VarList <- env in
      { while (if cur_env.isNil() then
	          false
	       else
	         not (cur_env.head() = self)
	       fi) loop
	  { out_string("get_parent().");
	    cur_env <- cur_env.tail();
          }
        pool;
        if cur_env.isNil() then
          { out_string("Error:  free occurrence of ");
            print_self();
            out_string("\n");
            abort();
            self;
          }
        else
          out_string("get_x()")
        fi;
      }
  };
};

(*
 * Functions
 *)
class Lambda inherits Expr {
  arg : Variable;
  body : Expr;

  init(a:Variable, b:Expr) : Lambda {
    {
      arg <- a;
      body <- b;
      self;
    }
  };

  print_self() : SELF_TYPE {
    {
      out_string("\\");
      arg.print_self();
      out_string(".");
      body.print_self();
      self;
    }
  };

  beta() : Expr { self };

  apply(actual : Expr) : Expr {
    body.substitute(arg, actual)
  };

  -- We allow variables to be reused
  substitute(x : Variable, e : Expr) : Expr {
    if x = arg then
      self
    else
      let new_body : Expr <- body.substitute(x, e),
	  new_lam : Lambda <- new Lambda in
	new_lam.init(arg, new_body)
    fi
  };

  gen_code(env : VarList, closures : LambdaListRef) : SELF_TYPE {
    {
      out_string("((new Closure");
      out_int(closures.add(env, self));
      out_string(").init(");
      if env.isNil() then
        out_string("new Closure))")
      else
	out_string("self))") fi;
      self;
    }
  };

  gen_closure_code(n : Int, env : VarList,
		   closures : LambdaListRef) : SELF_TYPE {
    {
      out_string("class Closure");
      out_int(n);
      out_string(" inherits Closure {\n");
      out_string("  apply(y : EvalObject) : EvalObject {\n");
      out_string("    { out_string(\"Applying closure ");
      out_int(n);
      out_string("\\n\");\n");
      out_string("      x <- y;\n");
      body.gen_code(env.add(arg), closures);
      out_string(";}};\n");
      out_string("};\n");
    }
  };
};

(*
 * Applications
 *)
class App inherits Expr {
  fun : Expr;
  arg : Expr;

  init(f : Expr, a : Expr) : App {
    {
      fun <- f;
      arg <- a;
      self;
    }
  };

  print_self() : SELF_TYPE {
    {
      out_string("((");
      fun.print_self();
      out_string(")@(");
      arg.print_self();
      out_string("))");
      self;
    }
  };

  beta() : Expr {
    case fun of
      l : Lambda => l.apply(arg);     -- Lazy evaluation
      e : Expr =>
	let new_fun : Expr <- fun.beta(),
	    new_app : App <- new App in
	  new_app.init(new_fun, arg);
    esac
  };

  substitute(x : Variable, e : Expr) : Expr {
    let new_fun : Expr <- fun.substitute(x, e),
        new_arg : Expr <- arg.substitute(x, e),
        new_app : App <- new App in
      new_app.init(new_fun, new_arg)
  };

  gen_code(env : VarList, closures : LambdaListRef) : SELF_TYPE {
    {
      out_string("(let x : EvalObject <- ");
      fun.gen_code(env, closures);
      out_string(",\n");
      out_string("     y : EvalObject <- ");
      arg.gen_code(env, closures);
      out_string(" in\n");
      out_string("  case x of\n");
      out_string("    c : Closure => c.apply(y);\n");
      out_string("    o : Object => { abort(); new EvalObject; };\n");
      out_string("  esac)");
    }
  };
};

(*
 * Term: A class for building up terms
 *
 *)

class Term inherits IO {
  (*
   * The basics
   *)
  var(x : String) : Variable {
    let v : Variable <- new Variable in
      v.init(x)
  };

  lam(x : Variable, e : Expr) : Lambda {
    let l : Lambda <- new Lambda in
      l.init(x, e)
  };

  app(e1 : Expr, e2 : Expr) : App {
    let a : App <- new App in
      a.init(e1, e2)
  };

  (*
   * Some useful terms
   *)
  i() : Expr {
    let x : Variable <- var("x") in
      lam(x,x)
  };

  k() : Expr {
    let x : Variable <- var("x"),
        y : Variable <- var("y") in
    lam(x,lam(y,x))
  };

  s() : Expr {
    let x : Variable <- var("x"),
        y : Variable <- var("y"),
        z : Variable <- var("z") in
      lam(x,lam(y,lam(z,app(app(x,z),app(y,z)))))
  };

};

(*
 *
 * The main method -- build up some lambda terms and try things out
 *
 *)

class Main6 inherits Term {
  -- Beta-reduce an expression, printing out the term at each step
  beta_reduce(e : Expr) : Expr {
    {
      out_string("beta-reduce: ");
      e.print_self();
      let done : Bool <- false,
          new_expr : Expr in
        {
	  while (not done) loop
	    {
	      new_expr <- e.beta();
	      if (new_expr = e) then
		done <- true
	      else
		{
		  e <- new_expr;
		  out_string(" =>\n");
		  e.print_self();
		}
	      fi;
	    }
          pool;
	  out_string("\n");
          e;
	};
    }
  };

  eval_class() : SELF_TYPE {
    {
      out_string("class EvalObject inherits IO {\n");
      out_string("  eval() : EvalObject { { abort(); self; } };\n");
      out_string("};\n");
    }
  };

  closure_class() : SELF_TYPE {
    {
      out_string("class Closure inherits EvalObject {\n");
      out_string("  parent : Closure;\n");
      out_string("  x : EvalObject;\n");
      out_string("  get_parent() : Closure { parent };\n");
      out_string("  get_x() : EvalObject { x };\n");
      out_string("  init(p : Closure) : Closure {{ parent <- p; self; }};\n");
      out_string("  apply(y : EvalObject) : EvalObject { { abort(); self; } };\n");
      out_string("};\n");
    }
  };

  gen_code(e : Expr) : SELF_TYPE {
    let cl : LambdaListRef <- (new LambdaListRef).reset() in
      {
	out_string("Generating code for ");
	e.print_self();
	out_string("\n------------------cut here------------------\n");
	out_string("(*Generated by lam.cl (Jeff Foster, March 2000)*)\n");
	eval_class();
	closure_class();
	out_string("class Main {\n");
	out_string("  main() : EvalObject {\n");
	e.gen_code(new VarList, cl);
	out_string("\n};\n};\n");
	while (not (cl.isNil())) loop
	  let e : VarList <- cl.headE(),
	      c : Lambda <- cl.headC(),
	      n : Int <- cl.headN() in
	    {
	      cl.removeHead();
	      c.gen_closure_code(n, e, cl);
	    }
	pool;
	out_string("\n------------------cut here------------------\n");
      }
  };

  main() : Int {
    {
      i().print_self();
      out_string("\n");
      k().print_self();
      out_string("\n");
      s().print_self();
      out_string("\n");
      beta_reduce(app(app(app(s(), k()), i()), i()));
      beta_reduce(app(app(k(),i()),i()));
      gen_code(app(i(), i()));
      gen_code(app(app(app(s(), k()), i()), i()));
      gen_code(app(app(app(app(app(app(app(app(i(), k()), s()), s()),
                                   k()), s()), i()), k()), i()));
      gen_code(app(app(i(), app(k(), s())), app(k(), app(s(), s()))));
      0;
    }
  };
};


(*
 *  This file shows how to implement a list data type for lists of integers.
 *  It makes use of INHERITANCE and DYNAMIC DISPATCH.
 *
 *  The List class has 4 operations defined on List objects. If 'l' is
 *  a list, then the methods dispatched on 'l' have the following effects:
 *
 *    isNil() : Bool		Returns true if 'l' is empty, false otherwise.
 *    head()  : Int		Returns the integer at the head of 'l'.
 *				If 'l' is empty, execution aborts.
 *    tail()  : List		Returns the remainder of the 'l',
 *				i.e. without the first element.
 *    cons(i : Int) : List	Return a new list containing i as the
 *				first element, followed by the
 *				elements in 'l'.
 *
 *  There are 2 kinds of lists, the empty list and a non-empty
 *  list. We can think of the non-empty list as a specialization of
 *  the empty list.
 *  The class List defines the operations on empty list. The class
 *  Cons inherits from List and redefines things to handle non-empty
 *  lists.
 *)


class List {
   -- Define operations on empty lists.

   isNil() : Bool { true };

   -- Since abort() has return type Object and head() has return type
   -- Int, we need to have an Int as the result of the method body,
   -- even though abort() never returns.

   head()  : Int { { abort(); 0; } };

   -- As for head(), the self is just to make sure the return type of
   -- tail() is correct.

   tail()  : List { { abort(); self; } };

   -- When we cons and element onto the empty list we get a non-empty
   -- list. The (new Cons) expression creates a new list cell of class
   -- Cons, which is initialized by a dispatch to init().
   -- The result of init() is an element of class Cons, but it
   -- conforms to the return type List, because Cons is a subclass of
   -- List.

   cons(i : Int) : List {
      (new Cons2).init(i, self)
   };

};


(*
 *  Cons inherits all operations from List. We can reuse only the cons
 *  method though, because adding an element to the front of an emtpy
 *  list is the same as adding it to the front of a non empty
 *  list. All other methods have to be redefined, since the behaviour
 *  for them is different from the empty list.
 *
 *  Cons needs two attributes to hold the integer of this list
 *  cell and to hold the rest of the list.
 *
 *  The init() method is used by the cons() method to initialize the
 *  cell.
 *)

class Cons2 inherits List {

   car : Int;	-- The element in this list cell

   cdr : List;	-- The rest of the list

   isNil() : Bool { false };

   head()  : Int { car };

   tail()  : List { cdr };

   init(i : Int, rest : List) : List {
      {
	 car <- i;
	 cdr <- rest;
	 self;
      }
   };

};



(*
 *  The Main class shows how to use the List class. It creates a small
 *  list and then repeatedly prints out its elements and takes off the
 *  first element of the list.
 *)

class Main7 inherits IO {

   mylist : List;

   -- Print all elements of the list. Calls itself recursively with
   -- the tail of the list, until the end of the list is reached.

   print_list(l : List) : Object {
      if l.isNil() then out_string("\n")
                   else {
			   out_int(l.head());
			   out_string(" ");
			   print_list(l.tail());
		        }
      fi
   };

   -- Note how the dynamic dispatch mechanism is responsible to end
   -- the while loop. As long as mylist is bound to an object of 
   -- dynamic type Cons, the dispatch to isNil calls the isNil method of
   -- the Cons class, which returns false. However when we reach the
   -- end of the list, mylist gets bound to the object that was
   -- created by the (new List) expression. This object is of dynamic type
   -- List, and thus the method isNil in the List class is called and
   -- returns true.

   main() : Object {
      {
	 mylist <- new List.cons(1).cons(2).cons(3).cons(4).cons(5);
	 while (not mylist.isNil()) loop
	    {
	       print_list(mylist);
	       mylist <- mylist.tail();
	    }
	 pool;
      }
   };

};

class Main8 inherits IO {
    pal(s : String) : Bool {
	if s.length() = 0
	then true
	else if s.length() = 1
	then true
	else if s.substr(0, 1) = s.substr(s.length() - 1, 1)
	then pal(s.substr(1, s.length() -2))
	else false
	fi fi fi
    };

    i : Int;

    main() : SELF_TYPE {
	{
            i <- ~1;
	    if pal("12344321")
	    then out_string("12344321 is a palindrome.\n")
	    else out_string("12344321 is not a palindrome.\n")
	    fi;
	}
    };
};

class Main9 inherits IO {

 main() : Int {	-- main() is an atrophied method so we can parse.
 0 
 }; 

 out : Int <-		-- out is our 'output'.Its values are the primes.
 {
 out_string("2 is trivially prime.\n");
 2;
 };

 testee : Int <- out;	-- testee is a number to be tested for primeness. 

 divisor : Int;	-- divisor is a number which may factor testee.

 stop : Int <- 500;	-- stop is an arbitrary value limiting testee. 	

 m : Object <-		-- m supplants the main method.
 while true loop 
 {

 testee <- testee + 1;
 divisor <- 2;

 while 
 if testee < divisor * divisor 
 then false 		-- can stop if divisor > sqrt(testee).
	 else if testee - divisor*(testee/divisor) = 0 
 then false 		-- can stop if divisor divides testee. 
 else true
 fi fi 
 loop 
 divisor <- divisor + 1
 pool; 

 if testee < divisor * divisor	-- which reason did we stop for?
 then 	-- testee has no factors less than sqrt(testee).
 {
 out <- testee;	-- we could think of out itself as the output.
 out_int(out); 
 out_string(" is prime.\n");
 }
 else	-- the loop halted on testee/divisor = 0, testee isn't prime.
 0	-- testee isn't prime, do nothing.
	fi; 	

 if stop <= testee then 
 "halt".abort()	-- we could think of "halt" as SIGTERM.
 else 
 "continue"
 fi; 

 } 
 pool;

};

class Utility {
    modulo(num: Int, mod: Int): Int {
        num - (num / mod) * mod
    };
};

class Random {
    a: Int <- 1103515245;
    c: Int <- 12345;
    m: Int <- 2147483648;
    last: Int <- 1;
    util: Utility <- new Utility;
    
    setSeed(seed: Int): Int {
        last <- seed
    };
    
    next(): Int {
        last <- util.modulo(last * a + c, m) / 32
    };
    
    -- min: inclusive minimum
    -- max: exclusive maximum
    nextBetween(min: Int, max: Int): Int {{
        if max - min < 1 then
        	abort()
        else
        	"do nothing"
        fi;
        last <- util.modulo(last * a + c, m) / 32;
        util.modulo(last, max - min) + min;
    }};
};

class Main10 inherits IO {
    main() : Object {
        let i: Int,
        	rand: Random <- new Random,
        	util: Utility <- new Utility,
        	min: Int <- 1,
        	max: Int <- 0,
        	a: A2I <- new A2I
        in {
            out_string("Enter a number to use as a random seed:\n");
            rand.setSeed(24);
            while not min < max loop { 
                out_string("Minimum number (inclusive):\n");
                min <- 0;
                out_string("Maximum number (exclusive):\n");
                max <- 2000;
                if not min < max then
                	out_string("Maximum must be greater than minimum.  Please try again.\n")
                else
                	self
                fi;
            } pool;
            out_string("Random numbers between ".concat(a.i2a(~1*max).concat(" and ".concat(a.i2a(max).concat(":\n")))));
        	while i < 100 loop {
                out_string(a.i2a(rand.nextBetween(min, max)));
                if util.modulo(i + 1, 10) = 0 then
                	out_string("\n")
                else
                	out_string(", ")
                fi;
                i <- i + 1;
            } pool;
        }
    };
};

class Tricky2 inherits IO {
      my_int : Int <- {out_string("initialized my_int from "); out_string(self.type_name()); out_string("\n"); 42;};
      attr : SELF_TYPE <- self;
      print() : SELF_TYPE {{out_string("Came from "); out_string(self.type_name()); out_string("\n"); self;}};
      run_other(a : Tricky2) : SELF_TYPE {{a.print(); attr;}};
      me() : Tricky2 {new SELF_TYPE};
};

class Tricky3 inherits Tricky2 {
      print() : SELF_TYPE {{out_string("Came from Tricky3!\n"); self;}};
};

class Tricky inherits Tricky3 {
      main() : Object {{
      	     ((new Tricky3).me().print().me())@Tricky2.print();
	     (new Tricky2).me().print().run_other(new Tricky3);
      }};
};



class Main inherits IO {
      main() : Object {{
      	     (new Main0).main(); --A2I
	     (new Main1).main(); --Static vs. Dynamic dispatch
	     (new Main2).main(); --CellularAutomaton
	     (new Main3).main(); --Complex Numbers
	     (new Main4).main(); --Trying out some built-in runtime methods
	     (new Main5).main(); --Testing dispatch, recursive attribute inits
	     (new Main6).main(); --Lambda functions in COOL... tests a LOT, from complex dispatches to pretty involved algorithms. In general, it's a pretty big bit of code.
	     (new Main7).main(); --List class... Tests mutually recursive classes, dispatch
	     (new Main8).main(); --Palindrome checker... Further tests built-in (runtime) functions
	     (new Main10).main(); --Prints random numbers between -2000 and 2000... tests complex arithmetic expressions/dispatches
	     (new Tricky).main(); --My own example testing SELF_TYPE and dispatch
	     (new Main9).main(); --Prints out primes... Another extended algorithm that tests multiple things (aborts at the end of function so I put Main9 at the end)	     
	     
      }};
};