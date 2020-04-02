#include "Parser.h"

list<string> Parser::parseExp(istream& is) {
	list<string> exp;
	char c;
	bool numbGen = false;
	bool pendingNumb = true;
	int openBrackets = 0;
	string token;
	while (is.get(c) && c != '\n') {
		if (!isspace(c) || (numbGen && !pendingNumb)) { // skipping spaces
			if (c == '(' || c == ')') {
				if (c == ')' && openBrackets <= 0) {
					cerr << "unable to close brackets";
				} 
				else {
					if (c == '(' && pendingNumb) {
						++openBrackets;
					}
					else if (c == ')') {
						--openBrackets;
						if (numbGen) {
							numbGen = false;
							exp.push_back(token);
							token.clear();
						}
					} 
					else {
						cerr << "unexpected " << c;
						exit(EXIT_FAILURE);
					}
					token.push_back(c);
					exp.push_back(token);
					token.clear();
				}
			}
			else if (c == '-' && !numbGen && pendingNumb) {
				numbGen = true;
				token.push_back('!');
				exp.push_back(token);
				token.clear();
			} 
			else {
				if (pendingNumb) {
					if (isDigit(c)) {
						token.push_back(c);
						numbGen = true;
						pendingNumb = false;
					}
					else {
						cerr << "non digit found: " << c;
						exit(EXIT_FAILURE);
					}
				}
				else if (numbGen) {
					if (isDigit(c)) {
						token.push_back(c);
					} 
					else if (isspace(c) || c == '+' || c == '-' || c == '*' || c == '/') {
						numbGen = false;
						exp.push_back(token);
						token.clear();
						if (!isspace(c)) {
							token.push_back(c);
							exp.push_back(token);
							token.clear();
							//if (c != ')') {
								pendingNumb = true;
							//}
						}
					} 
					else {
						cerr << "non digit found" << c;
						exit(EXIT_FAILURE);
					}
				} 
				else {
					if (c == '+' || c == '-' || c == '*' || c == '/') {
						token.push_back(c);
						exp.push_back(token);
						token.clear();
						pendingNumb = true;
					} 
					else {
						cerr << "non operator found" << c;
						exit(EXIT_FAILURE);
					}
				}
			}
		}
	}
	if (pendingNumb && !exp.empty()) {
		cerr << "pending number";
		exit(EXIT_FAILURE);
	}
	exp.push_back(token);
	token.clear();
	return exp;
}

bool Parser::isDigit(char c) {
	return c >= '0' && c <= '9';
}