/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"
#include <map>
#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;
using std::map;
/** 
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */ 
AnagramDict::AnagramDict(const string& filename)
{
	ifstream words(filename);
	string word;
	vector<string> collect;
	if(words.is_open())
	{
		while(getline(words, word))
		{
			collect.push_back(word);	
		}
	}
	for(auto& i : collect)
	{
		vector<string> anags;
		for(auto & j : collect)
		{
			if(i.size() == j.size())
			{
				if(std::is_permutation(i.begin(), i.end(), j.begin()))
					anags.push_back(j);
			}
		}
		dict[i] = anags;
	}
}

/** 
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */ 
AnagramDict::AnagramDict(const vector< string >& words)
{
	for(auto& i : words)
	{
		vector<string> anags;
		for(auto & j : words)
		{
			if(i.size() == j.size())
			{
				if(std::is_permutation(i.begin(), i.end(), j.begin()))
					anags.push_back(j);
			}
		}
		dict[i] = anags;
	}
}

/**
 * @param word The word to find anagrams of. 
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the 
 * word list.
 */
vector< string > AnagramDict::get_anagrams(const string& word) const
{
	if(dict.count(word) <= 0 || dict.at(word).size() < 2)
	{
		vector<string> empty;
		return empty;
	}
    return dict.at(word);
}       

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector< vector< string > > AnagramDict::get_all_anagrams() const
{
	vector< vector<string> > out;
	for(std::map<string, vector<string>>::const_iterator it = dict.begin(); it != dict.end(); ++it)
		if((it->second).size() >= 2)
			out.push_back(it->second);
    return out; 
}


