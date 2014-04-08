#ifndef COOL_DISPATCH_H_
#define COOL_DISPATCH_H_

#include "Expression.h"

class Dispatch : public Expression {
public:
	std::vector<Expression*> arguments;
	Dispatch(Expression*, std::vector<Expression*>);
	Dispatch(Expression*, Expression*, std::vector<Expression*>);
	Dispatch(Expression*, Expression*, Expression*, std::vector<Expression*>);
};



#endif