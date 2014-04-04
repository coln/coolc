#include "Loop.h"

Loop::Loop(Expression* condition, Expression* loop)
	: condition(condition), loop(loop)
{
}
Loop::Loop(const Loop& l)
	: Expression(l), condition(l.condition), loop(l.loop)
{
}
Loop& Loop::operator=(Loop l){
	Expression::operator=(l);
	condition = l.condition;
	loop = l.loop;
	return *this;
}
Loop::~Loop(){
	delete condition;
	delete loop;
}