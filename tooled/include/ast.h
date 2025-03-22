#pragma once
#include <cstdarg>
#include <string>
#include <vector>
// Essentially modelling these as structs
// Class for AST node

class AstNode
{
public:
    long long id;
    unsigned int colno;
    unsigned int line;
    AstNode();
    AstNode(unsigned int line, unsigned int colno);

    void add_children(unsigned int count, ...);
};

class Term : public AstNode
{
public:
    std::string name;
    std::string val;
    // to string conversions done in constructor for ease of use and readability
    Term(const char *name, const char *val);
    Term(const char *name, const char *val, unsigned int line, unsigned int colno);
};

class NonTerm : public AstNode
{
public:
    std::string name;
    std::vector<AstNode *> children;

    NonTerm(const char *name);
    void add_children(unsigned int count, ...);
};

// some basics
class Idfr : public Term
{
};

union cnst_val
{
    unsigned long ul;
    int i;
    unsigned int ui;
    long l;
    float f;
    double d;
    char c;
    unsigned char uc;
};
class Cnst : public Term
{
public:
    // todo: semantic check - CHANGE CONSTRUCTOR
    Cnst(const char *name, const char *val, unsigned int line, unsigned int colno) : Term(name, val, line, colno) {};
    union cnst_val val;
};

class StrLit : public Term
{
public:
    StrLit(const char *name, const char *val) : Term(name, val) {};
};

enum PrExprType
{
    EXPRESSION_G,
    IDENTIFIER_G,
    CONSTANT_G,
    STRING_LITERAL_G
};

// expressions and their corresponding grammar helpers
class Expr : public NonTerm
{
public:
    Expr() : NonTerm("") {};
    virtual ~Expr() {};
};

class ArgExprList: public Expr {
    public:
    std::vector<Expr*> args;
    ArgExprList(){}
};

ArgExprList* gen_argexprlist(ArgExprList*l, Expr* arg);

class PrExpr : public Expr
{
public:
    PrExprType expr_type;
    union expr_val
    {
        Idfr *identifier = nullptr;
        Cnst *constant;
        StrLit *string_lit;
        Expr *expr;
    } val;
    PrExpr() : expr_type(EXPRESSION_G) {}
};

PrExpr* gen_prexpr_idfr(Idfr* i);
PrExpr* gen_prexpr_cnst(Cnst* c);
PrExpr* gen_prexpr_strlit(StrLit* s);


union postfix_data {
    Expr* e2;
    Term* op;
    Idfr* id;
    ArgExprList* args;
};
class PostfixExpr: public Expr {
    public:
    PostfixExpr* e1;
    //only for member access
    union postfix_data data;
    PostfixExpr() : e1(nullptr) {
        data.id = nullptr;
    }
};

PostfixExpr* gen_postfix_arr(Expr* e1, Expr* idx);
PostfixExpr* gen_postfix_voidfun(Expr* e1);
PostfixExpr* gen_postfix_fun(Expr* e1, ArgExprList* args);
PostfixExpr* gen_postfix_struni(Expr* e1, AstNode* op, Idfr* acc);
PostfixExpr* gen_postfix_idop(Expr* e1, AstNode* op);

class UnaryExpr : public Expr
{
public:
    Expr *oprnd;
    Term *op;
    UnaryExpr() : oprnd(nullptr), op(nullptr) {}
};

UnaryExpr *build_unary_expr();

class AddExpr : public Expr
{
};

class MultExpr : public Expr
{
};
class AndExpr : public Expr
{
};
class OrExpr : public Expr
{
};
class XorExpr : public Expr
{
};
class LogAndExpr : public Expr
{
};
class LogOrExpr : public Expr
{
};
class RelExpr : public Expr
{
};
class EqExpr : public Expr
{
};
class ShiftExpr : public Expr
{
};
class CondExpr : public Expr
{
};
class AssignExpr : public Expr
{
};
