#include "Conditional.h"

Conditional::Conditional(Expression* ifBranch, Expression* thenBranch)
	: ifBranch(ifBranch), thenBranch(thenBranch)
{
}
Conditional::Conditional(Expression* ifBranch, Expression* thenBranch,
								Expression* elseBranch)
	: ifBranch(ifBranch), thenBranch(thenBranch), elseBranch(elseBranch)
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