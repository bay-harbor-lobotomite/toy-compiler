#pragma once
#include <ast.h>
#include <expr.h>
#include <decl.h>

class Enumtr : public NonTerm
{
public:
    Idfr *idfr;
    ConstExpr *const_expr;
    Enumtr() : idfr(nullptr), const_expr(nullptr) {}
};
Enumtr *gen_enumtr(Idfr *i, Expr *e);

class EnumtrList : public NonTerm
{
public:
    std::vector<Enumtr *> enumtrs;
    EnumtrList()  {}
};
EnumtrList *gen_enumtrlist(EnumtrList *el, Enumtr *e);

class EnumSpec : public NonTerm
{
public:
    Idfr *idfr;
    EnumtrList *elist;
    EnumSpec() : idfr(nullptr), elist(nullptr) {}
};
EnumSpec *gen_enumspec(Idfr *i, EnumtrList *el);

class TypeName : public NonTerm
{
public:
    SpecQualList *spec_qual_list;
    AbsDecl *abs_decl;
    TypeName() : spec_qual_list(nullptr), abs_decl(nullptr) {}
};
TypeName *gen_typename(SpecQualList *sql, AbsDecl *ad);

class StructDecl : public NonTerm
{
public:
    Decl *decl;
    ConstExpr *const_expr;
    StructDecl() : decl(nullptr), const_expr(nullptr) {}
};
StructDecl *gen_structdecl(Decl *d, Expr *e);

class StructDeclList : public NonTerm
{
public:
    std::vector<StructDecl *> struct_decls;
    StructDeclList() {}
};
StructDeclList *gen_structdecl_list(StructDeclList *sl, StructDecl *s);

class StructDecln : public NonTerm
{
public:
    SpecQualList *spec_qual_list;
    StructDeclList *struct_decl_list;
    StructDecln() : spec_qual_list(nullptr), struct_decl_list(nullptr) {}
};
StructDecln *gen_structdecln(SpecQualList *sql, StructDeclList *sdl);

class StructDeclnList : public NonTerm
{
public:
    std::vector<StructDecln *> struct_declns;
    StructDeclnList() {}
};
StructDeclnList *gen_structdeclnlist(StructDeclnList *sl, StructDecln *s);

class StructOrUnionSpec : public NonTerm
{
    public:
    bool is_struct;
    Idfr* idfr;
    StructDeclnList* struct_decln_list;
    StructOrUnionSpec(): idfr(nullptr), struct_decln_list(nullptr) {}
};
StructOrUnionSpec* gen_structorunion_spec(const char* kind, Idfr* i, StructDeclnList* sdl);
