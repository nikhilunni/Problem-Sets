(*
 *  CS164 Spring 2004
 *
 *  Programming Assignment 1
 *    Implementation of a simple stack machine.
 *
 *  Skeleton file
 *)


class StackCommand inherits IO {
  name: String;
  name() : String {name};
  show() : Object {out_string(name)};
  init(n : String) : SELF_TYPE {{
    name <- n;
    self;
  }};
  eval_stack(stack : Stack) : Object { out_string("") };
  push_command(stack : Stack) : Object { eval_stack(stack) };
};

class PlusCommand inherits StackCommand {
   (*
    * From atoi.cl
    *)
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
      { abort(); 0; }
      fi fi fi fi fi fi fi fi fi fi
  };
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

  i2a_aux(i : Int) : String {
      if i = 0 then "" else
          (let next : Int <- i / 10 in
              i2a_aux(next).concat(i2c(i - next * 10))
          )
      fi
  };
  eval_stack(stack : Stack) : Object {
    let 
        firstInt : Int <- a2i_aux(stack.tail().head().name()),
        secondInt : Int <- a2i_aux(stack.tail().tail().head().name())
    in {
--        stack.pop();
--        stack.pop();
--        stack.pop();
        stack.push(new StackCommand.init(i2a_aux(firstInt+secondInt)));
    }
  };
};

class SCommand inherits StackCommand {

  eval_stack(stack : Stack) : Object {
     let first : StackCommand,
         second : StackCommand
      in {
          stack.pop();
          first <- stack.pop();
          second <- stack.pop();
          stack.push(first);
          stack.push(second);
      }
  };
};

(*
 * Stack/Cons lifted from example data structures in http://nathanfriend.io/cooltojs/
 *)
class Stack {
   car : StackCommand;
   cdr : Stack;
   head()  : StackCommand { car };
   tail()  : Stack { cdr };
   pop()   : StackCommand {
     let a : StackCommand <- head()
     in {
         car <- tail().head();
         cdr <- tail().tail();
         a;
       }
   };    
   push(i : StackCommand)  : Stack {{
       if isvoid head() then {
           car <- i;
       } else {
           if isvoid tail() then {
               cdr <- new Stack.init(car); 
               car <- i;
           } else {
               cdr <- tail().push(head());
               car <- i;
           } fi;
       } fi;
       self;
   }};
   init(i : StackCommand) : Stack {{
	   car <- i;
       self;
   }};
   init2(i : StackCommand, e : Stack) : Stack {{
       car <- i;
       cdr <- e;
   }};
};

class Main inherits IO {
  prompt() : String {{
          out_string(">");
          in_string();
  }};    
  print_stack(l : Stack) : Object {
     if isvoid l then out_string("")
     else {
       out_string(l.head().name());
       out_string("\n");
       print_stack(l.tail());
     }
     fi
  };
  main() : Object {
     let input : String,
         s : Stack <- new Stack
     in {
         while (((input <- prompt()) = "x") = false) loop
         {
             if input = "+" then s.push(new PlusCommand.init(input)) else 
             if input = "s" then s.push(new SCommand.init(input)) else
             if input = "d" then print_stack(s) else
             if input = "e" then s.head().eval_stack(s) else
             s.push(new StackCommand.init(input))
             fi fi fi fi;
--             out_string(input.concat("\n"));
         }
         pool;
     }
  };

};