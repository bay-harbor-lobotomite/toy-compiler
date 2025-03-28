CXX=g++ -g
CFLAGS=-Wall -g
BISON=bison
BISONFLAGS=--warnings=none -o
LEX=flex
LD=ld

SRC_DIR=src
OBJ_DIR=obj
INC_DIR=include
SPEC_DIR=spec
GRAMMAR=$(SPEC_DIR)/grammar.y
LEXSPEC=$(SPEC_DIR)/lexspec.l
INCFLAGS = $(addprefix -I, $(INC_DIR))
LDFLAgs=-lfl

OBJS=$(OBJ_DIR)/parser.o $(OBJ_DIR)/udtype.o $(OBJ_DIR)/stmt.o $(OBJ_DIR)/expr.o $(OBJ_DIR)/decl.o $(OBJ_DIR)/ast.o $(OBJ_DIR)/symtable.o $(OBJ_DIR)/lexer.o $(OBJ_DIR)/dotgen.o

all: compiler

$(OBJ_DIR)/udtype.o: $(SRC_DIR)/udtype.cpp
	$(CXX) -c $(INCFLAGS) $(LDFLAGS) $(SRC_DIR)/udtype.cpp -o $(OBJ_DIR)/udtype.o

$(OBJ_DIR)/stmt.o: $(SRC_DIR)/stmt.cpp
	$(CXX) -c $(INCFLAGS) $(LDFLAGS) $(SRC_DIR)/stmt.cpp -o $(OBJ_DIR)/stmt.o

$(OBJ_DIR)/decl.o: $(SRC_DIR)/decl.cpp
	$(CXX) -c $(INCFLAGS) $(LDFLAGS) $(SRC_DIR)/decl.cpp -o $(OBJ_DIR)/decl.o

$(OBJ_DIR)/expr.o: $(SRC_DIR)/expr.cpp
	$(CXX) -c $(INCFLAGS) $(LDFLAGS) $(SRC_DIR)/expr.cpp -o $(OBJ_DIR)/expr.o

$(OBJ_DIR)/ast.o: $(SRC_DIR)/ast.cpp
	$(CXX) -c $(INCFLAGS) $(LDFLAGS) $(SRC_DIR)/ast.cpp -o $(OBJ_DIR)/ast.o

$(OBJ_DIR)/dotgen.o: $(SRC_DIR)/dotgen.cpp
	$(CXX) -c $(INCFLAGS) $(LDFLAGS) $(SRC_DIR)/dotgen.cpp -o $(OBJ_DIR)/dotgen.o

$(OBJ_DIR)/symtable.o: $(SRC_DIR)/symtable.cpp
	$(CXX) -c $(INCFLAGS) $(LDFLAGS) $(SRC_DIR)/symtable.cpp -o $(OBJ_DIR)/symtable.o

$(OBJ_DIR)/parser.o: grammar
	$(CXX) -c $(INCFLAGS) $(LDFLAGS) $(SRC_DIR)/y.tab.c -o $(OBJ_DIR)/parser.o

$(OBJ_DIR)/lexer.o: lexspec
	$(CXX) -c $(INCFLAGS) $(LDFLAGS) $(SRC_DIR)/lex.yy.c -o $(OBJ_DIR)/lexer.o $(CFLAGS)


compiler: $(OBJS)
	$(LD) -Ur $(OBJS) -o $(OBJ_DIR)/final.o
	$(CXX) $(OBJ_DIR)/final.o -o $(OBJ_DIR)/compiler

clean:
	rm -f $(OBJ_DIR)/*.o $(OBJ_DIR)/compiler $(SRC_DIR)/y.tab.c $(INC_DIR)/y.tab.h $(SRC_DIR)/lex.yy.c

.PHONY: grammar
grammar: $(GRAMMAR)
	$(BISON) --header=$(INC_DIR)/y.tab.h $(BISONFLAGS) $(SRC_DIR)/y.tab.c $(GRAMMAR)

.PHONY: lexspec
lexspec: $(LEXSPEC)
	$(LEX) -o $(SRC_DIR)/lex.yy.c $(LEXSPEC)