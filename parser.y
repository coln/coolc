%{
	#define YYERROR_VERBOSE 1
#include <stdio.h>
#include <stdlib.h>
#include "CoolMath.h"
int yylex();
int yyerror(const char*);
extern int yylineno;
extern char *yytext;
%}

%union {
	int intval;
	double floatval;
	char* stringval;
}

// Define Terminals
%token <intval> INTEGER;
%token <floatval> FLOAT;
%token <stringval> KEYWORD_ECHO;
%token <stringval> IDENTIFIER;
%token <stringval> STRING;
%type <floatval> expression

%token LPAREN
%token RPAREN
%token SEMICOLON
%token ASSIGN

// Precedence
%precedence ASSIGN
%left PLUS MINUS
%left TIMES DIVIDE
%left NEG


// Grammar
%%
program: statement SEMICOLON program
| statement SEMICOLON
| statement error SEMICOLON program { yyerrok; }
;

statement: IDENTIFIER ASSIGN expression  { coolVarSet($1, $3); }
| KEYWORD_ECHO expression { printf("%g\n", $2); }
| KEYWORD_ECHO STRING { printf("%s\n", $2); }
| expression
;

expression: LPAREN expression RPAREN  { $$ = $2; }
| MINUS expression %prec NEG  { $$ = -$2; }
| expression PLUS expression  { $$ = coolAdd($1, $3); }
| expression MINUS expression  { $$ = coolSubtract($1, $3); }
| expression TIMES expression  { $$ = coolMultiply($1, $3); }
| expression DIVIDE expression  { $$ = coolDivide($1, $3); }
| INTEGER  { $$ = $1; }
| FLOAT  { $$ = $1; }
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
	fprintf(stderr, "ERROR: %s at symbol \"%s\" ", msg, yytext);
	fprintf(stderr, "on line %d\n", yylineno);
	return 1;
}