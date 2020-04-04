#include "Parser.h"

list<string> Parser::parseExp(istream& is) {
	list<string> exp;
	char c;
	bool isNumbGen = false;
	bool isPendingNumb = true;
	bool isPendingPoint = false;
	int openBrackets = 0;
	string token;
	while (is.get(c) && c != '\n') {
		if (!isspace(c) || (isNumbGen && !isPendingNumb)) { // skipping spaces
			if (c == '(' || c == ')') {
				if (c == ')' && openBrackets <= 0) {
					cerr << "unable to close brackets";
				}
				else {
					if (c == '(' && isPendingNumb) {
						++openBrackets;
						isNumbGen = false;
					}
					else if (c == ')') {
						--openBrackets;
						if (isNumbGen) {
							isNumbGen = false;
							isPendingPoint = false;
							exp.push_back(token);
							token.clear();
						}
					}
					else {
						cerr << "unexpected " << c;
						exit(EXIT_FAILURE);
					}
					exp.push_back(string(1, c));
				}
			}
			else if (c == '-' && !isNumbGen && isPendingNumb) {
				isNumbGen = true;
				isPendingPoint = true;
				exp.push_back(string(1, NEGATIVE_FUNC_SIGN));
			}
			else {
				if (isPendingNumb) {
					if (isDigit(c)) {
						token.push_back(c);
						isNumbGen = true;
						isPendingPoint = true;
						isPendingNumb = false;
					}
					else {
						cerr << "non digit found: " << c;
						exit(EXIT_FAILURE);
					}
				}
				else if (isNumbGen) {
					if (isDigit(c) || isPoint(c)) {
						if (!isPendingPoint) {
							cerr << "unexpected point found";
							exit(EXIT_FAILURE);
						}
						else {
							isPendingPoint = false;
						}
						token.push_back(c);
					}
					else if (isspace(c) || c == '+' || c == '-' || c == '*' || c == '/') {
						isNumbGen = false;
						isPendingPoint = false;
						exp.push_back(token);
						token.clear();
						if (!isspace(c)) {
							exp.push_back(string(1, c));
							isPendingNumb = true;
						}
					}
					else {
						cerr << "non digit found" << c;
						exit(EXIT_FAILURE);
					}
				}
				else {
					if (c == '+' || c == '-' || c == '*' || c == '/') {
						exp.push_back(string(1, c));
						isPendingNumb = true;
					}
					else {
						cerr << "non operator found" << c;
						exit(EXIT_FAILURE);
					}
				}
			}
		}
	}
	if (isPendingNumb && !exp.empty()) {
		cerr << "pending number";
		exit(EXIT_FAILURE);
	}
	if (openBrackets > 0) {
		cerr << "unclosed brackets";
		exit(EXIT_FAILURE);
	}
	if (isNumbGen) {
		exp.push_back(token);
		token.clear();
	}
	return exp;
}

OperatorType Parser::getOperatorTypeByName(string name) {
	if (name.compare(string(1, NEGATIVE_FUNC_SIGN)) == 0) {
		return OperatorType::NEG;
	}
	if (name.compare("(") == 0) {
		return OperatorType::LEFT_PAR;
	}
	if (name.compare(")") == 0) {
		return OperatorType::RIGHT_PAR;
	}
	if (name.compare("+") == 0) {
		return OperatorType::PLUS;
	}
	if (name.compare("-") == 0) {
		return OperatorType::MIN;
	}
	if (name.compare("*") == 0) {
		return OperatorType::MULT;
	}
	if (name.compare("/") == 0) {
		return OperatorType::DIV;
	}
	return OperatorType::NONE;
}

bool Parser::isDigit(char c) {
	return c >= '0' && c <= '9';
}

bool Parser::isPoint(char c) {
	return c == Parser::POINT_CHAR;
}