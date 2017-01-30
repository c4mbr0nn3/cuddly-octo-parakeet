// BST.cpp : definisce il punto di ingresso dell'applicazione console.
//

#include "stdafx.h"
#include <iostream>
#include<iomanip>
#include<cmath>
#include<random>
#include<time.h>
#include<algorithm>
using namespace std;

double randNumberDouble(double max)
{
	return (((double)rand()*(max) / (double)RAND_MAX) - max) *(-1);
}

class treeNode
{
private:
	int value;
	treeNode *left;
	treeNode *right;
	treeNode *parent;
public:
	treeNode()
	{
		value = NULL;
		left = NULL;
		right = NULL;
		parent = NULL;
	}
	treeNode(int element)
	{
		value = element;
		left = NULL;
		right = NULL;
		parent = NULL;
	}
	treeNode(int element, treeNode* ancestor)
	{
		value = element;
		left = NULL;
		right = NULL;
		parent = ancestor;
	}
	treeNode(treeNode& myObject)
	{
		value = myObject.value;
		left = myObject.left;
		right = myObject.right;
		parent = myObject.parent;
	}
	~treeNode(){}

	int getValue()
	{
		return value;
	}
	void setValue(int element)
	{
		value = element;
	}
	treeNode* getLeft()
	{
		return left;
	}
	void setLeft(int element)
	{
		left = new treeNode(element, this);
	}
	treeNode* getRight()
	{
		return right;
	}
	void setRight(int element)
	{
		right = new treeNode(element, this);
	}
	treeNode* getParent()
	{
		return parent;
	}
	void setParent(treeNode *a)
	{
		parent = a;
	}
};

class tree
{
private:
	treeNode *root;
public:
	tree()
	{
		root = new treeNode();
	}
	tree(int element)
	{
		root = new treeNode(element);
	}
	tree(tree& myObject)
	{
		root = myObject.root;
	}
	~tree() {}

	void addRoot(int element)
	{
		root->setValue(element);
	}
	treeNode* getRoot()
	{
		return root;
	}
	void addLeft(int key, treeNode* node)
	{
		node->setLeft(key);
	}
	void addRight(int key, treeNode* node)
	{
		node->setRight(key);
	}
	/*void randomBST(treeNode* node, int level)
	{
		if (level == 0)
		{
			return;
		}
		double tmpTrigger = randNumberDouble(1);
		int max = numeric_limits<int>::max();
		if (tmpTrigger < 0.5)
		{
			int tmpValue = rand() % max;
			node->setLeft(tmpValue);
			tmpTrigger = randNumberDouble(1);
			if (tmpTrigger < 0.5)
			{
				tmpValue = rand() % max;
				node->setRight(tmpValue);
				randomBST(node->getRight(), level - 1);
			}
			randomBST(node->getLeft(), level - 1);
		}
		else
		{
			int tmpValue = rand() % max;
			root->setRight(tmpValue);
			tmpTrigger = randNumberDouble(1);
			if (tmpTrigger < 0.5)
			{
				tmpValue = rand() % max;
				root->setLeft(tmpValue);
				randomBST(node->getLeft(), level - 1);
			}
			randomBST(node->getRight(), level - 1);
		}
	}*/
	void randomBST(treeNode* node, int level)
	{
		if (level == 0) // RETURN
		{
			return;
		}
		double tmpTrigger = randNumberDouble(1);
		int max = numeric_limits<int>::max();
		if (tmpTrigger < 0.5) // LEFT
		{

		}
	}
	void addNode(int key, treeNode* node)
	{
		if (node->getLeft() == NULL && key < node->getValue())
		{
			node->setLeft(key);
			cout << "node added! Value: " << key << endl;
		}
		else if (node->getRight() == NULL && key > node->getValue())
		{
			node->setRight(key);
			cout << "node added! Value: " << key << endl;
		}

		if (key < node->getValue())
		{
			addNode(key, node->getLeft());
		}
		else if (key > node->getValue())
		{
			addNode(key, node->getRight());
		}
	}
	void searchBST(int element, treeNode* node)
	{
		if (element == node->getValue())
		{
			cout << "Founded!! Element: " << node->getValue() << endl;
			return;
		}
		if (element < node->getValue())
		{
			cout << "Go Left!" << endl;
			searchBST(element, node->getLeft());
		}
		else
		{
			cout << "Go Right!" << endl;
			searchBST(element, node->getRight());
		}
	}
	int height(treeNode* node)
	{
		if (node == NULL)
			return -1;
		else
			return (1 + max(height(node->getLeft()), height(node->getRight())));
	}
	void inorder(treeNode* root)
	{
		if (root != NULL) {
			inorder(root->getLeft());
			cout << root->getValue() << " ";
			inorder(root->getRight());
		}
	}
	/*void postorder(treeNode* p, int indent = 0)
	{
		if (p != NULL) {
			if (p->getLeft()) postorder(p->getLeft(), indent + 4);
			if (p->getRight()) postorder(p->getRight(), indent + 4);
			if (indent) {
				std::cout << std::setw(indent) << ' ';
			}
			cout << p->getValue() << "\n ";
		}
	}*/
};

int main()
{
	tree *testTree = new tree(50);

	//testTree->randomBST(testTree->getRoot(), 3);
	testTree->addNode(59, testTree->getRoot());
	testTree->addNode(90, testTree->getRoot());
	testTree->addNode(45, testTree->getRoot());
	testTree->addNode(10, testTree->getRoot());
	testTree->addNode(30, testTree->getRoot());
	testTree->addNode(25, testTree->getRoot());
	testTree->addNode(20, testTree->getRoot());

	//cout << testTree->getRoot()->getLeft();

	testTree->inorder(testTree->getRoot());
	cout << endl;

	testTree->searchBST(20, testTree->getRoot());

	cout << testTree->height(testTree->getRoot()) << endl;

	system("pause");

	return 0;
}