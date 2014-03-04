#ifndef COOL_TOKEN_H_
#define COOL_TOKEN_H_

#include <string>

struct TokenType {
	enum Enum {
		ERROR,
		END,
		
		DIGIT,
		LETTER,
		WHITESPACE,
		IDENTIFIER,
		KEYWORD,
		INTEGER,
		
		PLUS,
		MINUS,
		TIMES,
		DIVIDE,
		EQUALS,
		
		OPEN_PAREN,
		CLOSED_PAREN,
		OPEN_BRACE,
		CLOSED_BRACE,
		
		COLON,
		SEMICOLON
	} e;
	TokenType(Enum e = ERROR) : e(e) {}
	operator Enum() { return e; }
	bool operator==(const TokenType &t) const {
		return (e == t.e);
	}
	static const char* toString(const TokenType &t) {
		switch(t.e){
			case ERROR: return "ERROR";
			case END: return "END";
			case DIGIT: return "DIGIT";
			case LETTER: return "LETTER";
			case WHITESPACE: return "WHITESPACE";
			case IDENTIFIER: return "IDENTIFIER";
			case KEYWORD: return "KEYWORD";
			case INTEGER: return "INTEGER";
			case PLUS: return "PLUS";
			case MINUS: return "MINUS";
			case TIMES: return "TIMES";
			case DIVIDE: return "DIVIDE";
			case EQUALS: return "EQUALS";
			case OPEN_PAREN: return "OPEN_PAREN";
			case CLOSED_PAREN: return "CLOSED_PAREN";
			case OPEN_BRACE: return "OPEN_BRACE";
			case CLOSED_BRACE: return "CLOSED_BRACE";
			case COLON: return "COLON";
			case SEMICOLON: return "SEMICOLON";
		}
		return "";
	}
};

class Token {
public:
	TokenType type;
	std::string value;
	int line;
	Token(TokenType type = TokenType::ERROR, std::string value = "", int line = 0)
			: type(type), value(value), line(line) {}
	bool operator==(const Token &t) const {
		return (type == t.type && value.compare(t.value) == 0);
	}
};

#endif