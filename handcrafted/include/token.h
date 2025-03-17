#pragma once
#include "token_type.h"
#include <string>
#include <vector>

#define MAX_TOKEN_SIZE 256

struct Token
{
    TokenType type;
    int line;
    char lexeme[MAX_TOKEN_SIZE];
    Token(TokenType type, int line, char *value);
    std::string to_string();
};