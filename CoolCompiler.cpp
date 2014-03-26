#include "CoolCompiler.h"

CoolCompiler::CoolCompiler(){
	variables["one"] = 1;
	variables["two"] = 2;
}
CoolCompiler::~CoolCompiler(){}

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
	std::cerr << location << ": " << msg << std::endl; 
}
void CoolCompiler::error(const std::string& msg){
	std::cerr << msg << std::endl;
}