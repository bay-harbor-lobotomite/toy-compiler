a toy compiler for (hopefully) a subset of the C programming language/C-like language of my own making.
# Project so far
- Implemented a small free-format scanner in C++. Not using lex or any other lexical analyzer generator because it was probably faster to implement by hand than learning the specification format idk.
- Setup bison to go with the project, written a small grammar that parses and prints simple expressions. Plan on writing a complete grammar and write my own recursive descent parser because why tf not.
# Shit I used
- [This book](https://craftinginterpreters.com/)
- [Yacc grammar for ANSI C 1985 that I extended](https://www.lysator.liu.se/c/ANSI-C-grammar-y.html)
- [Similar lex spec](https://www.lysator.liu.se/c/ANSI-C-grammar-l.html)
- [The Dragon book for reference](https://www.amazon.in/Compilers-2e-Aho/dp/9332518661)
- Borrowing ideas and some code (hehe) for type handling, AST construction paradigm and dot file generation from [these guys](https://github.com/sidjay10/CS335-C-Compiler)
