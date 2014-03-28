#include "Attribute.h"

Attribute::Attribute(){}
Attribute::Attribute(Symbol *symbol)
	: symbol(symbol)
{
}
Attribute::Attribute(Symbol *symbol, Expression *expression)
	: symbol(symbol), expression(expression)
{
}