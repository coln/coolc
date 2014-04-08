#ifndef COOL_CASE_H_
#define COOL_CASE_H_

#include "Attribute.h"
#include "Expression.h"

class Case : public Expression {
public:
	Expression *expression;
	std::vector<Attribute*> branches;
	
	Case(Expression*, std::vector<Attribute*>);
	Case(const Case&);
	Case& operator=(Case);
	~Case();
	
	virtual void print(int = 0);
};

#endif