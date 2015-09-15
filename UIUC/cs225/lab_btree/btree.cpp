/**
 * @file btree.cpp
 * Implementation of a B-tree class which can be used as a generic dictionary
 * (insert-only). Designed to take advantage of caching to be faster than
 * standard balanced binary search trees.
 *
 * @author Matt Joras
 * @date Winter 2013
 */
#include <iostream>
using std::vector;

/**
 * Finds the value associated with a given key.
 * @param key The key to look up.
 * @return The value (if found), the default V if not.
 */
template <class K, class V>
V BTree<K, V>::find(const K& key) const
{
    return root == nullptr ? V() : find(root, key);
}

/**
 * Private recursive version of the find function.
 * @param subroot A reference of a pointer to the current BTreeNode.
 * @param key The key we are looking up.
 * @return The value (if found), the default V if not.
 */
template <class K, class V>
V BTree<K, V>::find(const BTreeNode* subroot, const K& key) const
{
//	std::cout << key << std::endl;
//	std::cout << *subroot << std::endl << std::endl << std::endl;
	int idx = insertion_idx(subroot->elements, key);
		
//	if(key == 3)
//		std::cout << *subroot << std::endl;

	if(subroot->elements[idx] == key)
	{	
		return subroot->elements[idx].value;
	}
	else
	{
		
		if(subroot->is_leaf)
			return V();
		else
		{
			return find(subroot->children[idx],key);
		}
	}	
}

/**
 * Inserts a key and value into the BTree. If the key is already in the
 * tree do nothing.
 * @param key The key to insert.
 * @param value The value to insert.
 */
template <class K, class V>
void BTree<K, V>::insert(const K& key, const V& value)
{
	//std::cout << "insert orig" << std::endl;
    /* Make the root node if the tree is empty. */
    if(root == nullptr)
    {
        root = new BTreeNode(true, order);
    }
    insert(root, DataPair(key, value));
    /* Increase height by one by tossing up one element from the old
     * root node. */
    if(root->elements.size() >= order)
    {
        BTreeNode* new_root = new BTreeNode(false, order);
        new_root->children.push_back(root);
        split_child(new_root, 0);

		//std::cout << *new_root << std::endl;
		//std::cout << *(new_root->children[0]) << std::endl;
		//std::cout << *(new_root->children[1]) << std::endl;
	
        root = new_root;
    }
//	std::cout << *root << std::endl;
}

/**
 * Splits a child node of a BTreeNode. Called if the child became too 
 * large.
 * @param parent The parent whose child we are trying to split.
 * @param child_idx The index of the child in its parent's children
 * vector.
 */


template <class K, class V>
void BTree<K, V>::split_child(BTreeNode* parent, size_t child_idx)
{
	vector<DataPair> childElems = parent->children[child_idx]->elements;
	vector<BTreeNode*> childChildren = parent->children[child_idx]->children;
	int idx = insertion_idx(parent->elements, childElems[childElems.size()/2].key); 
	parent->elements.insert(parent->elements.begin() + idx, childElems[childElems.size() / 2]);
	
	BTreeNode * left = new BTreeNode(parent->children[child_idx]->is_leaf, order);
	BTreeNode * right= new BTreeNode(parent->children[child_idx]->is_leaf, order); 
	left->elements.insert(left->elements.begin(), childElems.begin(), childElems.begin()+(childElems.size()-1)/2);
	right->elements.insert(right->elements.begin(), childElems.begin()+childElems.size()/2+1, childElems.begin() + childElems.size()); 

	
	if(!parent->children[child_idx]->is_leaf)
	{
		left->children.insert(left->children.begin(), childChildren.begin(), childChildren.begin() + (childChildren.size()+1)/2);
		right->children.insert(right->children.begin(), childChildren.begin() + (childChildren.size()+1)/2, childChildren.end());
	}

	delete parent->children[child_idx];
	parent->children[child_idx] = left;
	parent->children.insert(parent->children.begin() + child_idx+1, right);


/* TODO Your code goes here! */

    /* Assume we are splitting the 3 6 8 child.
     * We want the following to happen.
     *     | 2 | 
     *    /     \
     * | 1 |   | 3 | 6 | 8 |
     *
     *
     * Insert a pointer into parent's children which will point to the 
     * new right node. The new right node is empty at this point.
     *     | 2 |   | 
     *    /     \
     * | 1 |   | 3 | 6 | 8 |
     *
     * Insert the mid element from the child into its new position in the
     * parent's elements. At this point the median is still in the child.
     *     | 2 | 6 | 
     *    /     \
     * | 1 |   | 3 | 6 | 8 |
     *
     * Now we want to copy over the elements (and children) to the right
     * of the child median into the new right node, and make sure the left
     * node only has the elements (and children) to the left of the child 
     * median.
     *     | 2 | 6 | 
     *    /   /     \
     * | 1 | | 3 | | 8 |
     *
     */
}

/**
 * Private recursive version of the insert function.
 * @param subroot A reference of a pointer to the current BTreeNode.
 * @param pair The DataPair to be inserted.
 * Note: Original solution used std::lower_bound, but making the students
 * write an equivalent seemed more instructive.
 */
template <class K, class V>
void BTree<K, V>::insert(BTreeNode* subroot, const DataPair& pair)
{
    /* There are two cases to consider. 
     * If the subroot is a leaf node and the key doesn't exist subroot, we 
     * should simply insert the pair into subroot.
     * Otherwise (subroot is not a leaf and the key doesn't exist in subroot)
     * we need to figure out which child to insert into and call insert on it.
     * After this call returns we need to check if the child became too large
     * and thus needs to be split to maintain order. 
     */

    /* TODO Your code goes here! */
	int idx = insertion_idx(subroot->elements, pair.key);
    if(subroot->is_leaf && !(subroot->elements[idx] == pair))
	{
		subroot->elements.insert(subroot->elements.begin() + idx, pair);
		//std::cout << *subroot << std::endl;
	}
	else if(!subroot->is_leaf && !(subroot->elements[idx] == pair))
	{
		insert(subroot->children[idx], pair);
		if(subroot->children[idx]->elements.size() >= order)
			split_child(subroot,idx);	
	}
			
	
}

