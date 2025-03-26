D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			[Ee][+-]?{D}+
FS			(f|F|l|L)
IS			(u|U|l|L)*

%{
#include <stdio.h>
#include <ast.h>
#include <expr.h>
#include <decl.h>
#include "y.tab.h"


void count();
void comment();
int check_type();
%}

%%
"/*"			{ comment(); }

"auto"			{ yylval.storage_class_specifier = gen_storagecl_spec(AUTO, 0, 0); count(); return(AUTO); }
"break"			{ count(); return(BREAK); }
"case"			{ count(); return(CASE); }
"char"			{ yylval.type_specifier = gen_typespec(CHAR, 0, 0) ;count(); return(CHAR); }
"const"			{ yylval.type_qualifier = gen_typequal(CONST, 0, 0) ;count(); return(CONST); }
"continue"		{ count(); return(CONTINUE); }
"default"		{ count(); return(DEFAULT); }
"do"			{ count(); return(DO); }
"double"		{ count(); return(DOUBLE); }
"else"			{ count(); return(ELSE); }
"enum"			{ count(); return(ENUM); }
"extern"		{ yylval.storage_class_specifier = gen_storagecl_spec(EXTERN, 0, 0); count(); return(EXTERN); }
"float"			{ yylval.type_specifier = gen_typespec(FLOAT, 0, 0) ;count(); return(FLOAT); }
"for"			{ count(); return(FOR); }
"goto"			{ count(); return(GOTO); }
"if"			{ count(); return(IF); }
"int"			{ yylval.type_specifier = gen_typespec(INT, 0, 0) ;count(); return(INT); }
"long"			{ yylval.type_specifier = gen_typespec(LONG, 0, 0) ;count(); return(LONG); }
"register"		{ yylval.storage_class_specifier = gen_storagecl_spec(REGISTER, 0, 0); count(); return(REGISTER); }
"return"		{ count(); return(RETURN); }
"short"			{ yylval.type_specifier = gen_typespec(SHORT, 0, 0) ;count(); return(SHORT); }
"signed"		{ yylval.type_specifier = gen_typespec(SIGNED, 0, 0) ;count(); return(SIGNED); }
"sizeof"		{ count(); return(SIZEOF); }
"static"		{ yylval.storage_class_specifier = gen_storagecl_spec(STATIC, 0, 0); count(); return(STATIC); }
"struct"		{ count(); return(STRUCT); }
"switch"		{ count(); return(SWITCH); }
"typedef"		{ yylval.storage_class_specifier = gen_storagecl_spec(TYPEDEF, 0, 0); count(); return(TYPEDEF); }
"union"			{ count(); return(UNION); }
"unsigned"		{ yylval.type_specifier = gen_typespec(UNSIGNED, 0, 0) ; count(); return(UNSIGNED); }
"void"			{ yylval.type_specifier = gen_typespec(VOID, 0, 0) ; count(); return(VOID); }
"volatile"		{ yylval.type_qualifier = gen_typequal(VOLATILE, 0, 0) ; count(); return(VOLATILE); }
"while"			{ count(); return(WHILE); }

{L}({L}|{D})*		{ count(); return(check_type()); }

0[xX]{H}+{IS}?		{ count(); return(CONSTANT); }
0{D}+{IS}?		{ count(); return(CONSTANT); }
{D}+{IS}?		{ count(); return(CONSTANT); }
L?'(\\.|[^\\'])+'	{ count(); return(CONSTANT); }

{D}+{E}{FS}?		{ count(); return(CONSTANT); }
{D}*"."{D}+({E})?{FS}?	{ count(); return(CONSTANT); }
{D}+"."{D}*({E})?{FS}?	{ count(); return(CONSTANT); }

L?\"(\\.|[^\\"])*\"	{ count(); return(STRING_LITERAL); }

">>="			{yylval.terminal = new Term(">>=", NULL); count(); return(RIGHT_ASSIGN); }
"<<="			{yylval.terminal = new Term("<<=", NULL); count(); return(LEFT_ASSIGN); }
"+="			{yylval.terminal = new Term("+=", NULL); count(); return(ADD_ASSIGN); }
"-="			{yylval.terminal = new Term("-=", NULL); count(); return(SUB_ASSIGN); }
"*="			{yylval.terminal = new Term("*=", NULL); count(); return(MUL_ASSIGN); }
"/="			{yylval.terminal = new Term("/=", NULL); count(); return(DIV_ASSIGN); }
"%="			{yylval.terminal = new Term("%=", NULL); count(); return(MOD_ASSIGN); }
"&="			{yylval.terminal = new Term("&=", NULL); count(); return(AND_ASSIGN); }
"^="			{yylval.terminal = new Term("^=", NULL); count(); return(XOR_ASSIGN); }
"|="			{yylval.terminal = new Term("|=", NULL); count(); return(OR_ASSIGN); }
">>"			{yylval.terminal = new Term(">>", NULL); count(); return(RIGHT_OP); }
"<<"			{yylval.terminal = new Term("<<", NULL); count(); return(LEFT_OP); }
"++"			{yylval.terminal = new Term("++", NULL); count(); return(INC_OP); }
"--"			{yylval.terminal = new Term("--", NULL); count(); return(DEC_OP); }
"->"			{yylval.terminal = new Term("->", NULL); count(); return(PTR_OP); }
"&&"			{yylval.terminal = new Term("&&", NULL); count(); return(AND_OP); }
"||"			{yylval.terminal = new Term("||", NULL); count(); return(OR_OP); }
"<="			{yylval.terminal = new Term("<=", NULL); count(); return(LE_OP); }
">="			{yylval.terminal = new Term(">=", NULL); count(); return(GE_OP); }
"=="			{yylval.terminal = new Term("==", NULL); count(); return(EQ_OP); }
"!="			{yylval.terminal = new Term("!=", NULL); count(); return(NE_OP); }
";"				{yylval.terminal = new Term(";", NULL); count(); return(';'); }
("{"|"<%")		{yylval.terminal = new Term("{", NULL); count(); return('{'); }
("}"|"%>")		{yylval.terminal = new Term("}", NULL); count(); return('}'); }
","				{yylval.terminal = new Term(",", NULL); count(); return(','); }
":"				{yylval.terminal = new Term(":", NULL); count(); return(':'); }
"="				{yylval.terminal = new Term("=", NULL); count(); return('='); }
"("				{yylval.terminal = new Term("(", NULL); count(); return('('); }
")"				{yylval.terminal = new Term(")", NULL); count(); return(')'); }
("["|"<:")		{yylval.terminal = new Term("[", NULL); count(); return('['); }
("]"|":>")		{yylval.terminal = new Term("]", NULL); count(); return(']'); }
"."				{yylval.terminal = new Term(".", NULL); count(); return('.'); }
"&"				{yylval.terminal = new Term("&", NULL);count(); return('&'); }
"!"				{yylval.terminal = new Term("!", NULL);count(); return('!'); }
"~"				{yylval.terminal = new Term("~", NULL);count(); return('~'); }
"-"				{yylval.terminal = new Term("-", NULL);count(); return('-'); }
"+"				{yylval.terminal = new Term("+", NULL);count(); return('+'); }
"*"				{yylval.terminal = new Term("*", NULL);count(); return('*'); }
"/"				{yylval.terminal = new Term("/", NULL);count(); return('/'); }
"%"				{yylval.terminal = new Term("%", NULL);count(); return('%'); }
"<"				{yylval.terminal = new Term("<", NULL);count(); return('<'); }
">"				{yylval.terminal = new Term(">", NULL);count(); return('>'); }
"^"				{yylval.terminal = new Term("^", NULL);count(); return('^'); }
"|"				{yylval.terminal = new Term("|", NULL);count(); return('|'); }
"?"				{yylval.terminal = new Term("?", NULL);count(); return('?'); }

[ \t\v\n\f]		{ count(); }
.			{ /* ignore bad characters */ }

%%

#include <ast.h>

int yywrap()
{
	return(1);
}


void comment()
{
	char c, c1;

loop:
	while ((c = yyinput()) != '*' && c != 0)
		putchar(c);

	if ((c1 = yyinput()) != '/' && c != 0)
	{
		unput(c1);
		goto loop;
	}

	if (c != 0)
		putchar(c1);
}


int column = 0;

void count()
{
	int i;

	for (i = 0; yytext[i] != '\0'; i++)
		if (yytext[i] == '\n')
			column = 0;
		else if (yytext[i] == '\t')
			column += 8 - (column % 8);
		else
			column++;

	ECHO;
}


int check_type()
{
/*
* pseudo code --- this is what it should check
*
*	if (yytext == type_name)
*		return(TYPE_NAME);
*
*	return(IDENTIFIER);
*/

/*
*	it actually will only return IDENTIFIER
*/

	return(IDENTIFIER);
}