#ifndef COOL_COOL_COMPILER_H_
#define COOL_COOL_COMPILER_H_

#include <iostream>
#include <map>
#include <string>
#include "parser.h"

// Tell Flex the lexer's prototype ...
#define YY_DECL \
	yy::CoolParser::symbol_type yylex(CoolCompiler& compiler)
// ... and declare it for the parser's sake.
YY_DECL;

class CoolCompiler {
public:
	struct Flags {
		bool verbose;
		bool traceLexer;
		bool traceParser;
		std::string outputFile;
		Flags() : verbose(false),
						traceLexer(false), traceParser(false),
						outputFile("") {}
	} flags;
	
	std::map<std::string, int> variables;
	std::string filename;
	int result;
	
	CoolCompiler();
	virtual ~CoolCompiler();
	bool compile(const char*);
	void lexerBegin();
	void lexerEnd();
	int parse(const std::string&);
	void error(const yy::location&, const std::string&);
	void error(const std::string&);
};


#endif