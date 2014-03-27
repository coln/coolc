#ifndef COOL_FEATURES_H_
#define COOL_FEATURES_H_

#include <vector>
#include "Attribute.h"
#include "Method.h"

class Features {
public:
	std::vector<Attribute*> attributes;
	std::vector<Method*> methods;
	
	Features(){}
	
	void addAttribute(Attribute*);
	void addMethod(Method*);
};

#endif