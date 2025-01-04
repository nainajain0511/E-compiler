/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "minheap.h"
// using namespace std;
// #include <iostream>
//Write your code below this line
MinHeap::MinHeap(){
    this->root=NULL;
    this->size=0;
}

void MinHeap::push_heap(int num){
    HeapNode *node= new HeapNode(num);
    HeapNode *insert_at;
    if(size==0){
        this->root=node;
        size++;
        return;
    }
    int i=0;
    int res=1;
    for (i = 0; i < 8 * sizeof(unsigned int); i++) {
        int curr = 1 << i;
        if (curr > size){
            break;
        }
        res=curr;
    }
    int temp_size=size;
    int height=i;
    if(2*res==size+1){
        insert_at=this->root;
        while(insert_at->left!=NULL){
            insert_at=insert_at->left;
        }
    }
    else{
        insert_at=root;
        for(int m=1;m<height-1;m++){
            if(temp_size==res-1){
                while(insert_at->left!=NULL){
                    insert_at=insert_at->left;
                }  
                break;
            }
            if(temp_size-(res-1)<(res/2)){
                insert_at=insert_at->left;
                temp_size=temp_size-((res/2));
                res=res/2;
            }
            else{
                insert_at=insert_at->right;
                temp_size=temp_size-(res);
                res=res/2;
            }
        }
    }
    if(insert_at->left==NULL){
        insert_at->left=node;
        node->par=insert_at;
    }
    else{
        insert_at->right=node;
        node->par=insert_at;
    }
    HeapNode* temp=node;
    while(temp->par!=NULL){
        if((temp->par)->val>temp->val){
            int swap= (temp->par)->val;
            (temp->par)->val=temp->val;
            (temp->val)=swap;
        }
        else{
            break;
        }
        temp=temp->par;
    }
    size++;
}

int MinHeap::get_min(){
    return root->val;
}

void MinHeap::pop(){
    HeapNode *delete_at;
    if(size==1){
        this->root=NULL;
        size--;
        return;
    }
    int i=0;
    int res=1;
    for (i = 0; i < 8 * sizeof(unsigned int); i++) {
        int curr = 1 << i;
        if (curr > size){
            break;
        }
        res=curr;
    }
    int temp_size=size;
    int height=i;
    if(2*res==size+1){
        delete_at=this->root;
        while(delete_at->right!=NULL){
            delete_at=delete_at->right;
        }
        delete_at=delete_at->par;
    }
    else{
        delete_at=root;
        for(int m=1;m<height-1;m++){
            if(temp_size==res-1){
                while(delete_at->left!=NULL){
                    delete_at=delete_at->left;
                }  
                delete_at= delete_at->par;
                break;
            }
            if(temp_size-(res-1)<=(res/2)){
                delete_at=delete_at->left;
                temp_size=temp_size-((res/2));
                res=res/2;
            }
            else{
                delete_at=delete_at->right;
                temp_size=temp_size-(res);
                res=res/2;
            }
        }
    }
    if(delete_at->right==NULL){
        this->root->val=(delete_at->left)->val;
        delete_at->left=NULL;
    }
    else{
        this->root->val=(delete_at->right)->val;
        delete_at->right=NULL;
    }
    HeapNode* temp=root;
    while(temp->left!=NULL && temp->right!=NULL){
        if(temp->val<temp->left->val&&temp->val<temp->right->val){
            break;
        }
        else{
            if(temp->left->val<temp->val && temp->left->val<temp->right->val){
                int swap= temp->left->val;
                temp->left->val=temp->val;
                temp->val=swap;
                temp=temp->left;
            }
            else{
                int swap= temp->right->val;
                temp->right->val=temp->val;
                temp->val=swap;
                temp=temp->right;
            }
        }
    }
    if(temp->left!=NULL){
        if(temp->left->val<temp->val){
                int swap= temp->left->val;
                temp->left->val=temp->val;
                temp->val=swap;
                temp=temp->left;
            }
    }
    size--;
}

void destruct(HeapNode *node){
    if(node==NULL) {return;}
    destruct(node->left);
    destruct(node->right);
    delete node;
}
MinHeap::~MinHeap(){
    size=0;
    destruct(root);
}
// int main(){
//     MinHeap* table= new MinHeap();
//     for(int i=1;i<=100;i++){
//         table->push_heap(i);
//     }
//     cout<<"done"<<endl;
// }
