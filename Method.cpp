#include "Method.h"

Method::Method(){}
Method::Method(std::string name, std::string type, Expression *expression){
	symbol = new Symbol(name, type);
	this->expression = expression;
}
Method::Method(std::string name, std::string type,
				std::vector<Symbol*> *arguments, Expression *expression)
{
	symbol = new Symbol(name, type);
	this->arguments = arguments;
	this->expression = expression;
}