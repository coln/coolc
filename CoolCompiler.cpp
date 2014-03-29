#include "CoolCompiler.h"

CoolCompiler::~CoolCompiler(){
	// Kill all classes and its children
	std::vector<Class*>::iterator it;
	for(it = classes.begin(); it < classes.end(); ++it){
		delete *it;
	}
}
bool CoolCompiler::compile(int optind, int argc, char* argv[]){
	// Lex/Parse each input file
	int optionIndex = optind;
	while(optionIndex < argc){
		filename = argv[optionIndex];
		if(parse(argv[optionIndex++])){
			std::string msg = "error in parsing \"" + filename + "\"";
			error(msg);
			return false;
		}
	}
	
	// Enter semantic analysis
	if(!analyze()){
		return false;
	}
	return true;
}

// This returns 0 on success
int CoolCompiler::parse(const std::string& filename){
	lexerBegin();
	
	yy::CoolParser parser(*this);
	parser.set_debug_level(flags.traceParser || flags.verbose);
	int res = parser.parse();
	
	lexerEnd();
	return res;
}

bool CoolCompiler::analyze(){
	std::string msg;
	traceAnalyzer("Enterting Semantic Analysis phase...");
	
	// Make sure class Main is found
	bool mainFound = false;
	int numClasses = classes.size();
	int i;
	
	// Add class names to typeTable, check for class Main
	Class *thisClass;
	for(i = 0; i < numClasses; i++){
		thisClass = classes[i];
		if(typeTable.find(thisClass->name) != -1){
			msg = "the class \"" + thisClass->name + "\" has already been defined";
			error(thisClass->location, msg);
		}
		thisClass->nameIndex = typeTable.add(thisClass->name, true);
		if(thisClass->name == "Main"){
			mainFound = true;
		}
	}
	if(!mainFound){
		error("class \"Main\" not found");
		return false;
	}
	
	traceAnalyzer("Total classes created: %d", numClasses);
	
	// Check the inheritance exists
	for(i = 0; i < numClasses; i++){
		// Analyze the classes
		thisClass = classes[i];
		if(!thisClass->inherits.empty()){
			thisClass->inheritsIndex = typeTable.find(thisClass->inherits);
		}
		if(thisClass->inheritsIndex == -1){
			msg = "error inheriting \"" + thisClass->inherits;
			msg += "\": no such class";
			error(thisClass->location, msg);
		}
	}
	
	// Check the attributes
	for(i = 0; i < numClasses; i++){
		// Analyze the attributes
		thisClass = classes[i];
		Features *features = thisClass->features;
		std::vector<Attribute*> &attributes = features->attributes;
		int numAttributes = attributes.size();
		int j;
		for(j = 0; j < numAttributes; j++){
			// Check for duplicates of the attribute
			// Then add the attributes to a class list or something
		}
	}
	return true;
}

// Create an error class to handle all of this?
// Like an error stream?
void CoolCompiler::traceAnalyzer(const char *msg, ...){
	if(flags.traceAnalyzer || flags.verbose){
		static char errmsg[10000];
		va_list args;
		va_start(args, msg);
		vsprintf(errmsg, msg, args);
		va_end(args);
		std::cout << errmsg << std::endl;
	}
}


void CoolCompiler::error(const yy::location& location, const std::string& msg){
	// Because line.column format is just too good for me...
	std::cerr << filename + ":";
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
	std::cerr << ": " + msg << std::endl;
}
void CoolCompiler::error(const std::string& msg){
	std::cerr << filename << ": ";
	std::cerr << msg << std::endl;
}