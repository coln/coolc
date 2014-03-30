#include "CoolCompiler.h"

CoolCompiler::CoolCompiler()
	: errorFlag(false)
{
	typeTable.add("Int");
	typeTable.add("Bool");
	typeTable.add("String");
}

CoolCompiler::~CoolCompiler(){
	// Kill all classes and its children
	// This way, I can create new temp pointer and not worry about having
	// everything destruct when I want to delete the temp
	std::vector<Class*>::iterator it;
	for(it = classes.begin(); it < classes.end(); ++it){
		destructClass(*it);
	}
}
void CoolCompiler::destructClass(Class* &thisClass){
	destructFeatures(thisClass->features);
	delete thisClass;
}
void CoolCompiler::destructFeatures(Features* &features){
	std::vector<Attribute*>::iterator it;
	for(it = features->attributes.begin(); it != features->attributes.end(); ++it){
		destructAttribute(*it);
	}
	std::vector<Method*>::iterator it2;
	for(it2 = features->methods.begin(); it2 != features->methods.end(); ++it2){
		destructMethod(*it2);
	}
	features->attributes.clear();
	features->methods.clear();
	delete features;
}
void CoolCompiler::destructAttribute(Attribute* &attribute){
	destructSymbol(attribute->symbol);
	destructExpression(attribute->expression);
	delete attribute;
}
void CoolCompiler::destructSymbol(Symbol* &symbol){
	delete symbol;
}
void CoolCompiler::destructMethod(Method* &method){
	destructSymbol(method->symbol);
	destructExpression(method->expression);
	std::vector<Symbol*>::iterator it;
	for(it = method->arguments.begin(); it != method->arguments.end(); ++it){
		destructSymbol(*it);
	}
	method->arguments.clear();
	delete method;
}
void CoolCompiler::destructExpression(Expression* &expression){
	destructSymbol(expression->symbol);
	if(expression->lhs){
		destructExpression(expression->lhs);
	}
	if(expression->rhs){
		destructExpression(expression->rhs);
	}
	delete expression;
}


bool CoolCompiler::compile(int optind, int argc, char* argv[]){
	// Lex/Parse each input file
	int optionIndex = optind;
	while(optionIndex < argc){
		filename = argv[optionIndex];
		if(parse(argv[optionIndex++])){
			errorStream << "error in parsing \"" << filename << "\"";
			error();
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
	traceStream << "Entering Semantic Analysis phase...";
	traceAnalyzer();
	
	// Make sure class Main is found
	bool mainFound = false;
	std::vector<Class*>::iterator classIt;
	
	
	// Add class names to typeTable, check for class Main
	Class *thisClass;
	for(classIt = classes.begin(); classIt != classes.end(); ++classIt){
		thisClass = *classIt;
		if(typeTable.find(thisClass->name) != -1){
			errorStream << "the class \"" << thisClass->name;
			errorStream << "\" has already been defined";
			error(thisClass->location);
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
	traceStream << "Total classes created: " << classes.size();
	traceAnalyzer();
	
	
	// UM YEA so this can be reduced
	// Aka pass this off to a type checker class
	for(classIt = classes.begin(); classIt != classes.end(); ++classIt){
		thisClass = *classIt;
		
		// Analyze the classes
		if(!thisClass->inherits.empty()){
			thisClass->inheritsIndex = typeTable.find(thisClass->inherits);
		}
		if(thisClass->inheritsIndex == -1){
			errorStream << "error inheriting \"" << thisClass->inherits;
			errorStream << "\": no such class exists";
			error(thisClass->location);
		}
		
		// Analyze the attributes
		Features *features = thisClass->features;
		Features *tempFeatures = new Features();
		tempFeatures->location = features->location;
		
		
		std::vector<Attribute*> &attributes = features->attributes;
		std::vector<Attribute*>::iterator it;
		Attribute *thisAttr;
		for(it = attributes.begin(); it != attributes.end(); ++it){
			thisAttr = *it;
			// Check for duplicates
			if(tempFeatures->findAttribute(thisAttr->symbol->name)){
				errorStream << "an attribute with the name \"" << thisAttr->symbol->name;
				errorStream << "\" already exists";
				error(thisAttr->location);
			}
			tempFeatures->addAttribute(thisAttr);
			
			// Check the type exists
			if(typeTable.find(thisAttr->symbol->type) == -1){
				errorStream << "no such type \"" << thisAttr->symbol->type << "\" exists";
				error(thisAttr->location);
			}
			traceStream << "All class attributes of class \"";
			traceStream << thisClass->name << "\"";
			traceStream << " have been type checked.";
			traceAnalyzer();
		}
		
		std::vector<Method*> &methods = features->methods;
		std::vector<Method*>::iterator it2;
		Method *thisMethod;
		for(it2 = methods.begin(); it2 != methods.end(); ++it){
			thisMethod = *it2;
			// Check for duplicates
			if(tempFeatures->findMethod(thisMethod->symbol->name)){
				errorStream << "a method with the name \"" << thisMethod->symbol->name;
				errorStream << "\" already exists";
				error(thisMethod->location);
			}
			tempFeatures->addMethod(thisMethod);
			
			// Check the type exists
			if(typeTable.find(thisMethod->symbol->type) == -1){
				errorStream << "no such type \"" << thisAttr->symbol->type << "\" exists";
				error(thisMethod->location);
			}
			
			std::vector<Symbol*> &arguments = thisMethod->arguments;
			std::vector<Symbol*>::iterator it3;
			Symbol* thisArg;
			for(it3 = arguments.begin(); it3 != arguments.end(); ++it3){
				thisArg = *it3;
				// Check the type exists
				if(typeTable.find(thisArg->type) == -1){
					errorStream << "no such type \"" << thisArg->type << "\" exists";
					error(thisArg->location);
				}
			}
		}
		traceStream << "All class methods of class \"";
		traceStream << thisClass->name << "\"";
		traceStream << " have been type checked.";
		traceAnalyzer();
		delete tempFeatures;
	}
	
	// Code gen
	// if errorFlag... halt
	return true;
}

// Create an error class to handle all of this?
// Like an error stream?
void CoolCompiler::traceAnalyzer(){
	if(flags.traceAnalyzer || flags.verbose){
		std::cout << traceStream.str() << std::endl;
	}
	traceStream.str(std::string());
	traceStream.clear();
}


void CoolCompiler::error(const yy::location& location){
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
void CoolCompiler::error(const std::string& msg){
	errorStream << msg;
	error();
}
void CoolCompiler::error(){
	errorFlag = true;
	std::cerr << filename << ": ";
	std::cerr << errorStream.str() << std::endl;
	errorStream.str(std::string());
	errorStream.clear();
}