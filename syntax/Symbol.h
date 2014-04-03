#ifndef COOL_SYMBOL_H_
#define COOL_SYMBOL_H_

#include <string>
#include "Type.h"
#include "../parser.h"

class Symbol {
public:
	yy::location location;
	std::string name;
	std::string type;
	
	Symbol(const std::string, const std::string);
	bool operator==(const Symbol&) const;
};

#endif