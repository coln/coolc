#ifndef COOLC_COOL_COMPILER_H_
#define COOLC_COOL_COMPILER_H_

#include <getopt.h>
#include <cstdio>
#include "parser.h"
extern int yylex();
extern FILE* yyin;
extern const char* yyfilename;

struct Flags {
	int verbose;
	int lexer;
	int parser;
	int parseTree;
	char* output;
} flags;

void printUsage();
void getFlags(int, char**);
bool compile(const char*);

#endif