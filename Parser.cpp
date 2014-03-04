#include "Parser.h"

// Init tables
int Parser::actionTable[4][4] = {
	{ 1, X, 1, ACCEPT },
	{ X, X, X, REDUCE },
	{ X, X, 1, X },
	{ X, 2, X, REDUCE }
};

Parser::Parser()
		: verbose(false), showTree(false),
		  NT_S("S"), NT_A("A"),
		  T_plus("+"), T_int("int"), T_end("$"), T_error("error")
{
	if(reduceTable.size() > 0){
		return;
	}
	
	int numRows;
	stackVector_t rows[numRows];
	rows[0].push_back(ReduceItem(0, 0, T_error));
	rows[1].push_back(ReduceItem(3, 1, NT_A));
	rows[2].push_back(ReduceItem(0, 0, T_error));
	rows[3].push_back(ReduceItem(1, 1, NT_A));
	reduceTable_t v(numRows);
	v.push_back(rows[0]);
	v.push_back(rows[1]);
	v.push_back(rows[2]);
	v.push_back(rows[3]);
	reduceTable.assing(v.begin(), v.end());
}
Parser::~Parser(){
	stack.clear();
	tokens.clear();
}

Symbol& Parser::tokenToSymbol(const Token& token){
	if(token.type == TokenType::PLUS) return T_plus;
	if(token.type == TokenType::INTEGER) return T_int;
	if(token.type == TokenType::END) return T_end;
	return T_error;
}

bool Parser::analyze(){
	int index = 0;
	int action = 0;
	Symbol next;
	StackItem *top;
	
	// Init the stack
	stack.push(StackItem(0, NT_S));
	
	while(true){
		top = &stack.top();
		next = tokenToSymbol(tokens[i]);
		if(next == T_error){
			std::cerr << "Parser: Error in parsing token \"" << token[i].value << "\" ";
			std::cerr << "on line " << token[i].line;
			std::cerr << std::endl;
		}
		action = actionAt(top->state, next);
	}
}