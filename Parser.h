#ifndef COOL_PARSER_H_
#define COOL_PARSER_H_

#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include "Token.h"

struct StackItem {
	int state;
	Symbol symbol;
	StackItem(int state = 0, Symbol s = Symbol()) : state(state), symol(s) {}
};
struct ReduceItem {
	int numberOfReduces;
	int gotoState;
	Symbol replaceBy;
	ReduceItem(const int &number, const int &gotoState, const Symbol &replaceBy)
			: numberOfReduces(number), gotoState(gotoState), replaceBy(replaceBy) {}
};

class Parser {
private:
	enum States {
		ACCEPT = 0,
		X = -1, // ERROR
		REDUCE = -2,
		// SHIFT > 0
	}
	typedef std::stack<StackItem> stack_t;
	stack_t stack;
	stack_t parseTree;
	
	typedef std::vector<StackItem> stackVector_t;
	typedef std::vector<stackVector_t> reduceTable_t;
	static int actionTable[4][4];
	static reduceTable_t reduceTable;
	
	NonTerminal NT_S, NT_A;
	Terminal T_plus, T_int, T_end, T_error;
	
	int actionAt(const int&, const Symbol&);
	ReduceItem reduceAt(const int&, const Symbol&);
	Symbol& tokenToSymbol(const Token&);
	void showParseTree();
	
public:
	bool verbose;
	bool showTree;
	std::vector<Token> tokens;
	Parser();
	~Parser();
	bool analyze();
};

#endif