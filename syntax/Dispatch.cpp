#include "Dispatch.h"

Dispatch::Dispatch(Symbol *symbol)
	: Expression(DISPATCH), symbol(symbol)
{
}
Dispatch::Dispatch(Symbol *symbol, std::vector<Expression*> arguments)
	: Expression(DISPATCH), symbol(symbol), arguments(arguments)
{
}
Dispatch::Dispatch(const Dispatch &d)
	: Expression(d), symbol(d.symbol), arguments(d.arguments)
{
}
Dispatch& Dispatch::operator=(Dispatch d){
	Expression::operator=(d);
	std::swap(this->symbol, d.symbol);
	std::swap(this->arguments, d.arguments);
	return *this;
}
Dispatch::~Dispatch(){
	delete symbol;
	std::vector<Expression*>::iterator it;
	for(it = arguments.begin(); it != arguments.end(); ++it){
		delete *it;
	}
}

void Dispatch::print(int n){
	Expression::print(n);
	std::cout << "dispatch" << std::endl;
	symbol->print(n + 1);
	Expression::print(n + 1);
	std::cout << "arguments" << std::endl;
	
	std::vector<Expression*>::iterator it;
	for(it = arguments.begin(); it != arguments.end(); ++it){
		(*it)->print(n + 2);
	}
}