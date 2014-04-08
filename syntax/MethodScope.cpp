#include "MethodScope.h"

MethodScope::MethodScope(){}
MethodScope::~MethodScope(){
	// Methods will be destroyed by the classes container
	ScopeList::iterator it;
	for(it = table.begin(); it != table.end(); ++it){
		it->clear();
	}
	table.clear();
}

void MethodScope::enterScope(){
	Scope scope;
	table.push_back(scope);
	currentScope = &table.back();
}
void MethodScope::exitScope(){
	table.back().clear();
	table.pop_back();
	currentScope = &table.back();
}

// Add method to current scope
Method* MethodScope::add(Method* method){
	// Can't add method without scope
	if(currentScope == NULL){
		return NULL;
	}
	// Prevent overriding
	Scope::iterator it;
	for(it = currentScope->begin(); it != currentScope->end(); ++it){
		if((*it)->symbol->name == method->symbol->name){
			return *it;
		}
	}
	currentScope->push_back(method);
	return method;
}
Method* MethodScope::find(const std::string &name){
	ScopeList::iterator it;
	Scope::iterator it2;
	Method *method;
	for(it = table.begin(); it != table.end(); ++it){
		for(it2 = it->begin(); it2 != it->end(); ++it2){
			method = *it2;
			if(method->symbol->name == name){
				return method;
			}
		}
	}
	return NULL;
}

// Check if method exists in current scope
bool MethodScope::checkScope(const std::string &name){
	Scope::iterator it;
	for(it = currentScope->begin(); it != currentScope->end(); ++it){
		if((*it)->symbol->name == name){
			return true;
		}
	}
	return false;
}