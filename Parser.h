#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <list>

using namespace std;

class Parser
{
private:
	static bool isDigit(char c);
public:
	static list<string> parseExp(istream& is); 
};

