#include "Method.h"

Method::Method()
	: Expression(METHOD)
{
}

Method::Method(Symbol *symbol, Expression *expression)
	: Expression(METHOD), symbol(symbol), expression(expression)
{
}
Method::Method(Symbol *symbol, std::vector<Symbol*> arguments, Expression *expression)
	: Expression(METHOD), symbol(symbol), arguments(arguments), expression(expression)
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

void Method::print(int n){
	Expression::print(n);
	std::cout << "method " << symbol->name << ":" << symbol->type << std::endl;
	Expression::print(n + 1);
	std::cout << "method body" << std::endl;
	expression->print(n + 2);
}