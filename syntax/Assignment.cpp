#include "Assignment.h"

Assignment::Assignment(Symbol *symbol, Expression *expression)
	: Expression(ASSIGNMENT), symbol(symbol), expression(expression)
{
}

Assignment::Assignment(const Assignment& a)
	: Expression(a), symbol(a.symbol), expression(a.expression)
{
}
Assignment& Assignment::operator=(Assignment a){
	Expression::operator=(a);
	symbol = a.symbol;
	expression = a.expression;
	return *this;
}
Assignment::~Assignment(){
	delete symbol;
	delete expression;
}

void Assignment::print(int n){
	Expression::print(n);
	std::cout << "assignment" << std::endl;
	symbol->print(n + 1);
	expression->print(n + 1);
}