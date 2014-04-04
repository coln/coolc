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
class CoolCompiler;
class Class;
class Attribute;
class Method;
class Symbol;
class Expression;
class Assignment;
class Conditional;
class Loop;
class Block;
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
#include "syntax/Attribute.h"
#include "syntax/Method.h"
#include "syntax/Symbol.h"
#include "syntax/Expression.h"
#include "syntax/Assignment.h"
#include "syntax/Conditional.h"
#include "syntax/Loop.h"
#include "syntax/Block.h"

// This allows for the vector type below with the %printer
std::ostream& operator<<(std::ostream& os, const std::vector<Symbol*>& obj){
	os << "std::vector<Symbol*>";
	return os;
}
std::ostream& operator<<(std::ostream& os, const std::vector<Expression*>& obj){
	os << "std::vector<Expression*>";
	return os;
}

}

%printer { yyoutput << $$; } <*>;

// Define NonTerminals
%type <Class*> class_definition;
%type <std::vector<Expression*>> features;
%type <Attribute*> attribute;
%type <Method*> method;
%type <Symbol*> symbol_declaration;
%type <std::vector<Symbol*>> init_arg_list;
%type <Expression*> expression;
%type <Expression*> constants identifiers;
%type <Expression*> assignment conditional loop;
%type <Block*> block;
//%type <Expression*> assignment dispatch conditional loop block let cases;
//%type <Expression*> arithmetic comparison;

// Define Terminals
%define api.token.prefix {TOK_EN}
%token <std::string> IDENTIFIER TYPE;
%token <std::string> INT_CONSTANT BOOL_CONSTANT STRING_CONSTANT;
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
	: CLASS TYPE "{" features "}" ";"
		{
			Class *newClass = new Class($2);
			newClass->location = @$;
			newClass->features = $4;
			compiler.classes.push_back(newClass);
		}
	| CLASS TYPE INHERITS TYPE "{" features "}" ";"
		{
			Class *newClass = new Class($2, $4);
			newClass->location = @$;
			newClass->features = $6;
			compiler.classes.push_back(newClass);
		}
	;

features
	: %empty
		{
			$$ = $$;
		}
	| features attribute ";"
		{
			$1.push_back($2);
			$$ = $1;
		}
	| features method ";"
		{
			$1.push_back($2);
			$$ = $1;
		}
	;

// Class variables/symbols/attributes
attribute
	: symbol_declaration
		{
			$$ = new Attribute($1);
			$$->location = @$;
		}
	| symbol_declaration "<-" expression
		{
			$$ = new Attribute($1, $3);
			$$->location = @$;
		}
	;

symbol_declaration
	: IDENTIFIER ":" TYPE
		{
			$$ = new Symbol($1, $3);
			$$->location = @$;
		}
	;

// Method/function definitions
method
	: IDENTIFIER "(" ")" ":" TYPE "{" expression "}"
		{
			Symbol *name = new Symbol($1, $5);
			$$ = new Method(name, $7);
			$$->location = @$;
		}
	| IDENTIFIER "(" init_arg_list ")" ":" TYPE "{" expression "}"
		{
			Symbol *name = new Symbol($1, $6);
			$$ = new Method(name, $3, $8);
			$$->location = @$;
		}
	;

init_arg_list
	: symbol_declaration
		{
			$$.push_back($1);
		}
	| init_arg_list "," symbol_declaration
		{
			$1.push_back($3);
			$$ = $1;
		}
	;


// Expressions
expression
	: "(" expression ")" { $$ = $2; }
	| constants { $$ = $1; }
	| identifiers { $$ = $1; }
	| assignment { $$ = $1; }
	/*| dispatch*/
	| conditional { $$ = $1; }
	| loop { $$ = $1; }
	| "{" block "}" { $$ = $2; }
	/*| let { $$ = $1; }
	| cases { $$ = $1; }
	| NEW TYPE { $$ = new Expression($2, $1); }
	| ISVOID expression
	| arithmetic { $$ = $1; }
	| comparison { $$ = $1; }*/
	;

// Convert to type table/symbol table? something
constants
	: INT_CONSTANT
		{
			$$ = new Symbol($1, "Int");
			$$->location = @$;
		}
	| BOOL_CONSTANT
		{
			$$ = new Symbol($1, "Bool");
			$$->location = @$;
		}
	| STRING_CONSTANT
		{
			$$ = new Symbol($1, "String");
			$$->location = @$;
		}
	;

identifiers
	: IDENTIFIER
		{
			$$ = new Symbol($1);
			$$->location = @$;
		}
	| SELF
		{
			$$ = new Symbol("self");
			$$->location = @$;
		}
	;

assignment
	: identifiers ASSIGN expression
		{
			$$ = new Assignment($1, $3);
			$$->location = @$;
		}
	;

/*dispatch
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
*/
conditional
	: IF expression THEN expression FI
		{
			$$ = new Conditional($2, $4);
			$$->location = @$;
		}
	| IF expression THEN expression ELSE expression FI
		{
			$$ = new Conditional($2, $4, $6);
			$$->location = @$;	
		}
	;

loop
	: WHILE expression LOOP expression POOL
		{
			$$ = new Loop($2, $4);
			$$->location = @$;
		}
	;

block
	: expression ";"
		{
			$$ = new Block();
			$$->location = @$;
		}
	| block expression ";"
		{
			$$->expressions.push_back($2);
			$$ = $1;
		}
	;
/*
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
*/
%%

void yy::CoolParser::error(const location_type& location, const std::string& msg){
	compiler.errorStream << msg;
	compiler.error(location);
}