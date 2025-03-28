#pragma once
#include <cstdarg>
#include <string>
#include <vector>
#include <iostream>
// for token types
//  Essentially modelling these as structs
//  Class for AST node

class AstNode
{
public:
    long long id;
    unsigned int colno;
    unsigned int line;
    // for dot generation
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
    Term(): name(""), val("") {}
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
    NonTerm(): name("") {}
    void add_children(unsigned int count, ...);
    void to_dot() override;
};

// some basics
class Idfr : public Term
{
public:
    Idfr() : Term("identifier", "") {}
};
Idfr *gen_idfr(const char *val);

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
    Cnst(const char* name, const char* val): Term(name, val) {}
    Cnst(const char *name, const char *val, unsigned int line, unsigned int colno) : Term(name, val, line, colno) {};
    union cnst_val cval;
};
//will incorporate constant type during semantic analysis
Cnst* gen_cnst(const char* name, const char* val);

class StrLit : public Term
{
public:
    StrLit(const char *name, const char *val) : Term(name, val) {};
};