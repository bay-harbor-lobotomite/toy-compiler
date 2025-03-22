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

UnaryExpr *gen_unary_expr(Term* op, Expr *e) {
    auto u = new UnaryExpr();
    u->e = dynamic_cast<UnaryExpr*>(e);
    u->op = op;
    u->name = op->name;
    u->line = e->line;
    u->colno = e->colno;
    u->add_children(2, op, e);
    return u;
}
// UnaryExpr *gen_unary_cast(Term *op, Expr* ce) {
//     auto u = new UnaryExpr();
//     u->e = dynamic_cast<CastExpr*>(ce);
//     u->op = op;
//     u->name = op->name;
//     u->line = ce->line;
//     u->colno = ce->colno;
//     u->add_children(2, op, ce);
//     return u;
// }

BinaryExpr* gen_binary_expr(Expr*e1, Term* op, Expr* e2, const char* opname) {
    auto e = new BinaryExpr();
    e->e1 = dynamic_cast<BinaryExpr*>(e1);
    e->e2 = dynamic_cast<BinaryExpr*>(e2);
    e->op = op;
    //call semantic pass here for specific binary expression
    e->name = std::string(opname);
    e->line = e1->line;
    e->colno = e1->colno;
    e->add_children(3, e1, e2, op);
    return e;
}

CondExpr* gen_cond_expr(Expr* e1, Expr* e2, Expr* e3, const char *op) {
    auto c = new CondExpr();
    c->e1 = dynamic_cast<BinaryExpr*>(e1);
    c->e2 = e2;
    c->e3 = dynamic_cast<CondExpr*>(e3);
    auto opname = std::string(op);
    auto op_n = new Term(op, op);
    c->name = "conditional_expression";
    c->line = e1->line;
    c->colno = e1->colno;
    c->add_children(4, e1, e2, e3, op);
    return c;
}

AssignExpr* gen_assign_expr(Expr*e1, Term*op, Expr*e2) {
    auto e = new AssignExpr();
    e->e1 = e1;
    e->e2 = e2;
    e->op = op;
    e->name = op->name;
    e->add_children(3, e1, op, e2);
    e->line = e1->line;
    e->colno = e1->colno;
    return e;
}

TopLevelExpr* gen_toplevel_expr(Expr* e1, Expr * e2) {
    auto e = new TopLevelExpr();
    e->e1 = dynamic_cast<TopLevelExpr*>(e1);
    e->e2 = dynamic_cast<AssignExpr*>(e2);
    e->name = "top_level_expression";
    e->line = e1->line;
    e->colno = e1->colno;
    e->add_children(2, e1, e2);
    return e;
}