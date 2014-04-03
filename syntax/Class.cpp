#include "Class.h"

Class::Class(std::string name, Features *features)
	: name(name), features(features)
{
}
Class::Class(std::string name, std::string inherits, Features *features)
	: name(name), inherits(inherits), features(features)
{
}
Class::~Class(){}