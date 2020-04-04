#include "TreeNode.h"

void TreeNode::setValue(string v) {
	this->value = v;
}

void TreeNode::setOperatorType(OperatorType type) {
	this->operatorType = type;
}

void TreeNode::setFirstChild(TreeNode* node) {
	this->firstChild = node;
}

void TreeNode::setSecondChild(TreeNode* node) {
	this->secondChild = node;
}

TreeNode* TreeNode::getFirstChild() const {
	return firstChild;
}

TreeNode* TreeNode::getSecondChild() const {
	return secondChild;
}

string TreeNode::getValue() const {
	return value;
}

OperatorType TreeNode::getOperatorType() const {
	return operatorType;
}

TreeNode::~TreeNode() {
	deleteRec(this);
}

void TreeNode::deleteRec(TreeNode* node) {
	if (node) {
		deleteRec(node->getFirstChild());
		deleteRec(node->getSecondChild());
	}
}