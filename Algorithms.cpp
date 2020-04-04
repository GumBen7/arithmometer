#include "Algorithms.h"

list<string> Algorithms::getExpInRPN(const list<string>& exp) {
	list<string> expInRPN;
	stack<string> opStack;
	for (auto s : exp) {
		OperatorType type = Parser::getOperatorTypeByName(s);
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
			while (!opStack.empty() && Parser::getOperatorTypeByName(opName = opStack.top()) <= type) {
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