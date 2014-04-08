#include "Case.h"

Case::Case(Expression *expression, std::vector<Attribute*> branches)
	: Expression(CASE), expression(expression), branches(branches)
{
}
Case::Case(const Case& c)
	: Expression(c), expression(c.expression), branches(c.branches)
{
}
Case& Case::operator=(Case c){
	Expression::operator=(c);
	expression = c.expression;
	branches = c.branches;
	return *this;
}
Case::~Case(){
	std::vector<Attribute*>::iterator it;
	for(it = branches.begin(); it != branches.end(); ++it){
		delete *it;
	}
	delete expression;
}

void Case::print(int n){
	Expression::print(n);
	std::cout << "case" << std::endl;
	expression->print(n + 1);
	Expression::print(n);
	std::cout << "branches" << std::endl;
	
	std::vector<Attribute*>::iterator it;
	for(it = branches.begin(); it != branches.end(); ++it){
		(*it)->print(n + 1);
	}
}