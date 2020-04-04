#include "Parser.h"

const string Parser::UNEXPECTED_SYMB_ERROR = "ERROR unexpected symbol/at: ";
const string Parser::EXPECTED_ERROR_LINE = "expected ";
const string Parser::RIGHT_PARENTH_LACKS_ERROR = "ERROR lacks of right parentheses";
const string Parser::PENDING_NUMBER_ERROR = "ERROR lacks of number";

list<string> Parser::parseExp(istream& is) {
	list<string> exp;
	char c;
	streamsize i = 0;
	bool isNumbGen = false;
	bool isPendingNumb = true;
	bool isPendingPoint = false;
	int openBrackets = 0;
	string token;
	while (is.get(c) && c != '\n') {
		if (!isspace(c) || (isNumbGen && !isPendingNumb)) { // skipping spaces
			if (c == '(' || c == ')') {
				if (c == ')' && openBrackets <= 0) {
					stringstream ss;
					ss << UNEXPECTED_SYMB_ERROR << '\'' << c << "'/[" << i << "]; " << EXPECTED_ERROR_LINE << "'(' earlier";					
					throw range_error(ss.str());
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
						stringstream ss;
						ss << UNEXPECTED_SYMB_ERROR << '\'' << c << "\'/[" << i << "]; " << EXPECTED_ERROR_LINE << "operator";
						throw range_error(ss.str());
					}
					exp.push_back(string(1, c));
				}
			}
			else if (c == '-' && !isNumbGen && isPendingNumb) {
				isNumbGen = true;
				isPendingPoint = true;
				exp.push_back(string(1, (char)OperatorType::NEG));
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
						stringstream ss;
						ss << UNEXPECTED_SYMB_ERROR << '\'' << c << "\'/[" << i << "]";
						throw range_error(ss.str());
					}
				}
				else if (isNumbGen) {
					if (isDigit(c) || isPoint(c)) {
						if (isPoint(c)) {
							if (!isPendingPoint) {
								stringstream ss;
								ss << UNEXPECTED_SYMB_ERROR << '\'' << c << "\'/[" << i << "]";
								throw range_error(ss.str());
							}
							else {
								isPendingPoint = false;
							}
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
						stringstream ss;
						ss << UNEXPECTED_SYMB_ERROR << '\'' << c << "\'/[" << i << "]";
						throw range_error(ss.str());
					}
				}
				else {
					if (c == '+' || c == '-' || c == '*' || c == '/') {
						exp.push_back(string(1, c));
						isPendingNumb = true;
					}
					else {
						stringstream ss;
						ss << UNEXPECTED_SYMB_ERROR << '\'' << c << "\'/[" << i << "]; " << EXPECTED_ERROR_LINE << "operator";
						throw range_error(ss.str());
					}
				}
			}
		}
		++i;
	}
	if (isPendingNumb && !exp.empty()) {
		throw range_error(PENDING_NUMBER_ERROR);
	}
	if (openBrackets > 0) {
		throw range_error(RIGHT_PARENTH_LACKS_ERROR);
	}
	if (isNumbGen) {
		exp.push_back(token);
		token.clear();
	}
	return exp;
}

OperatorType Parser::getOperatorTypeByName(string name) {
	if (name.compare(string(1, (char)OperatorType::NEG)) == 0) {
		return OperatorType::NEG;
	}
	if (name.compare("(") == 0) {
		return OperatorType::LEFT_PAR;
	}
	if (name.compare(")") == 0) {
		return OperatorType::RIGHT_PAR;
	}
	if (name.compare("+") == 0) {
		return OperatorType::ADD;
	}
	if (name.compare("-") == 0) {
		return OperatorType::SUB;
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