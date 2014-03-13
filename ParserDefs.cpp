#include "Parser.h"

// Init tables
const int Parser::numStates = 13;
const NonTerminal Parser::NT_S("S");
const NonTerminal Parser::NT_A("A");
const NonTerminal Parser::NT_B("B");
const Terminal Parser::T_plus("+");
const Terminal Parser::T_times("*");
const Terminal Parser::T_lparen("(");
const Terminal Parser::T_rparen(")");
const Terminal Parser::T_int("int");
const Terminal Parser::T_end("$");
const Terminal Parser::T_error("error");
const action_t Parser::actionTable = Parser::initActionTable();
const reduce_t Parser::reduceTable = Parser::initReduceTable();
const action_t Parser::initActionTable() {
	// The rest will automatically init to 0 (X/ERROR)
	action_t table(numStates);
	
	// Grammar 03
	table[0][NT_S] = ACCEPT;
	table[0][NT_A] = 1;
	table[0][T_lparen] = 10;
	table[0][T_int] = 9;
	table[0][T_end] = ACCEPT;
	table[1][T_end] = REDUCE;
	table[2][T_plus] = 3;
	table[3][NT_A] = 4;
	table[3][NT_B] = 8;
	table[3][T_lparen] = 10;
	table[3][T_int] = 9;
	table[4][T_plus] = REDUCE;
	table[4][T_times] = REDUCE;
	table[4][T_rparen] = REDUCE;
	table[4][T_end] = REDUCE;
	table[5][T_times] = 6;
	table[6][NT_A] = 7;
	table[6][NT_B] = 8;
	table[6][T_lparen] = 10;
	table[6][T_int] = 9;
	table[7][T_plus] = REDUCE;
	table[7][T_times] = REDUCE;
	table[7][T_rparen] = REDUCE;
	table[7][T_end] = REDUCE;
	table[8][T_plus] = REDUCE;
	table[8][T_times] = REDUCE;
	table[8][T_rparen] = REDUCE;
	table[8][T_end] = REDUCE;
	table[9][T_plus] = REDUCE;
	table[9][T_times] = REDUCE;
	table[9][T_rparen] = REDUCE;
	table[9][T_end] = REDUCE;
	table[10][NT_A] = 11;
	table[10][NT_B] = 8;
	table[10][T_lparen] = 10;
	table[10][T_int] = 9;
	table[11][T_rparen] = 12;
	table[12][T_plus] = REDUCE;
	table[12][T_times] = REDUCE;
	table[12][T_rparen] = REDUCE;
	table[12][T_end] = REDUCE;
	
	return table;
}
const reduce_t Parser::initReduceTable(){
	reduce_t table(numStates);
	table[0][T_end] = ReduceItem(1, NT_S);
	table[4][T_plus] = ReduceItem(3, NT_A);
	table[4][T_times] = ReduceItem(3, NT_A);
	table[4][T_rparen] = ReduceItem(3, NT_A);
	table[4][T_end] = ReduceItem(3, NT_A);
	table[7][T_plus] = ReduceItem(3, NT_A);
	table[7][T_times] = ReduceItem(3, NT_A);
	table[7][T_rparen] = ReduceItem(3, NT_A);
	table[7][T_end] = ReduceItem(3, NT_A);
	table[8][T_plus] = ReduceItem(1, NT_B);
	table[8][T_times] = ReduceItem(1, NT_B);
	table[8][T_rparen] = ReduceItem(1, NT_B);
	table[8][T_end] = ReduceItem(1, NT_B);
	table[9][T_plus] = ReduceItem(1, NT_B);
	table[9][T_times] = ReduceItem(1, NT_B);
	table[9][T_rparen] = ReduceItem(1, NT_B);
	table[9][T_end] = ReduceItem(1, NT_B);
	table[12][T_plus] = ReduceItem(3, NT_B);
	table[12][T_times] = ReduceItem(3, NT_B);
	table[12][T_rparen] = ReduceItem(3, NT_B);
	table[12][T_end] = ReduceItem(3, NT_B);
	return table;
}