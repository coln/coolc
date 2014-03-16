#include <getopt.h>
#include <cstdio>
#include <iostream>
#include "parser.yy.h"
extern int yylex();
extern FILE* yyin;

struct Flags {
	int verbose;
	int lexer;
	int parser;
	int parseTree;
	char* output;
} flags;

void printUsage(){
	std::cout << "Usage: coolc [-vplto] file ...\n"
					 "\n"
					 "   Options\n"
					 "       -v, --verbose\n"
					 "           Show all compilation info (analogous to -lp)\n"
					 "\n"
					 "       -l, --lexer\n"
					 "           Show all lexer info\n"
					 "\n"
					 "       -p, --parser\n"
					 "           Show all parser info\n"
					 "\n"
					 "       -t, --tree, --parse-tree\n" 
					 "           Show the final parse tree\n"
					 "\n"
					 "       -o, --output=FILE\n"
					 "           Specify a file FILE to name the output executable\n"
					 "           Default is a.out\n"
					;
}

void getFlags(int argc, char* argv[]){
	int flag;
	while(true){
		static struct option long_options[] = {
			{"verbose", no_argument, &flags.verbose, 1},
			{"lexer", no_argument, &flags.lexer, 1},
			{"parser", no_argument, &flags.parser, 1},
			{"tree", no_argument, &flags.parseTree, 1},
			{"parse-tree", no_argument, &flags.parseTree, 1},
			{"output", required_argument, 0, 'o'}
		};
		// getopt_long stores the option index here
		int option_index = 0;
		flag = getopt_long(argc, argv, "vlpto:", long_options, &option_index);
		switch(flag){
			// These flags are set by getopt_long
			case 0: // verbose
			case 1: // lexer
			case 2: // parser
			case 3: // tree
			case 4: // parse-tree
				break;
			case 'v':
				flags.verbose = 1;
				break;
			case 'l':
				flags.lexer = 1;
				break;
			case 'p':
				flags.parser = 1;
				break;
			case 't':
				flags.parseTree = 1;
				break;
			case 'o':
				flags.output = optarg;
				break;
			case '?':
				// getopt_long reported an error, so print usage once
				printUsage();
				return;
			default:
				return;
		}
	}
}

bool compile(const char* filename){
	FILE* file = fopen(filename, "r");
	if(!file){
		std::cerr << "coolc: Could not load file \"" << filename << "\"" << std::endl;
	}
	yyin = file;
	yyparse();
	return true;
}

int main(int argc, char* argv[]){
	if(argc < 2){
		printUsage();
		return 1;
	}
	getFlags(argc, argv);
	
	// The remaining arguments should be filenames
	int optionIndex = optind;
	if(optionIndex < argc){
		while(!compile(argv[optionIndex++])){
			return 1;
		}
	}
	return 0;
}