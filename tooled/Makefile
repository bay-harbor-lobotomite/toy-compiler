CXX=g++
CFLAGS=-Wall -g
BISON=bison
BISONFLAGS=-o
LEX=flex
LD=ld

SRC_DIR=src
OBJ_DIR=bin
INC_DIR=include
GRAMMAR=$(SRC_DIR)/grammar.y
LEXSPEC=$(SRC_DIR)/lexspec.l
INCFLAGS = $(addprefix -I, $(INC_DIR))
LDFLAgs=-lfl

OBJS=$(OBJ_DIR)/ast.o $(OBJ_DIR)/parser.o $(OBJ_DIR)/lexer.o

all: compiler

$(OBJ_DIR)/ast.o: $(SRC_DIR)/ast.cpp
	$(CXX) -c $(INCFLAGS) $(LDFLAGS) $(SRC_DIR)/ast.cpp -o $(OBJ_DIR)/ast.o

$(OBJ_DIR)/parser.o: grammar
	$(CXX) -c $(INCFLAGS) $(LDFLAGS) $(SRC_DIR)/y.tab.c -o $(OBJ_DIR)/parser.o

$(OBJ_DIR)/lexer.o: lexspec
	$(CXX) -c $(INCFLAGS) $(LDFLAGS) $(SRC_DIR)/lex.yy.c -o $(OBJ_DIR)/lexer.o $(CFLAGS)


compiler: $(OBJS)
	$(LD) -Ur $(OBJS) -o $(OBJ_DIR)/final.o
	$(CXX) $(OBJ_DIR)/final.o -o my_compiler

clean:
	rm -f $(OBJ_DIR)/*.o my_compiler $(SRC_DIR)/y.tab.c $(SRC_DIR)/y.tab.h $(SRC_DIR)/lex.yy.c

.PHONY: grammar
grammar: $(GRAMMAR)
	$(BISON) --header=$(SRC_DIR)/y.tab.h $(BISONFLAGS) $(SRC_DIR)/y.tab.c $(GRAMMAR)

.PHONY: lexspec
lexspec: $(LEXSPEC)
	$(LEX) -o $(SRC_DIR)/lex.yy.c $(LEXSPEC)