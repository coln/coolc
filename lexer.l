%{
#include <stdlib.h>
#include <string.h>
#include "parser.h"
%}

%option nounput
%option case-insensitive

INTEGER      [0-9]+
FLOAT        [0-9]+"."[0-9]*
EXPONENTIAL  [0-9]+("."[0-9]*)?[eE]["+""-"]?[0-9]*
IDENTIFIER   [a-zA-Z][a-zA-Z0-9]*
COMMENT      "--".*\n?

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

"echo"   { return KEYWORD_ECHO; }
"class"   { return CLASS; }
"inherits"   { return INHERITS; }

{IDENTIFIER}   {
	yylval.string = (char *)malloc(strlen(yytext) + 1);
	strcpy(yylval.string, yytext);
	return IDENTIFIER;
}

{COMMENT}   {}

.   { return yytext[0]; }
%%