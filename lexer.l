%{
#include <stdio.h>
#include <string.h>
#include "parser.h"
%}

WHITESPACE   [ \t\r\n]+
DIGIT   [0-9]
INTEGER   {DIGIT}+

SIMPLE_FLOAT   {DIGIT}+"."{DIGIT}*
EXPONENTIAL   {DIGIT}+("."{DIGIT}*)?[eE]["+""-"]?{DIGIT}*
FLOAT   ({SIMPLE_FLOAT}|{EXPONENTIAL})

KEYWORD_ECHO   (?i:"echo")

STRING   ([a-zA-Z_])?\"(\\.|[^\\"])*\"

IDENTIFIER   [a-zA-Z][a-zA-Z0-9]*
SINGLE_LINE_COMMENT   "//"(.*)
MULTI_LINE_COMMENT   ("/*")((.*)|\n)*("*/")

%%

{FLOAT}   {
	yylval.floatval = atof(yytext);
	return FLOAT;
}

{INTEGER}   {
	yylval.intval = atoi(yytext);
	return INTEGER;
}

{KEYWORD_ECHO}   {
	yylval.stringval = (char *)malloc(strlen(yytext) + 1);
	if(yylval.stringval != NULL){
		strcpy(yylval.stringval, yytext);
	}
	return KEYWORD_ECHO;
}

{IDENTIFIER}   {
	yylval.stringval = (char *)malloc(strlen(yytext) + 1);
	if(yylval.stringval != NULL){
		strcpy(yylval.stringval, yytext);
	}
	return IDENTIFIER;
}

{STRING}   {
	yylval.stringval = (char *)malloc(strlen(yytext) + 1);
	if(yylval.stringval != NULL){
		strcpy(yylval.stringval, yytext+1);
		yylval.stringval[strlen(yytext)-2] = '\0';
	}
	return STRING;
}

{SINGLE_LINE_COMMENT}   { /* Do nothing with comments or whitespace */ }
{MULTI_LINE_COMMENT}   {}
{WHITESPACE}   {}

"+"   { return PLUS; }
"-"   { return MINUS; }
"*"   { return TIMES; }
"/"   { return DIVIDE; }
"="   { return ASSIGN; }
"("   { return LPAREN; }
")"   { return RPAREN; }
";"   { return SEMICOLON; }

.   { /* Ignore bad characters */ }

%%