%{
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
int yylex();
int yyerror(const char*);
extern int yylineno;
extern char *yytext;
%}

%union {
	int intval;
	float floatval;
	std::string *stringval;
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
| input line { std::cout << "Result: " << *($2) << std::endl; }
;

line: num { $$ = $1; }
| exp { $$ = $1; }
;

num: INTEGER { $$ = $1; }
| FLOAT { $$ = $1; }
;

exp: KEYWORD { $$ = $1; }
| IDENTIFIER { $$ = $1; }
;
%%


int yyerror(const char *s){
	std::cerr << "ERROR: " << s << " at symbol \"" << yytext;
	std::cerr << "\" on line " << yylineno << std::endl;
	return 1;
}