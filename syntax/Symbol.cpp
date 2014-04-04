#include "Symbol.h"

Symbol::Symbol(const std::string &name)
	: name(name)
{
}
Symbol::Symbol(const std::string &name, const std::string &type)
	: name(name), type(type)
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
