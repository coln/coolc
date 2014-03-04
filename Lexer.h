#ifndef COOL_LEXER_H_
#define COOL_LEXERL_H_

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include "Token.h"

class Lexer {
private:
	TokenType getNextType();
	char popInput();
	TokenType findKeyword(std::string);
	void storeToken(const TokenType&, const std::string, const int&);
	
public:
	bool verbose;
	std::string filename;
	std::string input;
	std::vector<Token> tokens;
	bool analyze();
	Lexer();
	~Lexer();
};

#endif