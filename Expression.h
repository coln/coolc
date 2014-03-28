#ifndef COOL_EXPRESSION_H_
#define COOL_EXPRESSION_H_

#include <cstdlib>
#include <string>
#include "parser.h"

class Expression {
public:
	Symbol *symbol;
	
	Expression *lhs;
	std::string op;
	Expression *rhs;
	
	Expression();
	Expression(std::string);
	Expression(std::string, std::string);
	Expression(Expression*, std::string, Expression*);
	
	void evaluate();
	std::string itoa(int);
};

#endif