#ifndef COOL_SYMBOL_H_
#define COOL_SYMBOL_H_

class StringTable;
class Expression;

#include <string>
#include "StringTable.h"
#include "Expression.h"

class Symbol {
public:
	std::string name;
	std::string type;
	
	Symbol();
	Symbol(std::string, std::string);
};

#endif