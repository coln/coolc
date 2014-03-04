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
	action_t table;
	
	// One way to do it
	actionRow_t rows[numStates];
	rows[0][NT_S] = ACCEPT;
	rows[0][NT_A] = 1;
	rows[0][T_int] = 2;
	rows[0][T_end] = ACCEPT;
	rows[1][T_end] = REDUCE;
	rows[2][T_plus] = 3;
	rows[2][T_end] = REDUCE;
	rows[3][NT_A] = 4;
	rows[3][T_int] = 2;
	rows[4][T_end] = REDUCE;
	int count = numStates;
	while(--count >= 0){
		table.push_back(rows[count]);
	}
	
	table.clear();
	
	// Another way to do it
	std::vector<Symbol> indices(numIndices);
	indices.push_back(NT_A);
	indices.push_back(T_plus);
	indices.push_back(T_int);
	indices.push_back(T_end);
	indices.push_back(NT_S);
	
	int actions[numStates][numIndices - 1] = {
		{ 1, X, 2, ACCEPT },
		{ X, X, X, REDUCE },
		{ X, 3, X, REDUCE },
		{ 4, X, 2, X },
		{ X, X, X, REDUCE }
	};
	
	int i, j;
	actionRow_t row;
	for(i = 0; i < numStates; i++){
		for(j = 0; j < numIndices; j++){
			if(j == numIndices - 1){
				row[NT_S] = ACCEPT;
				continue;
			}
			row[indices[j]] = actions[i][j];
		}
		table.push_back(row);
	}
	
	return table;
}
const reduce_t Parser::initReduceTable(){
	reduce_t table;
	
	int numIndices = 1;
	reduceRow_t rows[numStates](1, ReduceItem(0, T_error));
	rows[1] = ReduceItem(1, NT_S);
	rows[2] = ReduceItem(1, NT_A);
	rows[4] = ReduceItem(3, NT_A);
	int count = numStates;
	while(--count >= 0){
		table.push_back(rows[count]);
	}
	return table;
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

int actionAt(const int &state, const Symbol &next){
	if(next == NT_S) return ACCEPT;
	if
}

// Yea I don't think this is good for large stacks.
void Parser::parseTree(){
	// Reverse the stack
	stack_t reverse;
	int size = parseTree.size();
	while(size-- > 0){
		reverse.push(parseTree.top());
		parseTree.pop();
	}
	size = reverse.size();
	while(size-- > 0){
		std::cout << reverse.top().symbol.value << std::endl;
		reverse.pop();
	}
}

bool Parser::analyze(){
	int index = 0;
	int action = 0;
	Symbol next;
	StackItem *top;
	
	// Init the stack
	stack.push(StackItem(0, Parser::NT_S));
	next = tokenToSymbol(tokens[i]);
	
	while(true){
		top = &stack.top();
		parseTree.push(stack.top());
		if(next == Parser::T_error){
			std::cerr << "Parser: Error in parsing token \"" << token[i].lexeme << "\" ";
			std::cerr << "on line " << token[i].line << std::endl;
		}
		action = actionAt(top->state, next);
		
		if(verbose){
			std::cout << "Top Stack: state = " << top->state << ", next = \"" << next->value << "\"";
			std::cout << std::endl;
			std::cout << "Action: ";
			if(action == ACCEPT) std::cout << "ACCEPT";
			if(action == ERROR) std::cout << "ERROR";
			if(action == REDUCE && stack.size() == 1) std::cout << "REDUCE TO FINAL";
			if(action == REDUCE) std::cout << "REDUCE";
			if(action > 0) std::cout << "SHIFT, GOTO STATE " << action;
			std::cout << std::endl << std::endl;
		}
		
		if(action == ACCEPT){
			if(showTree){
				parseTree();
			}
			return true;
		}else if(action == ERROR){
			std::cerr << "Parser: Error in parsing token \"" << token[i].lexeme << "\" ";
			std::cerr << "on line " << token[i].line << std::endl;
			std::cerr << "Invalid move." << std::endl;
			return false;
		}else if(action == REDUCE){
			ReduceItem reduce = reduceAt(top->state, next);
			int count = reduce.numberOfReduces;
			while(count-- > 0){
				stack.pop();
			}
			next = reduce.symbol;
			i--;
			continue;
		}else if(action > 0){
			stack.push(StackItem(action, next));
			next = tokenToSymbol(tokens[i]);
			i++;
			continue;
		}
	}
}