#include <iostream>
#include <string>
#include "dictionary.h"
#include <stdlib.h>
#include <map>

using namespace std;

string generator(int length)
{
	srand(time(NULL));
	string s(length, '0');
	for(int i = 0; i < length; i++)
		s[i] = 'a'+(rand()%26);
	return s;
		
}

int main(int argc, char* argv[])
{
   /** Dictionary<string, int> dict;
	map<string, int> actual;

	for(int i = 1; i < 1000; i++)
	{
		string s = generator(i);
		actual[s] = i;
		dict.insert(s,i);
	}
	//Test Insert
	for(map<string,int>::iterator it = actual.begin(); it != actual.end(); ++it)
	{
		if(actual[it->first] != dict.find(it->first))
		{
			cout << "Your result: " << dict.find(it->first) << ", but should be: " << actual[it->first] << endl;
		}
	}
**/

	Dictionary<string, int> dict;
    cout << "Empty? " << dict.isEmpty() << endl;
	dict.insert("hello", 42);
    cout << "Empty? " << dict.isEmpty() << endl;
    cout << "keyExists(\"hello\"): " << dict.keyExists("hello") << endl;
    cout << "find(\"hello\"): " << dict.find("hello") << endl;

    dict.remove("hello");
    cout << "Empty? " << dict.isEmpty() << endl;
    cout << "find(\"hello\"): " << dict.find("hello") << endl;
    return 0;
}
