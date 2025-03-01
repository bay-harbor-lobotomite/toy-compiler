#include "../include/lexer.h"
#include "../include/token.h"
#include <iostream>

Lexer::Lexer(std::string source)
{
    this->source = source;
    this->start = 0;
    this->current = 0;
    this->line = 1;
    initialize_keyword_map();
}

std::vector<Token> Lexer::scan_tokens()
{
    while (!ended())
    {
        start = current;
        tokenize();
    }

    tokens.push_back(Token(TokenType::END_OF_FILE, this->line, std::string("").data()));
    return tokens;
}

void Lexer::tokenize()
{
    char c = fstep();
    switch (c)
    {
    case '(':
        add_token(TokenType::L_PAREN, "(");
        break;
    case ')':
        add_token(TokenType::R_PAREN, ")");
        break;
    case '{':
        add_token(TokenType::L_BRACE, "{");
        break;
    case '}':
        add_token(TokenType::R_BRACE, "}");
        break;
    case '[':
        add_token(TokenType::L_SQUARE, "[");
        break;
    case ']':
        add_token(TokenType::R_SQUARE, "]");
        break;
    case '.':
        add_token(TokenType::PERIOD, ".");
        break;
    case ',':
        add_token(TokenType::COMMA, ",");
        break;
    case ';':
        add_token(TokenType::SEMICOLON, ";");
        break;
    case '+':
        add_token(TokenType::PLUS, "+");
        break;
    case '-':
        add_token(TokenType::MINUS, "-");
        break;
    case '*':
        add_token(TokenType::STAR, "*");
        break;
    case '!':
        is_next('=') ? add_token(TokenType::B_EQ, "!=") : add_token(TokenType::BANG, "!");
        break;
    case '=':
        is_next('=') ? add_token(TokenType::EQ_EQ, "==") : add_token(TokenType::EQ, "=");
        break;
    case '>':
        is_next('=') ? add_token(TokenType::GR_EQ, ">=") : add_token(TokenType::GR, ">");
        break;
    case '<':
        is_next('=') ? add_token(TokenType::LE_EQ, "<=") : add_token(TokenType::LE, "<");
        break;
    case '&':
        is_next('&') ? add_token(TokenType::BOOL_AND, "&&") : add_token(TokenType::BIT_AND, "&");
        break;
    case '|':
        is_next('|') ? add_token(TokenType::BOOL_OR, "||") : add_token(TokenType::BIT_OR, "|");
        break;
    case '/':
        if (is_next('/'))
        {
            while (lookahead() != '\n' && !ended())
                fstep();
        }
        else
        {
            add_token(TokenType::SLASH, "/");
        }
        break;
    case ' ':
    case '\t':
    case 'r':
        break;
    case '\n':
        line++;
        break;
    case '"':
        process_string_literal();
        break;
    default:
        if (is_digit(c))
        {
            process_number();
        }
        else if(is_alpha(c))
        {
            process_identifier();
        }
        else
        {
            std::cout << "Unexpected token :" << c << "\n";
        }
        break;
    }
}

void Lexer::add_token(TokenType type, std::string value)
{
    (this->tokens).push_back(Token(type, line, source.substr(start, current - start).data()));
}

char Lexer::fstep()
{
    return source[current++];
}
int Lexer::ended()
{
    return current >= (int)source.size() ? 1 : 0;
}
int Lexer::is_next(char expected)
{
    // conditional fstep
    if (this->ended() || this->source[this->current] != expected)
        return 0;
    current++;
    return true;
}
char Lexer::lookahead()
{
    if (ended())
        return '\0';
    return source[current];
}
char Lexer::lookahead_next()
{
    if (current + 1 >= (int)source.length())
        return '\0';
    return source[current + 1];
}
void Lexer::process_string_literal()
{
    while (lookahead() != '"' && !ended())
    {
        if (lookahead() == '\n')
            line++;
        fstep();
    }
    if (ended())
    {
        std::cout << "Unterminated string" << "\n";
        return;
    }
    fstep();
    // current has now consumed string terminator
    std::string actual_val = source.substr(start + 1, current - start - 2);
    add_token(TokenType::STRING, actual_val);
}
int Lexer::is_digit(char c)
{
    return c >= '0' && c <= '9';
}

int Lexer::is_alpha(char c)
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_';
}
int Lexer::is_alphanumeric(char c)
{
    return is_digit(c) || is_alpha(c);
}
void Lexer::initialize_keyword_map() {
    keywords["if"] = TokenType::IF;
    keywords["else"] = TokenType::ELSE;
    keywords["for"] = TokenType::FOR;
    keywords["while"] = TokenType::WHILE;
    keywords["print"] = TokenType::PRINT;
    keywords["return"] = TokenType::RETURN;
    keywords["super"] = TokenType::SUPER;
    keywords["this"] = TokenType::THIS;
    keywords["true"] = TokenType::TRUE;
    keywords["false"] = TokenType::FALSE;
    keywords["int"] = TokenType::INT;
    keywords["char"] = TokenType::CHAR;
    keywords["struct"] = TokenType::STRUCT;
}
//no trailing decimals allowed
void Lexer::process_number()
{
    //consume initial digits
    while(is_digit(lookahead()) && !ended()) fstep();
    if(lookahead() == '.' && is_digit(lookahead_next())) {
        fstep();
    }
    while(is_digit(lookahead())) fstep();
    add_token(TokenType::NUMBER, source.substr(start, current - start));
}
void Lexer::process_identifier() {
    while(is_alphanumeric(lookahead())) fstep();
    std::string val = source.substr(start, current - start);
    TokenType type = TokenType::IDENTIFIER;
    if(keywords.find(val) != keywords.end()) type = keywords[val];
    add_token(type, val);
}
