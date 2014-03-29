#ifndef COOL_COOL_COMPILER_H_
#define COOL_COOL_COMPILER_H_

class TypeTable;

#include <cstdlib>
#include <cstdarg>
#include <iostream>
#include <sstream>
#include <string>
#include "Class.h"
#include "TypeTable.h"
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
		bool traceAnalyzer;
		std::string outputFile;
		Flags() : verbose(false),
						traceLexer(false), traceParser(false), traceAnalyzer(false),
						outputFile("") {}
	} flags;
	
	TypeTable typeTable;
	std::vector<Class*> classes;
	std::string filename;
	int result;
	
	CoolCompiler(){};
	virtual ~CoolCompiler();
	bool compile(int, int, char**);
	void lexerBegin();
	void lexerEnd();
	int parse(const std::string&);
	bool analyze();
	
	void traceAnalyzer(const char*, ...);
	void error(const yy::location&, const std::string&);
	void error(const std::string&);
};

#endif