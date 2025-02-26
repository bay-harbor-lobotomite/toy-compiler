#include "../include/lexer.h"

Lexer::Lexer(std::string source)
{
    this->source = source;
    this->start = 0;
    this->current = 0;
    this->line = 1;
}

std::vector<Token> Lexer::scan_tokens()
{
    while (!ended())
    {
        start = current;
        tokenize();
    }

    tokens.push_back(Token(TokenType::END_OF_FILE, this->line, ""));
    return tokens;
}

void Lexer::tokenize()
{
    char c = fstep();
    switch (c)
    {
    case '(':
        add_token(TokenType::LEFT_PAREN, "(");
    }
}

void Lexer::add_token(TokenType type, std::string value)
{
    (this->tokens).push_back(Token(type, line, value.data()));
}

char Lexer::fstep()
{
    return source[current++];
}
int Lexer::ended()
{
    return current >= source.size() ? 1 : 0;
}