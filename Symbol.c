#include "Symbol.h"

Symbol *symbolTable;

Symbol* findSymbol(const char* name){
	if(name == NULL){
		return NULL;
	}
	
	Symbol* symbol;
	for(symbol = symbolTable; symbol != NULL; symbol = symbol->next){
		if(strcmp(symbol->name, name) == 0){
			return symbol;
		}
	}
	return NULL;
}

Symbol* getSymbol(const char* name){
	Symbol* symbol = findSymbol(name);
	if(symbol == NULL){
		yyerror("variable \"%s\" not defined", name);
	}
	return symbol;
}

Symbol* setSymbol(const char* name, double value = 0){
	Symbol* symbol = findSymbol(name);
	if(symbol != NULL){
		symbol->value = value;
		return NULL;
	}
	
	symbol = (Symbol *)malloc(sizeof(Symbol));
	if(symbol == NULL){
		yyerror("internal error creating variable \"%s\"", name);
		return NULL;
	}
	symbol->name = (char *)malloc(strlen(name) + 1);
	if(symbol->name == NULL){
		yyerror("internal error creating variable \"%s\"", name);
		return NULL;
	}
	strcpy(symbol->name, name);
	symbol->value = value;
	symbol->next = symbolTable;
	symbolTable = symbol;
	return symbol;
}