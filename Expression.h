#ifndef COOL_EXPRESSION_H_
#define COOL_EXPRESSION_H_

#include <string>

struct ExpType {
	enum Enum {
		INT,
		BOOL,
		STRING,
		IDENTIFIER,
		SELF
	} e;
	ExpType(Enum e = INT) : e(e) {}
	operator Enum(){ return e; }
};

class Expression {
public:
	std::string constant;
	ExpType type;
	
	Expression *lhs;
	std::string op;
	Expression *rhs;
	
	Expression(){}
	Expression(std::string constant, ExpType type)
		: constant(constant), type(type) {}
	Expression(Expression *lhs, std::string op, Expression *rhs)
		: lhs(lhs), op(op), rhs(rhs) {}
	
	void evaluate();
};

#endif