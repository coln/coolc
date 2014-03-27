#include "CoolCompiler.h"

bool CoolCompiler::compile(const char* filename){
	if(!parse(filename)){
		std::cerr << result << std::endl;
		return false;
	}
	return true;
}

int CoolCompiler::parse(const std::string& filename){
	this->filename = filename;
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