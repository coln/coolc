#include "Expression.h"

Expression::Expression()
	: type(EXPRESSION)
{
}
Expression::Expression(ExpType e)
	: type(e)
{
}
Expression::Expression(const Expression& e)
	: type(e.type), location(e.location)
{
}
Expression& Expression::operator=(Expression e){
	type = e.type;
	location = e.location;
	return *this;
}
Expression::~Expression(){}

void Expression::print(int n){
	int i = n;
	while(i--){
		std::cout << "  ";
	}
}