/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K & key) const
{
	return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node * subtree, const K & key) const
{
	if (subtree == NULL)
		return V();
	else if (key == subtree->key)
		return subtree->value;
	else
	{
		if (key < subtree->key)
			return find(subtree->left, key);
		else
			return find(subtree->right, key);
	}
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node * & t)
{
	*_out << __func__ << endl; // Outputs the rotation name (don't remove this)
	Node * temp = t->right;
	t->right = temp->left;
	temp->left = t;
	t->height = getHeight(t)+1;
	temp->height = getHeight(temp) + 1;
	t = temp;
}

template <class K, class V>
int AVLTree<K, V>::getHeight(Node * t)
{
	return 	(	(t->left == NULL ? -1 : t->left->height) >=
				(t->right == NULL ? -1 : t->right->height) ?
				(t->left == NULL ? -1 : t->left->height) :
				(t->right == NULL ? -1 : t->right->height));
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node * & t)
{
	*_out << __func__ << endl; // Outputs the rotation name (don't remove this)
	// Implemented for you:
	rotateLeft(t->left);
	rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node * & t)
{
	*_out << __func__ << endl; // Outputs the rotation name (don't remove this)
	Node * temp = t->left;
	t->left = temp->right;
	temp->right = t;
	t->height = getHeight(t)+1;
	temp->height = getHeight(temp)+1;
	t = temp;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node * & t)
{
	*_out << __func__ << endl; // Outputs the rotation name (don't remove this)
	rotateRight(t->right);
	rotateLeft(t);	
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
	insert(root, key, value);
}

template <class K, class V>
int AVLTree<K,V>::height(Node * subroot)
{
	return (subroot == NULL ? -1 : subroot->height);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node* & subroot, const K & key, const V & value)
{
    if(subroot == NULL)
	{
		subroot = new Node(key, value);
		subroot->height = 0;
		subroot->left = NULL; subroot->right = NULL;
	}
	else if(key < subroot->key)
	{
		insert(subroot->left, key, value);
		if(height(subroot->left) - height(subroot->right) == 2)
		{
			if(key < subroot->left->key)
				rotateRight(subroot);
			else
				rotateLeftRight(subroot);
		}
	}
	else if(key > subroot->key)
	{
		insert(subroot->right,key,value);
		if(height(subroot->left) - height(subroot->right) == -2)
		{
			if(key > subroot->right->key)
				rotateLeft(subroot);
			else
				rotateRightLeft(subroot);
		}
	}
	else;
	subroot->height = getHeight(subroot) + 1;	
}
