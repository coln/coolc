#include "Symbol.h"

Symbol::Symbol(const std::string &name, Expression *value)
	: Expression(SYMBOL), name(name), value(value)
{
}
Symbol::Symbol(const std::string &name, const std::string &type, Expression *value)
	:  Expression(SYMBOL), name(name), type(type), value(value)
{
}
Symbol::Symbol(const Symbol& s)
	: Expression(s), name(s.name), type(s.type)
{
}
Symbol& Symbol::operator=(Symbol s){
	Expression::operator=(s);
	name = s.name;
	type = s.type;
	return *this;
}

bool Symbol::operator==(const Symbol &s) const {
	return (name == s.name && type == s.type);
}

void Symbol::print(int n){
	Expression::print(n);
	std::cout << "symbol \"" << name << "\"";
	if(!type.empty()){
		std::cout << ":" << type;
	}
	std::cout << std::endl;
}