#include <ast.h>
#include <udtype.h>

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