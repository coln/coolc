#include "New.h"

New::New(const std::string &type)
	: Expression(NEW), type(type)
{	
}

void New::print(int n){
	Expression::print(n);
	std::cout << "new " << type << std::endl;
}