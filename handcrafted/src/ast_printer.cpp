#include "../include/expr.h"
#include <iostream>
int main() {
    Visitor visitor;
    Expr*expression = new Binary(
         new Unary(
            Token(TokenType::MINUS, 1, std::string("-").data()),
            new Literal("123")),
        Token(TokenType::STAR, 1, std::string("*").data()),
        new Grouping(
            new Literal("45.67")));
    std::cout << expression->accept(visitor);
    return 0;
}