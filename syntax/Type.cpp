#include "Type.h"

Type::Type(){}
Type::Type(const std::string name)
	: name(name)
{
}
Type::Type(const Type& type)
	: name(type.name), children(type.children)
{
}
Type& Type::operator=(Type type){
	name = type.name;
	std::swap(children, type.children);
	return *this;
}
Type::~Type(){
	children.clear();
}

void Type::addChild(const std::string &name){
	children.push_back(Type(name));
}
void Type::addChild(Type &type){
	children.push_back(type);
}


// This ensures a <= (less than or equal) relationship
Type* Type::findChild(const std::string &name){
	if(this->name == name){
		return this;
	}
	if(children.size() <= 0){
		return NULL;
	}
	
	Type_iterator it;
	Type *found;
	for(it = children.begin(); it != children.end(); ++it){
		if(it->name == name){
			return &(*it);
		}
		found = it->findChild(name);
		if(found != NULL){
			return found;
		}
	}
	return NULL;
}

void Type::removeChild(const std::string &name){
	if(children.size() <= 0){
		return;
	}
	Type_iterator it;
	for(it = children.begin(); it < children.end(); ++it){
		if(it->name == name){
			it = children.erase(it);
		}
	}
}

bool Type::isChild(const std::string &name){
	if(findChild(name) != NULL){
		return true;
	}
	return false;
}

void Type::print(int n){
	if(name != "Int" && name != "Bool" && name != "String"){
		int i;
		std::cout << "  ";
		for(i = 0; i < n; ++i){
			std::cout << "  ";
		}
		std::cout << name << std::endl;
	}
	
	Type_iterator it;
	for(it = children.begin(); it != children.end(); ++it){
		it->print(n+1);
	}
}