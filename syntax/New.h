#ifndef COOL_NEW_H_
#define COOL_NEW_H_

#include "Expression.h"

class New : public Expression {
public:
	std::string type;
	
	New(const std::string&);
	
	virtual void print(int = 0);
};

#endif