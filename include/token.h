#pragma once
#include "token_type.h"
#include <string>
#include <vector>

#define MAX_TOKEN_SIZE 256

typedef struct __token
{
    TokenType type;
    int line;
    char lexeme[MAX_TOKEN_SIZE];
    __token(TokenType type, int line, char *value);
    std::string to_string();
} Token;