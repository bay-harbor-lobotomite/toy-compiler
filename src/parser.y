%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char *s);

%}

%union {
    char* str;
}

%token <str> IDENTIFIER NUMBER STRING
%token L_PAREN R_PAREN L_SQUARE R_SQUARE L_BRACE R_BRACE
%token PLUS MINUS STAR SLASH
%token PERIOD COMMA SEMICOLON
%token BANG B_EQ EQ EQ_EQ LE LE_EQ GR GR_EQ BIT_AND BIT_OR BOOL_OR BOOL_AND
%token ELSE FALSE FOR IF PRINT RETURN SUPER THIS TRUE WHILE INT CHAR STRUCT END_OF_FILE

%%


program:
    statement_list END_OF_FILE { printf("Parsing complete.\n"); }
    ;

statement_list:
    statement
    | statement_list statement
    ;

statement:
    expression SEMICOLON { printf("Parsed an expression.\n"); }
    | assignment SEMICOLON { printf("Parsed an assignment.\n"); }
    ;

assignment:
    IDENTIFIER EQ expression { printf("Assignment: %s = expr\n", $1); }
    ;

expression:
    expression PLUS expression { printf("Addition\n"); }
    | expression MINUS expression { printf("Subtraction\n"); }
    | expression STAR expression { printf("Multiplication\n"); }
    | expression SLASH expression { printf("Division\n"); }
    | L_PAREN expression R_PAREN
    | NUMBER { printf("Number: %s\n", $1); }
    | IDENTIFIER { printf("Identifier: %s\n", $1); }
    ;
%%
void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main() {
    return yyparse();
}