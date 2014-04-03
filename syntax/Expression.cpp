#include "Expression.h"

#include <iostream>
Expression::Expression(){}
Expression::Expression(std::string identifier)
	: lhs(NULL), op(""), rhs(NULL)
{
	symbol = new Symbol(identifier, "");
}
Expression::Expression(std::string identifier, std::string type)
	: lhs(NULL), op(""), rhs(NULL)
{
	symbol = new Symbol(identifier, type);
}
Expression::Expression(Expression *lhs, std::string op, Expression *rhs)
	: symbol(NULL), lhs(lhs), op(op), rhs(rhs)
{
}

Expression::Expression(const Expression& e)
	: symbol(e.symbol), lhs(e.lhs), op(e.op), rhs(e.rhs)
{
}
Expression& Expression::operator=(Expression e){
	std::swap(this->symbol, e.symbol);
	std::swap(this->lhs, e.lhs);
	std::swap(this->rhs, e.rhs);
	return *this;
}

Expression::~Expression(){}


void Expression::evaluate(){
	/*bool isArithmatic = (op == "+" || op == "-" || op == "*" || op == "/" || op == "~");
	double arithmetic;
	
	if(op == "+"){
		arithmetic = atof(lhs->constant.c_str()) + atof(rhs->constant.c_str());
	}else if(op == "-"){
		arithmetic = atof(lhs->constant.c_str()) - atof(rhs->constant.c_str());
	}else if(op == "*"){
		arithmetic = atof(lhs->constant.c_str()) + atof(rhs->constant.c_str());
	}else if(op == "/"){
		if(atof(rhs->constant.c_str()) == 0){
			// error divide by zero
		}else{
			arithmetic = atof(lhs->constant.c_str()) / atof(rhs->constant.c_str());
		}
	}
	
	if(isArithmatic){
		constant = itoa((int)arithmetic);
		type = ExpType::INTEGER;
		return;
	}
	
	bool isComparison = (op == "<" || op == "<=" || op == "=" || op == "not");
	bool comparison;
	if(op == "<"){
		comparison = atof(lhs->constant.c_str()) < atof(rhs->constant.c_str());
	}else if(op == "<="){
		comparison = atof(lhs->constant.c_str()) <= atof(rhs->constant.c_str());
	}else if(op == "="){
		comparison = atof(lhs->constant.c_str()) == atof(rhs->constant.c_str());
	}else if(op == "not"){
		comparison = !atof(lhs->constant.c_str());
	}
	
	if(isComparison){
		constant = (comparison) ? "true" : "false";
		type = ExpType::BOOL;
		return;
	}*/
}