#ifndef COOL_CONDITIONAL_H_
#define COOL_CONDITIONAL_H_

#include "Expression.h"

class Conditional : public Expression {
public:
	Expression *ifBranch;
	Expression *thenBranch;
	Expression *elseBranch;
	Conditional(Expression*, Expression*);
	Conditional(Expression*, Expression*, Expression*);
	Conditional(const Conditional&);
	Conditional& operator=(Conditional);
	~Conditional();
};

#endif