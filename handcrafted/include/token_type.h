#pragma once
#include <unordered_map>
#include <string>
#include "parser.tab.h"

enum TokenType
{
    IDENTIFIER = 258, /* IDENTIFIER  */
    NUMBER = 259,     /* NUMBER  */
    STRING = 260,     /* STRING  */
    L_PAREN = 261,    /* L_PAREN  */
    R_PAREN = 262,    /* R_PAREN  */
    L_SQUARE = 263,   /* L_SQUARE  */
    R_SQUARE = 264,   /* R_SQUARE  */
    L_BRACE = 265,    /* L_BRACE  */
    R_BRACE = 266,    /* R_BRACE  */
    PLUS = 267,       /* PLUS  */
    MINUS = 268,      /* MINUS  */
    STAR = 269,       /* STAR  */
    SLASH = 270,      /* SLASH  */
    PERIOD = 271,     /* PERIOD  */
    COMMA = 272,      /* COMMA  */
    SEMICOLON = 273,  /* SEMICOLON  */
    BANG = 274,       /* BANG  */
    B_EQ = 275,       /* B_EQ  */
    EQ = 276,         /* EQ  */
    EQ_EQ = 277,      /* EQ_EQ  */
    LE = 278,         /* LE  */
    LE_EQ = 279,      /* LE_EQ  */
    GR = 280,         /* GR  */
    GR_EQ = 281,      /* GR_EQ  */
    BIT_AND = 282,    /* BIT_AND  */
    BIT_OR = 283,     /* BIT_OR  */
    BOOL_OR = 284,    /* BOOL_OR  */
    BOOL_AND = 285,   /* BOOL_AND  */
    ELSE = 286,       /* ELSE  */
    FALSE = 287,      /* FALSE  */
    FOR = 288,        /* FOR  */
    IF = 289,         /* IF  */
    PRINT = 290,      /* PRINT  */
    RETURN = 291,     /* RETURN  */
    SUPER = 292,      /* SUPER  */
    THIS = 293,       /* THIS  */
    TRUE = 294,       /* TRUE  */
    WHILE = 295,      /* WHILE  */
    INT = 296,        /* INT  */
    CHAR = 297,       /* CHAR  */
    STRUCT = 298,     /* STRUCT  */
    END_OF_FILE = 299 /* END_OF_FILE  */
};