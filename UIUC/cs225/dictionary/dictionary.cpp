#include "dictionary.h"
#include "inttypes.h"
template <class K, class V>
Dictionary<K, V>::Dictionary()
{
	numElems = 0;
	table = new triple *[1000000];
	for(int i = 0; i < 1000000; i++)
		table[i] = NULL;
	numTotal = 1000000;
}

template <class K, class V>
Dictionary<K,V>::Dictionary(const Dictionary & other)
{
	numElems = other.numElems;
	numTotal = other.numTotal;
	table = new triple *[numTotal];
	for(int i = 0; i < numTotal; i++)
	{
		if(other.table[i] == NULL)
			table[i] = NULL;
		else
			table[i] = new triple((other.table[i])->first, (other.table[i])->second, (other.table[i])->firstHash);	
	}
}

template<class K, class V>
Dictionary<K,V>::~Dictionary()
{
	for(int i = 0; i < numTotal; i++)
		delete table[i];
	delete[] table;
	table = NULL;
}

template <class K, class V>
void Dictionary<K, V>::insert(const K & key, const V & value)
{
	if(!keyExists(key))
	{
		insert_helper(0,key,value,table);
		numElems++;
		if((double)(numElems) / numTotal > 0.45) 
			resizeTable();
	}
}

template <class K, class V>
void Dictionary<K, V>::insert_helper(bool hashType, const K key, const V value, triple ** hashTable)
{
	int idx = hash(hashType,key);
	if(hashTable[idx] != NULL)
	{
		triple * displaced_sucker = hashTable[idx];
		insert_helper(!(displaced_sucker->firstHash),displaced_sucker->first,displaced_sucker->second, hashTable); //Insert the booted element with alternate hash function to its previous one
	}
	hashTable[idx] = new triple(key,value,hashType);
}

template <class K, class V>
void Dictionary<K,V>::resizeTable()
{
	triple ** newTable = new triple * [numElems * 2];
	numElems *= 2; //Hashing algorithm implicitly uses numElems, so we have to double it now.
	int i = 0;
	for(i = 0; i < numElems; i++)
		newTable[i] = NULL;
 
	for(i = 0; i < numElems/2; i++)
	{
		if(table[i] != NULL)
			insert_helper(0,table[i]->first,table[i]->second, newTable);		
	}
}

template <class K, class V>
void Dictionary<K, V>::remove(const K & key)
{
	int hash1 = hash(0,key);
	triple * loc1 = table[hash1];
	if(loc1 == NULL || loc1->first != key)
	{
		int hash2 = hash(1,key);
		triple * loc2 = table[hash2];
		if(loc2 != NULL && loc2->first == key)
		{
			delete table[hash2];
			table[hash2] = NULL;
			numElems--;
		}
	}
	else
	{
		delete table[hash1];
		table[hash1] = NULL;
		numElems--;
	}
}

template <class K, class V>
V Dictionary<K, V>::find(const K & key)
{
	triple * loc1 = table[hash(0,key)];
	if(loc1 == NULL || loc1->first != key)
	{
		triple * loc2 = table[hash(1,key)];
		if(loc2 != NULL && loc2->first == key)
			return loc2->second;
	}
	else
		return loc1->second;	
	return V(); //Copout!
}

template <class K, class V>
bool Dictionary<K, V>::keyExists(const K & key)
{
	triple * loc1 = table[hash(0,key)];
	if(loc1 == NULL || loc1->first != key)
	{
		triple * loc2 = table[hash(1,key)];
		if(loc2 != NULL && loc2->first == key)
			return true;
	}
	else
		return true;

	return false;
}

template <class K, class V>
bool Dictionary<K, V>::isEmpty() const
{
	return (numElems == 0);
}

template <class K, class V>
uint32_t Dictionary<K,V>::hash(int hashType, uint32_t key)
{
	return (hashType == 0 ? ThomasWangHash(key) % numTotal : BobJenkinsIntHash(key) % numTotal);
}

template <class K, class V>
uint32_t Dictionary<K,V>::hash(int hashType, string key)
{
	return (hashType == 0 ? BobJenkinsHash(key) % numTotal : KnuthHash(key) % numTotal);
}


template <class K, class V>
uint32_t Dictionary<K,V>::ThomasWangHash(uint32_t key) //http://burtleburtle.net/bob/hash/integer.html
{
	key += ~(key << 15);
	key ^= (key >> 10);
	key += (key << 3);
	key ^= (key >> 6);
	key += ~(key << 11);
	key ^= (key >> 16);	
	return key;
}

template <class K, class V>
uint32_t Dictionary<K,V>::BobJenkinsIntHash(uint32_t key) //https://gist.github.com/badboy/6267743
{
	key = (key+0x7ed55d16) + (key<<12);
	key = (key^0xc761c23c) ^ (key>>19);
	key = (key+0x165667b1) + (key<<5);
	key = (key+0xd3a2646c) ^ (key<<9);
	key = (key+0xfd7046c5) + (key<<3);
	key = (key^0xb55a4f09) ^ (key>>16);
   return key;
}

template <class K, class V>
uint32_t Dictionary<K,V>::BobJenkinsHash(string key) //http://en.wikipedia.org/wiki/Jenkins_hash_function 
{
	unsigned int out, i;
	for(out = i = 0; i < key.length(); i++)
	{
		out += key[i];
		out += (out << 10);
		out ^= (out >> 6);
	}
	out += (out << 3);
	out ^= (out >> 11);
	out += (out << 15);
	return out;
}

template <class K, class V>
uint64_t Dictionary<K,V>::KnuthHash(string key) //http://stackoverflow.com/questions/9545619/a-fast-hash-function-for-string-in-c-sharp
{
	uint64_t hashedVal = 3074457345618258791ul;
	for(int i = 0; i < key.length(); i++)
	{
		hashedVal += key[i];
		hashedVal *= 3074457345618258799ul;
	}
	return hashedVal;
}

