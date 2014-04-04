#ifndef COOL_SEMANTIC_H_
#define COOL_SEMANTIC_H_

class CoolCompiler;

#include <iostream>
#include <sstream>
#include "syntax/Type.h"
#include "syntax/SymbolTable.h"
#include "syntax/Class.h"
#include "CoolCompiler.h"
#include "parser.h"

class Semantic {
private:	
	Type objectType;
	std::stringstream traceStream;
	bool populateTypes();
	bool organizeTypes();
	void trace();
	
public:
	CoolCompiler &compiler;
	
	Semantic(CoolCompiler&);
	bool analyze();
};

#endif