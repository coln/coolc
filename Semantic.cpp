#include "Semantic.h"

Semantic::Semantic(CoolCompiler &compiler)
	: objectType("Object"), compiler(compiler)
{
	objectType.addChild("Int");
	objectType.addChild("Bool");
	objectType.addChild("String");
}


bool Semantic::analyze(){
	traceStream << "Entering Semantic Analysis phase...";
	trace();
	
	traceStream << "Checking for class Main";
	trace();
	if(!populateTypes()){
		return false;
	}
	
	traceStream << "Total classes created: " << compiler.classes.size();
	traceStream << std::endl;
	traceStream << "Checking inheritance";
	trace();
	if(!organizeTypes()){
		return false;
	}
	
	parseTree();
	
	traceStream << "Type checking all classes, methods, and attributes";
	trace();
	if(!typeCheck()){
		return false;
	}
	// For each class, method, let declaration, and block, create a new scope
	// Go through the classes down the tree analyzing each symbol and its type
	
	return true;
}

void Semantic::trace(bool force){
	if(compiler.flags.verbose || compiler.flags.semantic || force){
		std::cout << traceStream.str() << std::endl;
	}
	traceStream.str(std::string());
	traceStream.clear();
}

bool Semantic::populateTypes(){
	// Make sure class Main is found
	bool mainFound = false;
	
	// Get all class names
	std::vector<Class*>::iterator it;
	Class *thisClass;
	for(it = compiler.classes.begin(); it != compiler.classes.end(); ++it){
		thisClass = *it;
		
		// Check duplicates
		if(objectType.findChild(thisClass->name) != NULL){
			compiler.errorStream << "the class \"" << thisClass->name;
			compiler.errorStream << "\" has already been defined";
			compiler.error(thisClass->location);
			return false;
		}
		if(thisClass->name == "Main"){
			mainFound = true;
		}
		objectType.addChild(thisClass->name);
	}
	if(!mainFound){
		compiler.errorStream << "class \"Main\" not found";
		compiler.error();
		return false;
	}
	return true;
}

bool Semantic::organizeTypes(){
	std::vector<Class*>::iterator it;
	Class *thisClass;
	Type *currentType;
	Type *inheritType;
	for(it = compiler.classes.begin(); it != compiler.classes.end(); ++it){
		thisClass = *it;
		
		// Top-level class
		if(thisClass->inherits.empty()){
			continue;
		}
		
		// Can't inherit from self
		if(thisClass->inherits == thisClass->name){
			compiler.errorStream << "the class \"" << thisClass->name;
			compiler.errorStream << "\" cannot inherit from itself";
			compiler.error(thisClass->location);
			return false;
		}
		if(thisClass->inherits == "Int"){
			compiler.errorStream << "the class \"" << thisClass->name;
			compiler.errorStream << "\" cannot inherit from Int";
			compiler.error(thisClass->location);
			return false;
		}
		if(thisClass->inherits == "Bool"){
			compiler.errorStream << "the class \"" << thisClass->name;
			compiler.errorStream << "\" cannot inherit from Bool";
			compiler.error(thisClass->location);
			return false;
		}
		if(thisClass->inherits == "String"){
			compiler.errorStream << "the class \"" << thisClass->name;
			compiler.errorStream << "\" cannot inherit from String";
			compiler.error(thisClass->location);
			return false;
		}
		
		
		// Check inheritance and add it to type tree
		currentType = objectType.findChild(thisClass->name);
		inheritType = objectType.findChild(thisClass->inherits);
		if(inheritType == NULL){
			compiler.errorStream << "error inheriting class \"";
			compiler.errorStream << thisClass->inherits;
			compiler.errorStream << "\": no such class exists";
			compiler.error(thisClass->location);
			return false;
		}
		inheritType->addChild(*currentType);
		objectType.removeChild(currentType->name);
	}
	
	if(compiler.flags.types){
		std::cout << "Type Inheritance Tree:" << std::endl;
		objectType.print();
	}
	
	return true;
}

void Semantic::parseTree(){
	if(!compiler.flags.verbose && !compiler.flags.parseTree){
		return;
	}
	traceStream << "Parse tree";
	trace(true);
	std::vector<Class*>::iterator it;
	for(it = compiler.classes.begin(); it != compiler.classes.end(); ++it){
		(*it)->print();
	}
}

Type* Semantic::getType(Expression *expression){
	Type *type;
	if(expression->type == Expression::ATTRIBUTE){
		Attribute *attribute = dynamic_cast<Attribute*>(expression);
		type = objectType.findChild(attribute->symbol->type);
		
	}else if(expression->type == Expression::METHOD){
		Method *method = dynamic_cast<Method*>(expression);
		type = objectType.findChild(method->symbol->type);
		
	}else if(expression->type == Expression::ARITHMETIC){
		type = objectType.findChild("Int");
		
	}else if(expression->type == Expression::ASSIGNMENT){
		Assignment *assignment = dynamic_cast<Assignment*>(expression);
		type = objectType.findChild(assignment->symbol->type);
		
	}else if(expression->type == Expression::BLOCK){
		Block *block = dynamic_cast<Block*>(expression);
		type = getType(block->expressions.back());
		
	}else if(expression->type == Expression::CASE){
		// ?
		// Join of the branches
		
	}else if(expression->type == Expression::COMPARISON){
		type = objectType.findChild("Bool");
		
	}else if(expression->type == Expression::CONDITIONAL){
		// ?
		// Join of the cases?
		
	}else if(expression->type == Expression::DISPATCH){
		// ?
		
	}else if(expression->type == Expression::ISVOID){
		type = objectType.findChild("Bool");
		
	}else if(expression->type == Expression::LET){
		Let *let = dynamic_cast<Let*>(expression);
		type = getType(let->expression);
		
	}else if(expression->type == Expression::NEW){
		//NewExp *newExp = dynamic_cast<NewExp*>(expression);
		//type = objectType.findChild(newExp->symbol->type);
		
	}else if(expression->type == Expression::WHILE){
		type = &objectType;
		
	}
	return type;	
}

// Symbols and Methods have separate tables because Cool defines them separately
// I.E. attributes and methods can have the same name and it's alright
bool Semantic::typeCheck(){
	std::vector<Class*>::iterator class_it;
	Class *thisClass;
	std::vector<Expression*>::iterator feat_it;
	
	for(class_it = compiler.classes.begin(); class_it != compiler.classes.end(); ++class_it){
		thisClass = *class_it;
		compiler.symbolScope.enterScope();
		compiler.methodScope.enterScope();
		
		for(feat_it = thisClass->features.begin(); feat_it != thisClass->features.end(); ++feat_it){
			Expression *feature = *feat_it;
			std::cout << "Check feature type" << std::endl;
			if(!typeCheckExpression(feature)){
				return false;
			}
		}
		compiler.symbolScope.exitScope();
		compiler.methodScope.exitScope();
	}
	return true;
}

bool Semantic::typeCheckExpression(Expression *expression){
	std::cout << "Check expression type" << std::endl;
	if(expression->type == Expression::SYMBOL){
		Symbol *symbol = dynamic_cast<Symbol*>(expression);
		return typeCheckSymbol(symbol);
		
	}else if(expression->type == Expression::ATTRIBUTE){
		Attribute *attribute = dynamic_cast<Attribute*>(expression);
		return typeCheckAttribute(attribute);
		
	}else if(expression->type == Expression::METHOD){
		Method *method = dynamic_cast<Method*>(expression);
		return typeCheckMethod(method);
		
	}else if(expression->type == Expression::ARITHMETIC){
		Arithmetic *arithmetic = dynamic_cast<Arithmetic*>(expression);
		return typeCheckArithmetic(arithmetic);
		
	}else if(expression->type == Expression::ASSIGNMENT){
		Assignment *assignment = dynamic_cast<Assignment*>(expression);
		return typeCheckAssigment(assignment);
		
	}else if(expression->type == Expression::BLOCK){
		Block *block = dynamic_cast<Block*>(expression);
		return typeCheckBlock(block);
		
	}else if(expression->type == Expression::CONDITIONAL){
		Conditional *conditional = dynamic_cast<Conditional*>(expression);
		return typeCheckConditional(conditional);
		
	}else if(expression->type == Expression::DISPATCH){
		Dispatch *dispatch = dynamic_cast<Dispatch*>(expression);
		return typeCheckDispatch(dispatch);
		
	}else if(expression->type == Expression::LET){
		Let *let = dynamic_cast<Let*>(expression);
		return typeCheckLet(let);
		
	}else if(expression->type == Expression::NEW){
		//New *newExp = dynamic_cast<New*>(expression);
		// return typeCheckNew(newExp);
		
	}else if(expression->type == Expression::WHILE){
		While *whileExp = dynamic_cast<While*>(expression);
		return typeCheckWhile(whileExp);
		
	}
	compiler.errorStream << "unknown expression type";
	compiler.error(expression->location);
	return false;
}

bool Semantic::typeCheckSymbol(Symbol *symbol){
	std::cout << "Check symbol type" << std::endl;
	Symbol *find = compiler.symbolScope.find(symbol->name);
	if(!symbol->type.empty() && 
		symbol->type != "Int" && 
		symbol->type != "Bool" && 
		symbol->type != "String" &&
		find == NULL)
	{
		compiler.errorStream << "error: symbol \"";
		compiler.errorStream << symbol->name << "\"";
		compiler.errorStream << " was not defined in this scope";
		compiler.error(symbol->location);
		return false;
	}
	if(symbol->type.empty()){
		compiler.errorStream << "cannot find type for symbol \"";
		compiler.errorStream << symbol->name << "\"";
		compiler.error(symbol->location);
		return false;
	}
	return true;
}
bool Semantic::typeCheckAttribute(Attribute *attribute){
	std::cout << "Check attribute type" << std::endl;
	bool checkScope = compiler.symbolScope.checkScope(attribute->symbol->name);
	Symbol *symbol = compiler.symbolScope.find(attribute->symbol->name);
	if(checkScope){
		compiler.errorStream << "the symbol \"" << attribute->symbol->name;
		compiler.errorStream << "\" already exists";
		compiler.error(attribute->location);
		compiler.errorStream << "original defined here";
		compiler.error(symbol->location);
		return false;
	}
	Type *type = objectType.findChild(attribute->symbol->type);
	if(type == NULL){
		compiler.errorStream << "no such type \"" << attribute->symbol->type;
		compiler.errorStream << "\" exists";
		compiler.error(attribute->symbol->location);
		return false;
	}
	if(!typeCheckExpression(attribute->expression)){
		return false;
	}
	Type *expressionType = getType(attribute->expression);
	if(expressionType == NULL){
		compiler.errorStream << "unknown attribute expression type";
		compiler.error(attribute->location);
		return false;
	}
	Type *check = type->findChild(expressionType->name);
	if(check == NULL){
		compiler.errorStream << "type mismatch: ";
		compiler.errorStream << "type \"" << expressionType->name;
		compiler.errorStream << "\", expecting type \"";
		compiler.errorStream << type->name << "\"";
		compiler.error(attribute->location);
	}
	attribute->symbol->type = type->name;
	attribute->symbol->value = attribute->expression;
	compiler.symbolScope.add(attribute->symbol);
	return true;
}
bool Semantic::typeCheckMethod(Method *method){
	std::cout << "Check method type" << std::endl;
	Method *methodScope = compiler.methodScope.find(method->symbol->name);
	if(methodScope != NULL){
		compiler.errorStream << "the method \"" << method->symbol->name;
		compiler.errorStream << "\" already exists";
		compiler.error(method->location);
		compiler.errorStream << "original defined here";
		compiler.error(methodScope->location);
		return false;
	}
	Type *type = objectType.findChild(method->symbol->type);
	if(type == NULL){
		compiler.errorStream << "no such type \"" << method->symbol->type;
		compiler.errorStream << "\" exists";
		compiler.error(method->symbol->location);
		return false;
	}
	method->symbol->type = type->name;
	compiler.methodScope.add(method);
	
	std::vector<Symbol*>::iterator it;
	for(it = method->arguments.begin(); it != method->arguments.end(); ++it){
		Type *type = objectType.findChild((*it)->type);
		if(type == NULL){
			compiler.errorStream << "no such type \"" << (*it)->type;
			compiler.errorStream << "\" exists";
			compiler.error((*it)->location);
			return false;
		}
	}
	
	compiler.symbolScope.enterScope();
	compiler.methodScope.enterScope();
	if(!typeCheckExpression(method->expression)){
		return false;
	}
	compiler.symbolScope.exitScope();
	compiler.methodScope.exitScope();
	return true;
}
bool Semantic::typeCheckArithmetic(Arithmetic *arithmetic){
	std::cout << "Check arithmetic type" << std::endl;
	Type *lhsType = getType(arithmetic->lhs);
	Type *rhsType = getType(arithmetic->rhs);
	if(lhsType == NULL){
		compiler.errorStream << "unknown expression type";
		compiler.error(arithmetic->lhs->location);
		return false;
	}
	if(rhsType == NULL){
		compiler.errorStream << "unknown expression type";
		compiler.error(arithmetic->rhs->location);
		return false;
	}
	if(lhsType->name != "Int"){
		compiler.errorStream << "cannot use operator \"";
		compiler.errorStream << Arithmetic::typeToString(arithmetic->operation);
		compiler.errorStream << "\" with type " << lhsType->name;
		compiler.error(arithmetic->lhs->location);
		return false;
	}
	if(rhsType->name != "Int"){
		compiler.errorStream << "cannot use operator \"";
		compiler.errorStream << Arithmetic::typeToString(arithmetic->operation);
		compiler.errorStream << "\" with type " << rhsType->name;
		compiler.error(arithmetic->rhs->location);
		return false;
	}
	return true;
}
bool Semantic::typeCheckAssigment(Assignment *assignment){
	std::cout << "Check assignment type" << std::endl;
	Symbol *symbol = compiler.symbolScope.find(assignment->symbol->name);
	if(symbol == NULL){
		compiler.errorStream << "error: \"" << assignment->symbol->name;
		compiler.errorStream << "\" was not declared in this scope";
		compiler.error(assignment->symbol->location);
		return false;
	}
	Type *type = objectType.findChild(symbol->type);
	std::cout << "Type: " << type->name << std::endl;
	if(type == NULL){
		compiler.errorStream << "no such type \"" << symbol->type;
		compiler.errorStream << "\" exists";
		compiler.error(symbol->location);
		return false;
	}
	if(!typeCheckExpression(assignment->expression)){
		return false;
	}
	
	Type *expressionType = getType(assignment->expression);
	if(expressionType == NULL){
		compiler.errorStream << "unknown assignment expression type";
		compiler.error(assignment->location);
		return false;
	}
	Type *check = type->findChild(expressionType->name);
	if(check == NULL){
		compiler.errorStream << "type mismatch: ";
		compiler.errorStream << "type \"" << expressionType->name;
		compiler.errorStream << "\", expecting type \"";
		compiler.errorStream << type->name << "\"";
		compiler.error(assignment->location);
	}
	assignment->symbol->type = symbol->type;
	symbol->value = assignment->expression;
	compiler.symbolScope.add(symbol);
	return true;
}
bool Semantic::typeCheckBlock(Block *block){
	std::cout << "Check block type" << std::endl;
	std::vector<Expression*>::iterator it;
	for(it = block->expressions.begin(); it != block->expressions.end(); ++it){
		if(!typeCheckExpression(*it)){
			return false;
		}
	}
	return true;
}
bool Semantic::typeCheckCase(Case *caseExp){
	// ?
	return true;
}
bool Semantic::typeCheckComparison(Comparison *comparison){
	std::cout << "Check comparison type" << std::endl;
	Type *lhsType = getType(comparison->lhs);
	if(lhsType == NULL){
		compiler.errorStream << "unknown expression type";
		compiler.error(comparison->lhs->location);
		return false;
	}
	
	// NOT
	if(comparison->operation == Comparison::NOT){
		if(lhsType->name != "Bool"){
			compiler.errorStream << "cannot find NOT of type \"";
			compiler.errorStream << lhsType->name << "\"";
			compiler.error(comparison->lhs->location);
			return false;
		}
	}
	
	Type *rhsType = getType(comparison->rhs);
	if(rhsType == NULL){
		compiler.errorStream << "unknown expression type";
		compiler.error(comparison->rhs->location);
		return false;
	}
	
	// <, <=
	if(comparison->operation == Comparison::LESS_THAN
		|| comparison->operation == Comparison::LESS_THAN_EQUALS)
	{
		if(lhsType->name != "Int"){
			compiler.errorStream << "cannot use operator ";
			compiler.errorStream << Comparison::typeToString(comparison->operation);
			compiler.errorStream << " with type " << lhsType->name;
			compiler.error(comparison->lhs->location);
			return false;
		}
		if(rhsType->name != "Int"){
			compiler.errorStream << "cannot use operator ";
			compiler.errorStream << Comparison::typeToString(comparison->operation);
			compiler.errorStream << " with type " << rhsType->name;
			compiler.error(comparison->rhs->location);
			return false;
		}
	}
	
	// =
	if(comparison->operation == Comparison::EQUALS){
		if(lhsType->name == "Int" && rhsType->name != "Int"){
			compiler.errorStream << "cannot compare type Int with type \"";
			compiler.errorStream << rhsType->name << "\"";
			compiler.error(comparison->location);
			return false;
		}
		if(lhsType->name == "Bool" && rhsType->name != "Bool"){
			compiler.errorStream << "cannot compare type Bool with type \"";
			compiler.errorStream << rhsType->name << "\"";
			compiler.error(comparison->location);
			return false;
		}
		if(lhsType->name == "String" && rhsType->name != "String"){
			compiler.errorStream << "cannot compare type String with type \"";
			compiler.errorStream << rhsType->name << "\"";
			compiler.error(comparison->location);
			return false;
		}
		if(rhsType->name == "Int" && lhsType->name != "Int"){
			compiler.errorStream << "cannot compare type Int with type \"";
			compiler.errorStream << lhsType->name << "\"";
			compiler.error(comparison->location);
			return false;
		}
		if(rhsType->name == "Bool" && lhsType->name != "Bool"){
			compiler.errorStream << "cannot compare type Bool with type \"";
			compiler.errorStream << lhsType->name << "\"";
			compiler.error(comparison->location);
			return false;
		}
		if(rhsType->name == "String" && lhsType->name != "String"){
			compiler.errorStream << "cannot compare type String with type \"";
			compiler.errorStream << lhsType->name << "\"";
			compiler.error(comparison->location);
			return false;
		}
	}
	return true;
}
bool Semantic::typeCheckConditional(Conditional *conditional){
	std::cout << "Check conditional type" << std::endl;
	Type *ifType = getType(conditional->ifBranch);
	if(ifType->name != "Bool"){
		compiler.errorStream << "error: if statement type \"";
		compiler.errorStream << ifType->name << "\"";
		compiler.errorStream << ", expecting type Bool";
		compiler.error(conditional->ifBranch->location);
		return false;
	}
	return true;
}
bool Semantic::typeCheckDispatch(Dispatch *dispatch){
	// ?
	return true;
}
bool Semantic::typeCheckLet(Let *let){
	std::cout << "Check let type" << std::endl;
	compiler.symbolScope.enterScope();
	compiler.methodScope.enterScope();
	
	std::vector<Attribute*>::iterator it;
	for(it = let->attributes.begin(); it != let->attributes.end(); ++it){
		if(!typeCheckAttribute(*it)){
			return false;
		}
	}
	if(!typeCheckExpression(let->expression)){
		return false;
	}
	compiler.symbolScope.exitScope();
	compiler.methodScope.exitScope();
	return true;
}
bool Semantic::typeCheckNew(){
	// ?
	return true;	
}
bool Semantic::typeCheckWhile(While *whileExp){
	std::cout << "Check while type" << std::endl;
	Type *whileType = getType(whileExp->condition);
	if(whileType->name != "Bool"){
		compiler.errorStream << "error: while statement type \"";
		compiler.errorStream << whileType->name << "\"";
		compiler.errorStream << ", expecting type Bool";
		compiler.error(whileExp->location);
		return false;
	}
	if(!typeCheckExpression(whileExp->loop)){
		return false;
	}
	return true;
}