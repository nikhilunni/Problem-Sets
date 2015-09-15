module blackbox(b, s, l, g);
    output b;
    input  s, l, g;
    wire   w07, w09, w16, w25, w26, w27, w32, w44, w45, w48, w59, w60, w70, w72, w77, w80, w87, w90, w91, w96;

    and a57(b, w80, w70);
    or  o99(w80, w45, w16);
    not n74(w16, w45);
    or  o1(w70, w07, w96);
    and a65(w96, w77, w32);
    not n20(w77, w32);
    or  o55(w32, w25, w90);
    and a89(w25, s, w59);
    not n36(w59, g);
    and a19(w90, l, w48, g);
    not n92(w48, s);
    and a30(w45, l, w91);
    or  o76(w91, w72, w87);
    not n12(w72, s);
    and a68(w87, g, s);
    or  o3(w07, w27, w60);
    and a84(w27, g, w09);
    not n42(w09, s);
    and a46(w60, s, w26, w44);
    not n71(w26, l);
    not n2(w44, g);

endmodule // blackbox
