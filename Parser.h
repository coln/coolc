#ifndef COOL_PARSER_H_
#define COOL_PARSER_H_

#include <iostream>
#include <map>
#include <string>
#include <stack>
#include <vector>
#include "Token.h"
#include "Symbol.h"

struct StackItem {
	int state;
	Symbol symbol;
	StackItem(int state = 0, Symbol s = Symbol()) : state(state), symbol(s) {}
};
struct ReduceItem {
	int numberOfReduces;
	Symbol replaceBy;
	ReduceItem(const int &number, const Symbol &replaceBy)
			: numberOfReduces(number), replaceBy(replaceBy) {}
};

typedef std::map<Symbol, int> actionRow_t;
typedef std::vector<actionRow_t> action_t;
typedef std::vector<ReduceItem> reduceRow_t;
typedef std::vector<reduceRow_t> reduce_t;


class Parser {
private:
	static const int numStates;
	static const int numSymbols;
	static const NonTerminal NT_S, NT_A;
	static const Terminal T_plus, T_int, T_end, T_error;
	static const action_t actionTable;
	static const reduce_t reduceTable;
	
	enum States {
		X = 0, // ERROR
		ACCEPT = -1, // ERROR
		REDUCE = -2,
		// SHIFT > 0
	};
	typedef std::stack<StackItem> stack_t;
	stack_t stack;
	stack_t parseTree;
	
	static const action_t initActionTable();
	static const reduce_t initReduceTable();
	int actionAt(const int&, const Symbol&);
	ReduceItem reduceAt(const int&, const Symbol&);
	Symbol& tokenToSymbol(const Token&);
	void showParseTree();
	
public:
	bool verbose;
	bool showTree;
	std::vector<Token> tokens;
	Parser() : verbose(false), showTree(false) {}
	~Parser();
	bool analyze();
};

#endif