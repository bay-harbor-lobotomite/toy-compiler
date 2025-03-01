CC=g++
CFLAGS=-Wall -g
BISON=bison
BISONFLAGS=-d

SRC_DIR=src
OBJ_DIR=obj

OBJS=$(OBJ_DIR)/lexer.o $(OBJ_DIR)/token.o $(OBJ_DIR)/parser_utils.o $(OBJ_DIR)/parser.o $(OBJ_DIR)/main.o

all: my_compiler

$(OBJ_DIR)/parser.o: $(SRC_DIR)/parser.y
	gcc -c $(SRC_DIR)/parser.tab.c -o $(OBJ_DIR)/parser.o

$(OBJ_DIR)/lexer.o: $(SRC_DIR)/lexer.cpp
	$(CC) -c $(SRC_DIR)/lexer.cpp -o $(OBJ_DIR)/lexer.o $(CFLAGS)

$(OBJ_DIR)/token.o: $(SRC_DIR)/token.cpp
	$(CC) -c $(SRC_DIR)/token.cpp -o $(OBJ_DIR)/token.o $(CFLAGS)

$(OBJ_DIR)/parser_utils.o: $(SRC_DIR)/parser_utils.cpp
	$(CC) -c $(SRC_DIR)/parser_utils.cpp -o $(OBJ_DIR)/parser_utils.o $(CFLAGS)

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp
	$(CC) -c $(SRC_DIR)/main.cpp -o $(OBJ_DIR)/main.o $(CFLAGS)

my_compiler: $(OBJS)
	$(CC) $(OBJS) -o my_compiler

clean:
	rm -f $(OBJ_DIR)/*.o my_compiler
