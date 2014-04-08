#include "Class.h"

Class::Class(const std::string &name)
	: Expression(CLASS), name(name)
{
}
Class::Class(const std::string &name, const std::string &inherits)
	: Expression(CLASS), name(name), inherits(inherits)
{
}
Class::Class(const Class& c)
	: Expression(c), name(c.name), inherits(c.inherits), features(c.features)
{
}
Class& Class::operator=(Class c){
	Expression::operator=(c);
	name = c.name;
	inherits = c.inherits;
	features = c.features;
	return *this;
}
Class::~Class(){
	std::vector<Expression*>::iterator it;
	for(it = features.begin(); it != features.end(); ++it){
		delete *it;
	}
	features.clear();
}

void Class::print(int n){
	Expression::print(n);
	std::cout << "class " << name;
	if(!inherits.empty()){
		std::cout << " inherits " << inherits;
	}
	std::cout << std::endl;
	std::vector<Expression*>::iterator it;
	for(it = features.begin(); it != features.end(); ++it){
		(*it)->print(n + 1);
	}
}