// tut6.cpp : definisce il punto di ingresso dell'applicazione console.
//

#include "stdafx.h"
#include <iostream>
#include<fstream>
#include<iomanip>
#include<cmath>
#include<random>
#include<time.h>
#include<algorithm>
#include <stdio.h>
#include <stdlib.h>
#include<vector>
#include <string>
#include<sstream>
#include<queue>
#include <functional>

using namespace std;

# define INF 0x3f3f3f3f

class  DisjointSets
{
public:
	int *parent;
	int *rnk;
	int n;
	DisjointSets(int n) {
		this->n = n;
		parent = new int[n + 1];
		rnk = new int[n + 1];

		for (int i = 0; i <= n; i++)
		{
			rnk[i] = 0;
			parent[i] = i;
		}
	}
	~DisjointSets() {}

	int find(int u) {
		if (u != parent[u])
			parent[u] = find(parent[u]);
		return parent[u];
	}

	void merge(int x, int y) {
		x = find(x);
		y = find(y);

		if (rnk[x] > rnk[y])
			parent[y] = x;
		else
			parent[x] = y;

		if (rnk[x] == rnk[y])
			rnk[y]++;
	}
};

class Node
{
//private:

public:
	int value;

	Node()
	{
		value = NULL;
	}
	Node(int element)
	{
		value = element;
	}
	Node(const Node& myObject)
	{
		value = myObject.value;
	}
	~Node() {}

	int getValue()
	{
		return value;
	}
	void setValue(int element)
	{
		value = element;
	}
};

class edge
{
public:
	Node start;
	Node end;
	double weight;

	edge() {
		start = NULL;
		end = NULL;
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

//private:

};

struct sortWeight
{
	inline bool operator()(const edge& A, const edge& B) {
		return (A.weight < B.weight);
	}
};

class graph
{
public:
	vector<edge> edges;
	int V;
	int E;

	graph() {
		V = NULL;
		E = NULL;
	}
	graph(int v, int e) {
		V = v;
		E = e;
	}
	graph(const graph& myObject)
	{
		V = myObject.V;
		E = myObject.E;
		edges = myObject.edges;
	}
	~graph() {}

	void addEdge(int src, int dest, double w) {
		Node newNode1(src);
		Node newNode2(dest);
		edge newEdge(newNode1, newNode2, w);
		edges.push_back(newEdge);
		++E;
		cout << "Edge added: (" << src << "," << dest << "," << w << ")" << endl;
	}
	double kruskalMST() {
		double mst_wt = 0;

		sort(edges.begin(), edges.end(),sortWeight());
		
		DisjointSets ds(V);

		for (unsigned i = 0; i != edges.size(); ++i)
		{
			int u = edges[i].getStart().getValue();
			int v = edges[i].getEnd().getValue();

			int set_u = ds.find(u);
			int set_v = ds.find(v);

			if (set_u != set_v)
			{
				cout << u << " - " << v << endl;

				mst_wt += edges[i].getWeight();

				ds.merge(set_u, set_v);
			}
		}
		return mst_wt;
	}

	void loadFile(string filePath) {
		vector<int> tmp;
		//vector<int>::iterator it;
		string line;
		ifstream in(filePath);
		if (!in) {
			cout << "unable to open file" << endl;
			return;
		}
		while (getline(in, line))
		{
			stringstream linestream(line);
			int src;
			int dest;
			double weight;

			linestream >> src >> dest >> weight;
			if (find(tmp.begin(),tmp.end(),src)==tmp.end())
			{
				tmp.push_back(src);
			}
			if (find(tmp.begin(), tmp.end(), dest) == tmp.end())
			{
				tmp.push_back(dest);
			}
			addEdge(src, dest, weight);
		}
		V = tmp.size();
	}
};

int main()
{
	graph *g = new graph();
	string filePath;
	cout << "Enter filename of the graph: ";
	cin >> filePath;
	g->loadFile(filePath);

	cout << "Edges of MST are \n";
	double mst_wt = g->kruskalMST();

	cout << "\nWeight of MST is " << mst_wt << endl;

	system("pause");
	return 0;
}

