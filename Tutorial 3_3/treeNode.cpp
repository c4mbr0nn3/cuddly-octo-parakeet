#include "treeNode.h"

// cracking the coding interview
// introduction to c++ for financial engineering

treeNode::treeNode()
{
	value = NULL;
}

treeNode::treeNode(int a)
{
	value = a;
}

treeNode::~treeNode()
{
}

int treeNode::getValue()
{
	return value;
}

void treeNode::setValue(int a)
{
	value = a;
}

/*treeNode* treeNode::getParent()
{
	return parent;
}

void treeNode::setParent(treeNode *a)
{
	parent = a;
}*/
treeNode* treeNode::getLeft()
{
	return left;
}

void treeNode::setLeft(int a)
{
	left = new treeNode(a);
}

treeNode* treeNode::getRight()
{
	return right;
}

void treeNode::setRight(int a)
{
	right = new treeNode(a);
}

pair<treeNode*, treeNode*> treeNode::children()
{
	pair<treeNode*, treeNode*> children;
	if (left != nullptr)
	{
		children.first = left;
	}
	if (right != nullptr)
	{
		children.second = right;
	}
	return children;
}
