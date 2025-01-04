/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "heapnode.h"

//Write your code below this line

HeapNode::HeapNode(){
    this->par= NULL;
    this->left= NULL;
    this->right= NULL;
    this->val=0;
}

HeapNode::HeapNode(int _val){
    this->par= NULL;
    this->left= NULL;
    this->right= NULL;
    this->val=_val;
}

HeapNode::~HeapNode(){
    this->par= NULL;
    this->left= NULL;
    this->right= NULL;
    this->val=0;
}