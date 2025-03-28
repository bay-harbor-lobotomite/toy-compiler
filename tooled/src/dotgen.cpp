#include <string>
#include <sstream>
#include <iostream>
#include <assert.h>
#include <fstream>

#include <ast.h>
#include <expr.h>
#include <decl.h>
#include <udtype.h>
#include <stmt.h>
#include "y.tab.h"

extern FILE *yyin;
extern FILE *yyout;

AstNode * root = NULL;

static std::ofstream dot_file;

int main(int argc, char *argv[]) {
  FILE *fh;
  FILE *fo;

  if (argc != 4){
  }
  if ((fh = fopen(argv[1], "r"))){
  	yyin = fh;
  }
  else{
	  std::cout << "Input file does not exist!";
	  exit(0);
  }

  	dot_file.open(argv[3]); // = outfile;

	std::stringstream ss;
	ss << "digraph G {\n";
	ss << "\tordering=out\n";
	dot_file << ss.str();

	root = new NonTerm("translation_unit");
	int abc = yyparse();
	root->to_dot();

	assert(abc == 0);
	
    // if(abc == 0){
	// 	std::cout << "Syntax error!" << "\n";
	// 	exit(0);
	// }
	
	ss.str("");
	ss << "}\n";
	dot_file << ss.str();

	dot_file.close();

  return 0;
}

void file_writer(std::string s){
	dot_file << s;
}
