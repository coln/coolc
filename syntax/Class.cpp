#include "Class.h"

Class::Class(const std::string &name)
	: name(name)
{
}
Class::Class(const std::string &name, const std::string &inherits)
	: name(name), inherits(inherits)
{
}
Class::~Class(){
	std::vector<Expression*>::iterator it;
	for(it = features.begin(); it != features.end(); ++it){
		delete *it;
	}
	features.clear();
}