#ifndef COOL_COOL_COMPILER_H_
#define COOL_COOL_COMPILER_H_

#include <iostream>
#include <sstream>
#include <string>
#include "syntax/Class.h"
#include "syntax/SymbolScope.h"
#include "syntax/MethodScope.h"
#include "Semantic.h"
#include "parser.h"

// Tell Flex the lexer's prototype ...
#define YY_DECL \
	yy::CoolParser::symbol_type yylex(CoolCompiler& compiler)
// ... and declare it for the parser's sake.
YY_DECL;

class CoolCompiler {
private:
	CoolCompiler(const CoolCompiler&);
	CoolCompiler& operator=(CoolCompiler);
	
public:
	struct Flags {
		bool verbose;
		bool lexer;
		bool parser;
		bool parseTree;
		bool semantic;
		bool types;
		std::string outputFile;
		Flags() : verbose(false),
						lexer(false), parser(false), parseTree(false),
						semantic(false), types(false),
						outputFile("") {}
	} flags;
	std::string filename;
	int result;
	
	SymbolScope symbolScope;
	MethodScope methodScope;
	std::vector<Class*> classes;
	
	CoolCompiler();
	virtual ~CoolCompiler();
	
	bool compile(int, int, char**);
	void lexerBegin();
	void lexerEnd();
	int parse(const std::string&);
	
	std::stringstream errorStream;
	void error(const yy::location&, const std::string&);
	void error(const yy::location&);
	void error(const std::string&);
	void error();
};

#endif