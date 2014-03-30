#include "Method.h"

Method::Method(){}

Method::Method(std::string name, std::string type, 
				Expression *expression)
	: expression(expression)
{
	symbol = new Symbol(name, type);
}
Method::Method(std::string name, std::string type,
				std::vector<Symbol*> arguments, Expression *expression)
	: arguments(arguments), expression(expression)
{
	symbol = new Symbol(name, type);
}

Method::Method(const Method& m)
	: location(m.location), symbol(m.symbol), expression(m.expression)
{
}
Method& Method::operator=(Method m){
	location = m.location;
	std::swap(this->symbol, m.symbol);
	std::swap(this->expression, m.expression);
	return *this;
}

Method::~Method(){}