#ifndef COOL_EXPRESSION_H_
#define COOL_EXPRESSION_H_

#include "../parser.h"

class Expression {
public:
	yy::location location;
	
	Expression();
	Expression(const Expression&);
	Expression& operator=(Expression);
	~Expression();
	
	// For interpreter
	//virtual void evaluate();
	
	// For compiler
	// virtual void assemble();
};

#endif