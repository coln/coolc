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
	StackItem(int state = 0, Symbol s = Symbol()) : state(state), symol(s) {}
};
struct ReduceItem {
	int numberOfReduces;
	Symbol replaceBy;
	ReduceItem(const int &number, const Symbol &replaceBy)
			: numberOfReduces(number), replaceBy(replaceBy) {}
};

class Parser {
private:
	typedef std::map<Symbol, int> actionRow_t;
	typedef std::vector<actionRow_t> action_t;
	typedef std::vector<ReduceItem> reduceRow_t;
	typedef std::vector<reduceRow_t> reduce_t;
	static const action_t actionTable;
	static const reduceTable_t reduceTable;
	NonTerminal NT_S, NT_A;
	Terminal T_plus, T_int, T_end, T_error;
	
	enum States {
		ACCEPT = 0,
		X = -1, // ERROR
		REDUCE = -2,
		// SHIFT > 0
	}
	int numStates;
	typedef std::stack<StackItem> stack_t;
	stack_t stack;
	stack_t parseTree;
	
	static action_t initActionTable();
	static reduce_t initReduceTable();
	int actionAt(const int&, const Symbol&);
	ReduceItem reduceAt(const int&, const Symbol&);
	Symbol& tokenToSymbol(const Token&);
	void showParseTree();
	
public:
	bool verbose;
	bool showTree;
	std::vector<Token> tokens;
	Parser() : verbose(false), showTree(false),
					numStates(5),
					NT_S("S"), NT_A("A"),
					T_plus("+"), T_int("int"), T_end("$"), T_error("error");
	~Parser();
	bool analyze();
};

#endif