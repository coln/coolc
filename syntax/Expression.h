#ifndef COOL_EXPRESSION_H_
#define COOL_EXPRESSION_H_

#include <iostream>
#include "../parser.h"

class Expression {
public:
	typedef enum {
		EXPRESSION,
		BOOL,
		INT,
		STRING,
		CLASS,
		SYMBOL,
		ATTRIBUTE,
		METHOD,
		ARITHMETIC,
		ASSIGNMENT,
		BLOCK,
		CASE,
		COMPARISON,
		CONDITIONAL,
		DISPATCH,
		ISVOID,
		LET,
		NEW,
		WHILE
	} ExpType;
	ExpType type;
	yy::location location;
	
	Expression();
	Expression(ExpType);
	Expression(const Expression&);
	Expression& operator=(Expression);
	virtual ~Expression();
	
	static ExpType getType(const std::string&);
	virtual void print(int = 0);
	
	// For interpreter
	//virtual void evaluate();
	
	// For compiler
	// virtual void assemble();
};

#endif