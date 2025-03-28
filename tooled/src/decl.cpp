#include <decl.h>
#include <expr.h>
#include <ast.h>
#include <udtype.h>
#include <stmt.h>
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
    ts->name = std::string("type_specifier_") + ts->name;
    return ts;
}

TypeQual* gen_typequal(int kind, int line, int colno) {
    auto tq = new TypeQual(kind);
    auto nm = kind == CONST ? "CONST" : "VOLATILE";
    tq->name = std::string("type_qualifier_") + std::string(nm);
    return tq;
}

StorageClassSpec* gen_storagecl_spec(int kind, int line, int colno) {
    auto sc = new StorageClassSpec(kind);
    sc->name = stringify_kind(kind);
    sc->name = std::string("storage_class_specifier_") + sc->name;
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
DeclnSpecs *gen_declnspecs(DeclnSpecs *ds, TypeSpec *ts, TypeQual *tq, StorageClassSpec* scs) {
    DeclnSpecs* t_ds;
    if(!ds) t_ds = new DeclnSpecs();
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

Decln* gen_decln(DeclnSpecs* ds, InitDeclList* idl) {
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
    t_idl->name = "init_declarator_list";
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


ParamDecln* gen_paramdecln(DeclnSpecs* ds, AbsDecl* ad, Decl* d) {
    auto pd = new ParamDecln();
    pd->decln_specs = ds;
    pd->name = "parameter_declaration";
    pd->add_children(1, ds);
    if(ad) 
    {
        pd->abs_decl = ad;
        pd->add_children(1, ad);
    }
    if(d)
    {   
        pd->decl = d;
        pd->add_children(1, d);
    }
    return pd;
}

ParamList* gen_paramlist(ParamList* pl, ParamDecln* pd) {
    ParamList* tpl;
    if(pl) tpl = pl;
    else tpl = new ParamList();
    tpl->name = "parameter_list";
    tpl->add_children(1, pd);
    tpl->param_declarations.push_back(pd);
    return tpl;
}

DirDecl* gen_dirdecl_decl(Decl* dc) {
    auto dd = new DirDecl();
    dd->name = "direct_declarator_declarator";
    dd->add_children(1, dc);
    dd->decl = dc;
    return dd;
}
DirDecl* gen_dirdecl_func(DirDecl* ddn, ParamList* pl, IdfrList* il) {
    auto dd = new DirDecl();
    dd->name = "direct_declarator_function";
    if(pl)
    {
        dd->add_children(1, pl);
        dd->param_list = pl;
    }
    if(il)
    {
        dd->add_children(1, il);
        dd->idfr_list = il;
    }
    dd->add_children(1, ddn);
    dd->dir_decl = ddn;
    return dd;
}
DirDecl* gen_dirdecl_arr(DirDecl* ddn, Expr* ce) {
    auto dd = new DirDecl();
    dd->name = "direct_declarator_array";
    if(ce)
    {
        auto cce = dynamic_cast<ConstExpr*>(ce);
        dd->add_children(1, cce);
        dd->const_expr = cce;
    }
    dd->add_children(1, ddn);
    dd->dir_decl = ddn;
    return dd;    
}
DirDecl* gen_dirdecl_idfr(Idfr* i) {
    auto dd = new DirDecl();
    dd->name = "direct_declarator_identifier";
    dd->add_children(1, i);
    dd->idfr = i;
    return dd;
}

AbsDecl* gen_absdecl(DirAbsDecl* dad, Ptr* p) {
    auto ad = new AbsDecl();
    ad->name = "abstract_declarator";
    if(dad)
    {
        ad->dir_abs_decl = dad;
        ad->add_children(1, dad);
    }
    if(p)
    {
        ad->ptr = p; 
        ad->add_children(1, p);
    }
    return ad;    
}

DirAbsDecl* gen_dirabsdecl_decl(AbsDecl* adc) {
    auto dad = new DirAbsDecl();
    dad->name = "direct_abstract_declarator_declarator";
    dad->add_children(1, adc);
    dad->abs_decl = adc;
    return dad;    
}
DirAbsDecl* gen_dirabsdecl_func(DirAbsDecl* dadn, ParamList* pl) {
    auto dad = new DirAbsDecl();
    dad->name = "direct_abstract_declarator_function";
    if(pl)
    {
        dad->add_children(1, pl);
        dad->param_list = pl;
    }
    if(dadn)
    {
        dad->add_children(1, dadn);
        dad->dir_abs_decl = dadn;
    } 
    return dad;
}
DirAbsDecl* gen_dirabsdecl_arr(DirAbsDecl* dadn,Expr* ce) {
    auto dad = new DirAbsDecl();
    dad->name = "direct_abstract_declarator_array";
    if(ce)
    {
        auto cen = dynamic_cast<ConstExpr*>(ce);
        dad->add_children(1, cen);
        dad->const_expr = cen;
    }
    if(dadn)
    {
        dad->add_children(1, dadn);
        dad->dir_abs_decl = dadn;
    } 
    return dad;
}

DeclnList* gen_declnlist(DeclnList* dl, Decln* d) {
    DeclnList* tdl;
    if(dl) tdl = dl;
    else tdl = new DeclnList();
    tdl->name = "declaration_list";
    tdl->add_children(1, d);
    tdl->declns.push_back(d);
    return tdl;    
}

FuncDef* gen_funcdef(DeclnSpecs* ds, Decl* d, DeclnList* dl, Stmt* cs) {
    std::vector<NonTerm*> params = {ds, d, dl};
    CompStmt* ncs = nullptr;
    if(cs) {
        ncs = dynamic_cast<CompStmt*>(cs);
        params.push_back(ncs);
    }
    auto fd = new FuncDef();
    fd->name = std::string("function_definition");
    for(auto param: params)
    {
        if(param)
        {
            fd->add_children(1, param);
        }
    }
    if(ds) fd->decln_specs = ds;
    if(d) fd->decl = d;
    if(dl) fd->decln_list = dl;
    if(ncs) fd->comp_stmt = ncs;
    return fd;
}