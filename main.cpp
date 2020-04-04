#include <iostream>
#include <list>

#include "Parser.h"
#include "Algorithms.h"

using namespace std;

int main() {
	list<string> exp = Parser::parseExp(cin);
	for (auto s : Algorithms::getExpInRPN(exp)) {
		cout << s << endl;
	}
	return 0;
}