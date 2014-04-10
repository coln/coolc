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
class Symbol;
class Attribute;
class Method;
class Expression;

class Int;
class Bool;
class String;

class Arithmetic;
class Assignment;
class Block;
class Case;
class Comparison;
class Conditional;
class Dispatch;
class Let;
class While;
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
#include "Headers.h"

// This allows for the vector type below with the %printer
std::ostream& operator<<(std::ostream& os, const std::vector<Expression*>& obj){
	os << "std::vector<Expression*>";
	return os;
}
std::ostream& operator<<(std::ostream& os, const std::vector<Symbol*>& obj){
	os << "std::vector<Symbol*>";
	return os;
}
std::ostream& operator<<(std::ostream& os, const std::vector<Attribute*>& obj){
	os << "std::vector<Attribute*>";
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
%type <Symbol*> constants identifiers;
%type <Expression*> assignment conditional dispatch loop let;
%type <Symbol*> dispatch_id;
%type <std::vector<Expression*>> arg_list;
%type <std::vector<Attribute*>> init_attribute_list;
%type <Block*> block;

%type <Expression*> cases;
%type <std::vector<Attribute*>> case_branches;
%type <Attribute*> case_branch;

%type <Expression*> arithmetic comparison;


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
	: %empty { $$; }
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
	| dispatch
	| conditional { $$ = $1; }
	| loop { $$ = $1; }
	| "{" block "}" { $$ = $2; }
	| let { $$ = $1; }
	| cases { $$ = $1; }
	| NEW TYPE { $$ = new New($2); $$->location = @$; }
	| ISVOID expression { $$ = new IsVoid($2); $$->location = @$; }
	| arithmetic { $$ = $1; }
	| comparison { $$ = $1; }
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

dispatch
	: dispatch_id "(" arg_list ")"
		{
			$$ = new Dispatch($1, $3);
			$$->location = @$;
		}
	| dispatch_id "(" ")"
		{
			$$ = new Dispatch($1);
			$$->location = @$;
		}
	;

dispatch_id
	: expression "." IDENTIFIER
		{
			$$ = new Symbol($3, $1);
			$$->location = @$;
		}
	| IDENTIFIER
		{
			$$ = new Symbol($1);
			$$->location = @$;
		}
	| expression "@" TYPE "." IDENTIFIER
		{
			$$ = new Symbol($5, $3, $1);
			$$->location = @$;
		}
	;

arg_list
	: expression { $$.push_back($1); }
	| arg_list "," expression { $1.push_back($3); $$ = $1; }
	;

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
			$$ = new While($2, $4);
			$$->location = @$;
		}
	;

block
	: expression ";"
		{
			$$ = new Block();
			$$->location = @$;
			$$->addChild($1);
		}
	| block expression ";"
		{
			$1->addChild($2);
			$$ = $1;
		}
	;

let
	: LET init_attribute_list IN expression
		{
			$$ = new Let($2, $4);
			$$->location = @$;
		}
	;

init_attribute_list
	: attribute
		{
			$$.push_back($1);
		}
	| init_attribute_list "," attribute
		{
			$1.push_back($3);
			$$ = $1;
		}
	;

cases
	: CASE expression OF case_branches ESAC
		{
			$$ = new Case($2, $4);
			$$->location = @$;
		}
	;

case_branches
	: case_branch
		{
			$$.push_back($1);
		}
	| case_branches case_branch
		{
			$1.push_back($2);
			$$ = $1;
		}
	;

case_branch
	: symbol_declaration "=>" expression ";"
		{
			$$ = new Attribute($1, $3);
			$$->location = @$;
		}
	;

arithmetic
	: expression "+" expression { $$ = new Arithmetic($1, Arithmetic::PLUS, $3); $$->location = @$; }
	| expression "-" expression { $$ = new Arithmetic($1, Arithmetic::MINUS, $3); $$->location = @$; }
	| expression "*" expression { $$ = new Arithmetic($1, Arithmetic::TIMES, $3); $$->location = @$; }
	| expression "/" expression { $$ = new Arithmetic($1, Arithmetic::DIVIDE, $3); $$->location = @$; }
	| "~" expression { $$ = new Arithmetic($2, Arithmetic::INVERSE, NULL); $$->location = @$; }
	;

comparison
	: expression "<" expression
		{
			$$ = new Comparison($1, Comparison::LESS_THAN, $3);
			$$->location = @$;
		}
	| expression "<=" expression
		{
			$$ = new Comparison($1, Comparison::LESS_THAN_EQUALS, $3);
			$$->location = @$;
		}
	| expression "=" expression
		{
			$$ = new Comparison($1, Comparison::EQUALS, $3);
			$$->location = @$;
		}
	| NOT expression
		{
			$$ = new Comparison($2, Comparison::NOT, NULL);
			$$->location = @$;
		}
	;

%%

void yy::CoolParser::error(const location_type& location, const std::string& msg){
	compiler.errorStream << msg;
	compiler.error(location);
}