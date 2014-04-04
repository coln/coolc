#include "Assignment.h"

Assignment::Assignment(Expression *identifier, Expression *expression)
	: identifier(identifier), expression(expression)
{
}

Assignment::~Assignment(){
	delete expression;
}