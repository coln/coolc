#include "Attribute.h"

Attribute::Attribute()
	: location(location)
{
}
Attribute::Attribute(Symbol *symbol)
	: symbol(symbol)
{
}
Attribute::Attribute(Symbol *symbol, Expression *expression)
	: symbol(symbol), expression(expression)
{
}
Attribute::Attribute(const Attribute& a)
	: location(a.location), symbol(a.symbol), expression(a.expression)
{
}
Attribute& Attribute::operator=(Attribute a){
	location = a.location;
	std::swap(this->symbol, a.symbol); 
	std::swap(this->expression, a.expression);
	return *this;
}

Attribute::~Attribute(){}