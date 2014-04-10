#ifndef COOL_SEMANTIC_H_
#define COOL_SEMANTIC_H_

class CoolCompiler;

#include <iostream>
#include <sstream>
#include "syntax/Type.h"
#include "syntax/SymbolScope.h"
#include "syntax/MethodScope.h"
#include "Headers.h"
#include "CoolCompiler.h"
#include "parser.h"

class Semantic {
private:	
	Type objectType;
	std::stringstream traceStream;
	void parseTree();
	Type* getType(Expression*);
	bool populateTypes();
	bool organizeTypes();
	bool typeCheck();
	bool typeCheckExpression(Expression*);
	bool typeCheckSymbol(Symbol*);
	bool typeCheckAttribute(Attribute*);
	bool typeCheckMethod(Method*);
	bool typeCheckArithmetic(Arithmetic*);
	bool typeCheckAssigment(Assignment*);
	bool typeCheckBlock(Block*);
	bool typeCheckCase(Case*);
	bool typeCheckComparison(Comparison*);
	bool typeCheckConditional(Conditional*);
	bool typeCheckDispatch(Dispatch*);
	bool typeCheckIsVoid(IsVoid*);
	bool typeCheckLet(Let*);
	bool typeCheckNew(New*);
	bool typeCheckWhile(While*);
	void trace(bool force = false);
	
public:
	CoolCompiler &compiler;
	
	Semantic(CoolCompiler&);
	bool analyze();
};

#endif