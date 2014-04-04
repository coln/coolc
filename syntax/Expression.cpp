#include "Expression.h"

Expression::Expression(){}
/*Expression::Expression(Symbol *constant)
	: constant(constant)
{
}
Expression::Expression(Assignment *assignment)
	: assignment(assignment)
{
}

Expression::Expression(Expression *lhs, std::string op, Expression *rhs)
	: symbol(NULL), lhs(lhs), op(op), rhs(rhs)
{
}
*/
Expression::Expression(const Expression& e)
	: location(e.location)
{
}
Expression& Expression::operator=(Expression e){
	location = e.location;
	return *this;
}

Expression::~Expression(){}