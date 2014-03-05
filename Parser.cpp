#include "Parser.h"

// Init tables
const int Parser::numStates = 5;
const int Parser::numSymbols = 5;
const NonTerminal Parser::NT_S("S");
const NonTerminal Parser::NT_A("A");
const Terminal Parser::T_plus("+");
const Terminal Parser::T_int("int");
const Terminal Parser::T_end("$");
const Terminal Parser::T_error("error");
const action_t Parser::actionTable = Parser::initActionTable();
const reduce_t Parser::reduceTable = Parser::initReduceTable();
const action_t Parser::initActionTable() {
	action_t table(numStates);
	
	// One way to do it
	// The rest will automatically init to 0 (X/ERROR)
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
	int numIndices = 1;
	reduceRow_t blankRow(numIndices, ReduceItem(0, T_error));
	reduce_t table(numStates, blankRow);
	
	table[1][0] = ReduceItem(1, NT_S);
	table[2][0] = ReduceItem(1, NT_A);
	table[4][0] = ReduceItem(3, NT_A);
	
	return table;
}


Parser::~Parser(){
	int size = stack.size();
	while(size-- > 0){
		stack.pop();
	}
	tokens.clear();
}

Symbol Parser::tokenToSymbol(const Token& token){
	if(token.type == TokenType::PLUS) return T_plus;
	if(token.type == TokenType::INTEGER) return T_int;
	if(token.type == TokenType::END) return T_end;
	return T_error;
}

int Parser::actionAt(const int &state, const Symbol &next){
	return actionTable[state].find(next)->second;
}
ReduceItem Parser::reduceAt(const int &state, const Symbol &next){
	// There is only one index for every state, see Grammar
	return reduceTable[state][0];
}

// Yea I don't think this is good for large stacks.
void Parser::updateParseTree(){
	// Reverse the stack
	stack_t stack2 = stack;
	stack_t reverse;
	int size = stack2.size();
	while(size-- > 0){
		reverse.push(stack2.top());
		stack2.pop();
	}
	size = reverse.size();
	while(size-- > 0){
		parseTree += reverse.top().symbol.value + " ";
		reverse.pop();
	}
	parseTree += '\n';
}

bool Parser::analyze(){
	int index = 0;
	int action = 0;
	Symbol next;
	StackItem *top;
	
	// Init the stack
	stack.push(StackItem(0, Parser::NT_S));
	next = tokenToSymbol(tokens[index]);
	
	while(true){
		top = &stack.top();
		if(next == T_error){
			std::cerr << "Parser: Error in parsing token \"" << tokens[index].lexeme << "\" ";
			std::cerr << "on line " << tokens[index].line << std::endl;
		}
		action = actionAt(top->state, next);
		
		if(verbose){
			std::cout << "Top Stack: state = " << top->state << ", next = \"" << next.value << "\"";
			std::cout << std::endl;
			std::cout << "Action: ";
			if(action == ACCEPT) std::cout << "ACCEPT";
			if(action == X) std::cout << "ERROR";
			if(action == REDUCE && stack.size() == 1) std::cout << "REDUCE TO FINAL";
			if(action == REDUCE) std::cout << "REDUCE";
			if(action > 0) std::cout << "SHIFT, GOTO STATE " << action;
			std::cout << std::endl;
		}
		
		updateParseTree();
		
		if(action == ACCEPT){
			if(showTree){
				std::cout << parseTree << std::endl;
			}
			return true;
		}else if(action == X){
			std::cerr << "Parser: Error in parsing token \"" << tokens[index].lexeme << "\" ";
			std::cerr << "on line " << tokens[index].line << std::endl;
			std::cerr << "Invalid move." << std::endl;
			return false;
		}else if(action == REDUCE){
			ReduceItem reduce = reduceAt(top->state, next);
			int count = reduce.numberOfReduces;
			while(count-- > 0){
				stack.pop();
			}
			next = reduce.replaceBy;
			index--;
			continue;
		}else if(action > 0){
			index++;
			stack.push(StackItem(action, next));
			next = tokenToSymbol(tokens[index]);
			continue;
		}
	}
}