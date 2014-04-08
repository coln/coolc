#include "SymbolScope.h"

SymbolScope::SymbolScope(){}
SymbolScope::~SymbolScope(){
	// Attributes will be destroyed by the classes container
	ScopeList::iterator it;
	for(it = table.begin(); it != table.end(); ++it){
		it->clear();
	}
	table.clear();
}

void SymbolScope::enterScope(){
	Scope scope;
	table.push_back(scope);
	currentScope = &table.back();
}
void SymbolScope::exitScope(){
	table.back().clear();
	table.pop_back();
	currentScope = &table.back();
}

// Add symbol to current scope
void SymbolScope::add(Symbol* symbol){
	// Can't add symbol without scope
	if(currentScope == NULL){
		return;
	}
	// Prevent overriding
	Scope::iterator it;
	for(it = currentScope->begin(); it != currentScope->end(); ++it){
		if((*it)->name == symbol->name){
			return;
		}
	}
	currentScope->push_back(symbol);
}
Symbol* SymbolScope::find(const std::string &name){
	ScopeList::iterator it;
	Scope::iterator it2;
	for(it = table.begin(); it != table.end(); ++it){
		for(it2 = it->begin(); it2 != it->end(); ++it2){
			if((*it2)->name == name){
				return *it2;
			}
		}
	}
	return NULL;
}

// Check if symbol exists in current scope
bool SymbolScope::checkScope(const std::string &name){
	Scope::iterator it;
	for(it = currentScope->begin(); it != currentScope->end(); ++it){
		if((*it)->name == name){
			return true;
		}
	}
	return false;
}