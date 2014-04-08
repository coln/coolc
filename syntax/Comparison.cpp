#include "Comparison.h"

Comparison::Comparison(Expression *lhs, OpType operation, Expression *rhs)
	: Expression(COMPARISON), lhs(lhs), operation(operation), rhs(rhs)
{
}
Comparison::Comparison(const Comparison& c)
	: Expression(c), lhs(c.lhs), operation(c.operation), rhs(c.rhs)
{
}
Comparison& Comparison::operator=(Comparison c){
	Expression::operator=(c);
	lhs = c.lhs;
	operation = c.operation;
	rhs = c.rhs;
	return *this;
}
Comparison::~Comparison(){
	delete lhs;
	delete rhs;
}

std::string Comparison::typeToString(OpType type){
	switch(type){
		case LESS_THAN: return "<";
		case LESS_THAN_EQUALS: return "<=";
		case EQUALS: return "=";
		case NOT: return "NOT";
	}
	return "";
}

void Comparison::print(int n){
	Expression::print(n);
	std::cout << "comparison" << std::endl;
	lhs->print(n + 1);
	Expression::print(n + 1);
	switch(operation){
		case LESS_THAN: std::cout << "<"; break;
		case LESS_THAN_EQUALS: std::cout << "<="; break;
		case EQUALS: std::cout << "="; break;
		case NOT: std::cout << "not"; break;
	}
	std::cout << std::endl;
	rhs->print(n + 1);
}