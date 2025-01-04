/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"

//Write your code below this line

Parser::Parser(){
    symtable = new SymbolTable();
}
// PARSE MAIN NEGATIVE MAT BHULIO MC BCL
void Parser::parse(vector<string> code){
    int i=0;
    if(code[1]==":="){
        i=2;
        if(code[0]=="del"){
            ExprTreeNode *head= new ExprTreeNode();
            ExprTreeNode* le = new ExprTreeNode();
            ExprTreeNode* ri= new ExprTreeNode();
            le->type="DEL";
            ri->type="VAR";
            ri->id=code[2];
            head->right=ri;
            head->left=le;
            expr_trees.push_back(head);
            return;
        }
        if(code.size()==3){
            if(code[0]=="ret"){
                ExprTreeNode *head= new ExprTreeNode();
                ExprTreeNode* le = new ExprTreeNode();
                ExprTreeNode* ri= new ExprTreeNode();
                le->type="RET";
                bool digit= true;
                size_t m=0;
                if(code[2][0]=='-'){m=1;}
                for(;m<code[2].size();m++){
                    if(code[2][m]!='0'&&code[2][m]!='1'&&code[2][m]!='2'&&code[2][m]!='3'&&code[2][m]!='4'&&code[2][m]!='5'&&code[2][m]!='6'&&code[2][m]!='7'&&code[2][m]!='8'&&code[2][m]!='9'){
                        digit=false;
                    }
                }
                if(digit){
                    ri->type="VAL";
                    ri->num=stoi(code[2]);
                }
                else{
                    ri->type="VAR";
                    ri->id=code[2];
                }
                head->right=ri;
                head->left=le;
                expr_trees.push_back(head);
                return;
            }
            ExprTreeNode* head= new ExprTreeNode();
            ExprTreeNode* le = new ExprTreeNode();
            ExprTreeNode* ri= new ExprTreeNode();
            le->type= "VAR";
            le->id=code[0];
            bool digit= true;
            size_t m=0;
            if(code[i][0]=='-'){m=1;}
            for(;m<code[i].size();m++){
                if(code[i][m]!='0'&&code[i][m]!='1'&&code[i][m]!='2'&&code[i][m]!='3'&&code[i][m]!='4'&&code[i][m]!='5'&&code[i][m]!='6'&&code[i][m]!='7'&&code[i][m]!='8'&&code[i][m]!='9'){
                    digit=false;
                }
            }
            if(digit){
                ri->type="VAL";
                ri->num= stoi(code[i]);
            }
            else{
                ri->type="VAR";
                ri->id=code[i];
            }
            head->right=ri;
            head->left=le;
            expr_trees.push_back(head);
            return;
        }
    }
    i++;
    int j=i+1;
    ExprTreeNode* curr = new ExprTreeNode();
    if(code[i]=="("){
        vector<string>temp;
        int count=1;
        temp.push_back("(");
        while(count!=1 || code[j]!=")"){
            if(code[j]=="("){count++;}
            else if(code[j]==")"){count--;}
            temp.push_back(code[j]);
            j++;
        }
        j++;
        temp.push_back(")");
        parse(temp);
        curr->left=expr_trees.back();
        expr_trees.pop_back();
    }
    else{
        ExprTreeNode* le = new ExprTreeNode();
        bool digit= true;
        size_t m=0;
        if(code[i][0]=='-'){m=1;}
        for(;m<code[i].size();m++){
            if(code[i][m]!='0'&&code[i][m]!='1'&&code[i][m]!='2'&&code[i][m]!='3'&&code[i][m]!='4'&&code[i][m]!='5'&&code[i][m]!='6'&&code[i][m]!='7'&&code[i][m]!='8'&&code[i][m]!='9'){
                digit=false;
                break;
            }
        }
        if(digit){
            le->type="VAL";
            le->num= stoi(code[i]);
            curr->left=le;
        }
        else{
            le->type="VAR";
            le->id=code[i];
            curr->left=le;
        }
    }
    if(code[j]=="/"){curr->type="DIV";}
    else if(code[j]=="+"){curr->type="ADD";}
    else if(code[j]=="*"){curr->type="MUL";}
    else if(code[j]=="-"){curr->type="SUB";}
    i=j+1;
    if(code[i]=="("){
        j=i+1;
        vector<string>temp;
        int count=1;
        temp.push_back("(");
        while(count!=1 || code[j]!=")"){
            if(code[j]=="("){count++;}
            else if(code[j]==")"){count--;}
            temp.push_back(code[j]);
            j++;
        }
        j++;
        temp.push_back(")");
        parse(temp);
        curr->right=expr_trees.back();
        expr_trees.pop_back();
    }
    else{
        ExprTreeNode* ri = new ExprTreeNode();
        bool digit= true;
        size_t m=0;
        if(code[i][0]=='-'){m=1;}
        for(;m<code[i].size();m++){
            if(code[i][m]!='0'&&code[i][m]!='1'&&code[i][m]!='2'&&code[i][m]!='3'&&code[i][m]!='4'&&code[i][m]!='5'&&code[i][m]!='6'&&code[i][m]!='7'&&code[i][m]!='8'&&code[i][m]!='9'){
                digit=false;
            }
        }
        if(digit){
            ri->type="VAL";
            ri->num=stoi(code[i]);
            curr->right=ri;
        }
        else{
            ri->type="VAR";
            ri->id=code[i];
            curr->right=ri;
        }
    }
    expr_trees.push_back(curr); 
    if(code[1]==":="){
        ExprTreeNode* rn = new ExprTreeNode();
        rn->type="eq";
        rn->right=expr_trees.back();
        expr_trees.pop_back();
        ExprTreeNode* lev= new ExprTreeNode();
        lev->type="VAR";
        if(code[0]=="ret"){
            lev->type="RET";
        }
        else{
            lev->id=code[0];
        }
        rn->left= lev;
        expr_trees.push_back(rn);
        return;
    }
}

Parser::~Parser(){
    while(!expr_trees.empty()){
        ExprTreeNode* rn = expr_trees.back();
        expr_trees.pop_back();
        delete rn;
    }
    symtable->~SymbolTable();
}