#ifndef COOL_METHOD_H_
#define COOL_METHOD_H_

#include <string>
#include <vector>
#include "Expression.h"

class Method {
public:
	std::string name;
	//UserTypes type;
	std::string type;
	std::vector<Symbol*> *arguments;
	Expression *expression;
	
	Method(){}
	Method(std::string name, std::string type, Expression *expression)
		: name(name), type(type), expression(expression) {}
	Method(std::string name, std::string type,
				std::vector<Symbol*> *arguments, Expression *expression)
		: name(name), type(type), arguments(arguments), expression(expression) {} 
};

#endif