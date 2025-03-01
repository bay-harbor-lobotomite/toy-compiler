/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IDENTIFIER = 258,              /* IDENTIFIER  */
    NUMBER = 259,                  /* NUMBER  */
    STRING = 260,                  /* STRING  */
    L_PAREN = 261,                 /* L_PAREN  */
    R_PAREN = 262,                 /* R_PAREN  */
    L_SQUARE = 263,                /* L_SQUARE  */
    R_SQUARE = 264,                /* R_SQUARE  */
    L_BRACE = 265,                 /* L_BRACE  */
    R_BRACE = 266,                 /* R_BRACE  */
    PLUS = 267,                    /* PLUS  */
    MINUS = 268,                   /* MINUS  */
    STAR = 269,                    /* STAR  */
    SLASH = 270,                   /* SLASH  */
    PERIOD = 271,                  /* PERIOD  */
    COMMA = 272,                   /* COMMA  */
    SEMICOLON = 273,               /* SEMICOLON  */
    BANG = 274,                    /* BANG  */
    B_EQ = 275,                    /* B_EQ  */
    EQ = 276,                      /* EQ  */
    EQ_EQ = 277,                   /* EQ_EQ  */
    LE = 278,                      /* LE  */
    LE_EQ = 279,                   /* LE_EQ  */
    GR = 280,                      /* GR  */
    GR_EQ = 281,                   /* GR_EQ  */
    BIT_AND = 282,                 /* BIT_AND  */
    BIT_OR = 283,                  /* BIT_OR  */
    BOOL_OR = 284,                 /* BOOL_OR  */
    BOOL_AND = 285,                /* BOOL_AND  */
    ELSE = 286,                    /* ELSE  */
    FALSE = 287,                   /* FALSE  */
    FOR = 288,                     /* FOR  */
    IF = 289,                      /* IF  */
    PRINT = 290,                   /* PRINT  */
    RETURN = 291,                  /* RETURN  */
    SUPER = 292,                   /* SUPER  */
    THIS = 293,                    /* THIS  */
    TRUE = 294,                    /* TRUE  */
    WHILE = 295,                   /* WHILE  */
    INT = 296,                     /* INT  */
    CHAR = 297,                    /* CHAR  */
    STRUCT = 298,                  /* STRUCT  */
    END_OF_FILE = 299              /* END_OF_FILE  */
  };
  typedef enum yytokentype yytoken_kind_t;
  typedef enum yytokentype TokenType;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 10 "src/parser.y"

    char* str;

#line 112 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

#ifdef __cplusplus
extern "C" {
#endif
int yylex();
#ifdef __cplusplus
}
#endif


extern YYSTYPE yylval;

#ifdef __cplusplus
extern "C" {
#endif
int yyparse (void);
#ifdef __cplusplus
}
#endif


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
