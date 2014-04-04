#ifndef COOL_BLOCK_H_
#define COOL_BLOCK_H_

#include <vector>
#include "Expression.h"

class Block : public Expression {
public:
	std::vector<Expression*> expressions;
	Block();
	Block(std::vector<Expression*>);
	Block(const Block&);
	Block& operator=(Block);
	~Block();
};

#endif