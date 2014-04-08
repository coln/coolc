#ifndef COOL_ASSIGNMENT_H_
#define COOL_ASSIGNMENT_H_

#include "Symbol.h"
#include "Expression.h"

class Assignment : public Expression {
public:
	Symbol *symbol;
	Expression *expression;
	
	Assignment(Symbol*, Expression*);
	Assignment(const Assignment&);
	Assignment& operator=(Assignment);
	~Assignment();
	
	virtual void print(int = 0);
};

#endif