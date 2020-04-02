#include <iostream>

#include "Parser.h"

using namespace std;

int main() {
	for (auto t : Parser::parseExp(cin)) {
		cout << t << endl;
	}
	return 0;
}