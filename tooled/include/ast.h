#pragma once
#include <cstddef>
#include <string>
#include <vector>
#include <cstdarg>
// Essentially modelling these as structs
// Class for AST node

class AstNode
{
public:
    long long id;
    size_t colno;
    size_t line;
    AstNode();
    AstNode(size_t line, size_t colno);

    virtual void add_children(size_t count, ...);
};

class Term : public AstNode
{
public:
    std::string name;
    std::string val;
    // to string conversions done in constructor for ease of use and readability
    Term(const char *name, const char *val);
    Term(const char *name, const char *val, size_t line, size_t colno);
};

class NonTerm : public AstNode
{
public:
    std::string name;
    std::vector<AstNode *> children;

    NonTerm(const char *name);
    void add_children(size_t count, ...);
};

// some basics
class Idfr : public Term
{
};

union cnst_val{
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
    //todo: semantic check - CHANGE CONSTRUCTOR
    Cnst(const char* name, const char*val, size_t line, size_t colno): Term(name, val, line, colno) {};
    union cnst_val val;
};

class StrLit : public Term
{
    public:
    StrLit(const char *name, const char* val): Term(name, val) {};
};

enum PrExprType
{
    EXPRESSION,
    IDENTIFIER,
    CONSTANT,
    STRING_LITERAL
};


// expressions and their corresponding grammar helpers
class Expr : public NonTerm
{
public:
    Expr() : NonTerm("") {};
};

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
    PrExpr() : expr_type(EXPRESSION) {}
};

class UnaryExpr : public Expr {

};

class AddExpr: public Expr {

};

class MultExpr: public Expr {

};
class AndExpr: public Expr {

};
class OrExpr: public Expr {

};
class XorExpr: public Expr {

};
class LogAndExpr: public Expr {

};
class LogOrExpr: public Expr {

};
class RelExpr: public Expr {

};
class EqExpr: public Expr {

};
class ShiftExpr: public Expr {

};
class CondExpr: public Expr {

};
class AssignExpr : public Expr {

};



