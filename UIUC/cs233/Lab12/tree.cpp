#include "tree.h"

char TreeNode::counter = 0;
using namespace std;

TreeNode* process_trace(TreeNode* root, vector <string> trace) {
  root->access();
  for(vector<string>::iterator it = trace.begin(); it != trace.end(); ++it) {
    char instr = (*it)[0];
    switch(instr) {
    case 'P':
      root = root->getParent();
      root->access();
      break;
    case 'C':
      root = root->getChild((*it)[1] - '0');
      root->access();
      break;
    case 'M':
      root->change( (*it)[1] );
      root->access();
      root->modify();
    }
  }
  return root;
}
