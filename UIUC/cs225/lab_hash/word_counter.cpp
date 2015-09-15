/**
 * @file word_counter.cpp
 * Implementation of the WordFreq class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Spring 2012
 */

using std::vector;
using std::pair;
using std::string;
using std::ifstream;
using std::istringstream;
using std::cout;
using std::endl;

template <template <class K, class V> class HT>
WordFreq<HT>::WordFreq( const string & infile ) : filename( infile ) { /* nothing */ }

template <template <class K, class V> class HT>
vector< pair<string, int> > WordFreq<HT>::getWords( int threshold ) const {
	TextFile infile( filename );
	vector< pair<string, int> > ret;
	HT<string,int> hash(2048);
	while(infile.good())
	{
		string next = infile.getNextWord();
		if(!hash.keyExists(next))
			hash.insert(next, 1);
		else
			hash[next]++;
	}
	typename HT<string,int>::iterator it;
	for(it = hash.begin(); it != hash.end(); ++it)
	{
		if(it->second >= threshold)
		{
			pair<string,int> p(it->first,it->second);
			ret.push_back(p);
		}
	}
	return ret;
}
