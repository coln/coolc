#include "CoolCompiler.h"

CoolCompiler::~CoolCompiler(){
	// Kill all classes and its children
	/* We must go deeper captain
	int numClasses = classes.size();
	int i;
	for(i = 0; i < numClasses; i++){
		delete classes[i];
	}
	*/
}

bool CoolCompiler::compile(int optind, int argc, char* argv[]){
	int optionIndex = optind;
	while(optionIndex < argc){
		filename = argv[optionIndex];
		if(parse(argv[optionIndex++])){
			error(std::string("error in parsing \"").append(filename).append("\""));
			return false;
		}
	}
	
	/*
	First make sure a class called Main with a method called main exists
	Then run the type checker for every class
	Then evaluate every class
	*/
	
	// Awesome socks
	// Now let's perform semantic analysis, optimization, and code gen
	if(flags.traceAnalyzer || flags.verbose){
		int numClasses = classes.size();
		std::cout << "Total classes created: " << numClasses << std::endl;
	}
	
	// Make sure class Main is found
	bool mainFound = false;
	int i;
	for(i = 0; i < numClasses; i++){
		if(classes[i].name == "Main"){
			mainFound = true;
		}
	}
	if(!mainFound){
		error("class \"Main\" not found");
		return false;
	}
	
	for(i = 0; i < numClasses; i++){
		classes[i]->evaluate();
	}
	return true;
}

// This returns 0 on success
int CoolCompiler::parse(const std::string& filename){
	lexerBegin();
	
	yy::CoolParser parser(*this);
	parser.set_debug_level(flags.verbose || flags.traceParser);
	int res = parser.parse();
	
	lexerEnd();
	return res;
}

void CoolCompiler::error(const yy::location& location, const std::string& msg){
	// Because line.column format is just too good for me...
	std::cerr << filename << ":";
	if(location.begin.line != location.end.line){
		std::cerr << location.begin.line << ":" << location.begin.column;
		std::cerr << " - ";
		std::cerr << location.end.line << ":" << location.end.column;
	}else if(location.begin.column < location.end.column - 1){
		std::cerr << location.begin.line << ":" << location.begin.column;
		std::cerr << " - ";
		std::cerr << location.end.column - 1;
	}else{
		std::cerr << location.begin.line << ":" << location.begin.column;
	}
	std::cerr << ": " << msg << std::endl;
}
void CoolCompiler::error(const std::string& msg){
	std::cerr << msg << std::endl;
}