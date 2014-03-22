#ifndef COOLC_COOL_MATH_H_
#define COOLC_COOL_MATH_H_

#include "parser.h"

double coolAdd(double, double);
double coolSubtract(double, double);
double coolMultiply(double, double);
double coolDivide(double, double);

extern int yyerror(const char*, ...);

#endif