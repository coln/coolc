#ifndef COOL_CLASS_H_
#define COOL_CLASS_H_

class Features;
class Expression;

#include <string>
#include <vector>
#include "Features.h"
#include "Expression.h"
#include "parser.h"

class Class {
public:
	const yy::location location;
	std::string name;
	std::string inherits;
	int nameIndex;
	int inheritsIndex;
	Features *features;
	
	Class(const yy::location, std::string, Features*);
	Class(const yy::location, std::string, std::string, Features*);
	~Class();
	
	void checkTypes();
	void evaluate();
};



#endif