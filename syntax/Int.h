#ifndef COOL_INT_H_
#define COOL_INT_H_

#include "Expression.h"

class Int : public Expression {
public:
	std::string value;
	
	Int();
	Int(const std::string&);
	Int(const Int&);
	Int& operator=(const Int&);
	~Int();
	
	virtual void print(int = 0);
};

#endif