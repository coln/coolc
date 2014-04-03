#ifndef COOL_SYMBOL_TABLE_H_
#define COOL_SYMBOL_TABLE_H_

#include <algorithm>
#include <string>
#include <vector>
#include "Symbol.h"

class SymbolTable {	
private:
	typedef std::vector<Symbol*> Scope;
	typedef std::vector<Scope> ScopeList;
	ScopeList table;
	Scope *currentScope;
	
public:
	void enterScope();
	void exitScope();
	void add(Symbol*);
	Symbol* find(const std::string&);
	bool checkScope(const Symbol*&);
	
	SymbolTable();
	SymbolTable(const SymbolTable&);
	SymbolTable& operator=(SymbolTable);
	~SymbolTable();
};

#endif