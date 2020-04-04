#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <list>

#include "OpearatorType.h"

using namespace std;

class Parser
{
private:
	static const char NEGATIVE_FUNC_SIGN = '~';
	static const char POINT_CHAR = '.';
	static bool isDigit(char c);
	static bool isPoint(char c);
public:
	static list<string> parseExp(istream& is); 
	static OperatorType getOperatorTypeByName(string name);
};

