#ifndef COOL_SYMBOL_H_
#define COOL_SYMBOL_H_

#include <string>
#include "parser.h"

class Symbol {
public:
	yy::location location;
	std::string name;
	std::string type;
	
	Symbol(std::string, std::string);
};

#endif