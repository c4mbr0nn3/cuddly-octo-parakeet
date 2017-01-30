#pragma once
#include <iostream>
using namespace std;

class treeNode
{
private:
	int value;
	treeNode *left;
	treeNode *right;
	//treeNode *parent;
public:
	treeNode();
	treeNode(int a);
	~treeNode();
	int getValue();
	void setValue(int a);
	//treeNode* getParent();
	//void setParent(treeNode *a);
	treeNode* getLeft();
	void setLeft(int a);
	treeNode* getRight();
	void setRight(int a);
	pair<treeNode*, treeNode*> children();
};

