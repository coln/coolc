%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
extern int yyerror(const char*, ...);
extern yy_size_t yyleng;

int yycolumn = 1;

// As defined in cool_manual.pdf (p.9)
#define MAX_STRING_LENGTH 1024
#define YY_USER_ACTION { \
	yylloc.first_line = yylloc.last_line = yylineno; \
	yylloc.first_column = yycolumn; \
	yylloc.last_column = yycolumn + yyleng; \
	yycolumn += yyleng; \
}

%}

%option nounput
%x MULTI_COMMENT

INTEGER          [0-9]+
IDENTIFIER       [a-z][a-zA-Z0-9_]*
TYPE             [A-Z][a-zA-Z0-9_]*
STRING_CONSTANT  \"(\\.|[^\\"])*\"
 /* " */
SINGLE_COMMENT          "--".*



%%
<INITIAL,MULTI_COMMENT>\n {
	yylineno++;
	yycolumn = 1;
}

 /* Comments */
"(*"                   { BEGIN(MULTI_COMMENT); }
<MULTI_COMMENT><<EOF>> { yyerror("unclosed comment"); BEGIN(INITIAL); }
<MULTI_COMMENT>"*)"    { BEGIN(INITIAL); }
<MULTI_COMMENT>.       {}
	
{SINGLE_COMMENT}   {}


 /* Constants */
{INTEGER}   {
	yylval.intType = atol(yytext);
	return INT_CONSTANT;
}

{STRING_CONSTANT}   {
	int len = strlen(yytext);
	if(len > MAX_STRING_LENGTH){
		yyerror("string constant length too long");
		len = MAX_STRING_LENGTH;
	}
	yylval.stringType = (char *)malloc(len + 1);
	strcpy(yylval.stringType, yytext);
	return STRING_CONSTANT;
}

"t"(?i:"rue")   {
	yylval.boolType = 1;
	return BOOL_CONSTANT;
}
"f"(?i:"alse")   {
	yylval.boolType = 0;
	return BOOL_CONSTANT;
}


 /* Keywords */
"echo"   { return KEYWORD_ECHO; }
"class"   { return CLASS; }
"inherits"   { return INHERITS; }
"new"   { return NEW; }
"self"   { return SELF; }
"let"   { return LET; }
"in"   { return IN; }
"case"   { return CASE; }
"of"   { return OF; }
"esac"   { return ESAC; }
"if"   { return IF; }
"then"   { return THEN; }
"else"   { return ELSE; }
"fi"   { return FI; }
"while"   { return WHILE; }
"loop"   { return LOOP; }
"pool"   { return POOL; }
"isvoid"   { return ISVOID; }
"not"   { return NOT; }

 /* Other operators */
"<="   { return LTE_OP; }
"=>"   { return CASE_ASSIGN; }
"<-"   { return ASSIGN; }


 /* Identifiers/Types */
{IDENTIFIER}   {
	yylval.identifier = (char *)malloc(strlen(yytext) + 1);
	strcpy(yylval.identifier, yytext);
	return IDENTIFIER;
}

{TYPE}   {
	yylval.type = (char *)malloc(strlen(yytext) + 1);
	strcpy(yylval.type, yytext);
	return TYPE;
}


 /*  Skip the blanks */
[ \t\v\r\f]   {}


.   { return yytext[0]; }
%%