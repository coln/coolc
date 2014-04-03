#ifndef COOL_TYPE_H_
#define COOL_TYPE_H_

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

/* Note:
 * Every class inherits from a father type "Object"
 * Thus why we do not need a type table explicitly
 */

class Type {
private:
	typedef std::vector<Type>::iterator Type_iterator;
	
public:
	std::string name;
	std::vector<Type> children;
	
	Type();
	Type(const std::string);
	Type(const Type&);
	Type& operator=(Type);
	~Type();
	
	void addChild(const std::string&);
	void addChild(Type&);
	Type* findChild(const std::string&);
	void removeChild(const std::string&);
	bool isChild(const std::string&);
	
	void print(int = 0);
};

#endif