#include "Features.h"

#include <iostream>
Features::Features(){}
Features::~Features(){
	std::vector<Attribute*>::iterator it;
	for(it = attributes.begin(); it < attributes.end(); ++it){
		delete *it;
	}
	std::vector<Method*>::iterator it2;
	for(it2 = methods.begin(); it2 < methods.end(); ++it2){
		delete *it2;
	}
	attributes.clear();
	methods.clear();
}

void Features::addAttribute(Attribute *attribute){
	attributes.push_back(attribute);
}
void Features::addMethod(Method *method){
	methods.push_back(method);
}