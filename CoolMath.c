#include "CoolMath.h"

static Variable variables[MAX_VARS];
static int nVars = 0;

double coolAdd(double a, double b){
	return (a + b);
}
double coolSubtract(double a, double b){
	return (a - b);
}
double coolMultiply(double a, double b){
	return (a * b);
}
double coolDivide(double a, double b){
	if(b == 0){
		fprintf(stderr, "Error: Divide by zero\n");
		return 0;
	}
	return (a / b);
}

Variable* coolFindVar(const char* name){
	if(name == NULL){
		return NULL;
	}
	int i;
	for(i = 0; i < nVars; i++){
		if(strcmp(variables[i].name, name) == 0){
			return variables + i;
		}
	}
	return NULL;
}
Variable* coolVarGet(const char* name){
	Variable *var;
	var = coolFindVar(name);
	if(var == NULL){
		fprintf(stderr, "Error: variable \"%s\" not defined.\n", name);
		return NULL;
	}
	return var;
}
void coolVarSet(const char* name, double value){
	if(name == NULL){
		return;
	}
	if(nVars >= MAX_VARS){
		fprintf(stderr, "Error: maximum number (%d) of variables reached.\n", MAX_VARS);
		return;
	}
	
	Variable *var;
	var = coolFindVar(name);
	if(var != NULL){
		var->value = value;
		return;
	}
	
	variables[nVars].value = value;
	variables[nVars].name = (char *)malloc(strlen(name) + 1);
	if(variables[nVars].name == NULL){
		fprintf(stderr, "Error: internal error created variable \"%s\".\n", name);
		return;
	}
	strcpy(variables[nVars].name, name);
	nVars += 1;
	return;
}