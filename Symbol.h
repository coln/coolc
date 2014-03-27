#ifndef COOL_SYMBOL_H_
#define COOL_SYMBOL_H_

#include <string>
#include "Expression.h"

class Symbol {
public:
	std::string name;
	//UserTypes type;
	std::string type;
	
	Symbol(){}
	Symbol(std::string name, std::string type)
		: name(name), type(type) {}
};

#endif