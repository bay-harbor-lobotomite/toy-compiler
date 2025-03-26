#include <decl.h>
#include <expr.h>
#include <ast.h>
#include <y.tab.h>

std::string stringify_kind(int kind) {
    std::stringstream ss;
    switch(kind)
    {
        case CHAR: ss << "CHAR"; break;
        case INT: ss << "INT"; break;
        case VOID: ss << "VOID"; break;
        case FLOAT: ss << "FLOAT"; break;
        case DOUBLE: ss << "DOUBLE"; break;
        case UNSIGNED: ss << "UNSIGNED"; break;
        case SIGNED: ss << "SIGNED"; break;
        case LONG: ss << "LONG"; break;
        case SHORT: ss << "SHORT"; break;
        case TYPE_NAME: ss << "TYPE_NAME"; break;
        case TYPEDEF: ss << "TYPEDEF"; break;
        case EXTERN: ss << "EXTERN"; break;
        case AUTO: ss << "AUTO"; break;
        case REGISTER: ss << "REGISTER"; break;
        case STATIC: ss << "STATIC"; break;
    }
    return ss.str();
}
TypeSpec* gen_typespec(int kind, int line, int colno) {
    auto ts = new TypeSpec(kind);
    ts->name = stringify_kind(kind);
    return ts;
}

TypeQual* gen_typequal(int kind, int line, int colno) {
    auto tq = new TypeQual(kind);
    auto nm = kind == CONST ? "CONST" : "VOLATILE";
    tq->name = std::string(nm);
    return tq;
}

StorageClassSpec* gen_storagecl_spec(int kind, int line, int colno) {
    auto sc = new StorageClassSpec(kind);
    sc->name = stringify_kind(kind);
    return sc;
}

SpecQualList* gen_specqual_list(SpecQualList* sql, TypeSpec* ts, TypeQual* tq) {
    SpecQualList* t_sql;
    if(!sql) t_sql = new SpecQualList();
    else t_sql = sql;
    t_sql->name = std::string("specifier_qualifier_list");
    if(ts) {
        t_sql->specifiers.push_back(ts);
        t_sql->add_children(1, ts);
    }
    else if(tq) {
        t_sql->qualifiers.push_back(tq);
        t_sql->add_children(1, tq);
    }
    return t_sql;
}

// optional arguments of sorts, trading off sensible nullability for conciseness
DeclSpecs *gen_declspecs(DeclSpecs *ds, TypeSpec *ts, TypeQual *tq, StorageClassSpec* scs) {
    DeclSpecs* t_ds;
    if(!ds) t_ds = new DeclSpecs();
    else t_ds = ds;
    t_ds->name = std::string("declaration_specifiers");
    if(ts) {
        t_ds->specifiers.push_back(ts);
        t_ds->add_children(1, ts);
    }
    else if(tq) {
        t_ds->qualifiers.push_back(tq);
        t_ds->add_children(1, tq);
    }
    else if(scs) {
        t_ds->sc_specifiers.push_back(scs);
        t_ds->add_children(1, scs);
    }
    return t_ds;
}

Decln* gen_decln(DeclSpecs* ds, InitDeclList* idl) {
    auto dn = new Decln(ds, idl);
    dn->name = "declaration";
    if(idl) dn->add_children(2, ds, idl);
    else dn->add_children(1, ds);
    return dn;
}

InitDeclList* gen_initdecl_list(InitDeclList* idl, InitDecl* id) {
    InitDeclList* t_idl;
    if(idl) t_idl = idl;
    else t_idl = new InitDeclList();
    t_idl->add_children(1, id);
    t_idl->init_decls.push_back(id);
    return t_idl;
}

InitDecl* gen_initdecl(Decl* d, Initializer* i) {
    auto id = new InitDecl(d, i);
    id->name = "init_declarator";
    id->add_children(2, d, i);
    return id;
}

Decl* gen_decl(DirDecl* dd, Ptr* p) {
    auto d = new Decl();
    d->name = "declarator";
    d->dir_decl = dd;
    if(p) d->ptr = p; 
    d->add_children(1, dd);
    if(p) d->add_children(1, p);
    return d;
}

Ptr* gen_ptr(TypeQualList* tql, Ptr* p) {
    auto pt = new Ptr();
    pt->name = "pointer";
    if(tql)
    {
        pt->add_children(1, tql);
        pt->type_qual_list = tql;
    }
    if(p)
    {
        pt->add_children(1, p);
        pt->ptr = p;
    }
    return pt;
}

TypeQualList* gen_typequal_list(TypeQualList* tql, TypeQual* tq) {
    TypeQualList* ttql;
    if(tql) ttql = tql;
    else ttql = new TypeQualList();
    ttql->type_quals.push_back(tq);
    ttql->add_children(1, tq);
    ttql->name = "type_qualifier_list";
    return ttql;
}

IdfrList* gen_idfrlist(IdfrList* il, Idfr* i) {
    IdfrList* til;
    if(il) til = il;
    else til = new IdfrList();
    til->add_children(1, i);
    til->name = "identifier_list";
    til->idfrs.push_back(i);
    return til;
}

InitializerList* gen_initializerlist(InitializerList* il, Initializer* i) {
    InitializerList* til;
    if(il) til = il;
    else til = new InitializerList();
    til->add_children(1, i);
    til->name = "initializer_list";
    til->initializers.push_back(i);
    return til;    
}

Initializer* gen_initializer(Expr* ae, InitializerList* il) {
    auto i = new Initializer();
    i->name = "initializer";
    if(ae) i->assign_expr = dynamic_cast<AssignExpr*>(ae);
    i->initializer_list = il;
    if(ae) i->add_children(1, ae);
    if(il) i->add_children(1, il);
    return i;
}
