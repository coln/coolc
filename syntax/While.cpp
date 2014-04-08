#include "While.h"

While::While(Expression* condition, Expression* loop)
	: Expression(WHILE), condition(condition), loop(loop)
{
}
While::While(const While& l)
	: Expression(l), condition(l.condition), loop(l.loop)
{
}
While& While::operator=(While l){
	Expression::operator=(l);
	condition = l.condition;
	loop = l.loop;
	return *this;
}
While::~While(){
	delete condition;
	delete loop;
}

void While::print(int n){
	Expression::print(n);
	std::cout << "while" << std::endl;
	condition->print(n + 1);
	Expression::print(n);
	std::cout << "loop" << std::endl;
	loop->print(n);
}