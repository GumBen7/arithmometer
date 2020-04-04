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
};

