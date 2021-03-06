%skeleton "lalr1.cc"
%require "3.0.2"
%define parser_class_name {CoolParser}
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
#define YYERROR_VERBOSE 1
#include <string>
#include <vector>
#include "syntax/TypeTable.h"
class TypeTable;
class CoolCompiler;
class Class;
class Features;
class Attribute;
class Method;
class Symbol;
class Expression;
}

// The parsing context
%param { CoolCompiler& compiler }
%locations
%initial-action {
	// Initialize the initial location.
	@$.begin.filename = @$.end.filename = &compiler.filename;
};

%define parse.trace
%define parse.error verbose

%code {
// We include it here because CoolCompiler needs to know about the yy namespace
#include "CoolCompiler.h"
#include "syntax/Class.h"
#include "syntax/Features.h"
#include "syntax/Attribute.h"
#include "syntax/Method.h"
#include "syntax/Symbol.h"
#include "syntax/Expression.h"

// This allows for the std::vector<Symbol*> type below with the %printer
std::ostream& operator<<(std::ostream& os, const std::vector<Symbol*>& obj){
	os << "std::vecotr<Symbol*>";
	return os;
}

}

%printer { yyoutput << $$; } <*>;

// Define Terminals
%define api.token.prefix {TOK_}
%token <std::string> IDENTIFIER TYPE;
%token <std::string> INT_CONSTANT BOOL_CONSTANT STRING_CONSTANT;

%type <Class*> class;
%type <Features*> features;
%type <Attribute*> attribute;
%type <Method*> method;
%type <Symbol*> symbol_declaration;
%type <std::vector<Symbol*>> init_arg_list;
%type <Expression*> expression constants identifiers arithmetic comparison;

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
	| program class
	| program class error { yyerrok; }
	;

// Class definitions
class
	: CLASS TYPE "{" features "}" ";"
		{
			compiler.classes.push_back(new Class($2, $4));
			compiler.classes.back()->location = @$;
		}
	| CLASS TYPE INHERITS TYPE "{" features "}" ";"
		{
			compiler.classes.push_back(new Class($2, $4, $6));
			compiler.classes.back()->location = @$;
		}
	;

features
	: %empty { $$ = new Features(); $$->location = @$;  }
	| features attribute ";" { $1->addAttribute($2); $$ = $1; }
	| features method ";" { $1->addMethod($2); $$ = $1; }
	;

// Class variables/symbols/attributes
attribute
	: symbol_declaration { $$ = new Attribute($1); $$->location = @$; }
	| symbol_declaration "<-" expression { $$ = new Attribute($1, $3); $$->location = @$; }
	;

symbol_declaration
	: IDENTIFIER ":" TYPE { $$ = new Symbol($1, $3); $$->location = @$; }
	;

// Method/function definitions
method
	: IDENTIFIER "(" ")" ":" TYPE "{" expression "}"
		{
			$$ = new Method($1, $5, $7);
			$$->location = @$;
		}
	| IDENTIFIER "(" init_arg_list ")" ":" TYPE "{" expression "}"
		{
			$$ = new Method($1, $6, $3, $8);
			$$->location = @$;
		}
	;

init_arg_list
	: symbol_declaration { $$.push_back($1); }
	| init_arg_list "," symbol_declaration { $1.push_back($3); }
	;


// Expressions
expression
	: "(" expression ")" { $$ = $2; }
	| constants { $$ = $1; }
	| identifiers { $$ = $1; }
	/*| assignment
	| dispatch
	| conditional
	| loop
	| "{" block "}"
	| let 
	| cases
	| NEW TYPE
	| ISVOID expression*/
	| arithmetic { $$ = $1; }
	| comparison { $$ = $1; }
	;


constants
	: INT_CONSTANT { $$ = new Expression($1, "Int"); $$->location = @$; }
	| BOOL_CONSTANT { $$ = new Expression($1, "Bool"); $$->location = @$; }
	| STRING_CONSTANT { $$ = new Expression($1, "String"); $$->location = @$; }
	;

identifiers
	: IDENTIFIER { $$ = new Expression($1); $$->location = @$; }
	| SELF { $$ = new Expression("self"); $$->location = @$; }
	;
/*
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
*/
arithmetic
	: expression "+" expression { $$ = new Expression($1, "+", $3); $$->location = @$; }
	| expression "-" expression { $$ = new Expression($1, "-", $3); $$->location = @$; }
	| expression "*" expression { $$ = new Expression($1, "*", $3); $$->location = @$; }
	| expression "/" expression { $$ = new Expression($1, "/", $3); $$->location = @$; }
	| "~" expression { $$ = new Expression($2, "~", NULL); }
	;

comparison
	: expression "<" expression { $$ = new Expression($1, "<", $3); $$->location = @$; }
	| expression "<=" expression { $$ = new Expression($1, "<=", $3); $$->location = @$; }
	| expression "=" expression { $$ = new Expression($1, "=", $3); $$->location = @$; }
	| NOT expression { $$ = new Expression($2, "not", NULL); $$->location = @$; }
	;
%%

void yy::CoolParser::error(const location_type& location, const std::string& msg){
	compiler.errorStream << msg;
	compiler.error(location);
}