#pragma once
#include "token.h"
#include <string>
#include <vector>
class Lexer
{
private:
    std::string source;
    std::vector<Token> tokens;
    int start;
    int current;
    int line;
    std::vector<Token> scan_tokens();
    char fstep();
    void tokenize();
    int ended();
    void add_token(TokenType type, std::string value);

public:
    Lexer(std::string source);
};