## Virtues of a programmer (from Programming Perl, Wall, Schwartz and
## Christiansen)
## 
## Laziness - The quality that makes you go to great effort to reduce
## overall energy expenditure. It makes you write labor-saving programs
## that other people will find useful, and document what you wrote so you
## don't have to answer so many questions about it. 
## 
## 
## This function generates a circuit (albeit a slow one) to compute whether
## a bus is all zeros.
## 
## python example_generator.py

from __future__ import print_function



## ????
#width = 8

#print("    input [{0}:0] in;".format(width - 1))
#print("    wire  [{0}:1] chain;".format(width - 1))
#print("")
#print("    or o1(chain[1], in[1], in[0]);")
#for i in range(2, width):
#    print("    or o{0}(chain[{0}], in[{0}], chain[{1}]);".format(i, i - 1))

#print("    not n0(zero, chain[{0}]);".format(width - 1))
