#ifndef COOL_SYBMOL_TABLE_H_
#define COOL_SYBMOL_TABLE_H_

#include <string>
#include <vector>
#include "Symbol.h"

class SymbolScope {	
private:
	typedef std::vector<Symbol*> Scope;
	typedef std::vector<Scope> ScopeList;
	ScopeList table;
	Scope *currentScope;
	
	SymbolScope(const SymbolScope&);
	SymbolScope& operator=(const SymbolScope&);
	
public:
	void enterScope();
	void exitScope();
	void add(Symbol*);
	Symbol* find(const std::string&);
	bool checkScope(const std::string&);
	
	SymbolScope();
	~SymbolScope();
};

#endif