module steering(left, right, walk, s);
    output 	left, right, walk;
    input [4:0] 	s;
	wire	n0,n1,n2,n3,n4,l0,l1,l2,l3,l4,l5,l6,l7,l8,l9,l10,nLeft,nWalk, w1,w2,w3,w4;
	not not4(n4,s[4]);
	not not3(n3,s[3]);
	not not2(n2,s[2]);
	not not1(n1,s[1]);
	not not0(n0,s[0]);

	and left1(l1,n4,n3,n2,n1,n0);
	and left2(l2,n4,s[3],n2,n1,n0);
	and left3(l3,n4,s[3],s[2],n1,n0);
	and left4(l4,s[4],n3,n2,n1,n0);
	and left5(l5,s[4],n3,s[2],n1,n0);
	and left6(l6,s[4],s[3],n2,n1,n0);
	and left7(l7,s[4],s[3],n2,n1,s[0]);
	and left8(l8,s[4],s[3],n2,s[1],n0);
	and left9(l9,s[4],s[3],s[2],n1,n0);
	and left10(l10,s[4],s[3],s[2],n1,s[0]);
	and left11(l11,s[4],s[3],s[2],s[1],n0);

	or o1(nLeft,l1,l2,l3,l4,l5,l6,l7,l8,l9,l10,l11);
	or o2(right,l2,l3,l4,l5,l6,l7,l8,l9,l10,l11);
	not not1(left, nLeft);	

	and walk1(w1,n4,s[3],s[2],s[1],n0);
	and walk2(w2,n4,s[3],s[2],s[1],s[0]);
	and walk3(w3,s[4],s[3],s[2],s[1],n0);
	and walk4(w4,s[4],s[3],s[2],s[1],s[0]);

	or o3(nWalk,w1,w2,w3,w4);
	not not2(walk, nWalk); 

endmodule // steering
