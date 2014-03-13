#include "Lexer.h"

Lexer::Lexer() : verbose(false) {};
Lexer::~Lexer(){
	input.clear();
	tokens.clear();
}

TokenType Lexer::getNextType(){
	if(input.size() <= 0){
		return TokenType::END;
	}
	char c = input[0];
	if(c == ' ' || c == '\t' || c == '\n') return TokenType::WHITESPACE;
	if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) return TokenType::LETTER;
	if(c >= '0' && c <= '9') return TokenType::DIGIT;
	if(c == '+') return TokenType::PLUS;
	if(c == '-') return TokenType::MINUS;
	if(c == '*') return TokenType::ASTERISK;
	if(c == '/') return TokenType::DIVIDE;
	if(c == '=') return TokenType::EQUALS;
	if(c == '(') return TokenType::OPEN_PAREN;
	if(c == ')') return TokenType::CLOSED_PAREN;
	if(c == '{') return TokenType::OPEN_BRACE;
	if(c == '}') return TokenType::CLOSED_BRACE;
	if(c == '.') return TokenType::PERIOD;
	if(c == ',') return TokenType::COMMA;
	if(c == ':') return TokenType::COLON;
	if(c == ';') return TokenType::SEMICOLON;
	return TokenType::ERROR;
}
char Lexer::popInput(){
	if(input.size() <= 0){
		return '\0';
	}
	int c = input[0];
	input.erase(0, 1);
	return c;
}
// No keywords for now
TokenType Lexer::findKeyword(std::string lexeme){
	return TokenType::IDENTIFIER;
}

void Lexer::storeToken(const TokenType &type, const std::string lexeme, const int &line){
	tokens.push_back(Token(type, lexeme, line));
	if(verbose){
		std::cout << "Token: \"" << lexeme << "\" ";
		std::cout << std::setw(10 - lexeme.length());
		std::cout << "Type: " << TokenType::toString(type) << std::endl;
	}
}

bool Lexer::analyze(){
	int line = 1;
	TokenType tokenType;
	std::string lexeme;
	
	TokenType nextType = getNextType();
	char next = popInput();
	while(nextType != TokenType::END){
		lexeme = "";
		switch(nextType){
			case TokenType::DIGIT:
				bool floatFlag = false;
				while(nextType == TokenType::DIGIT || nextType == TokenType::PERIOD){
					lexeme += next;
					nextType = getNextType();
					next = popInput();
					floatFlag = (!floatFlag && nextType == TokenType::PERIOD);
				}
				if(floatFlag){
					tokenType = TokenType::FLOAT;
				}else{
					tokenType = TokenType::INTEGER;
				}
				break;
			case TokenType::LETTER:
				while(nextType == TokenType::LETTER || nextType == TokenType::DIGIT){
					lexeme += next;
					nextType = getNextType();
					next = popInput();
				}
				tokenType = findKeyword(lexeme);
				break;
			case TokenType::ERROR:
				std::cerr << "Lexer: Error in \"" << filename << "\" near line " << line;
				std::cerr << std::endl;
				return false;
			default:
				if(next == '\n'){
					line++;
				}
				tokenType = nextType;
				lexeme = next;
				nextType = getNextType();
				next = popInput();
		}
		// No whitespace for now
		if(tokenType != TokenType::WHITESPACE){
			storeToken(tokenType, lexeme, line);
		}
	}
	storeToken(TokenType::END, "", line);
	return true;
}
