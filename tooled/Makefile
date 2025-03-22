CXX=g++
CFLAGS=-Wall -g
BISON=bison
BISONFLAGS=-o
LEX=flex

SRC_DIR=src
OBJ_DIR=bin
INC_DIR=include
GRAMMAR=$(SRC_DIR)/grammar.y
LEXSPEC=$(SRC_DIR)/lexspec.l

OBJS=$(OBJ_DIR)/parser.o $(OBJ_DIR)/ast.o $(OBJ_DIR)/lexer.o

all: compiler

$(OBJ_DIR)/ast.o: $(SRC_DIR)/ast.cpp
	$(CXX) -c $(SRC_DIR)/ast.cpp -o $(OBJ_DIR)/ast.o

$(OBJ_DIR)/parser.o: grammar
	$(CXX) -c $(SRC_DIR)/y.tab.c -o $(OBJ_DIR)/parser.o

$(OBJ_DIR)/lexer.o: lexspec
	$(CXX) -c $(SRC_DIR)/lex.yy.c -o $(OBJ_DIR)/lexer.o $(CFLAGS)

compiler: $(OBJS)
	$(CXX) $(OBJS) -o my_compiler -ll

clean:
	rm -f $(OBJ_DIR)/*.o my_compiler $(SRC_DIR)/y.tab.c $(SRC_DIR)/y.tab.h $(SRC_DIR)/lex.yy.c

.PHONY: grammar
grammar: $(GRAMMAR)
	$(BISON) --header=$(SRC_DIR)/y.tab.h $(BISONFLAGS) $(SRC_DIR)/y.tab.c $(GRAMMAR)

.PHONY: lexspec
lexspec: $(LEXSPEC)
	$(LEX) -o $(SRC_DIR)/lex.yy.c $(LEXSPEC)