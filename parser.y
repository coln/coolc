%{
#define YYERROR_VERBOSE 1
#include <stdio.h>
#include <stdlib.h>
#include "CoolMath.h"
int yylex();
int yyerror(const char *);
extern int yylineno;
extern char *yytext;
%}

%locations

%union {
	double constant;
	char* string;
}

// Define Terminals
%token <string> IDENTIFIER
%token <constant> CONSTANT;
%token KEYWORD_ECHO;
%token LPAREN "(" RPAREN ")" SEMICOLON ";";

%type <constant> expression;

// Precedence
%precedence ASSIGN
%left PLUS MINUS
%left TIMES DIVIDE
%left NEG


// Grammar
%%
program
	: statement SEMICOLON program
	| statement SEMICOLON
	| statement error SEMICOLON program { yyerrok; }
	;

statement
	: IDENTIFIER ASSIGN expression  { coolVarSet($1, $3); }
	| KEYWORD_ECHO expression { printf("%g\n", $2); }
	| expression
	;

expression
	: LPAREN expression RPAREN  { $$ = $2; }
	| MINUS expression %prec NEG  { $$ = -$2; }
	| expression PLUS expression  { $$ = coolAdd($1, $3); }
	| expression MINUS expression  { $$ = coolSubtract($1, $3); }
	| expression TIMES expression  { $$ = coolMultiply($1, $3); }
	| expression DIVIDE expression  { $$ = coolDivide($1, $3); }
	| CONSTANT  { $$ = $1; }
	| IDENTIFIER  {
		Variable* var = coolVarGet($1);
		if(var == NULL){
			$$ = 0;
		}else{
			$$ = var->value;
		}
	}
	;
%%


int yyerror(const char *msg){
	fprintf(stderr, "ERROR on line ");
	if(yylloc.first_line != yylloc.last_line){
		fprintf(stderr, "%d:%d - %d:%d",
					yylloc.first_line, yylloc.first_column,
					yylloc.last_line, yylloc.last_column - 1);
	}else if(yylloc.first_column < yylloc.last_column - 1){
		fprintf(stderr, "%d:%d - %d", yylloc.first_line,
					yylloc.first_column, yylloc.last_column - 1);
	}else{
		fprintf(stderr, "%d:%d", yylloc.first_line, yylloc.first_column);
	}
	fprintf(stderr, ": %s at symbol \"%s\"\n", msg, yytext);
	return 0;
}