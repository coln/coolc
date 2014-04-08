#include "Arithmetic.h"

Arithmetic::Arithmetic(Expression *lhs, OpType operation, Expression *rhs)
	: Expression(ARITHMETIC), lhs(lhs), operation(operation), rhs(rhs)
{
}
Arithmetic::Arithmetic(const Arithmetic& m)
	: Expression(m), lhs(m.lhs), operation(m.operation), rhs(m.rhs)
{
}
Arithmetic& Arithmetic::operator=(Arithmetic m){
	Expression::operator=(m);
	std::swap(lhs, m.lhs);
	std::swap(rhs, m.rhs);
	operation = m.operation;
	return *this;
}
Arithmetic::~Arithmetic(){
	delete lhs;
	delete rhs;
}

std::string Arithmetic::typeToString(OpType type){
	switch(type){
		case PLUS: return "+";
		case MINUS: return "-";
		case TIMES: return "*";
		case DIVIDE: return "/";
		case INVERSE: return "~";
	}
	return "";
}

void Arithmetic::print(int n){
	Expression::print(n);
	std::cout << "Arithmetic" << std::endl;
	lhs->print(n + 1);
	Expression::print(n);
	switch(operation){
		case PLUS: std::cout << "+"; break;
		case MINUS: std::cout << "-"; break;
		case TIMES: std::cout << "*"; break;
		case DIVIDE: std::cout << "/"; break;
		case INVERSE: std::cout << "~"; break;
	}
	std::cout << std::endl;
	rhs->print(n + 1);
}