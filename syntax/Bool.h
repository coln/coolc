#ifndef COOL_BOOL_H_
#define COOL_BOOL_H_

#include "Expression.h"

class Bool : public Expression {
public:
	std::string value;
	
	Bool(const std::string&);
	Bool(const Bool&);
	Bool& operator=(const Bool&);
	~Bool();
	
	virtual void print(int = 0);
};

#endif