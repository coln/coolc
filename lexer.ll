%{
#include <iostream>
#include "parser.yy.h"
%}

WHITESPACE   [ \t\r\n]+
DIGIT   [0-9]
INTEGER   {DIGIT}+
SIMPLE_FLOAT   {DIGIT}+"."{DIGIT}*
EXPONENTIAL1   {DIGIT}+[eE]["+""-"]?{DIGIT}*
EXPONENTIAL2   {DIGIT}+"."{DIGIT}*[eE]["+""-"]?{DIGIT}*
FLOAT   ({SIMPLE_FLOAT}|{EXPONENTIAL1}|{EXPONENTIAL2})
KEYWORD   (?i:"if"|"then"|"function")
IDENTIFIER   [a-zA-Z][a-zA-Z0-9]*
SINGLE_LINE_COMMENT   "//"(.*)
MULTI_LINE_COMMENT   ("/*")((.*)|\n)*("*/")

%%

{FLOAT}   {
	yylval.stringval = new std::string(yytext);
	return FLOAT;
}

{INTEGER}   {
	yylval.stringval = new std::string(yytext);
	return INTEGER;
}
{KEYWORD}   {
	yylval.stringval = new std::string(yytext);
	return KEYWORD;
}
{IDENTIFIER}   {
	yylval.stringval = new std::string(yytext);
	return IDENTIFIER;
}

{SINGLE_LINE_COMMENT}   {}  /* Do nothing with comments or whitespace */
{MULTI_LINE_COMMENT}   {}
{WHITESPACE}   {}

.   {
	std::cerr << "Lexer: Unrecognized character: " << yytext << std::endl;
}

%%