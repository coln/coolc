#ifndef COOL_FEATURES_H_
#define COOL_FEATURES_H_

class Attribute;
class Method;

#include <algorithm>
#include <vector>
#include "Attribute.h"
#include "Method.h"
#include "parser.h"

class Features {
public:
	yy::location location;
	std::vector<Attribute*> attributes;
	std::vector<Method*> methods;
	
	Features();
	~Features();
	
	void addAttribute(Attribute*);
	void addMethod(Method*);
	Attribute* findAttribute(const std::string&, const std::string& = "");
	Method* findMethod(const std::string&, const std::string& = "");
};

#endif