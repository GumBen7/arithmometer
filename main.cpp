#include <iostream>
#include <list>

#include "Parser.h"
#include "Algorithms.h"

using namespace std;

int main() {
	list<string> exp = Parser::parseExp(cin);
	cout << Algorithms::calculateExp(exp);
	return 0;
}