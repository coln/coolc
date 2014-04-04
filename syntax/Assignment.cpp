#include "Assignment.h"

Assignment::Assignment(Expression *identifier, Expression *expression)
	: identifier(identifier), expression(expression)
{
}

Assignment::Assignment(const Assignment& a)
	: Expression(a), identifier(a.identifier), expression(a.expression)
{
}
Assignment& Assignment::operator=(Assignment a){
	Expression::operator=(a);
	identifier = a.identifier;
	expression = a.expression;
	return *this;
}

Assignment::~Assignment(){
	delete identifier;
	delete expression;
}