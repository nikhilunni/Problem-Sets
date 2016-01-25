
(*
 *  execute "coolc bad.cl" to see the error messages that the coolc parser
 *  generates
 *
 *  execute "./myparser bad.cl" to see the error messages that your parser
 *  generates
 *)

(* no error *)
class A {
};

class Recover_features {
    test : Int;
    (* error : no comma between b:String and c:Int *)
    broken_feature(a : Integer , b : String c : Int) : Int {
        4
    };
    correct_feature : Int;
};

class Recover_let {
    method() : Object {
        let test : String <- "Hello",
	    broken_var : Int <= 4,
	    correct_var : Int <- 12+6
	in {
	    out_string(test);
        }
    };
};


(* error:  b is not a type identifier *)
Class b inherits A {
};

(* error:  a is not a type identifier *)
Class C inherits a {
};

(* error:  keyword inherits is misspelled *)
Class D inherts A {
};

(* error:  closing brace is missing *)
Class E inherits A {
;

