#ifndef COOL_EXPRESSION_H_
#define COOL_EXPRESSION_H_

#include <algorithm>
#include <string>
#include "Symbol.h"
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
	Expression(const Expression&);
	Expression& operator=(Expression);
	~Expression();
	
	void evaluate();
};

#endif