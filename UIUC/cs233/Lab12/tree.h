#ifndef TREE_H
#define TREE_H

#include <cassert>
#include <iostream>
#include <fstream>
#include <map>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

class TreeNode {
  unsigned accesses, modifications;
  char currentValue;

  vector <TreeNode*> children;
  TreeNode* parent;

  static char counter;
  
  char label;

  void addChild(TreeNode* child) {
    children.push_back(child);
  }

public:
  TreeNode(TreeNode* parent) {
    accesses = 0; modifications = 0;
    currentValue = (counter++)%26 + 'A';
    label = currentValue;

    this->parent = parent;
    if(parent != NULL)
      parent->addChild(this);
  }

  void access() { ++accesses; }
  void modify() { ++modifications; }
  
  void change(char new_val) {
    currentValue = new_val;
  }

  TreeNode* getParent() {
    return parent;
  }

  TreeNode* getChild(int i) {
    return children[i];
  }

  unsigned numberAccesses() { 
    return accesses;
  }

  unsigned numberModifications() { 
    return modifications;
  }

  char getValue() {
    return currentValue;
  }

  char getLabel() {
    return label;
  }
};

TreeNode* process_trace(TreeNode* root, vector <string> trace);

#endif
