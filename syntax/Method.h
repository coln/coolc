#ifndef COOL_METHOD_H_
#define COOL_METHOD_H_

#include <algorithm>
#include <vector>
#include "Symbol.h"
#include "Expression.h"

class Method : public Expression {
public:
	Symbol* symbol;
	std::vector<Symbol*> arguments;
	Expression *expression;
	
	Method();
	Method(Symbol*, Expression*);
	Method(Symbol*, std::vector<Symbol*>, Expression*);
	Method(const Method&);
	Method& operator=(Method);
	~Method();
	
	virtual void print(int = 0);
};

#endif