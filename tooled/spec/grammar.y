%{
	#include <expr.h>
	#include <decl.h>
	#include <ast.h>
	#include <stdio.h>
	int yylex();
	void yyerror(const char* s);
	extern AstNode* root;
	//type declarations
%}

%require "3.2"

%union{
	AstNode * node;
	Term * terminal;
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
	DeclSpecs* declaration_specifiers;
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
%token STRUCT UNION ENUM ELLIPSIS

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
	: storage_class_specifier {$$ = gen_declspecs(NULL, NULL, NULL, $1);}
	| storage_class_specifier declaration_specifiers {$$ = gen_declspecs($2, NULL, NULL, $1);}
	| type_specifier {$$ = gen_declspecs(NULL, $1, NULL, NULL);}
	| type_specifier declaration_specifiers {$$ = gen_declspecs($2, $1, NULL, NULL);}
	| type_qualifier {$$ = gen_declspecs(NULL, NULL, $1, NULL);}
	| type_qualifier declaration_specifiers {$$ = gen_declspecs($2, NULL, $1, NULL);}
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
	: struct_or_union IDENTIFIER '{' struct_declaration_list '}'
	| struct_or_union '{' struct_declaration_list '}'
	| struct_or_union IDENTIFIER
	;

struct_or_union
	: STRUCT
	| UNION
	;

struct_declaration_list
	: struct_declaration
	| struct_declaration_list struct_declaration
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list ';'
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list {$$ = gen_specqual_list($2, $1, NULL);}
	| type_specifier {$$ = gen_specqual_list(NULL, $1, NULL);}
	| type_qualifier specifier_qualifier_list {$$ = gen_specqual_list($2, NULL, $1);}
	| type_qualifier {$$ = gen_specqual_list(NULL, NULL, $1);}
	;

struct_declarator_list
	: struct_declarator
	| struct_declarator_list ',' struct_declarator
	;

struct_declarator
	: declarator
	| ':' constant_expression
	| declarator ':' constant_expression
	;

enum_specifier
	: ENUM '{' enumerator_list '}'
	| ENUM IDENTIFIER '{' enumerator_list '}'
	| ENUM IDENTIFIER
	;

enumerator_list
	: enumerator
	| enumerator_list ',' enumerator
	;

enumerator
	: IDENTIFIER
	| IDENTIFIER '=' constant_expression
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
	: IDENTIFIER
	| '(' declarator ')'
	| direct_declarator '[' constant_expression ']'
	| direct_declarator '[' ']'
	| direct_declarator '(' parameter_list ')'
	| direct_declarator '(' identifier_list ')'
	| direct_declarator '(' ')'
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
	: parameter_declaration
	| parameter_list ',' parameter_declaration
	;

parameter_declaration
	: declaration_specifiers declarator
	| declaration_specifiers abstract_declarator 
	| declaration_specifiers
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
	: pointer
	| direct_abstract_declarator
	| pointer direct_abstract_declarator
	;

direct_abstract_declarator
	: '(' abstract_declarator ')'
	| '[' ']'
	| '[' constant_expression ']'
	| direct_abstract_declarator '[' ']'
	| direct_abstract_declarator '[' constant_expression ']'
	| '(' ')'
	| '(' parameter_list ')'
	| direct_abstract_declarator '(' ')'
	| direct_abstract_declarator '(' parameter_list ')'
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
	: labeled_statement
	| compound_statement
	| expression_statement
	| selection_statement
	| iteration_statement
	| jump_statement
	;

labeled_statement
	: IDENTIFIER ':' statement
	| CASE constant_expression ':' statement
	| DEFAULT ':' statement
	;

compound_statement
	: '{' '}'
	| '{' statement_list '}'
	| '{' declaration_list '}'
	| '{' declaration_list statement_list '}'
	;

declaration_list
	: declaration
	| declaration_list declaration
	;

statement_list
	: statement
	| statement_list statement
	;

expression_statement
	: ';'
	| expression ';'
	;

selection_statement
	: IF '(' expression ')' statement
	| IF '(' expression ')' statement ELSE statement
	| SWITCH '(' expression ')' statement
	;

iteration_statement
	: WHILE '(' expression ')' statement
	| DO statement WHILE '(' expression ')' ';'
	| FOR '(' expression_statement expression_statement ')' statement
	| FOR '(' expression_statement expression_statement expression ')' statement
	;

jump_statement
	: GOTO IDENTIFIER ';'
	| CONTINUE ';'
	| BREAK ';'
	| RETURN ';'
	| RETURN expression ';'
	;

translation_unit
	: external_declaration
	| translation_unit external_declaration
	;

external_declaration
	: function_definition
	| declaration
	;

function_definition
	: declaration_specifiers declarator declaration_list compound_statement
	| declaration_specifiers declarator compound_statement
	| declarator declaration_list compound_statement
	| declarator compound_statement
	;

%%
#include <expr.h>
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