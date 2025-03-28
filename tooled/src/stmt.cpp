#include <stmt.h>
#include <expr.h>

StmtList* gen_stmtlist(StmtList* sl, Stmt* s) {
    StmtList* tsl;
    if(sl) tsl = sl;
    else tsl = new StmtList();
    tsl->add_children(1, s);
    tsl->name = "statement_list";
    tsl->stmts.push_back(s);
    return tsl;        
}

CompStmt* gen_compstmt(DeclnList* dl, StmtList* sl) {
    auto cs = new CompStmt();
    cs->name = "compound_statement";
    if(dl)
    {
        cs->add_children(1, dl);
        cs->decln_list = dl;
    }
    if(sl)
    {
        cs->add_children(1, sl);
        cs->stmt_list = sl;
    }
    return cs;    
}

JmpStmt* gen_jmpstmt_goto(Idfr* i) {
    auto js = new JmpStmt();
    js->name = "jump_statement_goto";
    js->kind = JmpStmtKind::JSK_GOTO;
    js->idfr = i;
    js->add_children(1, i);
    return js;
}
JmpStmt* gen_jmpstmt(JmpStmtKind k) {
    auto js = new JmpStmt();
    auto pref = std::string("jump_statement_");
    if(k == JmpStmtKind::JSK_RETURN) pref += "return";
    if(k == JmpStmtKind::JSK_BREAK) pref += "break";
    if(k == JmpStmtKind::JSK_CONTINUE) pref += "continue";
    js->kind = k;
    js->name = pref;
    return js;
}
JmpStmt* gen_jmpstmt_return(Expr* e) {
    auto js = new JmpStmt();
    js->name = "jump_statement_return";
    js->kind = JmpStmtKind::JSK_RETURN;
    js->expr = e;
    js->add_children(1, e);
    return js;
}

LabStmt* gen_labstmt_case(Expr* e, Stmt* s) {
    auto ls = new LabStmt();
    ls->name = "labeled_statement_case";
    ls->kind = LabStmtKind::LSK_CASE;
    ConstExpr* ce = nullptr;
    if(e) 
    {
        ce = dynamic_cast<ConstExpr*>(e);
        ls->const_expr = ce;
        ls->add_children(1, ce);
    }
    ls->stmt = s;
    ls->add_children(1, s);
    return ls;
}
LabStmt* gen_labstmt(Idfr* i, Stmt* s) {
    auto ls = new LabStmt();
    ls->name = "labeled_statement";
    ls->kind = LabStmtKind::LSK_LABEL;
    ls->idfr = i;
    ls->stmt = s;
    ls->add_children(2, i, s);
    return ls;
}
ExprStmt* gen_exprstmt(Expr* e) {
    auto es = new ExprStmt();
    es->name = "expression_statement";
    es->expr = e;
    if(e) es->add_children(1, e);
    return es;
}

SelStmt* gen_selstmt_if(Expr* e, Stmt* s1, Stmt* s2) {
    auto ss = new SelStmt();
    ss->name = "selection_statement_if";
    ss->kind = SSK_IF;
    ss->expr = e;
    ss->stmt1 = s1;
    ss->add_children(2, e, s1);
    if(s2)
    {
        ss->stmt2 = s2;
        ss->add_children(1, s2);
    }
    return ss;
}
SelStmt* gen_selstmt_switch(Expr* e, Stmt* s) {
    auto ss = new SelStmt();
    ss->name = "selection_statement_switch";
    ss->kind = SSK_SWITCH;
    ss->expr = e;
    ss->stmt1 = s;
    ss->add_children(2, e, s);
    return ss;
}

ItrStmt* gen_itrstmt_while(ItrStmtKind k, Expr* e, Stmt* s) {
    auto is = new ItrStmt();
    is->kind = k;
    auto pref = std::string("iteration_statement_");
    if(k == ItrStmtKind::ISK_WHILE) pref += "while";
    if(k == ItrStmtKind::ISK_DOWHILE) pref += "do_while";
    is->name = pref;
    is->expr = e;
    is->stmt = s;
    is->add_children(2, e, s);
    return is;
}
ItrStmt* gen_itrstmt_for(Stmt* es1, Stmt* es2, Expr* e, Stmt* s) {
    auto is = new ItrStmt();
    is->kind = ItrStmtKind::ISK_FOR;
    is->name = std::string("iteration_statement_for");
    is->expr_stmt1 = dynamic_cast<ExprStmt*>(es1);
    is->expr_stmt2 = dynamic_cast<ExprStmt*>(es2);
    is->expr = e;
    is->stmt = s;
    is->add_children(4, es1, es2, e, s);
    return is;
}