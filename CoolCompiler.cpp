#include "CoolCompiler.h"

CoolCompiler::CoolCompiler(){}

CoolCompiler::~CoolCompiler(){
	if(classes.size() <= 0){
		return;
	}
	std::vector<Class*>::iterator it;
	for(it = classes.begin(); it != classes.end(); ++it){
		delete *it;
	}
	classes.clear();
}


bool CoolCompiler::compile(int optind, int argc, char* argv[]){
	// Lex/Parse each input file
	int optionIndex = optind;
	if(optionIndex >= argc){
		errorStream << "no input files";
		error();
		return false;
	}
	while(optionIndex < argc){
		filename = argv[optionIndex];
		if(parse(argv[optionIndex++])){
			errorStream << "error in parsing \"" << filename << "\"";
			error();
			return false;
		}
	}
	
	// Enter semantic analysis
	Semantic semantic(*this);
	if(!semantic.analyze()){
		return false;
	}
	return true;
}

// This returns 0 on success
int CoolCompiler::parse(const std::string& filename){
	lexerBegin();
	
	yy::CoolParser parser(*this);
	parser.set_debug_level(flags.parser || flags.verbose);
	int res = parser.parse();
	
	lexerEnd();
	return res;
}

void CoolCompiler::error(const yy::location &location, const std::string &msg){
	errorStream << msg;
	error(location);
}
void CoolCompiler::error(const yy::location &location){
	// Because line.column format is just too good for me...
	std::stringstream newStream;
	newStream << "\b"; // To get rid of the space in error()
	
	if(location.begin.line != location.end.line){
		newStream << location.begin.line << ":" << location.begin.column;
		newStream << " - ";
		newStream << location.end.line << ":" << location.end.column;
	}else if(location.begin.column < location.end.column - 1){
		newStream << location.begin.line << ":" << location.begin.column;
		newStream << " - ";
		newStream << location.end.column - 1;
	}else{
		newStream << location.begin.line << ":" << location.begin.column;
	}
	newStream << ": ";
	newStream << errorStream.str();
	
	errorStream.str(std::string());
	errorStream.clear();
	errorStream << newStream.str();
	error();
}
void CoolCompiler::error(const std::string &msg){
	errorStream << msg;
	error();
}
void CoolCompiler::error(){
	if(filename.empty()){
		filename = "coolc";
	}
	std::cerr << filename << ": ";
	std::cerr << errorStream.str() << std::endl;
	errorStream.str(std::string());
	errorStream.clear();
}