#include "Method.h"

Method::Method(){}
Method::Method(std::string name, std::string type, Expression *expression){
	symbol = new Symbol(name, type);
	this->expression = expression;
}
Method::Method(std::string name, std::string type,
				std::vector<Symbol*> arguments, Expression *expression)
{
	symbol = new Symbol(name, type);
	this->arguments = arguments;
	this->expression = expression;
}

Method::Method(const Method& m)
	: symbol(m.symbol), expression(m.expression)
{
}
Method& Method::operator=(Method m){
	std::swap(this->symbol, m.symbol);
	std::swap(this->expression, m.expression);
	return *this;
}

Method::~Method(){
	delete symbol;
	delete expression;
	std::vector<Symbol*>::iterator it;
	for(it = arguments.begin(); it < arguments.end(); ++it){
		delete *it;
	}
	std::vector<Attribute*>::iterator it2;
	for(it2 = attributes.begin(); it2 < attributes.end(); ++it2){
		delete *it2;
	}
	arguments.clear();
	attributes.clear();
}