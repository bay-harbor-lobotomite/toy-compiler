#pragma once
#include "token.h"
#include "token_type.h"
#include <string>
#include <vector>
#include <map>
class Lexer
{
private:
    std::string source;
    std::vector<Token> tokens;
    int start;
    int current;
    int line;
    std::map<std::string, TokenType> keywords;
    char fstep();
    void tokenize();
    int ended();
    void add_token(TokenType type, std::string value);
    int is_next(char expected);
    char lookahead();
    char lookahead_next();
    void process_string_literal();
    void process_number();
    void process_identifier();
    int is_digit(char c);
    int is_alpha(char c);
    int is_alphanumeric(char c);
    void initialize_keyword_map();

public:
    Lexer(std::string source);
    std::vector<Token> scan_tokens();
};

extern "C" int yylex();