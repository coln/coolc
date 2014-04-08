#include "Int.h"

Int::Int(){}
Int::Int(const std::string &value)
	: Expression(INT), value(value)
{
}
Int::Int(const Int& i)
	: Expression(i), value(i.value)
{
}
Int& Int::operator=(const Int& i){
	Expression::operator=(i);
	value = i.value;
	return *this;
}
Int::~Int(){}

void Int::print(int n){
	Expression::print(n);
	std::cout << "Int " << value << std::endl;
}