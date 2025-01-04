/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"
// #include <iostream>
// using namespace std;
//Write your code below this line

SymNode::SymNode(){
    this->key="";
    this->height=0;
    this->address=-1;
    this->par=NULL;
    this->left=NULL;
    this->right=NULL;
}

SymNode::SymNode(string k){
    this->key=k;
    this->height=0;
    this->address=-1;
    this->par=NULL;
    this->left=NULL;
    this->right=NULL;
}

SymNode* SymNode::LeftLeftRotation(){
    if(this->par!=NULL){
        if((this->par)->left==this){
            (this->par)->left=this->right;
        }
        else{
            (this->par)->right=this->right;
        }
    }
    SymNode* temp= (this->right)->left;
    (this->right)->left=this;
    (this->right)->par=this->par;
    this->par=this->right;
    this->right=temp;
    if(this->right!=NULL){
        (this->right)->par=this;
    }
    //a ki height manage karna
    int rh;
    if(this->right==NULL){rh=-1;}
    else{rh=this->right->height;}
    int lh;
    if(this->left==NULL){lh=-1;}
    else{lh=this->left->height;}
    this->height=1+max(lh,rh);
    //b ki height manage karna
    lh=this->height;
    if((this->par)->right==NULL){rh=-1;}
    else{rh=((this->par)->right)->height;}
    (this->par)->height=1+max(lh,rh);
    return this->par;//root kar rha hu
}

SymNode* SymNode::RightRightRotation(){
    if(this->par!=NULL){
        if((this->par)->left==this){
            (this->par)->left=this->left;
        }
        else{
            (this->par)->right=this->left;
        }
    }
    SymNode* temp= (this->left)->right;
    (this->left)->right=this;
    (this->left)->par=this->par;
    this->par=this->left;
    this->left=temp;
    if(this->left!=NULL){
        (this->left)->par=this;
    }
    // //
    // (this->left)->par=this->par;
    // this->par=this->left;
    // this->left=(this->par)->right;
    // (this->left)->par=this;
    //a ki height manage karna
    int rh;
    if(this->right==NULL){rh=-1;}
    else{rh=this->right->height;}
    int lh;
    if(this->left==NULL){lh=-1;}
    else{lh=this->left->height;}
    this->height=1+max(lh,rh);
    // b ki height manage karna
    rh=this->height;
    if((this->par)->left==NULL){lh=-1;}
    else{lh=((this->par)->left)->height;}
    (this->par)->height=1+max(lh,rh);
    return this->par;//root return
}

SymNode* SymNode::RightLeftRotation(){
    this->right=(this->right)->RightRightRotation();
	return this->LeftLeftRotation();
}

SymNode* SymNode::LeftRightRotation(){
    this->left=(this->left)->LeftLeftRotation();
	return this->RightRightRotation();
}

SymNode::~SymNode(){
    this->key="";
    this->height=-1;
    this->address=-1;
}