#pragma once
#include <ast.h>

class Expr;
class ConstExpr;

class Stmt: public NonTerm {
    public:  
    Stmt() {};
    virtual ~Stmt() {};
};

class StmtList: public NonTerm {
    public:
    std::vector<Stmt*> stmts;
    StmtList() {}
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

enum JmpStmtKind {
    JSK_CONTINUE,
    JSK_BREAK,
    JSK_GOTO,
    JSK_RETURN,
};
class JmpStmt: public Stmt {
    public:
    JmpStmtKind kind;
    Idfr* idfr;
    Expr* expr;
    JmpStmt(): idfr(nullptr), expr(nullptr) {}
};
//going with a more atomic approach to avoid a very bloated function
JmpStmt* gen_jmpstmt_goto(Idfr* i);
JmpStmt* gen_jmpstmt(JmpStmtKind k);
JmpStmt* gen_jmpstmt_return(Expr* e);

enum SelStmtKind {
    SSK_IF,
    SSK_SWITCH,
};
class SelStmt: public Stmt {
    public:
    SelStmtKind kind;
    Expr* expr;
    Stmt* stmt1;
    Stmt* stmt2;
    SelStmt(): expr(nullptr), stmt1(nullptr), stmt2(nullptr) {}  
};
SelStmt* gen_selstmt_if(Expr* e, Stmt* s1, Stmt* s2);
SelStmt* gen_selstmt_switch(Expr* e, Stmt* s);

enum LabStmtKind {
    LSK_CASE,
    LSK_LABEL,
};
class LabStmt: public Stmt {
    public: 
    LabStmtKind kind;
    Idfr* idfr;
    ConstExpr* const_expr;
    Stmt* stmt;
    LabStmt(): idfr(nullptr), const_expr(nullptr), stmt(nullptr) {}
};
LabStmt* gen_labstmt_case(Expr* e, Stmt* s);
LabStmt* gen_labstmt(Idfr* i, Stmt* s);
class ExprStmt: public Stmt {
    public:
    Expr* expr;
    ExprStmt(): expr(nullptr) {}
};
ExprStmt* gen_exprstmt(Expr* e);

enum ItrStmtKind {
    ISK_WHILE,
    ISK_DOWHILE,
    ISK_FOR
};
class ItrStmt: public Stmt {
    public:
    ItrStmtKind kind;
    ExprStmt* expr_stmt1;
    ExprStmt* expr_stmt2;
    Expr* expr;
    Stmt* stmt;
    ItrStmt(): expr_stmt1(nullptr), expr_stmt2(nullptr), expr(nullptr), stmt(nullptr) {}    
};
ItrStmt* gen_itrstmt_while(ItrStmtKind k, Expr* e, Stmt* s);
ItrStmt* gen_itrstmt_for(Stmt* es1, Stmt* es2, Expr* e, Stmt* s);