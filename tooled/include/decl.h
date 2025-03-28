#pragma once
#include <ast.h>
#include <stmt.h>
#include <sstream>
// deeply coupled with y.tab.h :(((
// initially thought of storing an enum but instead will just sync up with the yytokentype enum
// redeclaring yytokentype here will not work cause of incomplete type, but ill just use an int for now
// enum TypeSpecKind {
//     TSK_CHAR = 289,
//     TSK_SHORT = 290,
//     TSK_INT = 291,
//     TSK_LONG = 292,
//     TSK_SIGNED = 293,
//     TSK_UNSIGNED = 294,
//     TSK_FLOAT = 295,
//     TSK_DOUBLE = 296,
//     TSK_VOID = 297,
//     TSK_TYPE_NAME = 283
// };
class Expr;
class AssignExpr;
class ConstExpr;
class TypeSpec : public Term
{
public:
    int spec_kind;
    TypeSpec(int kind) : Term("", ""), spec_kind(kind) {}
    // implement line and colno later
    //  TypeSpec(TypeSpecKind kind, unsigned int line, unsigned int colno): line(line), colno(colno), kind(kind) {}
};
TypeSpec *gen_typespec(int kind, int line, int colno);

class TypeQual : public Term
{
public:
    int qual_kind;
    TypeQual(int kind) : Term("", ""), qual_kind(kind) {}
};
TypeQual *gen_typequal(int kind, int line, int colno);

class StorageClassSpec : public Term
{
public:
    int sc_kind;
    StorageClassSpec(int kind) : Term("", ""), sc_kind(kind) {}
};
StorageClassSpec *gen_storagecl_spec(int kind, int line, int colno);

class SpecQualList : public NonTerm
{
public:
    std::vector<TypeSpec *> specifiers;
    std::vector<TypeQual *> qualifiers;
    SpecQualList(): NonTerm("") {}
};

// optional arguments of sorts, trading off sensible nullability for conciseness
SpecQualList *gen_specqual_list(SpecQualList *sql, TypeSpec *ts, TypeQual *tq);

class DeclnSpecs: public NonTerm {
    public:
    std::vector<TypeQual*> qualifiers;
    std::vector<TypeSpec*> specifiers;
    std::vector<StorageClassSpec*> sc_specifiers;
    DeclnSpecs(): NonTerm("") {}
};

// optional arguments of sorts, trading off sensible nullability for conciseness
DeclnSpecs *gen_declnspecs(DeclnSpecs *ds, TypeSpec *ts, TypeQual *tq, StorageClassSpec* scs);

//ok dropping the naming scheme for everyones good here
class InitializerList;
class Initializer: public NonTerm {
    public:
    AssignExpr* assign_expr;
    InitializerList* initializer_list;
    Initializer(): NonTerm(""), assign_expr(nullptr), initializer_list(nullptr) {}
};
Initializer* gen_initializer(Expr* ae, InitializerList* il);

class InitializerList: public NonTerm {
    public:
    std::vector<Initializer*> initializers;
    InitializerList(): NonTerm("") {}
};
InitializerList* gen_initializerlist(InitializerList* il, Initializer* i);

class TypeQualList: public NonTerm {
    public:
    std::vector<TypeQual*> type_quals;
    TypeQualList(): NonTerm("") {}
};
TypeQualList* gen_typequal_list(TypeQualList* tql, TypeQual* tq);

class Ptr: public NonTerm {
    public:
    Ptr* ptr;
    TypeQualList* type_qual_list;
    Ptr(): NonTerm(""), ptr(nullptr), type_qual_list(nullptr) {}
};
Ptr* gen_ptr(TypeQualList* tql, Ptr* p);

class AbsDecl;
class Decl;
class ParamDecln: public NonTerm {
    public:
    DeclnSpecs* decln_specs;
    AbsDecl* abs_decl;
    Decl* decl;
    ParamDecln(): NonTerm(""), decln_specs(nullptr), abs_decl(nullptr), decl(nullptr) {}
};
ParamDecln* gen_paramdecln(DeclnSpecs* ds, AbsDecl* ad, Decl* d);

class ParamList: public NonTerm {
    public:
    std::vector<ParamDecln*> param_declarations;
    ParamList(): NonTerm("") {}
};
ParamList* gen_paramlist(ParamList* pl, ParamDecln* pd);


class IdfrList: public NonTerm {
    public:
    std::vector<Idfr*> idfrs;
    IdfrList(): NonTerm("") {}
};
IdfrList* gen_idfrlist(IdfrList* il, Idfr* i);

class Decl;
class DirDecl: public NonTerm {
    public:
    Idfr* idfr;
    Decl* decl;
    DirDecl *dir_decl;
    ConstExpr * const_expr;
    IdfrList* idfr_list;
    ParamList* param_list;
    DirDecl(): NonTerm(""), idfr(nullptr), decl(nullptr), dir_decl(nullptr), const_expr(nullptr), idfr_list(nullptr), param_list(nullptr) {}
};
DirDecl* gen_dirdecl_decl(Decl* dc);
DirDecl* gen_dirdecl_func(DirDecl* ddn,ParamList* pl, IdfrList* il);
DirDecl* gen_dirdecl_arr(DirDecl* ddn,Expr* ce);
DirDecl* gen_dirdecl_idfr(Idfr* i);

class AbsDecl;
class DirAbsDecl: public NonTerm {
    public:
    DirAbsDecl* dir_abs_decl;
    AbsDecl* abs_decl;
    ConstExpr* const_expr;
    ParamList* param_list;
    DirAbsDecl(): NonTerm(""), dir_abs_decl(nullptr), abs_decl(nullptr), const_expr(nullptr), param_list(nullptr) {}
};
DirAbsDecl* gen_dirabsdecl_decl(AbsDecl* adc);
DirAbsDecl* gen_dirabsdecl_func(DirAbsDecl* dadn,ParamList* pl);
DirAbsDecl* gen_dirabsdecl_arr(DirAbsDecl* dadn,Expr* ce);

class AbsDecl: public NonTerm {
    public:
    DirAbsDecl* dir_abs_decl;
    Ptr* ptr;
    AbsDecl(): NonTerm(""), dir_abs_decl(nullptr), ptr(nullptr) {}
};
AbsDecl* gen_absdecl(DirAbsDecl* dad, Ptr* p);

class Decl: public NonTerm {
    public:
    DirDecl* dir_decl;
    Ptr* ptr;
    Decl(): NonTerm(""), dir_decl(nullptr), ptr(nullptr) {}
};
Decl* gen_decl(DirDecl* dd, Ptr* p);

class InitDecl: public NonTerm { 
    public:
    Decl* decl;
    Initializer* initializer;
    InitDecl(Decl* d, Initializer* i): NonTerm(""), decl(d), initializer(i) {}
};

InitDecl* gen_initdecl(Decl* d, Initializer* i);

class InitDeclList: public NonTerm {
    public:
    std::vector<InitDecl*> init_decls;
    InitDeclList(): NonTerm("") {} 
};

InitDeclList* gen_initdecl_list(InitDeclList* idl, InitDecl* id);

class Decln: public NonTerm {
    public:
    DeclnSpecs* decl_specs;
    InitDeclList* init_decl_list;
    Decln(): NonTerm("") {}
    Decln(DeclnSpecs* ds, InitDeclList* idl): NonTerm(""), decl_specs(ds), init_decl_list(idl) {}
};

//honestly not required but maintaining consistency
Decln* gen_decln(DeclnSpecs* ds, InitDeclList* idl);

class DeclnList: public NonTerm {
    public:
    std::vector<Decln*> declns;
    DeclnList(): NonTerm("") {}
};
DeclnList* gen_declnlist(DeclnList* dl, Decln* d);

class FuncDef: public NonTerm {
    public:
    DeclnSpecs* decln_specs;
    Decl* decl;
    DeclnList* decln_list;
    CompStmt* comp_stmt;
    FuncDef(): NonTerm(""), decln_specs(nullptr), decl(nullptr), decln_list(nullptr), comp_stmt(nullptr) {}
};
FuncDef* gen_funcdef(DeclnSpecs* ds, Decl* d, DeclnList* dl, Stmt* cs);
