#include "../include/lexer.h"
#include "../include/token.h"
#include <iostream>

int main()
{
    std::cout << "Hey!" << "\n";
    Lexer *lexer = new Lexer(std::string("Here's a source for you"));
    return 0;
}