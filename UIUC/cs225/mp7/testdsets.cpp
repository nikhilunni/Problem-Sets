/**
 * @file testdsets.cpp
 * Performs basic tests of DisjointSets.
 * @date April 2007
 * @author Jonathan Ray
 */

#include <iostream>
#include "dsets.h"

using std::cout;
using std::endl;

int main()
{
	DisjointSets disjSets;
    disjSets.addelements(7);

    disjSets.setunion(4, 1);
    disjSets.setunion(2, 3);
    disjSets.setunion(6, 5);
    disjSets.setunion(1, 3);

    cout << 0 << " " <<  disjSets.find(0) << endl;
	cout << 4 << " " << disjSets.find(1) << endl;
	cout << 4 << " " << disjSets.find(2) << endl;
	cout << 4 << " " << disjSets.find(3) << endl;
	cout << 4 << " " << disjSets.find(4) << endl;
	cout << 6 << " " << disjSets.find(5) << endl;
	cout << 6 << " " << disjSets.find(6) << endl;
/**
   DisjointSets s;
   
   s.addelements(50);
   s.setunion(2,3);
   s.setunion(3,5);
   s.setunion(5,7);
   s.setunion(7,2);
   s.setunion(4,6);

   cout << s.find(7) << endl;
   cout << s.find(5) << endl;
   cout << s.find(6) << endl;
   
   s.addelements(1);
   
   cout << s.find(50) << endl;
   
   s.setunion(50,3);
   
   cout << s.find(50) << endl;
   cout << "Disjoint Sets test complete"<< endl;
**/   
   return 0;
}

