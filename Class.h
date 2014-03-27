#ifndef COOL_CLASS_H_
#define COOL_CLASS_H_

#include <string>
#include "Features.h"
#include "Expression.h"

// Can we implement a string table somehow?
// Can method declarations eventually be turned into symbols?
// Can we remove "ExpType type" from Symbo.h and Method.h and use user declared types?
class Class {
public:
	std::string name;
	std::string inherits;
	Features *features;
	
	Class(){}
	Class(std::string name, Features *features)
		: name(name), features(features) {}
	Class(std::string name, std::string inherits, Features *features)
		: name(name), inherits(inherits), features(features) {}
	
	void evaluateFeatures();
};

#endif