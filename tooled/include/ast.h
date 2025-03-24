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
    //for dot generation
    bool is_printed = true;
    AstNode();
    AstNode(unsigned int line, unsigned int colno);

    void add_children(unsigned int count, ...);
    virtual void to_dot() = 0;
};

class Term : public AstNode
{
public:
    std::string name;
    std::string val;
    // to string conversions done in constructor for ease of use and readability
    Term(const char *name, const char *val);
    Term(const char *name, const char *val, unsigned int line, unsigned int colno);
    void to_dot() override;
};

class NonTerm : public AstNode
{
public:
    std::string name;
    std::vector<AstNode *> children;

    NonTerm(const char *name);
    void add_children(unsigned int count, ...);
    void to_dot() override;
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

class ArgExprList : public Expr
{
public:
    std::vector<Expr *> args;
    ArgExprList() {}
};

ArgExprList *gen_argexprlist(ArgExprList *l, Expr *arg);

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

PrExpr *gen_prexpr_idfr(Idfr *i);
PrExpr *gen_prexpr_cnst(Cnst *c);
PrExpr *gen_prexpr_strlit(StrLit *s);

union postfix_data
{
    Expr *e2;
    Term *op;
    Idfr *id;
    ArgExprList *args;
};
class PostfixExpr : public Expr
{
public:
    PostfixExpr *e1;
    // only for member access
    union postfix_data data;
    PostfixExpr() : e1(nullptr)
    {
        data.id = nullptr;
    }
};

PostfixExpr *gen_postfix_arr(Expr *e1, Expr *idx);
PostfixExpr *gen_postfix_voidfun(Expr *e1);
PostfixExpr *gen_postfix_fun(Expr *e1, ArgExprList *args);
PostfixExpr *gen_postfix_struni(Expr *e1, Term *op, Idfr *acc);
PostfixExpr *gen_postfix_idop(Expr *e1, Term *op);

class UnaryExpr : public Expr
{
public:
    Expr *e;
    Term *op;
    UnaryExpr() : e(nullptr), op(nullptr) {}
};

UnaryExpr *gen_unary_expr(Term *op, Expr *e);
// implement when type done
// UnaryExpr *gen_unary_cast(Term *op, Expr* ce);

class CastExpr : public Expr
{
};

// implement when type done
// CastExpr* gen_cast_expr(NonTerm* tn ,Expr* ce);

// could potentially model all these as multiple Exprs, one for each grammar rule, but trying to keep it as non redundant as possible
class BinaryExpr : public Expr
{
public:
    Expr *e1;
    Expr *e2;
    Term *op;
    BinaryExpr() : e1(nullptr), e2(nullptr), op(nullptr) {}
};

BinaryExpr *gen_binary_expr(Expr *e1, Term *op, Expr *e2, const char *opname);

// un-redundant any one of them if needed
// class MultExpr : public Expr
// {
// };
// class AddExpr : public Expr
// {
// };
// class AndExpr : public Expr
// {
// };
// class OrExpr : public Expr
// {
// };
// class XorExpr : public Expr
// {
// };
// class LogAndExpr : public Expr
// {
// };
// class LogOrExpr : public Expr
// {
// };
// class RelExpr : public Expr
// {
// };
// class EqExpr : public Expr
// {
// };
// class ShiftExpr : public Expr
// {
// };

class CondExpr : public Expr
{
public:
    Expr *e1;
    Expr *e2;
    Expr *e3;
    // implicitly the op here is ?:, let's store it as a terminal
    Term *op;
    CondExpr() : e1(nullptr), e2(nullptr), e3(nullptr), op(nullptr) {}
};

CondExpr *gen_cond_expr(Expr *e1, Expr *e2, Expr *e3, const char *op);
class AssignExpr : public Expr
{
public:
    Expr *e1;
    Expr *e2;
    Term *op;
    AssignExpr() : e1(nullptr), e2(nullptr), op(nullptr) {}
};
AssignExpr *gen_assign_expr(Expr *e1, Term *op, Expr *e2);
class TopLevelExpr : public Expr
{
public:
    Expr *e1;
    Expr *e2;
    TopLevelExpr() : e1(nullptr), e2(nullptr) {}
};
TopLevelExpr *gen_toplevel_expr(Expr *e1, Expr *e2);
class ConstExpr : public Expr
{
};

class TypeSpecifier: public Term {

};
class TypeQualifier: public Term {

};
class StorageClassSpecifier {

};
class SpecifierQualifierList {
    std::vector<TypeSpecifier*> specifiers;
    std::vector<TypeQualifier*> qualifiers;
};