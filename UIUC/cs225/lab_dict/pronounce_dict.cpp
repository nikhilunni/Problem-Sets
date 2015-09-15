/**
 * @file pronounce_dict.cpp
 * Implementation of the PronounceDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "pronounce_dict.h"

#include <iterator>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstring>
#include <algorithm>

using std::string;
using std::map;
using std::vector;
using std::ifstream;
using std::istream;
using std::istream_iterator;
using std::stringstream;

/** 
 * Constructs a PronounceDict from a CMU pronunciation dictionary
 * file. See http://www.speech.cs.cmu.edu/cgi-bin/cmudict .
 * @param pronun_dict_filename Filename of the CMU pronunciation
 * dictionary.
 */
PronounceDict::PronounceDict(const string& pronun_dict_filename)
{
    ifstream pronun_dict_file(pronun_dict_filename);
    string line;
    if(pronun_dict_file.is_open())
    {
        while(getline(pronun_dict_file, line))
        {
            /* Used to break the line by whitespace. The CMU Dict does this for
             * separating words from their pronunciations. */
            stringstream line_ss(line);
            istream_iterator< string > line_begin(line_ss);
            istream_iterator< string > line_end;
            if(line[0] != '#' && *line_begin != ";;;")
            {   
                /* Associate the word with the rest of the line
                 * (its pronunciation). */
                dict[*line_begin] = vector< string > (std::next(line_begin, 1), 
                                                      line_end);
            }
        }
    }
    /* If it's not open then... well... just don't do anything for the sake
     * of simplicity. */
}

/** 
 * Constructs a PronounceDict from a CMU std::map mapping the word
 * to a vector of strings which represent the pronunciation.
 * @param pronun_dict_filename Filename of the CMU pronunciation
 * dictionary.
 * @param pronun_dict Maps a string word to a vector of strings
 * representing its pronunciation.
 */
PronounceDict::PronounceDict(const map< string, vector< string > >& 
                             pronun_dict) : dict(pronun_dict)
{
    /* Nothing to see here. */  
}

/** 
 * Uses the dictionary to determine if the two words are homophones.
 * @param word1 First word to be tested.
 * @param word2 Second word to be tested.
 * @return true if the two words are homophones, false otherwise (or
 * one or both words weren't in the dictionary).
 * Note: The word keys in the dictionary are stored in uppercase.
 */
bool PronounceDict::homophones(const string& word1, const string& word2) const
{
	string copy1 = word1;
	string copy2 = word2;
	std::transform(copy1.begin(), copy1.end(), copy1.begin(), toupper);
	std::transform(copy2.begin(), copy2.end(), copy2.begin(), toupper);
	if(dict.count(copy1) > 0 && dict.count(copy2) > 0) 
	{
		vector<string> vec1 = dict.at(copy1);
		vector<string> vec2 = dict.at(copy2);
		return (std::equal(vec1.begin(), vec1.end(), vec2.begin())); 
	}
	return false;
}