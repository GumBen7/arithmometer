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
	static const string UNEXPECTED_SYMB_ERROR;
	static const string EXPECTED_ERROR_LINE;
	static const string RIGHT_PARENTH_LACKS_ERROR;
	static const string PENDING_NUMBER_ERROR;
	static const char POINT_CHAR = '.';
	static bool isDigit(char c);
	static bool isPoint(char c);
public:
	static list<string> parseExp(istream& is); 
	static OperatorType getOperatorTypeByName(string name);
};

