/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const {
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild( size_t currentIdx ) const {
    return currentIdx*2;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild( size_t currentIdx ) const {
    /// @todo Update to return the index of the right child.
    return currentIdx*2+1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent( size_t currentIdx ) const {
    /// @todo Update to return the index of the parent.
    return currentIdx/2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild( size_t currentIdx ) const {
    /// @todo Update to return whether the given node has a child
    return ((currentIdx)*2 < _elems.size());
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild( size_t currentIdx ) const {
	size_t left = leftChild(currentIdx), right = rightChild(currentIdx);
    return (right < _elems.size() ? 
				(higherPriority(_elems[left],_elems[right]) ? left : right) :
				left);
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown( size_t currentIdx) {
	if(currentIdx*2 < _elems.size())
	{
		size_t child = maxPriorityChild(currentIdx);
		if(higherPriority(_elems[child],_elems[currentIdx]))
		{
			std::swap(_elems[currentIdx],_elems[child]);
			heapifyDown(child);
		}
	}
}

template <class T, class Compare>
void swap(T& a, T& b) 
{
	T temp = a;
	a = b;
	b = temp;	
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp( size_t currentIdx ) {
    if( currentIdx == root() )
        return;
    size_t parentIdx = parent( currentIdx );
    if( higherPriority( _elems[ currentIdx ], _elems[ parentIdx ] ) ) {
        std::swap( _elems[ currentIdx ], _elems[ parentIdx ] );
        heapifyUp( parentIdx );
    }
}

template <class T, class Compare>
heap<T, Compare>::heap() {
 	_elems.push_back(T());
}

template <class T, class Compare>
heap<T, Compare>::heap( const std::vector<T> & elems ) {
	_elems.push_back(T());
	typename std::vector<T>::const_iterator iter;
	for(iter = elems.begin(); iter!= elems.end(); ++iter)
	//	push(*iter);
		_elems.push_back(*iter);
	for(size_t i = _elems.size()/2; i > 0; i--)
		heapifyDown(i);
}

template <class T, class Compare>
T heap<T, Compare>::pop() {
	T out = _elems[root()];
	std::swap(_elems[root()],_elems[_elems.size()-1]);
	_elems.pop_back();
	heapifyDown(root());
	return out;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const {
    return _elems[root()];
}

template <class T, class Compare>
void heap<T, Compare>::push( const T & elem ) {
	_elems.push_back(elem);
	heapifyUp(_elems.size()-1);
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const {
    return (_elems.size() == root());
}
