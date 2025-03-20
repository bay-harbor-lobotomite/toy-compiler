CC=g++
CFLAGS=-Wall -g
BISON=bison
BISONFLAGS=-d

SRC_DIR=src
OBJ_DIR=obj
INC_DIR=include

OBJS=$(OBJ_DIR)/ast.o $(OBJ_DIR)/parser.o $(OBJ_DIR)/lexer.o

all: compiler

$(OBJ_DIR)/ast.o: $(SRC_DIR)/ast.cpp
	$(CC) -c $(SRC_DIR)/ast.cpp -o $(OBJ_DIR)/ast.o

$(OBJ_DIR)/parser.o: $(SRC_DIR)/parser.y
	bison -d --header=$(SRC_DIR)/y.tab.h -o $(SRC_DIR)/y.tab.c $(SRC_DIR)/parser.y
	gcc -c $(SRC_DIR)/y.tab.c -o $(OBJ_DIR)/parser.o

$(OBJ_DIR)/lexer.o: $(SRC_DIR)/lexer.l
	flex -o $(SRC_DIR)/lex.yy.c $(SRC_DIR)/lexer.l
	gcc -c $(SRC_DIR)/lex.yy.c -o $(OBJ_DIR)/lexer.o $(CFLAGS)

compiler: $(OBJS)
	$(CC) $(OBJS) -o my_compiler -ll

clean:
	rm -f $(OBJ_DIR)/*.o my_compiler
