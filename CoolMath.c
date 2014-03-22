#include "CoolMath.h"

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
		yyerror("divide by zero");
		return 0;
	}
	return (a / b);
}