#ifndef COOL_ATTRIBUTE_H_
#define COOL_ATTRIBUTE_H_

#include "Symbol.h"
#include "Expression.h"

class Attribute {
public:
	Symbol *symbol;
	Expression *expression;
	
	Attribute(){}
	Attribute(Symbol *symbol)
		: symbol(symbol){}
	Attribute(Symbol *symbol, Expression *expression)
		: symbol(symbol), expression(expression){}
};

#endif