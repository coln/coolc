%{
#include <stdio.h>
#include <stdlib.h>
int yylex();
int yyerror(const char*);
extern int yylineno;
extern char *yytext;
%}

%union {
	int intval;
	float floatval;
	char* stringval;
}

// Define Terminals
%token <stringval> INTEGER;
%token <stringval> FLOAT;
%token <stringval> KEYWORD;
%token <stringval> IDENTIFIER;

// Define NonTerminals
%type <stringval> line
%type <stringval> num
%type <stringval> exp

// Grammar
%%
input: %empty
| '\n'
| input line { printf("Result: %s\n", $2); }
;

line: num
| exp
;

num: INTEGER
| FLOAT
;

exp: KEYWORD
| IDENTIFIER
;
%%


int yyerror(const char *msg){
	fprintf(stderr, "ERROR: %s at symbol \"%s\" ", msg, yytext);
	fprintf(stderr, "on line %d\n", yylineno);
	return 1;
}