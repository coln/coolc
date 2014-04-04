#ifndef COOL_ASSIGNMENT_H_
#define COOL_ASSIGNMENT_H_

#include "Expression.h"

class Assignment : public Expression {
public:
	Expression *identifier;
	Expression *expression;
	Assignment(Expression*, Expression*);
	~Assignment();
};

#endif