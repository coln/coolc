%{
#define YYERROR_VERBOSE 1
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "CoolMath.h"
#include "Symbol.h"
int yylex();
int yyerror(const char *, ...);
extern int yylineno;
extern char *yytext;
const char *yyfilename;
%}

%locations

%union {
	double constant;
	char* string;
}

// Define Terminals
%token <string> IDENTIFIER
%token <constant> CONSTANT;
%token KEYWORD_ECHO CLASS INHERITS;

%type <constant> expression;

// Precedence
%precedence '='
%left '+' '-'
%left '*' '/'
%left NEG

%start program


// Grammar
%%
class
	: class_declaration '{' class_body '}'
	;

class_declaration
	: CLASS IDENTIFIER
	| CLASS IDENTIFIER INHERITS IDENTIFIER
	;

class_body
	: %empty
	| class_body methods ';'
	| class_body attributes ';'
	;

methods
	: /* nothing yet */
	;

attributes
	: IDENTIFIER ':' IDENTIFIER
	| IDENTIFIER ':' IDENTIFIER '<' '-' expression
	;



program
	: statement ';' program
	| statement ';'
	| statement error ';' program { yyerrok; }
	| class ';'
	| class error ';' { yyerrok; }
	;

statement
	: IDENTIFIER '=' expression  { setSymbol($1, $3); }
	| KEYWORD_ECHO expression { printf("%g\n", $2); }
	| expression
	;

expression
	: '(' expression ')'  { $$ = $2; }
	| '-' expression %prec NEG  { $$ = -$2; }
	| expression '+' expression  { $$ = coolAdd($1, $3); }
	| expression '-' expression  { $$ = coolSubtract($1, $3); }
	| expression '*' expression  { $$ = coolMultiply($1, $3); }
	| expression '/' expression  { $$ = coolDivide($1, $3); }
	| CONSTANT  { $$ = $1; }
	| IDENTIFIER  {
		Symbol* var = getSymbol($1);
		if(var == NULL){
			$$ = 0;
		}else{
			$$ = var->value;
		}
	}
	;
%%


int yyerror(const char *msg, ...){
	fprintf(stderr, "%s:", yyfilename);
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
	
	// Print out the arguments in "printf" style
	static char errmsg[10000];
	va_list args;
	va_start(args, msg);
	vsprintf(errmsg, msg, args);
	va_end(args);
	fprintf(stderr, ": %s at symbol \"%s\"\n", errmsg, yytext);
	return 0;
}