%{
	#include <expr.h>
	#include <decl.h>
	#include <udtype.h>
	#include <stmt.h>
	#include <ast.h>
	#include <stdio.h>
	int yylex();
	void yyerror(const char* s);
	extern NonTerm* root;
	//type declarations
%}

%require "3.2"

%union{
	AstNode * node;
	Term * terminal;
	NonTerm* non_terminal;
	int value;
	Cnst *constant;
	StrLit *string_literal;
	Idfr* identifier;
	AssignExpr* assignment_expression;
	UnaryExpr* unary_expression;
	BinaryExpr* binary_expr;
	// uncomment these if you need specific type for any rule, right now they all become BinaryExpr with name
	// MultExpr* multiplicative_expression;
	// AddExpr* additive_expression;
	// ShiftExpr* shift_expression;
	// RelExpr* relational_expression;
	// EqExpr* equality_expression;
	// AndExpr* and_expression;
	// XorExpr* exclusive_or_expression;
	// OrExpr* inclusive_or_expression;
	// LogAndExpr* logical_and_expression;
	// LogOrExpr* logical_or_expression;
	CondExpr* conditional_expression;
	CastExpr* cast_expression;
	ConstExpr* constant_expression;
	Expr* expression;
	ArgExprList* argument_expression_list;
	TypeSpec* type_specifier;
	TypeQual* type_qualifier;
	SpecQualList* specifier_qualifier_list;
	StorageClassSpec* storage_class_specifier;
	DeclnSpecs* declaration_specifiers;
	InitDeclList* init_declarator_list;
	InitDecl* init_declarator;
	//masti
	Decln* declaration;
	Decl* declarator;
	Initializer* initializer;
	TypeQualList* type_qualifier_list;
	Ptr* pointer;
	DirDecl* direct_declarator;
	IdfrList* identifier_list;
	InitializerList* initializer_list;
	ParamDecln* parameter_declaration;
	ParamList* parameter_list;
	AbsDecl* abstract_declarator;
	DirAbsDecl* direct_abstract_declarator;
	DeclnList* declaration_list;
	Enumtr* enumerator;
	EnumtrList* enumerator_list;
	EnumSpec* enum_specifier;
	Stmt* statement;
	StmtList* statement_list;
	ItrStmt* iteration_statement;
	JmpStmt* jump_statement;
	SelStmt* selection_statement;
	CompStmt* compound_statement;
	LabStmt* labeled_statement;
	ExprStmt* expression_statement;
	FuncDef* function_definition;
	TypeName* type_name;
	StructDecl* struct_declarator;
	StructDeclList* struct_declarator_list;
	StructDecln* struct_declaration;
	StructDeclnList* struct_declaration_list;
	StructOrUnionSpec* struct_or_union_specifier;
}

%token <terminal> '.' 
%token <terminal> '(' ')' '[' ']' ',' '+' '-' '!' '&' '*' '~' '/' '%'
%token <terminal> '<' '>' '^' '|' ':' '?' ';' '{' '}'
%token <terminal> '='

%token <identifier> IDENTIFIER 
%token <constant> CONSTANT 
%token <string_literal> STRING_LITERAL 
%token <terminal> SIZEOF
//incrementally making things terminal when i need shit from them lol
%token <terminal> INC_OP DEC_OP PTR_OP 
%token <terminal> LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token <terminal> AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token <terminal> SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token <terminal> XOR_ASSIGN OR_ASSIGN TYPE_NAME

%token <storage_class_specifier> TYPEDEF EXTERN STATIC AUTO REGISTER
%token <type_specifier> CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE VOID
%token <type_qualifier> CONST VOLATILE
%token <terminal> STRUCT UNION ENUM ELLIPSIS

%token <node> CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%type <expression> expression
%type <expression> primary_expression
%type <expression> postfix_expression
%type <expression> unary_expression
%type <expression> cast_expression
%type <expression> binary_expression
%type <expression> logical_and_expression
%type <expression> logical_or_expression 
%type <expression> relational_expression
%type <expression> shift_expression 
%type <expression> inclusive_or_expression 
%type <expression> exclusive_or_expression
%type <expression> additive_expression
%type <expression> multiplicative_expression
%type <expression> equality_expression  
%type <expression> and_expression
%type <expression> conditional_expression
%type <expression> assignment_expression
%type <expression> constant_expression
%type <argument_expression_list> argument_expression_list
%type <terminal> assignment_operator unary_operator
%type <type_specifier> type_specifier
%type <storage_class_specifier> storage_class_specifier
%type <type_qualifier> type_qualifier
%type <specifier_qualifier_list> specifier_qualifier_list
%type <declaration_specifiers> declaration_specifiers
%type <init_declarator_list> init_declarator_list
%type <init_declarator> init_declarator
%type <declaration> declaration
%type <declarator> declarator
%type <initializer> initializer
%type <type_qualifier_list> type_qualifier_list
%type <pointer> pointer
%type <direct_declarator> direct_declarator
%type <identifier_list> identifier_list
%type <initializer_list> initializer_list
%type <parameter_declaration> parameter_declaration
%type <parameter_list> parameter_list
%type <direct_abstract_declarator> direct_abstract_declarator
%type <abstract_declarator> abstract_declarator
%type <declaration_list> declaration_list
%type <enumerator> enumerator
%type <enumerator_list> enumerator_list
%type <enum_specifier> enum_specifier
%type <statement> statement
%type <statement_list> statement_list
%type <statement> compound_statement
%type <statement> jump_statement
%type <statement> labeled_statement
%type <statement> iteration_statement
%type <statement> selection_statement
%type <statement> expression_statement
%type <non_terminal> external_declaration
%type <function_definition> function_definition
%type <type_name> type_name
%type <terminal> struct_or_union
%type <struct_declarator> struct_declarator
%type <struct_declarator_list> struct_declarator_list
%type <struct_declaration> struct_declaration
%type <struct_declaration_list> struct_declaration_list
%type <struct_or_union_specifier> struct_or_union_specifier


%start translation_unit
%%

primary_expression
	: IDENTIFIER {$$ = gen_prexpr_idfr($1);}
	| CONSTANT {$$ = gen_prexpr_cnst($1);}
	| STRING_LITERAL {$$ = gen_prexpr_strlit($1);}
	| '(' expression ')' {$$ = $2;}
	;

postfix_expression
	: primary_expression {$$ = $1;}
	| postfix_expression '[' expression ']' {$$ = gen_postfix_arr($1, $3);}
	| postfix_expression '(' ')' {$$ = gen_postfix_voidfun($1);}
	| postfix_expression '(' argument_expression_list ')'  {$$ = gen_postfix_fun($1, $3);}
	| postfix_expression '.' IDENTIFIER {$$ = gen_postfix_struni($1, $2, $3);}
	| postfix_expression PTR_OP IDENTIFIER {$$ = gen_postfix_struni($1, $2, $3);}
	| postfix_expression INC_OP {$$ = gen_postfix_idop($1, $2);}
	| postfix_expression DEC_OP {$$ = gen_postfix_idop($1, $2);}
	;

argument_expression_list
	: assignment_expression {$$ = gen_argexprlist(NULL, $1);}
	| argument_expression_list ',' assignment_expression {$$ = gen_argexprlist($1, $3);}
	;

unary_expression
	: postfix_expression {$$ = $1;}
	| INC_OP unary_expression {$$ = gen_unary_expr($1, $2);}
	| DEC_OP unary_expression {$$ = gen_unary_expr($1, $2);}
	| unary_operator cast_expression // implement when implemented cast expr {$$ = gen_unary_cast($1, $2);}
	| SIZEOF unary_expression {$$ = gen_unary_expr($1, $2);}
	| SIZEOF '(' type_name ')' // {$$ = gen_unary_expr($1, $2);}
	;

unary_operator
	: '&' {$$ = $1;}
	| '*' {$$ = $1;}
	| '+' {$$ = $1;}
	| '-' {$$ = $1;}
	| '~' {$$ = $1;}
	| '!' {$$ = $1;}
	;

cast_expression
	: unary_expression {$$ = $1;}
	| '(' type_name ')' cast_expression //do when you do type_name {$$ = gen_cast_expr($1, $3);}
	;

multiplicative_expression
	: cast_expression {$$ = $1;}
	| multiplicative_expression '*' cast_expression {$$ = gen_binary_expr($1, $2, $3, "multiplicative_expression");}
	| multiplicative_expression '/' cast_expression {$$ = gen_binary_expr($1, $2, $3, "multiplicative_expression");}
	| multiplicative_expression '%' cast_expression {$$ = gen_binary_expr($1, $2, $3, "multiplicative_expression");}
	;

additive_expression
	: multiplicative_expression {$$ = $1;}
	| additive_expression '+' multiplicative_expression {$$ = gen_binary_expr($1, $2, $3, "additive_expression");}
	| additive_expression '-' multiplicative_expression {$$ = gen_binary_expr($1, $2, $3, "additive_expression");}
	;

shift_expression
	: additive_expression {$$ = $1;}
	| shift_expression LEFT_OP additive_expression {$$ = gen_binary_expr($1, $2, $3, "shift_expression");}
	| shift_expression RIGHT_OP additive_expression {$$ = gen_binary_expr($1, $2, $3, "shift_expression");}
	;

relational_expression
	: shift_expression {$$ = $1;}
	| relational_expression '<' shift_expression {$$ = gen_binary_expr($1, $2, $3, "relative_expression");}
	| relational_expression '>' shift_expression {$$ = gen_binary_expr($1, $2, $3, "relative_expression");}
	| relational_expression LE_OP shift_expression {$$ = gen_binary_expr($1, $2, $3, "relative_expression");}
	| relational_expression GE_OP shift_expression {$$ = gen_binary_expr($1, $2, $3, "relative_expression");}
	;

equality_expression
	: relational_expression {$$ = $1;}
	| equality_expression EQ_OP relational_expression {$$ = gen_binary_expr($1, $2, $3, "equality_expression");}
	| equality_expression NE_OP relational_expression {$$ = gen_binary_expr($1, $2, $3, "equality_expression");}
	;

and_expression
	: equality_expression {$$ = $1;}
	| and_expression '&' equality_expression {$$ = gen_binary_expr($1, $2, $3, "and_expression");}
	;

exclusive_or_expression
	: and_expression {$$ = $1;}
	| exclusive_or_expression '^' and_expression {$$ = gen_binary_expr($1, $2, $3, "xor_expression");}
	;

inclusive_or_expression
	: exclusive_or_expression {$$ = $1;}
	| inclusive_or_expression '|' exclusive_or_expression {$$ = gen_binary_expr($1, $2, $3, "or_expression");}
	;

logical_and_expression
	: inclusive_or_expression {$$ = $1;}
	| logical_and_expression AND_OP inclusive_or_expression {$$ = gen_binary_expr($1, $2, $3, "logical_and_expression");}
	;

logical_or_expression
	: logical_and_expression {$$ = $1;}
	| logical_or_expression OR_OP logical_and_expression {$$ = gen_binary_expr($1, $2, $3, "logical_or_expression");}
	;

conditional_expression
	: logical_or_expression {$$ = $1;}
	| logical_or_expression '?' expression ':' conditional_expression {$$ = gen_cond_expr($1, $3, $5, "?:");}
	;

assignment_expression
	: conditional_expression {$$ = $1;}
	| unary_expression assignment_operator assignment_expression {$$ = gen_assign_expr($1, $2, $3);}
	;

assignment_operator
	: '=' {$$ = $1;}
	| MUL_ASSIGN {$$ = $1;}
	| DIV_ASSIGN {$$ = $1;}
	| MOD_ASSIGN {$$ = $1;}
	| ADD_ASSIGN {$$ = $1;}
	| SUB_ASSIGN {$$ = $1;}
	| LEFT_ASSIGN {$$ = $1;}
	| RIGHT_ASSIGN {$$ = $1;}
	| AND_ASSIGN {$$ = $1;}
	| XOR_ASSIGN {$$ = $1;}
	| OR_ASSIGN {$$ = $1;}
	;

expression
	: assignment_expression {$$ = $1;}
	| expression ',' assignment_expression {$$ = gen_toplevel_expr($1, $3);}
	;

//stupid def but makes sense
constant_expression
	: conditional_expression {$$ = $1;}
	;

declaration
	: declaration_specifiers ';' {$$ = gen_decln($1, NULL);}
	| declaration_specifiers init_declarator_list ';' {$$ = gen_decln($1, $2);}
	;

declaration_specifiers
	: storage_class_specifier {$$ = gen_declnspecs(NULL, NULL, NULL, $1);}
	| storage_class_specifier declaration_specifiers {$$ = gen_declnspecs($2, NULL, NULL, $1);}
	| type_specifier {$$ = gen_declnspecs(NULL, $1, NULL, NULL);}
	| type_specifier declaration_specifiers {$$ = gen_declnspecs($2, $1, NULL, NULL);}
	| type_qualifier {$$ = gen_declnspecs(NULL, NULL, $1, NULL);}
	| type_qualifier declaration_specifiers {$$ = gen_declnspecs($2, NULL, $1, NULL);}
	;

init_declarator_list
	: init_declarator {$$ = gen_initdecl_list(NULL, $1);}
	| init_declarator_list ',' init_declarator {$$ = gen_initdecl_list($1, $3);}
	;

init_declarator
	: declarator {$$ = gen_initdecl($1, NULL);}
	| declarator '=' initializer {$$ = gen_initdecl($1, $3);}
	;

storage_class_specifier
	: TYPEDEF {$$ = $1;}
	| EXTERN {$$ = $1;}
	| STATIC {$$ = $1;}
	| AUTO {$$ = $1;}
	| REGISTER {$$ = $1;}
	;

type_specifier
	: VOID {$$ = $1;}
	| CHAR {$$ = $1;}
	| SHORT {$$ = $1;}
	| INT {$$ = $1;}
	| LONG {$$ = $1;}
	| FLOAT {$$ = $1;}
	| DOUBLE {$$ = $1;}
	| SIGNED {$$ = $1;}
	| UNSIGNED {$$ = $1;}
	| struct_or_union_specifier 
	| enum_specifier 
	| TYPE_NAME 
	;

struct_or_union_specifier
	: struct_or_union IDENTIFIER '{' struct_declaration_list '}' {$$ = gen_structorunion_spec($1->name.c_str(), $2, $4);}
	| struct_or_union '{' struct_declaration_list '}' {$$ = gen_structorunion_spec($1->name.c_str(), NULL, $3);}
	| struct_or_union IDENTIFIER {$$ = gen_structorunion_spec($1->name.c_str(), $2, NULL);}
	;

struct_or_union
	: STRUCT {$$ = $1;}
	| UNION {$$ = $1;}
	;

struct_declaration_list
	: struct_declaration {$$ = gen_structdeclnlist(NULL, $1);}
	| struct_declaration_list struct_declaration {$$ = gen_structdeclnlist($1, $2);}
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list ';' {$$ = gen_structdecln($1, $2);}
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list {$$ = gen_specqual_list($2, $1, NULL);}
	| type_specifier {$$ = gen_specqual_list(NULL, $1, NULL);}
	| type_qualifier specifier_qualifier_list {$$ = gen_specqual_list($2, NULL, $1);}
	| type_qualifier {$$ = gen_specqual_list(NULL, NULL, $1);}
	;

struct_declarator_list
	: struct_declarator {$$ = gen_structdecl_list(NULL, $1);}
	| struct_declarator_list ',' struct_declarator {$$ = gen_structdecl_list($1, $3);}
	;

struct_declarator
	: declarator {$$ = gen_structdecl($1, NULL);}
	| ':' constant_expression {$$ = gen_structdecl(NULL, $2);}
	| declarator ':' constant_expression {$$ = gen_structdecl($1, $3);}
	;

enum_specifier
	: ENUM '{' enumerator_list '}' {$$ = gen_enumspec(NULL, $3);}
	| ENUM IDENTIFIER '{' enumerator_list '}' {$$ = gen_enumspec($2, $4);}
	| ENUM IDENTIFIER {$$ = gen_enumspec($2, NULL);}
	;

enumerator_list
	: enumerator {$$ = gen_enumtrlist(NULL, $1);}
	| enumerator_list ',' enumerator {$$ = gen_enumtrlist($1, $3);}
	;

enumerator
	: IDENTIFIER {$$ = gen_enumtr($1, NULL);}
	| IDENTIFIER '=' constant_expression {$$ = gen_enumtr($1, $3);}
	;

type_qualifier
	: CONST {$$ = $1;}
	| VOLATILE {$$ = $1;}
	;

declarator
	: pointer direct_declarator {$$ = gen_decl($2, $1);}
	| direct_declarator {$$ = gen_decl($1, NULL);}
	;

direct_declarator
	: IDENTIFIER {$$ = gen_dirdecl_idfr($1);}
	| '(' declarator ')' {$$ = gen_dirdecl_decl($2);}
	| direct_declarator '[' constant_expression ']' {$$ = gen_dirdecl_arr($1, $3);}
	| direct_declarator '[' ']' {$$ = gen_dirdecl_arr($1, NULL);}
	| direct_declarator '(' parameter_list ')' {$$ = gen_dirdecl_func($1, $3, NULL);}
	| direct_declarator '(' identifier_list ')' {$$ = gen_dirdecl_func($1, NULL, $3);}
	| direct_declarator '(' ')' {$$ = gen_dirdecl_func($1, NULL, NULL);}
	;

pointer
	: '*' {$$ = gen_ptr(NULL, NULL);}
	| '*' type_qualifier_list {$$ = gen_ptr($2, NULL);}
	| '*' pointer {$$ = gen_ptr(NULL, $2);}
	| '*' type_qualifier_list pointer {$$ = gen_ptr($2, $3);}
	;

type_qualifier_list
	: type_qualifier {$$ = gen_typequal_list(NULL, $1);}
	| type_qualifier_list type_qualifier {$$ = gen_typequal_list($1, $2);}
	;


//yeah i cant do ts
// parameter_type_list
// 	: parameter_list
// 	| parameter_list ',' ELLIPSIS
// 	;

parameter_list
	: parameter_declaration {$$ = gen_paramlist(NULL, $1);}
	| parameter_list ',' parameter_declaration {$$ = gen_paramlist($1, $3);}
	;

parameter_declaration
	: declaration_specifiers declarator {$$ = gen_paramdecln($1, NULL, $2);}
	| declaration_specifiers abstract_declarator {$$ = gen_paramdecln($1, $2, NULL);}
	| declaration_specifiers {$$ = gen_paramdecln($1, NULL, NULL);}
	;

identifier_list
	: IDENTIFIER {$$ = gen_idfrlist(NULL, $1);}
	| identifier_list ',' IDENTIFIER {$$ = gen_idfrlist($1, $3);}
	; 

type_name
	: specifier_qualifier_list 
	| specifier_qualifier_list abstract_declarator
	;

abstract_declarator
	: pointer {$$ = gen_absdecl(NULL, $1);}
	| direct_abstract_declarator {$$ = gen_absdecl($1, NULL);}
	| pointer direct_abstract_declarator {$$ = gen_absdecl($2, $1);}
	;

direct_abstract_declarator
	: '(' abstract_declarator ')' {$$ = gen_dirabsdecl_decl($2);}
	| '[' ']' {$$ = gen_dirabsdecl_arr(NULL, NULL);}
	| '[' constant_expression ']' {$$ = gen_dirabsdecl_arr(NULL, $2);}
	| direct_abstract_declarator '[' ']' {$$ = gen_dirabsdecl_arr($1, NULL);}
	| direct_abstract_declarator '[' constant_expression ']' {$$ = gen_dirabsdecl_arr($1, $3);}
	| '(' ')' {$$ = gen_dirabsdecl_func(NULL, NULL);}
	| '(' parameter_list ')' {$$ = gen_dirabsdecl_func(NULL, $2);}
	| direct_abstract_declarator '(' ')' {$$ = gen_dirabsdecl_func($1, NULL);}
	| direct_abstract_declarator '(' parameter_list ')' {$$ = gen_dirabsdecl_func($1, $3);}
	;

initializer
	: assignment_expression {$$ = gen_initializer($1, NULL);}
	| '{' initializer_list '}' {$$ = gen_initializer(NULL, $2);}
	| '{' initializer_list ',' '}' {$$ = gen_initializer(NULL, $2);}
	;

initializer_list
	: initializer {$$ = gen_initializerlist(NULL, $1);}
	| initializer_list ',' initializer {$$ = gen_initializerlist($1, $3);}
	;

statement
	: labeled_statement {$$ = $1;} 
	| compound_statement {$$ = $1;}
	| expression_statement {$$ = $1;}
	| selection_statement {$$ = $1;}
	| iteration_statement {$$ = $1;}
	| jump_statement {$$ = $1;}
	;

labeled_statement
	: IDENTIFIER ':' statement {$$ = gen_labstmt($1, $3);}
	| CASE constant_expression ':' statement {$$ = gen_labstmt_case($2, $4);}
	| DEFAULT ':' statement {$$ = gen_labstmt_case(NULL, $3);}
	; 

compound_statement
	: '{' '}' {$$ = gen_compstmt(NULL, NULL);}
	| '{' statement_list '}' {$$ = gen_compstmt(NULL, $2);}
	| '{' declaration_list '}' {$$ = gen_compstmt($2, NULL);}
	| '{' declaration_list statement_list '}' {$$ = gen_compstmt($2, $3);}
	;

declaration_list
	: declaration {$$ = gen_declnlist(NULL, $1);}
	| declaration_list declaration {$$ = gen_declnlist($1, $2);}
	;

statement_list
	: statement { $$ = gen_stmtlist(NULL, $1);}
	| statement_list statement {$$ = gen_stmtlist($1, $2);}
	;

expression_statement
	: ';' {$$ = gen_exprstmt(NULL);}
	| expression ';' {$$ = gen_exprstmt($1);}
	;

selection_statement
	: IF '(' expression ')' statement {$$ = gen_selstmt_if($3, $5, NULL);}
	| IF '(' expression ')' statement ELSE statement {$$ = gen_selstmt_if($3, $5, $7);}
	| SWITCH '(' expression ')' statement {$$ = gen_selstmt_switch($3, $5);}
	;

iteration_statement
	: WHILE '(' expression ')' statement {$$ = gen_itrstmt_while(ISK_WHILE, $3, $5);}
	| DO statement WHILE '(' expression ')' ';' {$$ = gen_itrstmt_while(ISK_DOWHILE, $5, $2);}
	| FOR '(' expression_statement expression_statement ')' statement {$$ = gen_itrstmt_for($3, $4, NULL, $6);}
	| FOR '(' expression_statement expression_statement expression ')' statement {$$ = gen_itrstmt_for($3, $4, $5, $7);}
	;

jump_statement
	: GOTO IDENTIFIER ';' {$$ = gen_jmpstmt_goto($2);}
	| CONTINUE ';' {$$ = gen_jmpstmt(JSK_CONTINUE);}
	| BREAK ';' {$$ = gen_jmpstmt(JSK_BREAK);}
	| RETURN ';' {$$ = gen_jmpstmt(JSK_RETURN);}
	| RETURN expression ';' {$$ = gen_jmpstmt_return($2);}
	;

translation_unit
	: external_declaration {root->add_children(1, $1);}
	| translation_unit external_declaration {root->add_children(1, $2);}
	;

external_declaration
	: function_definition {$$ = $1;}
	| declaration {$$ = $1;}
	;

function_definition
	: declaration_specifiers declarator declaration_list compound_statement {$$ = gen_funcdef($1, $2, $3, $4);}
	| declaration_specifiers declarator compound_statement {$$ = gen_funcdef($1, $2, NULL, $3);}
	| declarator declaration_list compound_statement {$$ = gen_funcdef(NULL, $1, $2, $3);}
	| declarator compound_statement {$$ = gen_funcdef(NULL, $1, NULL, $2);}
	;

%%
#include <expr.h>
#include <decl.h>
#include <udtype.h>
#include <stmt.h>
#include <ast.h>
#include <stdio.h>

extern char yytext[];
extern int column;

void yyerror(const char *s)
// char *s;
{
	fflush(stdout);
	printf("\n%*s\n%*s\n", column, "^", column, s);
}