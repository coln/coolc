#ifndef COOLC_SYMBOLS_H_
#define COOLC_SYMBOLS_H_

#include <stdlib.h>
#include <string.h>

typedef struct Symbol {
	char *name;
	double value;
	Symbol *next;
} Symbol;

Symbol* findSymbol(const char*);
Symbol* getSymbol(const char*);
Symbol* setSymbol(const char*, double);

extern int yyerror(const char*, ...);

#endif