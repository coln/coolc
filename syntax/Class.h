#ifndef COOL_CLASS_H_
#define COOL_CLASS_H_

#include <string>
#include <vector>
#include "Expression.h"
#include "../parser.h"

class Class : public Expression {
public:
	std::string name;
	std::string inherits;
	std::vector<Expression*> features;
	
	Class(const std::string&);
	Class(const std::string&, const std::string&);
	~Class();
};



#endif