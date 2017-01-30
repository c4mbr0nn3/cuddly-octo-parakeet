#include <iostream>
#include <string>
#include <random>		// random
#include <time.h>       // time //
#include <cmath>		// math
#include "treeNode.h"
#include <algorithm>

using namespace std;

double randNumberDouble(double max)
{
	return (((double)rand()*(max) / (double)RAND_MAX) - max) *(-1);
}

class tree
{
private:
	treeNode *root;
	//int treeNodeNumber;
public:
	tree()
	{
		root = nullptr;
	}
	tree(int a)
	{
		root->setValue(a);
		//++treeNodeNumber;
	}
	void addRoot(int a)
	{
		root = new treeNode(a);
		//++treeNodeNumber;
	}
	treeNode* getRoot()
	{
		return root;
	}
	/*void addLeft(treeNode *parent, treeNode *a)
	{
		a->setParent(parent);
		parent->setLeft(a);
		++treeNodeNumber;
	}
	void addRight(treeNode *parent, treeNode *a)
	{
		a->setParent(parent);
		parent->setLeft(a);
		++treeNodeNumber;
	}*/
	int size()
	{

		//return treeNodeNumber;
	}
	bool isEmpty()
	{
		return getRoot() == 0;
	}
	/*treeNode* getParent(treeNode *a)
	{
		return a->getParent();
	}
	treeNode* getLeft(treeNode *a)
	{
		return a->getLeft();
	}
	treeNode* getRight(treeNode *a)
	{
		return a->getRight();
	}*/
	pair<treeNode*, treeNode*> getChildren(treeNode *a)
	{
		return a->children();
	}
	int numberChildren(treeNode *a)
	{
		pair<treeNode*, treeNode*> temp = getChildren(a);
		int number = 0;
		if (temp.first != nullptr)
		{
			++number;
		}
		if (temp.second != nullptr)
		{
			++number;
		}
		return number;
	}
	bool isInternal(treeNode *a)
	{
		return numberChildren(a) > 0;
	}
	bool isExternal(treeNode *a)
	{
		return numberChildren(a) == 0;
	}
	bool isRoot(treeNode *a)
	{
		return a == root;
	}
	/*int depth(treeNode *a)
	{
		if (isRoot(a))
		{
			return 0;
		}
		else
		{
			return 1 + depth(getParent(a));
		}
	}*/
	void randomBST(treeNode* node, int level)
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
	}


	void insertBST(treeNode *root, int element)
	{
		if (!root)
		{
			root = new treeNode(element);
			return;
		}
		if (element < root->getValue())
		{
			insertBST(root->getLeft(), element);
			//return root->setLeft(element);
		}
		else
		{
			insertBST(root->getRight(), element);
			//return root->setRight(element);
		}
	}

	void generateRndBST(treeNode *root,treeNode *ref, int level)
	{
		/*int tmpValueNode = root->getValue + (std::rand() % (max - root->getValue + 1)); // da root a max RIGHT
		int tmpValueNode = (std::rand() % (root->getValue + 1)); // da 0 a root LEFT*/

		if (level == 0)
		{
			return;
		}

		double tmpValue = randNumberDouble(1);
		int max = numeric_limits<int>::max();

		if (tmpValue < 0.5) // LEFT
		{
			int tmpValue1 = (std::rand() % ( + 1)); // da 0 a root LEFT
			root->setLeft(tmpValue1);
			cout << "left: " << root->getLeft()->getValue() << endl;
			tmpValue = randNumberDouble(1);
			if (tmpValue < 0.5) // RIGHT
			{
				tmpValue1 = root->getValue() + (std::rand() % (max - root->getValue() + 1)); // da root a max RIGHT
				root->setRight(tmpValue1);
				cout << "right: " << root->getRight()->getValue() << endl;
				generateRndBST(root->getRight(),ref, level - 1);
			}
			generateRndBST(root->getLeft(),ref, level - 1);
		}
		else // RIGHT
		{
			int tmpValue2 = root->getValue() + (std::rand() % (max - root->getValue() + 1)); // da root a max RIGHT
			root->setRight(tmpValue2);
			cout << "right: " << root->getRight()->getValue() << endl;
			tmpValue = randNumberDouble(1);
			if (tmpValue < 0.5) // LEFT
			{
				tmpValue2 = (std::rand() % (root->getValue() + 1)); // da 0 a root LEFT
				root->setLeft(tmpValue2);
				cout << "left: " << root->getLeft()->getValue() << endl;
				generateRndBST(root->getLeft(),ref, level - 1);
			}
			generateRndBST(root->getRight(),ref, level - 1);
		}
	}

	treeNode* findBST(treeNode *root, int value)
	{
		if (root->getValue() == value)
		{
			cout << "Founded!" << endl;
			return root;
		}

		if (root->getValue() > value)
		{
			cout << "Go Left..." << endl;
			findBST(root->getLeft(), value);
		}
		else
		{
			cout << "Go Right..." << endl;
			findBST(root->getRight(), value);
		}
	}

	void preorder(treeNode *node)
	{
		if (node != nullptr)
		{
			cout << node->getValue()<< "---";
			preorder(node->getLeft());
			preorder(node->getRight());
		}
	}

	void postorder(treeNode *node)
	{
		if (node != nullptr)
		{
			postorder(node->getLeft());
			postorder(node->getRight());
			cout << node->getValue() << "---";
		}
	}
	void inorder(treeNode *node)
	{
		if (node != nullptr)
		{
			inorder(node->getLeft());
			cout << node->getValue() << "---";
			inorder(node->getRight());
		}
	}
	int size(treeNode *root)
	{
		int h = 1;
		if (root->getLeft()==nullptr && root->getRight()==nullptr)
		{
			return 1;
		}
		return max(1+size(root->getLeft()),1+size(root->getRight()));
	}
};
void main()
{
	srand((unsigned)time(NULL));

	// int a = 3;

	tree *tree1 = new tree();

	tree1->addRoot(10);
	tree1->getRoot()->setLeft(78);
	tree1->getRoot()->setRight(3928);
	tree1->getRoot()->getLeft()->setLeft(476);
	tree1->getRoot()->getLeft()->getLeft()->setRight(3939);

	tree1->preorder(tree1->getRoot());

	cout << tree1->size(tree1->getRoot());

	/*tree1->insertBST(tree1->getRoot(),5);
	tree1->insertBST(tree1->getRoot(), 4);
	tree1->insertBST(tree1->getRoot(), 7);
	tree1->insertBST(tree1->getRoot(), 11);
	tree1->insertBST(tree1->getRoot(), 22);
	tree1->insertBST(tree1->getRoot(), 3);
	tree1->insertBST(tree1->getRoot(), 16);

	tree1->inorder(tree1->getRoot());

	/*tree1->generateRndBST(tree1->getRoot(), tree1->getRoot(), 3);

	tree1->preorder(tree1->getRoot());

	cout << endl;

	tree1->postorder(tree1->getRoot());

	cout << endl;

	system("pause");

	int b;

	cin >> b;

	treeNode *node1;
	node1=tree1->findBST(tree1->getRoot(), b);
	cout << node1->getValue() << endl;*/

	system("pause");
}