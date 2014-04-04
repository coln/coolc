#include "Attribute.h"

Attribute::Attribute()
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
	: Expression(a), symbol(a.symbol), expression(a.expression)
{
}
Attribute& Attribute::operator=(Attribute a){
	Expression::operator=(a);
	std::swap(this->symbol, a.symbol); 
	std::swap(this->expression, a.expression);
	return *this;
}

Attribute::~Attribute(){
	delete symbol;
	delete expression;
}