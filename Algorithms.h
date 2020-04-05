#pragma once
#include <list>
#include <string>
#include <stack>
#include <iostream>
#include <iomanip>

#include "OpearatorType.h"
#include "Parser.h"

using namespace std;

class Algorithms
{
private:
	static const string DIVISION_BY_ZERO_ERROR;
public:
	static list<string> getExpInRPN(const list<string>& exp);
	static double calculateRPN(const list<string>& rPN, bool isLogging);
	static double calculateExp(const list<string>& exp, bool isLogging);
	static double operate(OperatorType type, double op1, double op2 = 0.);
	static bool operatorTypeLessThan(const OperatorType& l, const OperatorType& r);
	static bool operatorTypeLessThanOrEqual(const OperatorType& l, const OperatorType& r);
};

