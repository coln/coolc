#include "Semantic.h"

Semantic::Semantic(CoolCompiler &compiler)
	: objectType("Object"), compiler(compiler)
{
	objectType.addChild("Int");
	objectType.addChild("Bool");
	objectType.addChild("String");
}

bool Semantic::populateTypes(){
	traceStream << "Checking for class Main";
	trace();
	
	// Make sure class Main is found
	bool mainFound = false;
	
	// Get all class names
	std::vector<Class*>::iterator it;
	Class *thisClass;
	for(it = compiler.classes.begin(); it != compiler.classes.end(); ++it){
		thisClass = *it;
		
		// Check duplicates
		if(objectType.findChild(thisClass->name) != NULL){
			compiler.errorStream << "the class \"" << thisClass->name;
			compiler.errorStream << "\" has already been defined";
			compiler.error(thisClass->location);
			return false;
		}
		if(thisClass->name == "Main"){
			mainFound = true;
		}
		objectType.addChild(thisClass->name);
	}
	if(!mainFound){
		compiler.errorStream << "class \"Main\" not found";
		compiler.error();
		return false;
	}
	return true;
}
bool Semantic::organizeTypes(){
	traceStream << "Checking inheritance";
	trace();
	
	std::vector<Class*>::iterator it;
	Class *thisClass;
	Type *currentType;
	Type *inheritType;
	for(it = compiler.classes.begin(); it != compiler.classes.end(); ++it){
		thisClass = *it;
		
		// Top-level class
		if(thisClass->inherits.empty()){
			continue;
		}
		
		// Can't inherit from self
		if(thisClass->inherits == thisClass->name){
			compiler.errorStream << "the class \"" << thisClass->name;
			compiler.errorStream << "\" cannot inherit from itself";
			compiler.error(thisClass->location);
			return false;
		}
		
		// Check inheritance and add it to type tree
		currentType = objectType.findChild(thisClass->name);
		inheritType = objectType.findChild(thisClass->inherits);
		if(inheritType == NULL){
			compiler.errorStream << "error inheriting class \"";
			compiler.errorStream << thisClass->inherits;
			compiler.errorStream << "\": no such class exists";
			compiler.error(thisClass->location);
			return false;
		}
		inheritType->addChild(*currentType);
		objectType.removeChild(currentType->name);
	}
	
	if(compiler.flags.types){
		std::cout << "Type Inheritance Tree:" << std::endl;
		objectType.print();
	}
	
	return true;
}

bool Semantic::analyze(){
	traceStream << "Entering Semantic Analysis phase...";
	trace();
	
	if(!populateTypes()){
		return false;
	}
	
	traceStream << "Total classes created: " << compiler.classes.size();
	trace();
	
	if(!organizeTypes()){
		return false;
	}
	return true;
}

void Semantic::trace(){
	if(compiler.flags.verbose || compiler.flags.semantic){
		std::cout << traceStream.str() << std::endl;
	}
	traceStream.str(std::string());
	traceStream.clear();
}