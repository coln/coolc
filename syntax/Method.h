#ifndef COOL_METHOD_H_
#define COOL_METHOD_H_

class Symbol;
class Attribute;
class Expression;

#include <algorithm>
#include <string>
#include <vector>
#include "Symbol.h"
#include "Attribute.h"
#include "Expression.h"

class Method {
public:
	yy::location location;
	Symbol* symbol;
	std::vector<Symbol*> arguments;
	Expression *expression;
	
	Method();
	Method(std::string, std::string, Expression*);
	Method(std::string, std::string, std::vector<Symbol*>, Expression*);
	Method(const Method&);
	Method& operator=(Method);
	~Method();
};

#endif