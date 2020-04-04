#pragma once
#include <list>
#include <string>
#include <stack>

#include "OpearatorType.h"
#include "Parser.h"

using namespace std;

class Algorithms
{
public:
	static list<string> getExpInRPN(const list<string>& exp);
	static double calculateRPN(const list<string>& rPN);
	static double calculateExp(const list<string>& exp);
	static double operate(OperatorType type, double op1, double op2 = 0.);
	static bool operatorTypeLessThan(const OperatorType& l, const OperatorType& r);
	static bool operatorTypeLessThanOrEqual(const OperatorType& l, const OperatorType& r);
};

