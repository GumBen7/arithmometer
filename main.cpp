#include <iostream>
#include <list>
#include <iomanip>

#include "Parser.h"
#include "Algorithms.h"

using namespace std;

int main() {
	while (true) {
		char c;
		list<string> exp;
		cout << setprecision(10);
		cout << "Put down expression" << endl;
		try {
			exp = Parser::parseExp(cin, c);
		}
		catch (exception& e) {
			cout << setw(60) << e.what() << endl;
			while (c != '\n') {  //skipping until endl
				cin.get(c);
			}
		}
		if (!exp.empty()) {
			try {
				cout << setw(60) << "Result" << '\n' << setw(60) << Algorithms::calculateExp(exp) << endl;
			}
			catch (exception& e) {
				cout << setw(60) << e.what() << endl;
			}
		}
	}
	return 0;
}