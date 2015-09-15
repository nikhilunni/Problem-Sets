/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>
#include <algorithm>
#include <iostream>
#include "cartalk_puzzle.h"

using std::vector;
using std::ifstream;
using std::string;
/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of "StringTriples" (a typedef'd std::tuple, see top of 
 * cartalk_puzzle.h). Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector< StringTriple > cartalk_puzzle(PronounceDict d,
                                      const string& word_list_fname)
{
	vector<StringTriple> out;
	ifstream words(word_list_fname);
    string word;
    vector<string> collect;
    if(words.is_open())
    {
        while(getline(words, word))
        {
			if(word.size() > 1)
			{
				string sub1 = word.substr(1,word.size()-1);
				string sub2 = word.substr(0,1); sub2 += word.substr(2,word.size()-2);
				if(d.homophones(word, sub1) && d.homophones(sub1,sub2))
				{
					StringTriple success(word,sub1,sub2);
					out.push_back(success);
				}

			}
        }
    }
	return out;
}


