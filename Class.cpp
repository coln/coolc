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

void Class::checkTypes(){
	/*
	This will first check if its inherited class exists
	
	Then it check all of its attribute types to make sure all
	necessary classes are included/available properly
	
		This in turn calls the attribute type checker to make sure
		each expression on the RHS is of the correct type
	
	Then it will check all of its method types (and arg list types)
	to make sure all classes are included/availabe properly
	
		Again, this calls the method type checker to make sure
		each of its attributes have their classes included/available
			
			This then calls the attribute type checker
		
		Then we find the last expression of the method, and make sure
		the type matches the method type
	
	Repeat for each class
	*/
}

void Class::evaluate(){
	/*
	Okay the type checker has passed, and now it's time to eval the class
	
	First we eval the class attributes and assign the identifiers the 
	expression values (and store them in a table)
	
	Next we eval the methods
	
		This will eval the attributes like above, except the table the 
		identifiers are stored in are located in the Method class
		
		The last expression eval'ed will be the value of the method
	*/
}