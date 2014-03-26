%{
#include <cerrno>
#include <climits>
#include <cstdlib>
#include <string>
#include "CoolCompiler.h"
#include "parser.h"
// Work around an incompatibility in flex (at least versions
// 2.5.31 through 2.5.33): it generates code that does
// not conform to C89. See Debian bug 333231
// <http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=333231>.
#undef yywrap
#define yywrap() 1
// The location of the current token.
static yy::location loc;
%}

%option noyywrap nounput batch debug noinput

id [a-zA-Z][a-zA-Z_0-9]*
int [0-9]+
blank [ \t]

%{
	// Code run each time a pattern is matched.
	#define YY_USER_ACTION loc.columns(yyleng);
%}


%%
%{
	// Code run each time yylex is called.
	loc.step();
%}
{blank}+ { loc.step(); }
[\n]+ { loc.lines(yyleng); loc.step(); }

"-" return yy::CoolParser::make_MINUS(loc);
"+" return yy::CoolParser::make_PLUS(loc);
"*" return yy::CoolParser::make_STAR(loc);
"/" return yy::CoolParser::make_SLASH(loc);
"(" return yy::CoolParser::make_LPAREN(loc);
")" return yy::CoolParser::make_RPAREN(loc);
":=" return yy::CoolParser::make_ASSIGN(loc);

{int} {
	errno = 0;
	long n = strtol(yytext, NULL, 10);
	if(!(INT_MIN <= n && n <= INT_MAX && errno != ERANGE)){
		compiler.error(loc, "integer is out of range");
	}
	return yy::CoolParser::make_NUMBER(n, loc);
}

{id} {
	return yy::CoolParser::make_IDENTIFIER(yytext, loc);
}

. {
	compiler.error(loc, "invalid character");
}

<<EOF>> {
	return yy::CoolParser::make_END(loc);
}
%%


void CoolCompiler::lexerBegin(){
	yy_flex_debug = flags.verbose || flags.traceLexer;
	if(filename.empty() || filename == "-"){
		error("no input files");
		exit(EXIT_FAILURE);
	}
	
	yyin = fopen(filename.c_str(), "r");
	if(yyin == NULL){
		error("cannot open " + filename + ": " + strerror(errno));
		exit(EXIT_FAILURE);
	}
}
void CoolCompiler::lexerEnd(){
	fclose(yyin);
}