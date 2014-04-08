#ifndef COOL_MATH_H_
#define COOL_MATH_H_

#include <algorithm>
#include <string>
#include "Expression.h"

class Arithmetic : public Expression {
public:
	typedef enum {
		PLUS,
		MINUS,
		TIMES,
		DIVIDE,
		INVERSE
	} OpType;
	Expression *lhs;
	OpType operation;
	Expression *rhs;
	
	Arithmetic(Expression*, OpType, Expression*);
	Arithmetic(const Arithmetic&);
	Arithmetic& operator=(Arithmetic);
	~Arithmetic();
	
	static std::string typeToString(OpType);
	virtual void print(int = 0);
};

#endif