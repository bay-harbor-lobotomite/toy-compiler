#include "../include/ast.h"

static long long global_id = 0;

long long increment_id() {
    return global_id++;
}

AstNode::AstNode(size_t line, size_t colno) : id(increment_id()), line(line), colno(colno) {};
AstNode::AstNode(): id(increment_id()) {};

Term::Term(const char* name, const char* val) : name(std::string(name)) {
    if(val) this->val = std::string(val); 
}
Term::Term(const char* name, const char* val, size_t line, size_t colno) : name(std::string(name)), AstNode(line, colno)  {
    if(val) this->val = std::string(val); 
}

NonTerm::NonTerm(const char* name) : name(std::string(name)) {};

//never call! but cant make pure virtual either because Term can never call either :(
void AstNode::add_children(size_t count, ...) {
    //do nothing, throw error
}

void NonTerm::add_children(size_t count, ...) {
    va_list list; 
    va_start(list, count); 
    for (size_t i = 0; i < count; i++) { 
        children.push_back(va_arg(list, AstNode*));
    } 
    va_end(list); 
}