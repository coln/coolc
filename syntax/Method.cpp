#include "Method.h"

Method::Method(){}

Method::Method(Symbol *symbol, Expression *expression)
	: symbol(symbol), expression(expression)
{
}
Method::Method(Symbol *symbol, std::vector<Symbol*> arguments, Expression *expression)
	: symbol(symbol), arguments(arguments), expression(expression)
{
}

Method::Method(const Method& m)
	: Expression(m), symbol(m.symbol), expression(m.expression)
{
}
Method& Method::operator=(Method m){
	Expression::operator=(m);
	std::swap(this->symbol, m.symbol);
	std::swap(this->expression, m.expression);
	return *this;
}

Method::~Method(){
	std::vector<Symbol*>::iterator it;
	for(it = arguments.begin(); it != arguments.end(); ++it){
		delete *it;
	}
	delete symbol;
	delete expression;
}