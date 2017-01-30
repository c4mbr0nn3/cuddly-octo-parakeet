#pragma once
#include"City.h"

/* useless class, we kept it because we
are in a hurry and have taken code from 
our old tutorial on graph theory. */

class Node
{
private:
	City value;

public:

	Node()
	{
		value = City();
	}
	Node(City element)
	{
		value = element;
	}
	Node(const Node& myObject)
	{
		value = myObject.value;
	}
	~Node() {}

	City getValue()
	{
		return value;
	}
	void setValue(City element)
	{
		value = element;
	}
};

