#include "Block.h"

Block::Block()
	: Expression(BLOCK)
{
}

Block::Block(std::vector<Expression*> expressions)
	: Expression(BLOCK), expressions(expressions)
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

void Block::addChild(Expression *expression){
	expressions.push_back(expression);
}

void Block::print(int n){
	Expression::print(n);
	std::cout << "block" << std::endl;
	std::vector<Expression*>::iterator it;
	for(it = expressions.begin(); it != expressions.end(); ++it){
		(*it)->print(n + 1);
	}
}