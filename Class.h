#ifndef COOL_CLASS_H_
#define COOL_CLASS_H_

class StringTable;
class Features;
class Expression;

#include <string>
#include "Features.h"
#include "Expression.h"
#include "parser.h"

class Class {
public:
	std::string name;
	std::string inherits;
	Features *features;
	
	Class();
	Class(std::string, Features*);
	Class(std::string, std::string, Features*);
	
	void checkTypes();
	void evaluate();
};

#endif