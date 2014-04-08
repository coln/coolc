#ifndef COOL_WHILE_H_
#define COOL_WHILE_H_

#include "Expression.h"

class While : public Expression {
public:
	Expression *condition;
	Expression *loop;
	
	While(Expression*, Expression*);
	While(const While&);
	While& operator=(While);
	~While();
	
	virtual void print(int = 0);
};

#endif