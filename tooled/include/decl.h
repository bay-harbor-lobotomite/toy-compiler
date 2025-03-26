#include <ast.h>
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

class DeclSpecs: public NonTerm {
    public:
    std::vector<TypeQual*> qualifiers;
    std::vector<TypeSpec*> specifiers;
    std::vector<StorageClassSpec*> sc_specifiers;
    DeclSpecs(): NonTerm("") {}
};

// optional arguments of sorts, trading off sensible nullability for conciseness
DeclSpecs *gen_declspecs(DeclSpecs *ds, TypeSpec *ts, TypeQual *tq, StorageClassSpec* scs);

//ok dropping the naming scheme for everyones good here
class InitializerList;
class Initializer: public NonTerm {
    public:
    AssignExpr* assign_expr;
    InitializerList* initializer_list;
    Initializer(): NonTerm("") {}
};
Initializer* gen_initializer(Expr* ae, InitializerList* il);

class InitializerList: public NonTerm {
    public:
    std::vector<Initializer*> initializers;
    InitializerList(): NonTerm("") {}
};
InitializerList* gen_initializerlist(InitializerList* il, Initializer* i);

class DirDecl: public NonTerm {

};
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
    Ptr(): NonTerm("") {}
};
Ptr* gen_ptr(TypeQualList* tql, Ptr* p);

class Decl: public NonTerm {
    public:
    DirDecl* dir_decl;
    Ptr* ptr;
    Decl(): NonTerm("") {}
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
    DeclSpecs* decl_specs;
    InitDeclList* init_decl_list;
    Decln(): NonTerm("") {}
    Decln(DeclSpecs* ds, InitDeclList* idl): NonTerm(""), decl_specs(ds), init_decl_list(idl) {}
};

//honestly not required but maintaining consistency
Decln* gen_decln(DeclSpecs* ds, InitDeclList* idl);

class IdfrList: public NonTerm {
    public:
    std::vector<Idfr*> idfrs;
    IdfrList(): NonTerm("") {}
};
IdfrList* gen_idfrlist(IdfrList* il, Idfr* i);
