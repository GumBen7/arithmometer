#include "Algorithms.h"

list<string> Algorithms::getExpInRPN(const list<string>& exp) {
	list<string> expInRPN;
	stack<string> opStack;
	for (auto s : exp) {
		OperatorType type;
		type = Parser::getOperatorTypeByName(s);
		if (type == OperatorType::NONE) {
			expInRPN.push_back(s);
		}
		else if (type == OperatorType::LEFT_PAR || type == OperatorType::NEG) {
			opStack.push(s);
		}
		else if (type == OperatorType::RIGHT_PAR) {
			string opName;
			while (!opStack.empty() && Parser::getOperatorTypeByName(opName = opStack.top()) != OperatorType::LEFT_PAR) {
				expInRPN.push_back(opName);
				opStack.pop();
			}
			opStack.pop();
		}
		else {
			string opName;
			while (!opStack.empty() && operatorTypeLessThanOrEqual(Parser::getOperatorTypeByName(opName = opStack.top()), type)) {
				expInRPN.push_back(opName);
				opStack.pop();
			}
			opStack.push(s);
		}
	}
	while (!opStack.empty()) {
		expInRPN.push_back(opStack.top());
		opStack.pop();
	}
	return expInRPN;
}

double Algorithms::calculateRPN(const list<string>& rPN) {
	stack<double> st;
	for (auto s : rPN) {
		OperatorType type = Parser::getOperatorTypeByName(s);
		if (type == OperatorType::NONE) {
			st.push(stod(s));
		}
		else if (type == OperatorType::NEG) {
			double operand = st.top();
			st.pop();
			st.push(operate(type, operand));
		}
		else {
			double operand2 = st.top();
			st.pop();
			double operand1 = st.top();
			st.pop();
			st.push(operate(type, operand1, operand2));
		}
	}
	double res = st.top();
	st.pop();
	return res;
}

double Algorithms::calculateExp(const list<string>& exp) {
	return (calculateRPN(getExpInRPN(exp)));
}

double Algorithms::operate(OperatorType type, double op1, double op2) {
	if (type == OperatorType::NEG) {
		return -op1;
	}
	else if (type == OperatorType::ADD) {
		return op1 + op2;
	}
	else if (type == OperatorType::SUB) {
		return op1 - op2;
	}
	else if (type == OperatorType::MULT) {
		return op1 * op2;
	}
	else {
		return op1 / op2;
	}
}

bool Algorithms::operatorTypeLessThan(const OperatorType& l, const OperatorType& r) {

	if (l == OperatorType::NEG && r != OperatorType::NEG) {
		return true;
	}
	else {
		if (r == OperatorType::NEG) {
			return false;
		}
		else {
			if ((l == OperatorType::MULT || l == OperatorType::DIV) && (r != OperatorType::MULT && r != OperatorType::DIV)) {
				return true;
			}
			else {
				if (r == OperatorType::MULT || r == OperatorType::DIV) {
					return false;
				}
				else if ((l == OperatorType::ADD || l == OperatorType::SUB) && (r != OperatorType::ADD && r != OperatorType::SUB)) {
					return true;
				}
				else {
					return false;
				}
			}
		}


	}
	
}

bool Algorithms::operatorTypeLessThanOrEqual(const OperatorType& l, const OperatorType& r) {
	return !operatorTypeLessThan(r, l);
}
