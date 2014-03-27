%skeleton "lalr1.cc"
%require "3.0.2"
%define parser_class_name {CoolParser}
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
#define YYERROR_VERBOSE 1
#include <string>
class CoolCompiler;
}

// The parsing context.
%param { CoolCompiler& compiler }
%locations
%initial-action {
	// Initialize the initial location.
	@$.begin.filename = @$.end.filename = &compiler.filename;
};

%define parse.trace
%define parse.error verbose

%code {
#include "CoolCompiler.h"
}

%printer { yyoutput << $$; } <*>;

// Define Terminals
%define api.token.prefix {TOK_}
%token <std::string> IDENTIFIER;
%token <std::string> TYPE;
%token <int> INT_CONSTANT;
%token <std::string> STRING_CONSTANT;
%token <bool> BOOL_CONSTANT;

%token END 0;
%token CLASS INHERITS NEW SELF;
%token LET IN CASE OF ESAC CASE_ASSIGN "=>";
%token IF THEN ELSE FI;
%token WHILE LOOP POOL;
%token ISVOID NOT;

%token LBRACE "{" RBRACE "}" LPAREN "(" RPAREN ")";
%token COLON ":" SEMICOLON ";";
%token ASSIGN "<-" LT_OP "<" LTE_OP "<=" EQUALS "=";
%token PLUS "+" MINUS "-" TIMES "*" DIVIDE "/";
%token TILDE "~" AT "@" PERIOD "." COMMA ",";

// Precedence
%right "<-";
%left NOT;
%nonassoc "<" "<=" "=";
%left "+" "-";
%left "*" "/";
%left ISVOID;
%left "~";
%left "@";
%left ".";

%start program


%%
program
	: %empty
	| program class_definition
	| program class_definition error { yyerrok; }
	;

// Class definitions
class_definition
	: class_declaration "{" class_body "}" ";"
	| "{" class_body "}" ";"
	;

class_declaration
	: CLASS TYPE
	| CLASS TYPE INHERITS TYPE
	;

class_body
	: %empty
	| class_body attribute ";"
	| class_body method ";"
	;

// Class variables/symbols/attributes
attribute
	: symbol_declaration
	| symbol_declaration "<-" expression
	;

symbol_declaration
	: IDENTIFIER ":" TYPE
	;

// Method/function definitions
method
	: method_declaration ":" TYPE "{" expression "}"
	;

method_declaration
	: IDENTIFIER "(" init_arg_list ")"
	| IDENTIFIER "(" ")"
	;

init_arg_list
	: symbol_declaration
	| init_arg_list "," symbol_declaration
	;


// Expressions
expression
	: "(" expression ")"
	| constants
	| identifiers
	| assignment
	| dispatch
	| conditional
	| loop
	| "{" block "}"
	| let 
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
	: dispatch_id "(" arg_list ")"
	| dispatch_id "(" ")"
	;

dispatch_id
	: expression "." IDENTIFIER
	| IDENTIFIER
	| expression "@" TYPE "." IDENTIFIER
	;

arg_list
	: expression
	| arg_list "," expression
	;

conditional
	: IF expression THEN expression FI
	| IF expression THEN expression ELSE expression FI
	;
	
loop
	: WHILE expression LOOP expression POOL
	;

block
	: expression ";"
	| block expression ";"
	;

let
	: LET init_attribute_list IN expression
	;

init_attribute_list
	: attribute
	| init_attribute_list "," attribute
	;

cases
	: CASE expression OF case_branches ESAC
	;

case_branches
	: case_branch
	| case_branches case_branch
	;

case_branch
	: symbol_declaration "=>" expression ";"
	;

arithmetic
	: expression "+" expression
	| expression "-" expression
	| expression "*" expression
	| expression "/" expression
	| "~" expression
	;

comparison
	: expression "<" expression
	| expression "<=" expression
	| expression "=" expression
	| NOT expression
	;
%%

void yy::CoolParser::error(const location_type& location, const std::string& msg){
	compiler.error(location, msg);
}