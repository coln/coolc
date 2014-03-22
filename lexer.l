%{
#include <stdlib.h>
#include <string.h>
#include "parser.h"
%}

INTEGER      [0-9]+
FLOAT        [0-9]+"."[0-9]*
EXPONENTIAL  [0-9]+("."[0-9]*)?[eE]["+""-"]?[0-9]*        
KEYWORD_ECHO (?i:"echo")
IDENTIFIER   [a-zA-Z][a-zA-Z0-9]*
COMMENT      "--".*\n?

%option nounput

%%
 /*  Skip the blanks */
[\r\n\t ]+   {}

{INTEGER}   {
	yylval.constant = atol(yytext);
	return CONSTANT;
}

{FLOAT}   {
	yylval.constant = atof(yytext);
	return CONSTANT;
}
{EXPONENTIAL}   {
	yylval.constant = atof(yytext);
	return CONSTANT;
}

{KEYWORD_ECHO}   {
	yylval.string = (char *)malloc(strlen(yytext) + 1);
	strcpy(yylval.string, yytext);
	return KEYWORD_ECHO;
}

{IDENTIFIER}   {
	yylval.string = (char *)malloc(strlen(yytext) + 1);
	strcpy(yylval.string, yytext);
	return IDENTIFIER;
}

{COMMENT}   {}



.   { return yytext[0]; }
%%