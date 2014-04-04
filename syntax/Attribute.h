#ifndef COOL_ATTRIBUTE_H_
#define COOL_ATTRIBUTE_H_

#include <algorithm>
#include "Symbol.h"
#include "Expression.h"

class Attribute : public Expression {
public:
	Symbol *symbol;
	Expression *expression;
	
	Attribute();
	Attribute(Symbol*);
	Attribute(Symbol*, Expression*);
	Attribute(const Attribute&);
	Attribute& operator=(Attribute);
	~Attribute();
};

#endif