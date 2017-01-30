#pragma once
#include"Node.h"

class edge
{
private:
	Node start;	// first vertex of the edge
	Node end;	// second vertex of the edge
	double weight;
public:
	edge() {
		start = Node();
		end = Node();
		weight = NULL;
	}
	edge(Node s, Node e, double w) {
		start = s;
		end = e;
		weight = w;
	}
	edge(const edge& myObject) {
		start = myObject.start;
		end = myObject.end;
		weight = myObject.weight;
	}
	~edge() {}
	void setStart(Node node) {
		start = node;
	}
	Node getStart() {
		return start;
	}
	void setEnd(Node node) {
		end = node;
	}
	Node getEnd() {
		return end;
	}
	void setWeight(double w) {
		weight = w;
	}
	double getWeight() {
		return weight;
	}
};

