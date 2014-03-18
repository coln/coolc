%{
#include <stdio.h>
#include <string.h>
#include "parser.h"
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
	yylval.stringval = (char *)malloc(strlen(yytext) + 1);
	if(yylval.stringval != NULL){
		strcpy(yylval.stringval, yytext);
	}
	return FLOAT;
}

{INTEGER}   {
	yylval.stringval = (char *)malloc(strlen(yytext) + 1);
	if(yylval.stringval != NULL){
		strcpy(yylval.stringval, yytext);
	}
	return INTEGER;
}
{KEYWORD}   {
	yylval.stringval = (char *)malloc(strlen(yytext) + 1);
	if(yylval.stringval != NULL){
		strcpy(yylval.stringval, yytext);
	}
	return KEYWORD;
}
{IDENTIFIER}   {
	yylval.stringval = (char *)malloc(strlen(yytext) + 1);
	if(yylval.stringval != NULL){
		strcpy(yylval.stringval, yytext);
	}
	return IDENTIFIER;
}

{SINGLE_LINE_COMMENT}   {}  /* Do nothing with comments or whitespace */
{MULTI_LINE_COMMENT}   {}
{WHITESPACE}   {}

.   {
	fprintf(stderr, "Lexer: Unrecognized character: %s\n", yytext);
}

%%