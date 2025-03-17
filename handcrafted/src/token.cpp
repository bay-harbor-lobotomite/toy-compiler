#include "../include/token.h"
#include <cstring>

Token::Token(TokenType type, int line, char*value) {
    this->type = type;
    this->line = line;
    strncpy(this->lexeme, value, std::min((int)(sizeof(value) / sizeof(char)), MAX_TOKEN_SIZE));
}

std::string Token::to_string() {
    return std::string("{ " + std::to_string(this->type) + " , " + this->lexeme + ", [L" + std::to_string(this->line) + "] }");
}
