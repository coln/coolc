#ifndef COOL_LOOP_H_
#define COOL_LOOP_H_

#include "Expression.h"

class Loop : public Expression {
public:
	Expression *condition;
	Expression *loop;
	Loop(Expression*, Expression*);
	Loop(const Loop&);
	Loop& operator=(Loop);
	~Loop();
};

#endif