// Virtues of a programmer (from Programming Perl, Wall, Schwartz and
// Christiansen)
// 
// Laziness - The quality that makes you go to great effort to reduce
// overall energy expenditure. It makes you write labor-saving programs
// that other people will find useful, and document what you wrote so you
// don't have to answer so many questions about it. 


// This function generates a circuit (albeit a slow one) to compute whether
// a bus is all zeros.

// make example_generator
// ./example_generator

#include <cstdio>
using std::printf;

int
main() {
	for(int i = 2; i < 32; i++) {
		printf("alu1 a%d(out[%d],carryout[%d],A[%d],B[%d],carryout[%d],control);\n",
				i,i,i,i,i,i-1);
	}
	/** ????
    int width = 8;
  
    printf("    input [%d:0] in;\n", width - 1);
    printf("    wire  [%d:1] chain;\n\n", width - 1);
  
    printf("    or o1(chain[1], in[1], in[0]);\n");
    for (int i = 2 ; i < width ; i ++) {
        printf("    or o%d(chain[%d], in[%d], chain[%d]);\n", i, i, i, i-1);
    }
    printf("    not n0(zero, chain[%d]);\n", width - 1);
    **/
    return 0;
}
