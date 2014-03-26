%skeleton "lalr1.cc"
%require "3.0.2"
%define parser_class_name {CoolParser}
%define api.token.constructor
%define api.value.type variant
%define parse.assert


%code requires {
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

%define api.token.prefix {TOK_}
%token
	END 0 "end of file"
	ASSIGN ":="
	MINUS "-"
	PLUS "+"
	STAR "*"
	SLASH "/"
	LPAREN "("
	RPAREN ")"
	;

%token <std::string> IDENTIFIER "identifier"
%token <int> NUMBER "number"
%type <int> exp

%printer { yyoutput << $$; } <*>;

%%
%start unit;

unit
	: assignments exp { compiler.result = $2; }
	;
	
assignments
	: %empty {}
	| assignments assignment {}
	;
	
assignment
	: "identifier" ":=" exp { compiler.variables[$1] = $3; }
	;
	
%left "+" "-";
%left "*" "/";

exp
	: exp "+" exp { $$ = $1 + $3; }
	| exp "-" exp { $$ = $1 - $3; }
	| exp "*" exp { $$ = $1 * $3; }
	| exp "/" exp { $$ = $1 / $3; }
	| "(" exp ")" { std::swap($$, $2); }
	| "identifier" { $$ = compiler.variables[$1]; }
	| "number" { std::swap($$, $1); }
	;
%%

void yy::CoolParser::error(const location_type& location, const std::string& msg){
	compiler.error(location, msg);
}