#include "Symbol.h"

Symbol::Symbol(const std::string name, const std::string type)
	: name(name), type(type)
{
}

bool Symbol::operator==(const Symbol &s) const {
	return (name == s.name && type == s.type);
}
