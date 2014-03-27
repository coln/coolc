#include "Features.h"

void Features::addAttribute(Attribute *attribute){
	attributes.push_back(attribute);
}
void Features::addMethod(Method *method){
	methods.push_back(method);
}