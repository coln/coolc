#include "Bool.h"

Bool::Bool(const std::string &value)
	: Expression(BOOL), value(value)
{
}
Bool::Bool(const Bool& b)
	: Expression(b), value(b.value)
{
}
Bool& Bool::operator=(const Bool& b){
	Expression::operator=(b);
	value = b.value;
	return *this;
}
Bool::~Bool(){}

void Bool::print(int n){
	Expression::print(n);
	std::cout << "bool " << value << std::endl;
}