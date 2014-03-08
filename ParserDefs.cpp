#include "Parser.h"

// Init tables
const int Parser::numStates = 5;
const NonTerminal Parser::NT_S("S");
const NonTerminal Parser::NT_A("A");
const Terminal Parser::T_plus("+");
const Terminal Parser::T_int("int");
const Terminal Parser::T_end("$");
const Terminal Parser::T_error("error");
const action_t Parser::actionTable = Parser::initActionTable();
const reduce_t Parser::reduceTable = Parser::initReduceTable();
const action_t Parser::initActionTable() {
	// The rest will automatically init to 0 (X/ERROR)
	action_t table(numStates);
	
	// Grammar 01
	table[0][NT_S] = ACCEPT;
	table[0][NT_A] = 1;
	table[0][T_int] = 2;
	table[0][T_end] = ACCEPT;
	table[1][T_end] = REDUCE;
	table[2][T_plus] = 3;
	table[2][T_end] = REDUCE;
	table[3][NT_A] = 4;
	table[3][T_int] = 2;
	table[4][T_end] = REDUCE;
	
	return table;
}
const reduce_t Parser::initReduceTable(){
	reduce_t table(numStates);
	table[1][T_end] = ReduceItem(1, NT_S);
	table[2][T_end] = ReduceItem(1, NT_A);
	table[4][T_end] = ReduceItem(3, NT_A);
	return table;
}