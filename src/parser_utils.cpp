#include "../include/lexer.h"
#include "../include/token_type.h"
#include "../include/parser.tab.h"
#include "../include/parser_utils.h"
#include <cstring>

Lexer* global_lexer = nullptr;
int token_idx = 0;
std::vector<Token> token_list;


extern "C" int yylex() {
    static bool eof_returned = false;
    if (!global_lexer) return 0;

    if (token_list.empty()) {
        token_list = global_lexer->scan_tokens();
        token_idx = 0;
        eof_returned = false;
    }

    if (token_idx >= (int)token_list.size()) 
    {
        if (!eof_returned) {
            eof_returned = true;
            printf("yylex: Returning END_OF_FILE\n");
            return END_OF_FILE;
        }
        return 0;
    }

    Token token = token_list[token_idx++];

    switch (token.type) {
        case TokenType::IDENTIFIER:
        case TokenType::NUMBER:
        case TokenType::STRING:
            if(!std::string(token.lexeme).empty())
            yylval.str = strdup(token.lexeme);
            else yylval.str = strdup("");
            break;
        default:
            break;
    }

    return token.type;
}
