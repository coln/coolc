#ifndef COOL_COOL_MATH_H_
#define COOL_COOL_MATH_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VARS 1000

typedef struct {
	char* name;
	double value;
} Variable;

double coolAdd(double, double);
double coolSubtract(double, double);
double coolMultiply(double, double);
double coolDivide(double, double);

Variable* coolFindVar(const char*);
Variable* coolVarGet(const char*);
void coolVarSet(const char*, double);

#endif