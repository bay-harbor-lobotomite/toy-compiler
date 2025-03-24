#pragma once
#include <ast.h>
#include <vector>
#include <cstddef>
#include <sstream>
#include <string>  
#include <cstring>  
#include <stack>
#include <unordered_map>

//32 bit target
#define WORD_SIZE 4

class Type;
class TypeSpec;

extern std::vector<TypeSpec*> type_list;

enum Primitive {
    T_ERR = -1,
    T_UCHAR = 0,
    T_CHAR = 1,
    T_USHORT = 2,
    T_SHORT = 3, 
    T_UINT = 4,
    T_INT = 5,
    T_ULONG = 6,
    T_LONG = 7,
    T_FLOAT = 8,
    T_DOUBLE = 9,
    T_LDOUBLE = 10,
    T_VOID = 11,
};

unsigned int get_primitive_size(Primitive type);
std::string get_primitive_name(Primitive name);
void init_primitives();
int define_new_type(TypeSpec* ts);


//index ---> indexes into global type list
class Type {
    public:
    int type_index;
    
    //if function
    bool is_func;
    int arg_count;
    std::vector<Type> arg_ts;
    bool is_defined;

    //if array
    bool is_array;
    std::vector<int> dims; 

    //if pointer
    bool is_ptr;
    int ptr_level;

    //if const
    bool is_const;

    Type() {}
    Type(int idx): type_index(idx) {}

    //helpers
    TypeSpec* spec() const { return type_list[type_index];}
    std::string get_name() const;
    size_t get_size() const;
    bool is_primitive() const {return type_index >= T_UCHAR && type_index <= T_VOID;}
    bool is_pointer() const { return ptr_level > 0; }
    bool is_lvalue() const { return is_array || (!is_primitive() && !is_pointer());}
    bool is_int() const { return type_index >= T_UCHAR && type_index <= T_LONG && ptr_level == 0;}
    bool is_char() const { return (type_index == T_UCHAR || type_index == T_CHAR) && ptr_level == 0;}
    bool is_float() const { return type_index >= T_FLOAT && type_index <= T_LDOUBLE && ptr_level == 0;}
    bool is_numeric() const { return type_index >= T_UCHAR && type_index <= T_LDOUBLE && ptr_level == 0;}
    bool is_unsigned() const {return type_index % 2 == 0 && type_index >= 0 && type_index <= T_ULONG;}
    bool is_void() const { return type_index == T_VOID && ptr_level == 0;}
    bool is_invalid() const { return type_index == -1 || (type_index == T_VOID && !is_ptr && !is_func) ;} //only pointers and functions can be void
    void make_signed() { if(is_int() && type_index % 2 == 0) type_index++;}
    void make_unsigned() { if(is_int() && type_index % 2 == 1) type_index--;}

    //overloads
    friend bool operator==(Type &t1, Type &t2);
    friend bool operator!=(Type &t1, Type &t2);
};

// a type descriptor of sorts for basic primitives, defined struct/union types
// composite types like arrays and functions are composed using these primitives
class TypeSpec {
    public:
    int idx;
    size_t size;
    std::string name;
    bool is_pointer;
    bool is_struct;
    bool is_union;
    bool is_primitive;
    TypeSpec(): is_pointer(false), is_struct(false), is_union(false), is_primitive(false) {}
};

class Sym {
    public:
    std::string name;
    unsigned int line;
    unsigned int colno;
    Type type;
    //mem stuff
    size_t offset;
    Sym() {}
    Sym(auto name): name(name) {}
};
class SymTab {
    public:
    //kinda arbitrary
    int scope_level;
    std::unordered_map<std::string, Sym*> symbols;
    Sym* insert(Sym* symbol);
    Sym* lookup(const char* name) const;
    std::string dump();
    //memory leak na hojaye
    bool delete_symbols();
    SymTab() {}
    SymTab(int level): scope_level(level) {}
};

class SymTabStack {
    public:
    std::vector<SymTab*> tables;
    int scope;
    SymTabStack(): scope(0) {
        incr_scope();
    }
    bool incr_scope();  
    bool decr_scope();
    Sym* lookup_current_scope(const char* name);
    Sym* lookup_all_scopes(const char* name);
    Sym* insert(Sym* symbol);
    std::string dump();
};