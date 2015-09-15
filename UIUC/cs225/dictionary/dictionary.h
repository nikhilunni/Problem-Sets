/**
 * @file dictionary.h
 */

#ifndef _DICTIONARY_H_
#define _DICTIONARY_H_

#include <string>
#include "inttypes.h"
#include <utility>
#include <vector>

using namespace std;
/**
 * Implements the dictionary ADT.
 *
 * The implementation is up to you, but you must complete all the given
 *  public functions. You will need to add some member variables and private
 *  helper functions.
 */
template <class K, class V>
class Dictionary
{
    public:
        /**
         * Constructor: creates an empty dictionary.
         */
        Dictionary();
		Dictionary(const Dictionary & other);
        /**
         * Inserts the given key, value pair into the dictionary.
         * If the key already exists, do nothing.
         *
         * @param key The key to be inserted.
         * @param value The value to be inserted.
         */
        void insert(const K & key, const V & value);

        /**
         * Removes the given key (and its associated data) from the
         *  dictionary.
         *
         * @param key The key to be removed.
         */
        void remove(const K & key);

        /**
         * Finds the value associated with a given key.
         *
         * @param key The key whose data we want to find.
         * @return The value associated with this key, or the default value
         *  (V()) if it was not found.
         */
        V find(const K & key);

        /**
         * Determines if the given key exists in the dictionary.
         *
         * @param key The key we want to find.
         * @return A boolean value indicating whether the key was found.
         */
        bool keyExists(const K & key);

        /**
         * Determines if the dictionary is empty. Should be O(1).
         *
         * @return A boolean value indicating whether the dictionary is
         *  empty.
         */
        bool isEmpty() const;
		uint32_t hash(int hashType, uint32_t key);
		uint32_t hash(int hashType, string key);
		~Dictionary();
		struct triple
		{
			K first;
			V second;
			bool firstHash;
			triple(K f, V s) : first(f), second(s) {} 
			triple(K f, V s, bool h) : first(f), second(s), firstHash(h) {}
		};

    private:
		uint32_t ThomasWangHash(uint32_t key);
		uint32_t BobJenkinsHash(string key);
		uint32_t BobJenkinsIntHash(uint32_t key);
		uint64_t KnuthHash(string key); 
		void resizeTable();
		void insert_helper(bool hashType, const K key, const V value, triple ** hashTable);
		triple ** table;
		bool * filled;
		int numElems;
		int numTotal;
		};

#include "dictionary.cpp"
#endif
