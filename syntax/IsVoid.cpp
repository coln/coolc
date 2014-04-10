#include "IsVoid.h"

IsVoid::IsVoid(Expression *expression)
	: Expression(ISVOID), expression(expression)
{
}

void IsVoid::print(int n){
	Expression::print(n);
	std::cout << "isvoid" << std::endl;
	expression->print(n + 1);
}