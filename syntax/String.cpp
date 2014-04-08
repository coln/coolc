#include "String.h"

String::String(const std::string &value)
	: Expression(STRING), value(value)
{
}
String::String(const String& b)
	: Expression(b), value(b.value)
{
}
String& String::operator=(const String& b){
	Expression::operator=(b);
	value = b.value;
	return *this;
}
String::~String(){}

void String::print(int n){
	Expression::print(n);
	std::cout << "string " << value << std::endl;
}