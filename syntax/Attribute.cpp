#include "Attribute.h"

Attribute::Attribute(Symbol *symbol)
	: Expression(ATTRIBUTE), symbol(symbol)
{
}
Attribute::Attribute(Symbol *symbol, Expression *expression)
	: Expression(ATTRIBUTE), symbol(symbol), expression(expression)
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

void Attribute::print(int n){
	Expression::print(n);
	std::cout << "attribute" << std::endl;
	symbol->print(n + 1);
	expression->print(n + 1);
}