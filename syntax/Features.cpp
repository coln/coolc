#include "Features.h"

Features::Features(){}
Features::~Features(){}

void Features::addAttribute(Attribute *attribute){
	attributes.push_back(attribute);
}
void Features::addMethod(Method *method){
	methods.push_back(method);
}

Attribute* Features::findAttribute(const std::string &name, const std::string &type){
	std::vector<Attribute*>::iterator it;
	Attribute *thisAttr;
	for(it = attributes.begin(); it != attributes.end(); ++it){
		thisAttr = *it;
		if(name == thisAttr->symbol->name && (!type.empty() && type == thisAttr->symbol->type)){
			return thisAttr;
		}
	}
	return NULL;
}
Method* Features::findMethod(const std::string &name, const std::string &type){
	std::vector<Method*>::iterator it;
	Method* thisMethod;
	for(it = methods.begin(); it != methods.end(); ++it){
		thisMethod = *it;
		if(name == thisMethod->symbol->name && (!type.empty() && type == thisMethod->symbol->type)){
			return thisMethod;
		}
	}
	return NULL;
}