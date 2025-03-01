#include <iostream>
#include <fstream>
#include "../include/token.h"
#include "../include/lexer.h"
#include "../include/parser.tab.h"
#include "../include/parser_utils.h"


std::unordered_map<TokenType, std::string> token_strmap = {
    {L_PAREN, "L_PAREN"}, {R_PAREN, "R_PAREN"}, {L_BRACE, "L_BRACE"}, {R_BRACE, "R_BRACE"}, {L_SQUARE, "L_SQUARE"}, {R_SQUARE, "R_SQUARE"}, {PLUS, "PLUS"}, {MINUS, "MINUS"}, {PERIOD, "PERIOD"}, {COMMA, "COMMA"}, {SEMICOLON, "SEMICOLON"}, {SLASH, "SLASH"}, {STAR, "STAR"}, {BANG, "BANG"}, {B_EQ, "B_EQ"}, {EQ, "EQ"}, {EQ_EQ, "EQ_EQ"}, {LE, "LE"}, {LE_EQ, "LE_EQ"}, {GR, "GR"}, {GR_EQ, "GR_EQ"}, {BIT_AND, "BIT_AND"}, {BIT_OR, "BIT_OR"}, {BOOL_AND, "BOOL_AND"}, {BOOL_OR, "BOOL_OR"}, {IDENTIFIER, "IDENTIFIER"}, {STRING, "STRING"}, {NUMBER, "NUMBER"}, {ELSE, "ELSE"}, {FALSE, "FALSE"}, {FOR, "FOR"}, {IF, "IF"}, {PRINT, "PRINT"}, {RETURN, "RETURN"}, {SUPER, "SUPER"}, {THIS, "THIS"}, {TRUE, "TRUE"}, {WHILE, "WHILE"}, {INT, "INT"}, {CHAR, "CHAR"}, {STRUCT, "STRUCT"}, {END_OF_FILE, "END_OF_FILE"}};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <source_file.c>\n";
        return 1;
    }
    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << argv[1] << "\n";
        return 1;
    }
    std::string source_code((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    Lexer lexer(source_code);
    global_lexer = &lexer;
    auto tokens = global_lexer->scan_tokens();
    int parse_result = yyparse();

    if (parse_result == 0) {
        std::cout << "Parsing successful!\n";
    } else {
        std::cerr << "Parsing failed!\n";
    }

    return parse_result;
}
