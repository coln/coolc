#include "Block.h"

Block::Block(){}

Block::Block(std::vector<Expression*> expressions)
	: expressions(expressions)
{
}
Block::Block(const Block& b)
	: Expression(b), expressions(b.expressions)
{
}
Block& Block::operator=(Block b){
	Expression::operator=(b);
	expressions = b.expressions;
	return *this;
}
Block::~Block(){
	std::vector<Expression*>::iterator it;
	for(it = expressions.begin(); it != expressions.end(); ++it){
		delete *it;
	}
}