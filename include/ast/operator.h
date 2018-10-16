#pragma once

#include <string>

enum BOperator {
	PLUS, 
	MINUS, 
	MULTIPLY, 
	DIVIDE,
	MODULO, 
	AND, 
	OR, 
	GT, 
	GTE, 
	LT, 
	LTE, 
	EQ

}; // enum BOperator

enum UOperator {
	NOT,

}; // enum UOperator

std::string BOpToString(BOperator op);

std::string UOpToString(UOperator op);

