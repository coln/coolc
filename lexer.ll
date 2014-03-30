%{
#include <cerrno>
#include <climits>
#include <cstdlib>
#include <string>
#include "CoolCompiler.h"
#include "parser.h"
// Work around an incompatibility in flex (at least versions
// 2.5.31 through 2.5.33): it generates code that does
// not conform to C89. See Debian bug 333231
// <http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=333231>.
#undef yywrap
#define yywrap() 1
// The location of the current token.
static yy::location location;

// As defined in cool_manual.pdf (p.9)
#define MAX_STRING_LENGTH 1025
#define YY_USER_ACTION location.columns(yyleng);
%}

%option noyywrap nounput batch debug noinput

%x MULTI_COMMENT

INTEGER          [0-9]+
IDENTIFIER       [a-z][a-zA-Z0-9_]*
TYPE             [A-Z][a-zA-Z0-9_]*
STRING_CONSTANT  \"(\\.|[^\\"])*\"
 /* " */
SINGLE_COMMENT          "--".*


%%
%{
// Code run each time yylex is called.
location.step();
%}

<INITIAL,MULTI_COMMENT>\n {
	location.lines(yyleng);
	location.step();
}

 /* Comments */
"(*"                   { BEGIN(MULTI_COMMENT); }
<MULTI_COMMENT><<EOF>> { compiler.error("unclosed comment"); BEGIN(INITIAL); }
<MULTI_COMMENT>"*)"    { BEGIN(INITIAL); }
<MULTI_COMMENT>.       {}
	
{SINGLE_COMMENT}   {}


 /* Constants */
{INTEGER}  { return yy::CoolParser::make_INT_CONSTANT(yytext, location); }
{STRING_CONSTANT}  {
	int len = strlen(yytext);
	if(len > MAX_STRING_LENGTH){
		compiler.error("string constant length too long");
		len = MAX_STRING_LENGTH;
	}
	return yy::CoolParser::make_STRING_CONSTANT(yytext, location);
}

 /* Booleans */
"t"(?i:"rue")  { return yy::CoolParser::make_BOOL_CONSTANT("true", location); }
"f"(?i:"alse")  { return yy::CoolParser::make_BOOL_CONSTANT("false", location); }


 /* Keywords */
"class"  { return yy::CoolParser::make_CLASS(location); }
"inherits"  { return yy::CoolParser::make_INHERITS(location); }
"new"  { return yy::CoolParser::make_NEW(location); }
"self"  { return yy::CoolParser::make_SELF(location); }
"let"  { return yy::CoolParser::make_LET(location); }
"in"  { return yy::CoolParser::make_IN(location); }
"case"  { return yy::CoolParser::make_CASE(location); }
"of"  { return yy::CoolParser::make_OF(location); }
"esac"  { return yy::CoolParser::make_ESAC(location); }
"=>"  { return yy::CoolParser::make_CASE_ASSIGN(location); }
"if"  { return yy::CoolParser::make_IF(location); }
"then"  { return yy::CoolParser::make_THEN(location); }
"else"  { return yy::CoolParser::make_ELSE(location); }
"fi"  { return yy::CoolParser::make_FI(location); }
"while"  { return yy::CoolParser::make_WHILE(location); }
"loop"  { return yy::CoolParser::make_LOOP(location); }
"pool"  { return yy::CoolParser::make_POOL(location); }
"isvoid"  { return yy::CoolParser::make_ISVOID(location); }
"not"  { return yy::CoolParser::make_NOT(location); }

 /* Other operators */
"<"   { return yy::CoolParser::make_LT_OP(location); }
"<="  { return yy::CoolParser::make_LTE_OP(location); }
"="   { return yy::CoolParser::make_EQUALS(location); }
"<-"  { return yy::CoolParser::make_ASSIGN(location); }
"{"   { return yy::CoolParser::make_LBRACE(location); }
"}"   { return yy::CoolParser::make_RBRACE(location); }
"("   { return yy::CoolParser::make_LPAREN(location); }
")"   { return yy::CoolParser::make_RPAREN(location); }
":"   { return yy::CoolParser::make_COLON(location); }
";"   { return yy::CoolParser::make_SEMICOLON(location); }
"+"   { return yy::CoolParser::make_PLUS(location); }
"-"   { return yy::CoolParser::make_MINUS(location); }
"*"   { return yy::CoolParser::make_TIMES(location); }
"/"   { return yy::CoolParser::make_DIVIDE(location); }
"~"   { return yy::CoolParser::make_TILDE(location); }
"@"   { return yy::CoolParser::make_AT(location); }
"."   { return yy::CoolParser::make_PERIOD(location); }
","   { return yy::CoolParser::make_COMMA(location); }


 /* Identifiers/Types */
{IDENTIFIER}  { return yy::CoolParser::make_IDENTIFIER(yytext, location); }
{TYPE}  { return yy::CoolParser::make_TYPE(yytext, location); }


 /*  Skip the blanks */
[ \t\v\r\f]  { location.step(); }

.  {
	compiler.errorStream << "invalid character '" << yytext << "'";
	compiler.error(location);
}
<<EOF>>  { return yy::CoolParser::make_END(location); }
%%

void CoolCompiler::lexerBegin(){
	yy_flex_debug = flags.verbose || flags.traceLexer;
	if(filename.empty() || filename == "-"){
		errorStream << "no input files";
		error();
		exit(EXIT_FAILURE);
	}
	
	yyin = fopen(filename.c_str(), "r");
	if(yyin == NULL){
		errorStream << "cannot open " << filename << ": " << strerror(errno);
		error();
		exit(EXIT_FAILURE);
	}
}
void CoolCompiler::lexerEnd(){
	fclose(yyin);
}