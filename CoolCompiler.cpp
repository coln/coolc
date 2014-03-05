#include <getopt.h>
#include <fstream>
#include <iostream>
#include <string>
#include "Lexer.h"
#include "Parser.h"

struct Flags {
	int verbose;
	int lexer;
	int parser;
	int parseTree;
} flags;

void printUsage(){
	std::cout << "Usage: coolc [-vplt] file ...\n"
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
			{"parse-tree", no_argument, &flags.parseTree, 1}
		};
		// getopt_long stores the option index here
		int option_index = 0;
		flag = getopt_long(argc, argv, "vlpt", long_options, &option_index);
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
			case '?':
				// getopt_long reported an error, so print usage once
				printUsage();
				return;
			default:
				return;
		}
	}
}

std::string getFile(const char* filename){
	std::string input;
	std::fstream inputStream;
	inputStream.open(filename, std::ios_base::in);
	if(!inputStream.is_open()){
		std::cerr << "coolc: Could not load file \"" << filename << "\"" << std::endl;
		return "";
	}
	std::string line;
	while(getline(inputStream, line)){
		input += line + '\n';
	}
	return input;
}

bool compile(const char* filename){
	std::string input = getFile(filename);
	if(input == ""){
		return false;
	}
	
	if(flags.verbose){
		std::cout << "Compiling file \"" << filename << "\"..." << std::endl;
		std::cout << "Lexical analysis..." << std::endl;
	}
	Lexer lexer;
	lexer.verbose = (flags.verbose || flags.lexer);
	lexer.filename = filename;
	lexer.input = input;
	if(!lexer.analyze()){
		return false;
	}
	
	if(flags.verbose){
		std::cout << "Lexical analysis complete." << std::endl;
		std::cout << "Parsing..." << std::endl;
	}
	Parser parser;
	parser.verbose = (flags.verbose || flags.parser);
	parser.showTree = (flags.parseTree);
	parser.tokens = lexer.tokens;
	if(!parser.analyze()){
		return false;
	}
	
	if(flags.verbose){
		std::cout << "Parsing complete." << std::endl;
		std::cout << "Compilation complete (so far)." << std::endl;
	}
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