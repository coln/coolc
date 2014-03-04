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
	stack.push(StackItem(0, NT_S));
	
	while(true){
		top = &stack.top();
		parseTree.push(stack.top());
		next = tokenToSymbol(tokens[i]);
		if(next == T_error){
			std::cerr << "Parser: Error in parsing token \"" << token[i].value << "\" ";
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
			std::cerr << "Parser: Error in parsing token \"" << token[i].value << "\" ";
			std::cerr << "on line " << token[i].line << std::endl;
			std::cerr << "Invalid move." << std::endl;
			return false;
		}else if(action == REDUCE && stack.size() == 1){
			// The initial stack item accepts
			stack.pop();
			continue;
		}else if(action == REDUCE){
			ReduceItem reduce = reduceAt(top->state, next);
			int count = reduce.numberOfReduces;
			while(count-- > 0){
				stack.pop();
			}
			stack.push(StackItem(reduce.goto, reduce.Symbol));
			continue;
		}else if(action > 0){
			stack.push(StackItem(action, next));
			i++;
			continue;
		}
	}
}