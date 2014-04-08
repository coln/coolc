#include "Let.h"

Let::Let(std::vector<Attribute*> attributes, Expression* expression)
	: Expression(LET), attributes(attributes), expression(expression)
{	
}
Let::Let(const Let& l)
	: Expression(l), attributes(l.attributes), expression(l.expression)
{
}
Let& Let::operator=(Let l){
	Expression::operator=(l);
	attributes = l.attributes;
	expression = l.expression;
	return *this;
}
Let::~Let(){
	std::vector<Attribute*>::iterator it;
	for(it = attributes.begin(); it != attributes.end(); ++it){
		delete *it;
	}
	delete expression;
}

void Let::print(int n){
	Expression::print(n);
	std::cout << "let" << std::endl;
	std::vector<Attribute*>::iterator it;
	for(it = attributes.begin(); it != attributes.end(); ++it){
		(*it)->print(n + 1);
	}
	Expression::print(n);
	std::cout << "in" << std::endl;
	expression->print(n + 1);
}