#ifndef COOL_DISPATCH_H_
#define COOL_DISPATCH_H_

#include <algorithm>
#include "Symbol.h"
#include "Expression.h"

class Dispatch : public Expression {
public:
	Symbol *symbol;
	std::vector<Expression*> arguments;
	
	Dispatch(Symbol*);
	Dispatch(Symbol*, std::vector<Expression*>);
	Dispatch(const Dispatch&);
	Dispatch& operator=(Dispatch);
	~Dispatch();
	
	virtual void print(int = 0);
};



#endif