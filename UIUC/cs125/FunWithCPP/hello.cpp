//UIUC CS125 FALL 2013 MP. File: hello.cpp, CS125 Project: FunWithCPP, Version: 2013-11-19T00:05:13-0600.115261430
#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

int main()
{
   for(int i = 1; i <= 16; i++) {
	for(int j = 1; j <= 16; j++) {
		cout << i*j;
		cout << " ";
	}
	cout << endl;
   } 
   return 0;
}
