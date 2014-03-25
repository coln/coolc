#include "CoolCompiler.h"

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

void printUsage(){
	printf("Usage: coolc [-vplto] file ...\n"
					 "\n"
					 "   Options\n"
					 "       -o, --output=FILE\n"
					 "           Specify a file FILE to name the output executable\n"
					 "           Default is a.out\n"
					 "\n"
					);
}

void getFlags(int argc, char* argv[]){
	int flag;
	while(true){
		static struct option long_options[] = {
			{"output", required_argument, 0, 'o'}
		};
		// getopt_long stores the option index here
		int option_index = 0;
		flag = getopt_long(argc, argv, "o:", long_options, &option_index);
		switch(flag){
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
		fprintf(stderr, "coolc: Could not load file \"%s\"\n", filename);
		return false;
	}
	yyin = file;
	yyfilename = filename;
	yyparse();
	return true;
}