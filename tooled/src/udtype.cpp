#include <ast.h>
#include <udtype.h>
#include <expr.h>
#include <stmt.h>
#include <y.tab.h>

Enumtr* gen_enumtr(Idfr* i, Expr* e) {
    auto etr = new Enumtr();
    etr->idfr = i;
    etr->name = std::string("enumerator_") + i->name;
    etr->add_children(1, i);
    if(e)
    {
        auto ce = dynamic_cast<ConstExpr*>(e);
        etr->add_children(1, ce);
        etr->const_expr = ce;
    }
    return etr;
}

EnumtrList* gen_enumtrlist(EnumtrList* el, Enumtr* e) {
    EnumtrList* tel;
    if(el) tel = el;
    else tel = new EnumtrList();
    tel->add_children(1, e);
    tel->name = "enumerator_list";
    tel->enumtrs.push_back(e);
    return tel;        
}

EnumSpec* gen_enumspec(Idfr* i, EnumtrList* el) {
    auto es = new EnumSpec();
    if(i) {
        es->idfr = i;
        es->add_children(1, i);
    }
    if(el) {
        es->elist = el;
        es->add_children(1, el);
    }
    es->name = std::string("enum_specifier_") + i->name;
    return es;
}

TypeName* gen_typename(SpecQualList* sql, AbsDecl* ad) {
    auto tn = new TypeName();
    tn->name = "typename";
    tn->spec_qual_list = sql;
    tn->add_children(1, sql);
    if(ad)
    {
        tn->abs_decl = ad;
        tn->add_children(1, ad);
    }
    return tn;
}

StructDecl* gen_structdecl(Decl* d, Expr* e) {
    auto sd = new StructDecl();
    sd->name = "struct_declaration";
    if(d)
    {
        sd->decl = d;
        sd->add_children(1, d);
    }
    if(e)
    {
        auto ce = dynamic_cast<ConstExpr*>(e);
        sd->const_expr = ce;
        sd->add_children(1, ce);
    }
    return sd;
}

StructDeclList* gen_structdecl_list(StructDeclList* sl, StructDecl* s) {
    StructDeclList* tsl;
    if(sl) tsl = sl;
    else tsl = new StructDeclList();
    tsl->add_children(1, s);
    tsl->name = "struct_declarator_list";
    tsl->struct_decls.push_back(s);
    return tsl;        
}

StructDecln* gen_structdecln(SpecQualList* sql, StructDeclList* sdl) {
    auto sd = new StructDecln();
    sd->struct_decl_list = sdl;
    sd->spec_qual_list = sql;
    sd->name = "struct_declaration";
    sd->add_children(2, sql, sdl);
    return sd;
}

StructDeclnList* gen_structdeclnlist(StructDeclnList* sl, StructDecln* s) {
    StructDeclnList* tsl;
    if(sl) tsl = sl;
    else tsl = new StructDeclnList();
    tsl->add_children(1, s);
    tsl->name = "struct_declaration_list";
    tsl->struct_declns.push_back(s);
    return tsl;     
}

StructOrUnionSpec* gen_structorunion_spec(const char* kind, Idfr* i, StructDeclnList* sdl) {
    auto ss = new StructOrUnionSpec();
    ss->name = "struct_or_union_specifier";
    ss->is_struct = kind == "STRUCT";
    if(i)
    {
        ss->idfr = i;
        ss->add_children(1, i);
    }
    if(sdl)
    {
        ss->struct_decln_list = sdl;
        ss->add_children(1, sdl);
    }
    return ss;
}