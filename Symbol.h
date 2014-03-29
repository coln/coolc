#ifndef COOL_SYMBOL_H_
#define COOL_SYMBOL_H_

#include <string>

class Symbol {
public:
	std::string name;
	std::string type;
	
	Symbol(std::string, std::string);
};

#endif