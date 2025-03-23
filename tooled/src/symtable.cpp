#include <symtable.h>

std::vector<TypeSpec*> type_list;

std::string get_primitive_name(Primitive type)
{
    char *name;
    switch (type)
    {
    case T_UCHAR:
        strcpy(name, "unsigned char");
        break;
    case T_CHAR:
        strcpy(name, "char");
        break;
    case T_USHORT:
        strcpy(name, "unsigned short");
        break;
    case T_SHORT:
        strcpy(name, "short");
        break;
    case T_UINT:
        strcpy(name, "unsigned int");
        break;
    case T_INT:
        strcpy(name, "int");
        break;
    case T_ULONG:
        strcpy(name, "unsigned long");
        break;
    case T_LONG:
        strcpy(name, "long");
        break;
    case T_FLOAT:
        strcpy(name, "float");
        break;
    case T_DOUBLE:
        strcpy(name, "double");
        break;
    case T_LDOUBLE:
        strcpy(name, "long double");
        break;
    case T_VOID:
        strcpy(name, "void");
        break;
    default:
        // error
        break;
    }
    return std::string(name);
}

unsigned int get_primitive_size(Primitive type)
{
    size_t size = 0;
    switch (type)
    {
    case T_UCHAR:
        size = 1;
        break;
    case T_CHAR:
        size = 1;
        break;
    case T_USHORT:
        size = 2;
        break;
    case T_SHORT:
        size = 2;
        break;
    case T_UINT:
        size = 4;
        break;
    case T_INT:
        size = 4;
        break;
    case T_ULONG:
        size = 8;
        break;
    case T_LONG:
        size = 8;
        break;
    case T_FLOAT:
        size = 4;
        break;
    case T_DOUBLE:
        size = 8;
        break;
    case T_LDOUBLE:
        size = 16;
        break;
    case T_VOID:
        size = 0;
        break;
    default:
        // error
        break;
    }
    return size;
}
void init_primitives()
{
    for (auto i = 0; i <= T_VOID; i++)
    {
        auto ts = new TypeSpec();
        ts->idx = i;
        ts->is_primitive = true;
        ts->is_union = false;
        ts->is_struct = false;
        ts->is_pointer = false;
        ts->size = get_primitive_size((Primitive)i);
        ts->name = get_primitive_name((Primitive)i);
        type_list.push_back(ts);
    }
}
int define_new_type(TypeSpec *ts) {
    //check if type already exists
    for(auto it = type_list.begin(); it != type_list.end(); it++)
    {
        if((*it)->name == ts->name) return (*it)->idx;
    }
    type_list.push_back(ts);
    return type_list.size() - 1;
}

std::string Type::get_name() {
    std::stringstream ss;
    //type name
    ss << spec()->name;
    if(is_array) {
        ss << " ";
        for(auto dim: dims)
        {
            if(dim == 0) ss << "[]";
            else ss << "[" << dim << "]";
        }
    }
    //functions are treated as function pointers
    else if(is_pointer()) ss << "*";
    else if(is_func)
    {
        ss << "( ";
        if(arg_count > 0)
        {
            ss << arg_ts[0].get_name();
            if(arg_count > 1) {
                for(auto it = arg_ts.begin() + 1; it != arg_ts.end(); it++) ss << ", " << it->get_name();
            }
        }
        ss << " )";
    }
    return ss.str();
}

size_t Type::get_size() {
    if(is_primitive() && !is_array && !is_func && !is_pointer()) return spec()->size;
    if(is_array)
    {
        int dimacc = 1;
        //for each dimension
        for(auto dim : dims) dimacc *= dim;
        size_t sz = 1;
        if(is_primitive()) sz = spec()->size;
        // implement struct sizes here
        return sz * dimacc;
    }
    //functions treated as function pointers
    if(is_pointer() || is_func) return WORD_SIZE;
    //implement struct sizes here
}

bool operator==(Type&t1, Type&t2) {

}
bool operator!=(Type&t1, Type&t2) {

}