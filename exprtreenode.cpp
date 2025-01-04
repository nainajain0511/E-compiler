/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

//Write your code below this line

ExprTreeNode::ExprTreeNode(){
    this->type="";
    this->id="";
    this->num=0;
    this->left=NULL;
    this->right=NULL;
}

ExprTreeNode::ExprTreeNode(string t,int v){
    this->type="VAR";
    this->id=t;
    this->num=v;
}

ExprTreeNode::~ExprTreeNode(){
    this->type="";
    this->id="";
    this->num=0;
    this->left=NULL;
    this->right=NULL;
}

