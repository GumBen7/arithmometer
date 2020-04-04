#include <iostream>
#include <list>

#include "Parser.h"
#include "Algorithms.h"

using namespace std;

int main() {
	try {
		list<string> exp = Parser::parseExp(cin);
		cout << Algorithms::calculateExp(exp);
	}
	catch (exception& e) {
		cout << e.what();
	}
	return 0;
}