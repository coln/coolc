#ifndef COOL_DESTRUCTOR_H_
#define COOL_DESTRUCTOR_H_

#include <vector>
#include "Class.h"
#include "Features.h"
#include "Attribute.h"
#include "Symbol.h"
#include "Method.h"
#include "Expression.h"

class Destructor {
private:
	void destructClass(Class*&);
	void destructFeatures(Features*&);
	void destructAttribute(Attribute*&);
	void destructSymbol(Symbol*&);
	void destructMethod(Method*&);
	void destructExpression(Expression*&);
	
public:
	std::vector<Class*> *classes;
	Destructor();
	void run();
};

#endif