#pragma once
#include <ast.h>
#include <expr.h>

class Enumtr: public NonTerm {
    public:
    Idfr* idfr;
    ConstExpr* const_expr;
    Enumtr(): NonTerm(""), idfr(nullptr), const_expr(nullptr) {}
};
Enumtr* gen_enumtr(Idfr* i, Expr* e);

class EnumtrList: public NonTerm {
    public:
    std::vector<Enumtr*> enumtrs;
    EnumtrList(): NonTerm("") {}
};
EnumtrList* gen_enumtrlist(EnumtrList* el, Enumtr* e);

class EnumSpec: public NonTerm {
    public:
    Idfr* idfr;
    EnumtrList* elist;
    EnumSpec(): NonTerm(""), idfr(nullptr), elist(nullptr) {}
};
EnumSpec* gen_enumspec(Idfr* i, EnumtrList* el);