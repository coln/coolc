#ifndef COOL_SYMBOL_H_
#define COOL_SYMBOL_H_

#include <string>
#include "Expression.h"

class Symbol : public Expression {
public:
	std::string name;
	std::string type;
	
	Symbol(const std::string&);
	Symbol(const std::string&, const std::string&);
	Symbol(const Symbol&);
	Symbol& operator=(Symbol);
	bool operator==(const Symbol&) const;
};

#endif