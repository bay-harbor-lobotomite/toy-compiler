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

ArgExprList* gen_argexprlist(ArgExprList*l, Expr* arg){
    if(!l) l = new ArgExprList();
    l->args.push_back(arg);
    l->name = "args";
    l->add_children(1, arg);
    return l;
}

PrExpr* gen_prexpr_idfr(Idfr* i) {
    auto p = new PrExpr();
    p->name = "primary_expression";
    p->expr_type = IDENTIFIER_G;
    p->line = i->line;
    p->colno = i->colno;
    return p;
}
PrExpr* gen_prexpr_cnst(Cnst* c) {
    auto p = new PrExpr();
    p->name = "primary_expression";
    p->expr_type = CONSTANT_G;
    p->line = c->line;
    p->colno = c->colno;
    return p;
}
PrExpr* gen_prexpr_strlit(StrLit* s) {
    auto p = new PrExpr();
    p->name = "primary_expression";
    p->expr_type = STRING_LITERAL_G;
    p->line = s->line;
    p->colno = s->colno;
    return p;
}


PostfixExpr* gen_postfix_arr(Expr* e1, Expr* idx) {
    auto p = new PostfixExpr();
    p->e1 = dynamic_cast<PostfixExpr*>(e1);
    p->data.e2 = idx;
    p->name = "array_access";
    p->add_children(2, e1, idx);
    p->line = e1->line;
    p->colno = e1->colno;
    return p;
}
PostfixExpr* gen_postfix_voidfun(Expr* e1) {
    auto p = new PostfixExpr();
    p->e1 = dynamic_cast<PostfixExpr*>(e1);
    p->data.args = nullptr;
    p->name = "function_signature";
    p->add_children(1, e1);
    p->line = e1->line;
    p->colno = e1->colno;
    return p;
}
PostfixExpr* gen_postfix_fun(Expr* e1, ArgExprList* args) {
    auto p = new PostfixExpr();
    p->e1 = dynamic_cast<PostfixExpr*>(e1);
    p->data.args = args;
    p->name = "function_signature";
    p->add_children(2, e1, args);
    p->line = e1->line;
    p->colno = e1->colno;
    return p;
}
PostfixExpr* gen_postfix_struni(Expr* e1, Term* op, Idfr* acc) {
    auto p = new PostfixExpr();
    p->e1 = dynamic_cast<PostfixExpr*>(e1);
    p->data.op = op;
    p->name = op->name;
    p->add_children(3, e1, op, acc);
    p->line = e1->line;
    p->colno = e1->colno;
    return p;
}
PostfixExpr* gen_postfix_idop(Expr* e1, Term* op) {
    auto p = new PostfixExpr();
    p->e1 = dynamic_cast<PostfixExpr*>(e1);
    p->data.op = op;
    p->name = op->name;
    p->add_children(2, e1, op);
    p->line = e1->line;
    p->colno = e1->colno;
    return p;
}