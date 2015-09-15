/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Spring 2012, Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 */
#include<iostream>
using namespace std;
/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List()
{
	clear();
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear()
{
	ListNode * pntr = head;
	while(pntr != NULL)
	{
		ListNode * next = pntr->next;
		delete pntr;
		pntr = next;
	}	
	length = 0;
	head = NULL;
	tail = NULL;
}


/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const & ndata)
{
	ListNode * newHead = new ListNode(ndata);
	if(head != NULL)
	{
		head->prev = newHead;
		newHead->next = head;
		newHead->prev = NULL;
		head = newHead;
	}
	else
	{
		head = newHead;
		head->prev = NULL;
		head->next = NULL;
		tail = newHead;
	}
	length++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack( const T & ndata )
{
	ListNode * newTail = new ListNode(ndata);
	if(tail == NULL) 
	{
		newTail->prev = NULL;
		newTail->next = NULL;
		tail = newTail;
		head = newTail;
	}
	else
	{
		tail->next = newTail;
		newTail->prev = tail;
		tail = newTail;
	}
	length++;
}


/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse()
{
    reverse(head, tail);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse( ListNode * & startPoint, ListNode * & endPoint )
{
	if(startPoint != endPoint)
	{
		ListNode * oneBefore = startPoint->prev;
		ListNode * oneAfter = endPoint->next;
		ListNode * pntr = endPoint;
		ListNode * temp = NULL;
		while(pntr != startPoint)
		{
			temp = pntr->next;
			pntr->next = pntr->prev;
			pntr->prev = temp;
			pntr = pntr->next;
		}
		startPoint->prev = startPoint->next;
		if(oneBefore != NULL)
		{
			oneBefore->next = endPoint;
		}
		endPoint->prev = oneBefore;
		startPoint->next = oneAfter;
		if(oneAfter != NULL)
		{
			oneAfter->prev = startPoint;
		}
		temp = startPoint;
		startPoint = endPoint;
		endPoint = temp;

	}
}

template <class T>
void List<T>::printReverse()
{
	ListNode * iter = tail;
	cout << "<" << iter->data << " ";
	while(iter != head) 
	{
		iter = iter->prev;
		cout << iter->data << " ";
	}
	cout << ">" << endl;

}




/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth( int n )
{
	if(length > 0)
	{
			ListNode * p1;
			ListNode * p2 = head;
			for(int i = 1; i < n; i++)
				p2 = p2->next;
			reverse(head,p2);
			p1 = p2->next;
			p2 = p1;
			while(p1 != NULL)
			{
				for(int i = 1; i < n; i++)
				{
					if(p2 == tail) 
					{
						reverse(p1,tail);
						return;
					}	
					p2 = p2->next;
				}
				if(p2 == tail) 
				{
					reverse(p1, tail);
					p1 = NULL;
				}
				else 
				{
					reverse(p1,p2);
					p1 = p2->next;
				}	
				p2 = p1;
			}
	}

}


/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall()
{
	if(length > 0)
	{
			ListNode* curr = head;
			int i = 0;
			while(curr->next != tail)
			{
				if(i%2 == 1)
				{
					ListNode* before = curr->prev;
					ListNode* after = curr->next;
					tail->next = curr;
					curr->prev = tail;
					tail = curr;
					before->next = after;
					after->prev = before;
					curr = after;
				}
				else
				{
					curr = curr->next;
				}
				i++;
			}
			curr->prev->next = curr->next;
			curr->next->prev = curr->prev;
			curr->next->next = curr;
			curr->prev =curr->next;
			curr->next = NULL;
			tail = curr;

	}
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint)
{
    if (splitPoint > length)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head, splitPoint);

    int oldLength = length;
    if (secondHead == head)
    {
        // current list is going to be empty
        head = NULL;
        tail = NULL;
        length = 0;
    }
    else
    {
        // set up current list
        tail = head;
        while (tail->next != NULL)
            tail = tail->next;
        length = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head = secondHead;
    ret.tail = secondHead;
    if (ret.tail != NULL)
    {
        while (ret.tail->next != NULL)
            ret.tail = ret.tail->next;
    }
    ret.length = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint)
{
	ListNode * curr = start;
	for(int i = 0; i < splitPoint; i++)
		curr = curr->next;
	ListNode * secondHead = curr;
	curr->prev->next = NULL;
	curr->prev = NULL;
	return secondHead;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T> & otherList)
{
    // set up the current list
    head = merge(head, otherList.head);
    tail = head;

    // make sure there is a node in the new list
    if(tail != NULL)
    {
        while (tail->next != NULL)
            tail = tail->next;
    }
    length = length + otherList.length;

    // empty out the parameter list
    otherList.head = NULL;
    otherList.tail = NULL;
    otherList.length = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode * second)
{
	ListNode * p1 = first;
	ListNode * p2 = second;
	ListNode * curr;
	if(p1->data < p2->data)
	{
		curr = p1;
		p1 = p1->next;
	}
	else
	{
		curr = p2;
		p2 = p2->next;
	}
	while(p1 != NULL && p2 != NULL)
	{
		if(p1->data < p2->data)
		{
			curr->next = p1;
			p1->prev = curr;
			curr = p1;
			p1 = p1->next;
		}			
		else
		{
			curr->next = p2;
			p2->prev = curr;
			curr = p2;
			p2 = p2->next;
		}
	}
	if(p1 == NULL && p2 != NULL)
	{
		curr->next = p2;
		p2->prev = curr;
	}
	if(p2 == NULL && p1 != NULL)
	{
		curr->next = p1;
		p1->prev = curr;
	}
	return (first->data < second->data ? first : second);
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort()
{
    if (empty())
        return;
    head = mergesort(head, length);
    tail = head;
    while (tail->next != NULL)
        tail = tail->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode * List<T>::mergesort(ListNode * start, int chainLength)
{
	if(chainLength > 1)
	{
		ListNode * firstHalf = start;
		ListNode * secondHalf = split(start, chainLength / 2);
		firstHalf = mergesort(firstHalf, chainLength/2);
		secondHalf = mergesort(secondHalf, (chainLength+1)/2);
		firstHalf = merge(firstHalf, secondHalf);	
		return firstHalf;
	}
	else
		return start;
}

