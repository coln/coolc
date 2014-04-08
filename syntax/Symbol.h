#ifndef COOL_SYMBOL_H_
#define COOL_SYMBOL_H_

#include <string>
#include "Expression.h"

class Symbol : public Expression {
public:
	std::string name;
	std::string type;
	Expression *value;
	
	Symbol(const std::string&, Expression* = NULL);
	Symbol(const std::string&, const std::string&, Expression* = NULL);
	Symbol(const Symbol&);
	Symbol& operator=(Symbol);
	
	bool operator==(const Symbol&) const;
	virtual void print(int = 0);
};

#endif