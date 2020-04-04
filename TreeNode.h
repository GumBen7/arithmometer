#pragma once
#include <string>

#include "OpearatorType.h"

using namespace std;
class TreeNode
{
private: 
	TreeNode* firstChild = nullptr;
	TreeNode* secondChild = nullptr;

	string value;
	OperatorType operatorType;
	void deleteRec(TreeNode* node);

public:
	void setFirstChild(TreeNode* node);
	void setSecondChild(TreeNode* node);
	void setValue(string v);
	void setOperatorType(OperatorType type);
	TreeNode* getFirstChild() const;
	TreeNode* getSecondChild() const;
	string getValue() const;
	OperatorType getOperatorType() const;
	~TreeNode();
};

