#include "Conditional.h"

Conditional::Conditional(Expression* ifBranch, Expression* thenBranch)
	: Expression(CONDITIONAL), ifBranch(ifBranch), thenBranch(thenBranch)
{
}
Conditional::Conditional(Expression* ifBranch, Expression* thenBranch,
								Expression* elseBranch)
	: Expression(CONDITIONAL), ifBranch(ifBranch), 
		thenBranch(thenBranch), elseBranch(elseBranch)
{
}

Conditional::Conditional(const Conditional& c)
	: Expression(c), ifBranch(c.ifBranch), thenBranch(c.thenBranch), elseBranch(c.elseBranch)
{
}
Conditional& Conditional::operator=(Conditional c){
	Expression::operator=(c);
	ifBranch = c.ifBranch;
	thenBranch = c.thenBranch;
	elseBranch = c.elseBranch;
	return *this;
}
Conditional::~Conditional(){
	delete ifBranch;
	delete thenBranch;
	delete elseBranch;
}

void Conditional::print(int n){
	Expression::print(n);
	std::cout << "conditional" << std::endl;
	Expression::print(n + 1);
	std::cout << "if" << std::endl;
	ifBranch->print(n + 2);
	Expression::print(n + 1);
	std::cout << "then" << std::endl;
	thenBranch->print(n + 2);
	if(elseBranch != NULL){
		Expression::print(n + 1);
		std::cout << "else" << std::endl;
		elseBranch->print(n + 2);
	}
}