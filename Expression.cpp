#include "Expression.h"

Expression::Expression(){}
Expression::Expression(std::string identifier){
	symbol = new Symbol(identifier, "");
}
Expression::Expression(std::string identifier, std::string type){
	symbol = new Symbol(identifier, type);
}
Expression::Expression(Expression *lhs, std::string op, Expression *rhs)
	: lhs(lhs), op(op), rhs(rhs)
{	
}


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

/* itoa:  convert n to characters in s */
std::string Expression::itoa(int n){
	int sign;
	std::string str;

	if((sign = n) < 0){  /* record sign */
		n = -n;          /* make n positive */
	}
	
	char c[2];
	do {       /* generate digits in reverse order */
		c[0] = n % 10 + '0';
		c[1] = '\0';
		str.insert(0, c);   /* get next digit */
	} while ((n /= 10) > 0);     /* delete it */
	
	if(sign < 0){
		str.insert(0, "-");
	}
	return str;
}