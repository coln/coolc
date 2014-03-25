%{
#define YYERROR_VERBOSE 1
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "CoolMath.h"
#include "Symbol.h"
int yylex();
void yyerror(const char *, ...);
extern char *yytext;

const char *yyfilename;
%}

%locations

%union {
	int boolType;
	int intType;
	char* stringType;
	char* identifier;
	char* type;
}

// Define Terminals
%token <identifier> IDENTIFIER
%token <type> TYPE
%token <intType> INT_CONSTANT
%token <stringType> STRING_CONSTANT
%token <boolType> BOOL_CONSTANT

%token KEYWORD_ECHO
%token CLASS INHERITS NEW SELF
%token LET IN CASE OF ESAC CASE_ASSIGN "=>"
%token IF THEN ELSE FI
%token WHILE LOOP POOL
%token ISVOID NOT
%token ASSIGN "<-" LTE_OP "<="

// Precedence
%right "<-"
%left NOT
%nonassoc '<' "<=" '='
%left '+' '-'
%left '*' '/'
%left ISVOID
%left '~'
%left '@'
%left '.'

%start program


%%
program
	: %empty
	| program class
	| program class error { yyerrok; }
	;

// Class definitions
class
	: class_declaration '{' class_body '}' ';'
	| '{' class_body '}' ';'
	;

class_declaration
	: CLASS TYPE
	| CLASS TYPE INHERITS TYPE
	;

class_body
	: %empty
	| class_body attribute ';'
	| class_body method ';'
	;

// Class variables/symbols/attributes
attribute
	: symbol_declaration
	| symbol_declaration "<-" expression
	;

symbol_declaration
	: IDENTIFIER ':' TYPE
	;

// Method/function definitions
method
	: method_declaration ':' TYPE '{' expression '}'
	;

method_declaration
	: IDENTIFIER '(' init_arg_list ')'
	| IDENTIFIER '(' ')'
	;

init_arg_list
	: symbol_declaration
	| init_arg_list ',' symbol_declaration
	;


// Expressions
expression
	: '(' expression ')'
	| constants
	| identifiers
	| assignment
	| dispatch
	| conditional
	| loop
	| '{' block '}'
//	| let 
	| cases
	| NEW TYPE
	| ISVOID expression
	| arithmetic
	| comparison
	;


constants
	: BOOL_CONSTANT
	| INT_CONSTANT
	| STRING_CONSTANT
	;

identifiers
	: IDENTIFIER
	| SELF
	;

assignment
	: IDENTIFIER ASSIGN expression
	;

dispatch
	: dispatch_id '(' arg_list ')'
	| dispatch_id '(' ')'
	;

dispatch_id
	: expression '.' IDENTIFIER
	| IDENTIFIER
	| expression '@' TYPE '.' IDENTIFIER
	;

arg_list
	: expression
	| arg_list ',' expression
	;

conditional
	: IF expression THEN expression FI
	| IF expression THEN expression ELSE expression FI
	;
	
loop
	: WHILE expression LOOP expression POOL
	;

block
	: expression ';'
	| block expression ';'
	;

/*let
	: LET init_attribute_list IN expression
	;

init_attribute_list
	: attribute
	| init_attribute_list ',' attribute
	;
*/
cases
	: CASE expression OF case_branches ESAC
	;

case_branches
	: case_branch
	| case_branches case_branch
	;

case_branch
	: symbol_declaration "=>" expression ';'
	;

arithmetic
	: expression '+' expression
	| expression '-' expression
	| expression '*' expression
	| expression '/' expression
	| '~' expression
	;

comparison
	: expression '<' expression
	| expression "<=" expression
	| expression '=' expression
	| NOT expression
	;
%%


void yyerror(const char *msg, ...){
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
}