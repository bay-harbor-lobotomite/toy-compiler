#include <ast.h>
#include <sstream>

static long long global_id = 0;

long long increment_id() {
    return global_id++;
}

extern void file_writer(std::string);

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

//hehe stolen
void Term::to_dot() {
	if(is_printed){
		is_printed = 0;
		std::stringstream ss;
		ss << "\t" << id << " [label=\"" << name << " : " << val << "\"];\n";
		file_writer(ss.str());
	}
}

void NonTerm::to_dot() {
	if(is_printed){
		is_printed = 0;
		std::stringstream ss;
		ss << "\t" << id << " [label=\"" << name << "\"];\n";
		for (auto it = children.begin(); it != children.end(); it++) {
			ss << "\t" << id << " -> " << (*it)->id << ";\n";
		}
		file_writer(ss.str());

		for(auto it = children.begin(); it != children.end(); it++){
			(*it)->to_dot();
		}
	}
}

Idfr* gen_idfr(const char* val) {
	auto i = new Idfr();
	i->val = val;
	return i;
}
Cnst* gen_cnst(const char* name, const char* val) {
	return new Cnst(name, val);
}
