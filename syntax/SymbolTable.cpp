#include "SymbolTable.h"

SymbolTable::SymbolTable(){}
SymbolTable::SymbolTable(const SymbolTable& s)
	: table(s.table)
{
}
SymbolTable& SymbolTable::operator=(SymbolTable s){
	std::swap(this->table, s.table); 
	return *this;
}
SymbolTable::~SymbolTable(){
	// Symbols will be destroyed by the classes container
	ScopeList::iterator it;
	for(it = table.begin(); it != table.end(); ++it){
		it->clear();
	}
	table.clear();
}

void SymbolTable::enterScope(){
	Scope scope;
	table.push_back(scope);
	currentScope = &table.back();
}
void SymbolTable::exitScope(){
	table.back().clear();
	table.pop_back();
	currentScope = &table.back();
}

// Add symbol to current scope
void SymbolTable::add(Symbol* s){
	// Can't add symbol without scope
	if(currentScope == NULL){
		return;
	}
	currentScope->push_back(s);
}
Symbol* SymbolTable::find(const std::string &name){
	ScopeList::iterator it;
	Scope::iterator it2;
	Symbol *symbol;
	for(it = table.begin(); it != table.end(); ++it){
		for(it2 = it->begin(); it2 != it->end(); ++it2){
			symbol = *it2;
			if(symbol->name == name){
				return symbol;
			}
		}
	}
	return NULL;
}

bool SymbolTable::checkScope(const Symbol* &s){
	Scope::iterator it;
	Symbol *symbol;
	for(it = currentScope->begin(); it != currentScope->end(); ++it){
		symbol = *it;
		if(*symbol == *s){
			return true;
		}
	}
	return false;
}