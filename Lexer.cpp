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
	if((c >= 'a' && c <= 'z') || (c >= 'A' || c <= 'Z')) return TokenType::LETTER;
	if(c >= '0' && c <= '9') return TokenType::DIGIT;
	if(c == '+') return TokenType::PLUS;
	if(c == '-') return TokenType::MINUS;
	if(c == '*') return TokenType::TIMES;
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
char popInput(){
	if(input.size() <= 0){
		return '\0';
	}
	int c = input[0];
	input.erase(0, 1);
	return c;
}
// No keywords for now
TokenType findKeyword(std::string lexeme){
	return TokenType::INDENTIFER;
}

void storeToken(const TokenType &type, const std::string lexeme, const int &line){
	tokens.push(Token(type, lexeme, line));
	if(verbose){
		std::cout << "Token: \"" << std::setw(8) << std::left <<  lexeme << "\" ";
		std::cout << "Type: " << TokenType::toString(type) << std::endl;
	}
}

bool analyze(){
	int line = 0;
	TokenType tokenType;
	std::string lexeme;
	
	TokenType nextType = getNextType();
	char next = popInput();
	while(next != CharType::END){
		lexeme = "";
		switch(next){
			case TokenType::DIGIT:
				while(nextType == TokenType::DIGIT){
					lexeme += next;
					nextType = getNextType();
					next = popInput();
				}
				tokenType = TokenType::INTEGER;
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
				std::cerr << "Lexer: Error in \"" << filename << "\" near line " << lines;
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
}
