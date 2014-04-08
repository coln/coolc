#include <getopt.h>
#include <iostream>
#include "CoolCompiler.h"
#include "parser.h"

void printUsage();
bool getFlags(CoolCompiler&, int, char**);


int main(int argc, char* argv[]){
	CoolCompiler compiler;
	if(argc < 2){
		printUsage();
		return 1;
	}
	bool flags = getFlags(compiler, argc, argv);
	if(!flags){
		return 1;
	}
	
	// The remaining arguments should be filenames
	if(!compiler.compile(optind, argc, argv)){
		return 1;
	}
	return 0;
}

void printUsage(){
	std::cout << "Usage: coolc [-vplto] file ...\n"
			 "   Options\n"
			 "       -v, --verbose\n"
			 "           Show lexer and parser output and traces.\n"
			 "           Analogous to -lp\n"
			 "\n"
			 "       -l, --lexer\n"
			 "           Show lexer output and traces\n"
			 "\n"
			 "       -p, --parser\n"
			 "           Show parser output and traces\n"
			 "\n"
			 "       -t, --parse-tree\n"
			 "           Show complete parse tree output\n"
			 "\n" 
			 "       -s, --semantic\n"
			 "           Show semantic analyzer output and traces\n"
			 "\n"
			 "       -y, --types\n"
			 "           Show the type inheritance tree\n"
			 "\n"
			 "       -o, --output=FILE\n"
			 "           Specify a file FILE to name the output executable\n"
			 "           Default is a.out\n"
			 "\n"
			 ;
}
bool getFlags(CoolCompiler& compiler, int argc, char* argv[]){
	int flag;
	while(true){
		static struct option long_options[] = {
			{"verbose", no_argument, 0, 'v'},
			{"lexer", no_argument, 0, 'l'},
			{"parser", no_argument, 0, 'p'},
			{"parse-tree", no_argument, 0, 't'},
			{"semantic", no_argument, 0, 's'},
			{"types", no_argument, 0, 'y'},
			{"output", required_argument, 0, 'o'}
		};
		// getopt_long stores the option index here
		int option_index = 0;
		flag = getopt_long(argc, argv, "vlptsyo:", long_options, &option_index);
		switch(flag){
			case 'v':
				compiler.flags.verbose = true;
				break;
			case 'l':
				compiler.flags.lexer = true;
				break;
			case 'p':
				compiler.flags.parser = true;
				break;
			case 't':
				compiler.flags.parseTree = true;
				break;
			case 's':
				compiler.flags.semantic = true;
				break;
			case 'y':
				compiler.flags.types = true;
				break;
			case 'o':
				compiler.flags.outputFile = optarg;
				break;
			case '?':
				// getopt_long reported an error, so print usage once
				printUsage();
				return false;
			default:
				return true;
		}
	}
	return true;
}