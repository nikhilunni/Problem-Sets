#include "tree.h"

int main() {
  vector <TreeNode*> nodeList;
  TreeNode* A = new TreeNode(NULL);
  
  TreeNode* B = new TreeNode(A);
  TreeNode* C = new TreeNode(A);
  TreeNode* D = new TreeNode(C);

  TreeNode* E = new TreeNode(C);
  TreeNode* F = new TreeNode(C);

  TreeNode* G = new TreeNode(C);

  TreeNode* H = new TreeNode(G);
  TreeNode* I = new TreeNode(H);
  TreeNode* J = new TreeNode(H);
  TreeNode* K = new TreeNode(I);
  
  nodeList.push_back(A);
  nodeList.push_back(B);
  nodeList.push_back(C);
  nodeList.push_back(D);
  nodeList.push_back(E);
  nodeList.push_back(F);
  nodeList.push_back(G);
  nodeList.push_back(H);
  nodeList.push_back(I);
  nodeList.push_back(J);
  nodeList.push_back(K);

  vector <string> trace;
  trace.push_back("C0");
  trace.push_back("MZ");
  trace.push_back("P");
  trace.push_back("C1");
  trace.push_back("C0");
  trace.push_back("MY");
  trace.push_back("P");
  trace.push_back("C1");
  trace.push_back("P");
  trace.push_back("MX");
  trace.push_back("C3");
  trace.push_back("MR");
  trace.push_back("C0");
  trace.push_back("C1");
  trace.push_back("MQ");
  trace.push_back("P");
  trace.push_back("C0");
  trace.push_back("MT");
  trace.push_back("C0");
  trace.push_back("P");
  trace.push_back("ML");
  
  
  TreeNode* final = process_trace(A, trace);
  cout<<"Final position (label): " << final->getLabel()<<endl;
  
  for(unsigned i = 0; i < nodeList.size(); i++)
    cout<<nodeList[i]->getLabel()<<" details: accesses "<<nodeList[i]->numberAccesses()<<" value "<<nodeList[i]->getValue()<<" modifications: "<<nodeList[i]->numberModifications()<<endl;
}

/************
Expected answer:

Final position (label): I
A details: accesses 2 value A modifications: 0
B details: accesses 2 value Z modifications: 1
C details: accesses 4 value X modifications: 1
D details: accesses 2 value Y modifications: 1
E details: accesses 1 value E modifications: 0
F details: accesses 0 value F modifications: 0
G details: accesses 2 value R modifications: 1
H details: accesses 2 value H modifications: 0
I details: accesses 4 value L modifications: 2
J details: accesses 2 value Q modifications: 1
K details: accesses 1 value K modifications: 0
************/
