#ifndef COOL_ATTRIBUTE_H_
#define COOL_ATTRIBUTE_H_

class Symbol;
class Expression;

#include <algorithm>
#include "Symbol.h"
#include "Expression.h"
#include "parser.h"

class Attribute {
public:
	yy::location location;
	Symbol *symbol;
	Expression *expression;
	
	Attribute();
	Attribute(Symbol *symbol);
	Attribute(Symbol *symbol, Expression *expression);
	Attribute(const Attribute&);
	Attribute& operator=(Attribute);
	~Attribute();
};

#endif