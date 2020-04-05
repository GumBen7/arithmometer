#include <iostream>
#include <list>
#include <iomanip>

#include "Parser.h"
#include "Algorithms.h"

using namespace std;

static const bool IS_LOGGING_DEF = true;

int main() {
	while (true) {
		char c;
		bool isLogging = IS_LOGGING_DEF;
		int fieldWidth = Parser::FIELD_WIDTH_DEF;
		list<string> exp;
		cout << setprecision(Parser::PRECISION_DEF);
		cout << "Put down expression" << endl;
		try {
			exp = Parser::parseExp(cin, c);
		}
		catch (exception& e) {
			cout << setw(fieldWidth) << e.what() << endl;
			while (c != '\n') {  //skipping until endl
				cin.get(c);
			}
		}
		if (!exp.empty()) {
			if (isLogging) {
				cout << endl << setw(fieldWidth) << "Log" << endl;
			}
			try {
				cout << endl <<setw(fieldWidth) << "Result" << '\n' << setw(fieldWidth) << Algorithms::calculateExp(exp, isLogging) << endl;
			}
			catch (exception& e) {
				cout << setw(fieldWidth) << e.what() << endl;
			}
		}
	}
	return 0;
}