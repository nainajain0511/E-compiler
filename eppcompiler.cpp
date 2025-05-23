/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"
// #include <iostream>
// using namespace std;
//Write your code below this line

EPPCompiler::EPPCompiler(){
    Parser* temp = new Parser();
    targ= *temp;
    memory_size= 0;
    output_file= "demn";
    MinHeap* temp_heap = new MinHeap();
    least_mem_loc=*temp_heap;
}
// NEGATIVE NUMBERS MC

EPPCompiler::EPPCompiler(string out_file,int mem_limit){
    Parser* temp = new Parser();
    targ= *temp;
    memory_size= mem_limit;
    output_file= out_file;
    MinHeap* temp_heap = new MinHeap();
    least_mem_loc=*temp_heap;
    for(size_t i=0;i<mem_limit;i++){
        least_mem_loc.push_heap(i);
    }
}

void EPPCompiler::compile(vector<vector<string>> code){
    if(this->memory_size==0){
        this->memory_size=code.size();
        for(size_t i=0;i<memory_size;i++){
            least_mem_loc.push_heap(i);
        }
    }   
    for(size_t i=0;i<code.size();i++){
        this->targ.parse(code[i]);
        vector<string> temp= this->generate_targ_commands();
        write_to_file(temp);
    }
}

void demn(ExprTreeNode *node,vector<string> &tar,Parser *targ){
    if(node==NULL){
        return;
    }
    demn(node->right,tar,targ);
    demn(node->left,tar,targ);
    if(node->type=="VAL"){
        tar.push_back("PUSH "+to_string(node->num));
    }
    else if(node->type=="VAR"){
        int mem= (targ->symtable)->search(node->id);
        tar.push_back("PUSH mem["+to_string(mem)+"]");
    }
    else{
        tar.push_back(node->type);
    }
}

vector<string> EPPCompiler::generate_targ_commands(){
    ExprTreeNode* root=(targ.expr_trees).back();
    vector<string> ans;
    if(root->left->type=="DEL"){
        int mem=(targ.symtable)->search(root->right->id);
        ans.push_back("DEL = mem["+to_string(mem)+"]");
        targ.symtable->remove(root->right->id);
        least_mem_loc.push_heap(mem);
        return ans;
    }
    if(root->left->type=="RET"){
        demn(root->right,ans,&targ);
        ans.push_back("RET = POP");
        return ans;
    }
    else if(root->left->type=="VAR"){
        int mem=(targ.symtable)->search(root->left->id);
        if(mem==-2){
            mem=least_mem_loc.get_min();
            least_mem_loc.pop();
            targ.symtable->insert(root->left->id);
            targ.symtable->assign_address(root->left->id,mem);
        }
        demn(root->right,ans,&targ);
        ans.push_back("mem["+to_string(mem)+"] = POP");
        return ans;
    }
    return ans;
}

void EPPCompiler::write_to_file(vector<string> commands){
    fstream output;
	output.open(output_file, ios::out| ios::app);
	for (int i=0; i<commands.size(); i++){
		output << commands[i] << endl;
	}
	output.close();
}

EPPCompiler::~EPPCompiler(){
    targ.~Parser();
    memory_size=0;
    output_file="";
    MinHeap* heap = &least_mem_loc;
    heap->~MinHeap();
}

// int main(){
//     EPPCompiler* Compiler = new EPPCompiler("demn",2);
//     vector<vector<string>> ques;
//     vector<string> q1{"X1",":=","(","3","+","4",")"};
//     vector<string> q2{"X2", ":=", "(", "5", "*", "(", "2", "+", "X1", ")", ")"};
//     vector<string> q3{"ret",":=","(","X1","+","X2",")"};
//     ques.push_back(q1);
//     ques.push_back(q2);
//     ques.push_back(q3);
//     Compiler->compile(ques);
// }
// int main(){
//     EPPCompiler* Compiler = new EPPCompiler("demn4",100);
//     vector<vector<string>> ques;
//     // vector<string> q1{"x",":=","(","3","+","(","5","*","2",")",")"};
//     // vector<string> q2{"y", ":=","(","1","+","2",")"};
//     // vector<string> q3{"z",":=","(","x","*","y",")"};
//     // vector<string> q4{"w",":=","(","(","z","*","z",")","-","1000",")"};
//     // vector<string> q5{"del", ":=","z"};
//     // vector<string> q6{"ret", ":=","(","w","+","7",")"};
//     vector<string> q1{"x",":=","3"};
//     vector<string> q2{"y", ":=","5"};
//     vector<string> q3{"z",":=","7"};
//     vector<string> q4{"del",":=","x"};
//     vector<string> q5{"del", ":=","y"};
//     vector<string> q6{"w", ":=","(","5","+","(","z","/","2",")",")"};
//     vector<string> q7{"ret", ":=","w"};
//     ques.push_back(q1);
//     ques.push_back(q2);
//     ques.push_back(q3);
//     ques.push_back(q4);
//     ques.push_back(q5);
//     ques.push_back(q6);
//     ques.push_back(q7);
//     Compiler->compile(ques);
// }
