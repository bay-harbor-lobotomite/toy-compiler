#pragma once
#include <ast.h>
#include <decl.h>
class Stmt: public NonTerm {
    public:  
    Stmt() : NonTerm("") {};
    virtual ~Stmt() {};
};

class StmtList: public NonTerm {
    public:
    std::vector<Stmt*> stmts;
    StmtList(): NonTerm("") {}
};
StmtList* gen_stmtlist(StmtList* sl, Stmt* s);

class TopLvlStmt: public Stmt {

};
class DeclnList;
class CompStmt: public Stmt {
    public:
    DeclnList* decln_list;
    StmtList* stmt_list;
    CompStmt(): decln_list(nullptr), stmt_list(nullptr) {}
};
CompStmt* gen_compstmt(DeclnList* dl, StmtList* sl);
class JmpStmt: public Stmt {

};
class SelStmt: public Stmt {

};
class LabStmt: public Stmt {

};
class ExprStmt: public Stmt {

};
class ItrStmt: public Stmt {

};