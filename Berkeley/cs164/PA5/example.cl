(*  Example cool program testing as many aspects of the code generator
    as possible.
 *)
class Main inherits IO {
      main(): Int {(if (not (true)) then 12 else 10 fi )};
};

(*
class Main inherits IO {
  main():Object {{  out_int({ while 4 < 3 loop out_int(4) pool;
                   4 + 3 + 4*42 +
                   if (4 + 3 < 10/2) then 7 else 14 fi /
		   2; });

		   if ({out_int(72); 4/2 < 1;}) then abort() else out_int(73) fi;
		   out_int( (~62 + 2) / 7);
		   while true loop abort() pool;
		   out_int(~2);
                }};
};

*)
