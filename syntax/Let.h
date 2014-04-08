#ifndef COOL_LET_H_
#define COOL_LET_H_

#include "Attribute.h"
#include "Expression.h"

class Let : public Expression {
public:
	std::vector<Attribute*> attributes;
	Expression *expression;
	
	Let(std::vector<Attribute*>, Expression*);
	Let(const Let&);
	Let& operator=(Let);
	~Let();
	
	virtual void print(int = 0);
};

#endif