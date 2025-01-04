// /* Do NOT add/remove any includes statements from this header file */
// /* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"
// #include <iostream>
// using namespace std;
//Write your code below this line
int getheight(SymNode *temp){
    if(temp==NULL){
        return -1;
    }
    else{
        return temp->height;
    }
}
SymbolTable::SymbolTable(){
    this->size=0;
    this->root=NULL;
}
//NULL KA NULL KARNA HAIN
void SymbolTable::insert(string k){
    if(this->size==0){
        SymNode *temp=new SymNode(k);
        size++;
        this->root=temp;
        return;
    }
    SymNode* find;
    find=this->root;
    while(true){
        if(find->right==NULL&&find->left==NULL){
            break;
        }
        else if(find->key<k && find->right!=NULL){
            find=find->right;
        }
        else if(find->key>k && find->left!=NULL){
            find=find->left;
        }
        else{
            break;
        }
    }
    SymNode *temp=new SymNode(k);
    if(find->key<k){
        find->right=temp;
        temp->par=find;
    }
    else{
        find->left=temp;
        temp->par=find;
    }
    int lh=getheight(find->left);
    int rh=getheight(find->right);
    find->height=1+max(lh,rh);
    int hdiff=rh-lh;
    while(find!=NULL){
        lh=getheight(find->left);
        rh=getheight(find->right);
        find->height=1+max(lh,rh);
        hdiff=rh-lh;
        if(!(hdiff>=-1 && hdiff<=1)){
            break;
        }
        find=find->par;
    }
    if(find==NULL){
        size++;
        return;
    }

    SymNode *parent= find->par;
    SymNode* demn;
    bool bool_left=false;
    if(parent!=NULL && parent->left==find){bool_left=true;}
    if(hdiff<-1){
        int ldiff=getheight((find->left)->right)-getheight((find->left)->left);
        if(ldiff<0){
            demn= find->RightRightRotation();
        }
        else{
            demn= find->LeftRightRotation();
        }
    }
    else{
        int rdiff=getheight((find->right)->right)-getheight((find->right)->left);
        if(rdiff>0){
            demn= find->LeftLeftRotation();
        }
        else{
            demn= find->RightLeftRotation();
        }
    }
    if(parent==NULL){
        this->root=demn;
        size++;
        return;
    }
    else{
        demn->par=parent;
        if(bool_left){
            parent->left=demn;
        }
        else{
            parent->right=demn;
        }
    }
    while(demn!=NULL){
        lh=getheight(demn->left);
        rh=getheight(demn->right);
        demn->height=1+max(lh,rh);
        demn=demn->par;
    }
    size++;
}
SymNode* bstdeletion(SymNode* root){
    SymNode* current = root;
    SymNode* parent = root->par;
    if(current->left==NULL&& current->right==NULL){
        if((current->par)->left==current){
            (current->par)->left=NULL;
            delete current;
        }
        else{
            (current->par)->right=NULL;
            delete current;
        }
        return parent;
    }
    else if (current->left == NULL || current->right == NULL) {
        SymNode* current2;
        if (current->left == NULL){
            current2 = current->right;
        }
        else{
            current2 = current->left;
        }
        if (current == parent->left){
            parent->left = current2;
            current2->par=parent;
        }
        else{
            parent->right = current2;
            current2->par=parent;
        }
        return parent;
    }
    else{
        SymNode* parent2 = NULL;
        SymNode* temp=current->right;
        while (temp->left != NULL){
            parent2 = temp;
            temp = temp->left;
        }
        if (parent2 != NULL){
            parent2->left = temp->right;
            if((temp->right)!=NULL){
                (temp->right)->par=parent2;
            }
            current->key = temp->key;
            current->address=temp->address;
            return parent2;
        }
        else{
            current->right = temp->right;
            if(temp->right!=NULL){
                (temp->right)->par=current;
            }
            current->key = temp->key;
            current->address=temp->address;
            return current;
        }
    }
}
void SymbolTable::remove(string k){
    if(this->size==1){
        delete root;
        this->root=NULL;
        size--;
        return;
    }
    SymNode* find;
    find= this->root;
    bool found=true;
    while(true){
        if(k==find->key){
            break;
        }
        else if(find->left==NULL && find->right==NULL){
            found=false;
            break;
        }
        else if(k<find->key && find->left!=NULL){
            find=find->left;
        }
        else if(k>find->key && find->right!=NULL){
            find=find->right;
        }
        else{
            found=false;
            break;
        }
    }
    if(!found){
        return;
    }
    if(find==root && (root->left==NULL || root->right==NULL)){
        SymNode* demn2;
        if(root->left==NULL){
            demn2=root->right;
        }
        else{
            demn2=root->left;
        }
        demn2->par=NULL;
        this->root=demn2;
        size--;
        return;
    }
    SymNode* height_check= bstdeletion(find);
    if(height_check==NULL){

    }
    else{
        while(height_check->par!=NULL){
            bool bool_left=false;
            if(height_check->par->left==height_check){bool_left=true;}
            int lh=getheight(height_check->left);
            int rh=getheight(height_check->right);
            height_check->height=1+max(lh,rh);
            int hdiff=rh-lh;
            if(hdiff<-1){
                int ldiff=getheight((height_check->left)->right)-getheight((height_check->left)->left);
                if(ldiff<=0){
                    if(bool_left){height_check->par->left=height_check->RightRightRotation();}
                    else{height_check->par->right=height_check->RightRightRotation();}
                }
                else{
                    if(bool_left){height_check->par->left=height_check->LeftRightRotation();}
                    else{height_check->par->right=height_check->LeftRightRotation();}
                }
            }
            else if(hdiff>1){
                int rdiff=getheight((height_check->right)->right)-getheight((height_check->right)->left);
                if(rdiff>=0){
                    if(bool_left){height_check->par->left=height_check->LeftLeftRotation();}
                    else{height_check->par->right=height_check->LeftLeftRotation();}
                }
                else{
                    if(bool_left){height_check->par->left=height_check->RightLeftRotation();}
                    else{height_check->par->right=height_check->RightLeftRotation();}
                }
            }
            height_check=height_check->par;
        }
        int lh=getheight(height_check->left);
        int rh=getheight(height_check->right);
        height_check->height=1+max(lh,rh);
        int hdiff=rh-lh;
        if(hdiff<-1){
            int ldiff=getheight((height_check->left)->right)-getheight((height_check->left)->left);
            if(ldiff<=0){
                this->root=height_check->RightRightRotation();
                root->par=NULL;
            }
            else{
                this->root=height_check->LeftRightRotation();
                root->par=NULL;
            }
        }
        else if(hdiff>1){
            int rdiff=getheight((height_check->right)->right)-getheight((height_check->right)->left);
            if(rdiff>=0){
                this->root=height_check->LeftLeftRotation();
                root->par=NULL;
            }
            else{
                this->root=height_check->RightLeftRotation();
                root->par=NULL;
            }
        }
    }
    size--;
}

int SymbolTable::search(string k){
    if(this->size==0){
        return -2;
    }
    SymNode* find;
    find= this->root;
    bool found=true;
    while(true){
        if(k==find->key){
            break;
        }
        else if(find->left==NULL && find->right==NULL){
            found=false;
            break;
        }
        else if(k<find->key && find->left!=NULL){
            find=find->left;
        }
        else if(k>find->key && find->right!=NULL){
            find=find->right;
        }
        else{
            found=false;
            break;
        }
    }
    if(!found){
        return -2;
    }
    else{
        return find->address;
    }
}

void SymbolTable::assign_address(string k,int idx){
    SymNode* find;
    find= this->root;
    bool found=true;
    while(true){
        if(k==find->key){
            break;
        }
        else if(find->left==NULL && find->right==NULL){
            found=false;
            break;
        }
        else if(k<find->key && find->left!=NULL){
            find=find->left;
        }
        else if(k>find->key && find->right!=NULL){
            find=find->right;
        }
        else{
            found=false;
            break;
        }
    }
    find->address=idx;
}

int SymbolTable::get_size(){
    return size;
}

SymNode* SymbolTable::get_root(){
    return root;
}
void destruct(SymNode* node){
    if(node==NULL){ return;}
    destruct(node->left);
    destruct(node->right);
    delete node;
}
SymbolTable::~SymbolTable(){
    size=0;
    destruct(root);
}



// int main(){
//     SymbolTable* table = new SymbolTable();
//     SymNode* root = table->get_root();
//     table->insert("71");
//     root = table->get_root();
//     printTree(root,NULL,false);
//     cout<<"~~~~~~~~~~~~~~~~~~~~"<<endl;
//     table->insert("79");
//     root = table->get_root();
//     printTree(root,NULL,false);
//     cout<<"~~~~~~~~~~~~~~~~~~~~"<<endl;
//     table->insert("53");
//     root = table->get_root();
//     printTree(root,NULL,false);
//     cout<<"~~~~~~~~~~~~~~~~~~~~"<<endl;
//     table->insert("99");
//     root = table->get_root();
//     printTree(root,NULL,false);
//     cout<<"~~~~~~~~~~~~~~~~~~~~"<<endl;
//     table->insert("37");
//     root = table->get_root();
//     printTree(root,NULL,false);
//     cout<<"~~~~~~~~~~~~~~~~~~~~"<<endl;
//     table->insert("73");
//     root = table->get_root();
//     printTree(root,NULL,false);
//     cout<<"~~~~~~~~~~~~~~~~~~~~"<<endl;
//     table->insert("11");
//     root = table->get_root();
//     printTree(root,NULL,false);
//     cout<<"~~~~~~~~~~~~~~~~~~~~"<<endl;
//     table->insert("48");
//     root = table->get_root();
//     printTree(root,NULL,false);
//     cout<<"~~~~~~~~~~~~~~~~~~~~"<<endl;
//     table->remove("89");
//     root = table->get_root();
//     printTree(root,NULL,false);
//     cout<<"~~~~~~~~~~~~~~~~~~~~"<<endl;
// }