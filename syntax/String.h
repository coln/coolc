#ifndef COOL_STRING_H_
#define COOL_STRING_H_

#include "Expression.h"

class String : public Expression {
public:
	std::string value;
	
	String(const std::string&);
	String(const String&);
	String& operator=(const String&);
	~String();
	
	virtual void print(int = 0);
};

#endif