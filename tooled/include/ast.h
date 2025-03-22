#pragma once
#include <cstdarg>
#include <string>
#include <vector>
// Essentially modelling these as structs
// Class for AST node

struct AstNode
{
    long long id;
    unsigned int colno;
    unsigned int line;
    AstNode();
    AstNode(unsigned int line, unsigned int colno);

    void add_children(unsigned int count, ...);
};

struct Term : public AstNode
{
public:
    std::string name;
    std::string val;
    // to string conversions done in constructor for ease of use and readability
    Term(const char *name, const char *val);
    Term(const char *name, const char *val, unsigned int line, unsigned int colno);
};

struct NonTerm : public AstNode
{
public:
    std::string name;
    std::vector<AstNode *> children;

    NonTerm(const char *name);
    void add_children(unsigned int count, ...);
};

// some basics
struct Idfr : public Term
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
struct Cnst : public Term
{   
    public:
    //todo: semantic check - CHANGE CONSTRUCTOR
    Cnst(const char* name, const char*val, unsigned int line, unsigned int colno): Term(name, val, line, colno) {};
    union cnst_val val;
};

struct StrLit : public Term
{
    public:
    StrLit(const char *name, const char* val): Term(name, val) {};
};

enum PrExprType
{
    EXPRESSION_G,
    IDENTIFIER_G,
    CONSTANT_G,
    STRING_LITERAL_G
};


// expressions and their corresponding grammar helpers
struct Expr : public NonTerm
{
public:
    Expr() : NonTerm("") {};
};

struct PrExpr : public Expr
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

struct UnaryExpr : public Expr {
    public:
    Expr* oprnd;
    Term* op;
    UnaryExpr() : oprnd(nullptr), op(nullptr) {}
};

UnaryExpr* build_unary_expr();

struct AddExpr: public Expr {

};

struct MultExpr: public Expr {

};
struct AndExpr: public Expr {

};
struct OrExpr: public Expr {

};
struct XorExpr: public Expr {

};
struct LogAndExpr: public Expr {

};
struct LogOrExpr: public Expr {

};
struct RelExpr: public Expr {

};
struct EqExpr: public Expr {

};
struct ShiftExpr: public Expr {

};
struct CondExpr: public Expr {

};
struct AssignExpr : public Expr {

};



