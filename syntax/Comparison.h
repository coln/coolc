#ifndef COOL_COMPARISON_H_
#define COOL_COMPARISON_H_

#include <string>
#include "Expression.h"

class Comparison : public Expression {
public:
	typedef enum {
		LESS_THAN,
		LESS_THAN_EQUALS,
		EQUALS,
		NOT
	} OpType;
	Expression *lhs;
	OpType operation;
	Expression *rhs;
	
	Comparison(Expression*, OpType, Expression*);
	Comparison(const Comparison&);
	Comparison& operator=(Comparison);
	~Comparison();
	
	static std::string typeToString(OpType);
	virtual void print(int = 0);
};

#endif