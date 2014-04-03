#include "Destructor.h"
#include <iostream>
Destructor::Destructor(){}

void Destructor::run(){
	if(classes == NULL){
		return;
	}
	std::vector<Class*>::iterator it;
	for(it = classes->begin(); it != classes->end(); ++it){
		destructClass(*it);
	}
	classes->clear();
}

void Destructor::destructClass(Class* &thisClass){
	destructFeatures(thisClass->features);
	delete thisClass;
}
void Destructor::destructFeatures(Features* &features){
	std::vector<Attribute*>::iterator it;
	for(it = features->attributes.begin(); it != features->attributes.end(); ++it){
		destructAttribute(*it);
	}
	std::vector<Method*>::iterator it2;
	for(it2 = features->methods.begin(); it2 != features->methods.end(); ++it2){
		destructMethod(*it2);
	}
	features->attributes.clear();
	features->methods.clear();
	delete features;
}
void Destructor::destructAttribute(Attribute* &attribute){
	destructSymbol(attribute->symbol);
	destructExpression(attribute->expression);
	delete attribute;
}
void Destructor::destructSymbol(Symbol* &symbol){
	delete symbol;
}
void Destructor::destructMethod(Method* &method){
	destructSymbol(method->symbol);
	destructExpression(method->expression);
	std::vector<Symbol*>::iterator it;
	for(it = method->arguments.begin(); it != method->arguments.end(); ++it){
		destructSymbol(*it);
	}
	method->arguments.clear();
	delete method;
}
void Destructor::destructExpression(Expression* &expression){
	destructSymbol(expression->symbol);
	if(expression->lhs){
		destructExpression(expression->lhs);
	}
	if(expression->rhs){
		destructExpression(expression->rhs);
	}
	delete expression;
}