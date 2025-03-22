#include "../include/ast.h"

static long long global_id = 0;

long long increment_id() {
    return global_id++;
}

AstNode::AstNode(unsigned int line, unsigned int colno) : id(increment_id()), line(line), colno(colno) {};
AstNode::AstNode(): id(increment_id()) {};

Term::Term(const char* name, const char* val) : name(std::string(name)) {
    if(val) this->val = std::string(val); 
}
Term::Term(const char* name, const char* val, unsigned int line, unsigned int colno) : name(std::string(name)), AstNode(line, colno)  {
    if(val) this->val = std::string(val); 
}

NonTerm::NonTerm(const char* name) : name(std::string(name)) {};

//never call! but cant make pure virtual either because Term can never call either :(
void AstNode::add_children(unsigned int count, ...) {
    //do nothing, throw error
}

void NonTerm::add_children(unsigned int count, ...) {
    va_list list; 
    va_start(list, count); 
    for (unsigned int i = 0; i < count; i++) { 
        children.push_back(va_arg(list, AstNode*));
    } 
    va_end(list); 
}