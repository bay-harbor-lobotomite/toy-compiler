#include <stmt.h>

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