#ifndef COOL_METHOD_SCOPE_H_
#define COOL_METHOD_SCOPE_H_

#include <string>
#include <vector>
#include "Method.h"

class MethodScope {	
private:
	typedef std::vector<Method*> Scope;
	typedef std::vector<Scope> ScopeList;
	ScopeList table;
	Scope *currentScope;
	
	MethodScope(const MethodScope&);
	MethodScope& operator=(const MethodScope&);
	
public:
	void enterScope();
	void exitScope();
	Method* add(Method*);
	Method* find(const std::string&);
	bool checkScope(const std::string&);
	
	MethodScope();
	~MethodScope();
};

#endif