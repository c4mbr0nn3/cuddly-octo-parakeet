#include "stdafx.h"
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <iostream>
#include <stdlib.h>     
#include <time.h>       
#include <string>
#include <fstream>
#include <iterator>
#include <sstream>
#include <utility>
#include <algorithm>
#include <limits.h>


#define V 8
#define E 13 // number of edges, for bellman ford

using namespace std;


class graph {
public:
	graph() {};
	int adj_matrix[V][V] = { 0,2,5,0,0,0,0,0,
		0,0,2,0,0,4,0,0,
		0,0,0,3,6,0,0,0,
		0,0,0,0,1,0,2,0,
		0,0,0,0,0,0,0,4,
		0,0,0,1,0,0,4,7,
		0,0,0,0,0,0,0,2,
		0,0,0,0,0,0,0,0 };
};

// DIJKSTRA
vector<pair<int, int>> initialize(int init) {
	vector<pair<int, int>> d_p;
	for (int i = 0; i < V; i++) {
		pair<int, int> tmp(INT_MAX, i);
		d_p.push_back(tmp);
	}
	pair<int, int> tmp1(0, init);
	d_p[init] = tmp1;
	return d_p;
}
vector<pair<int, int>> modifyQueue(int newDistance, int vertexToBeFound, vector<pair<int, int>> v) {

	for (int i = 0; i < v.size(); i++)
		if (v[i].second == vertexToBeFound) {
			pair<int, int> tmp(newDistance, vertexToBeFound);
			v[i] = tmp;
			sort(v.begin(), v.end());
		}
	return v;
}
void dijkstra(graph g, int init) {
	// initialize a vector containing nodes and relative distances
	// the node init = init+1 in the graph drawing
	vector<pair<int, int>> d_v = initialize(init);
	int previous[V];
	int distance[V];
	for (int i = 0; i < V; i++) {
		previous[i] = NULL;
		distance[i] = INT_MAX;
	}
	previous[init] = init;
	distance[init] = 0;
	sort(d_v.begin(), d_v.end());

	while (d_v.size() != 0) {
		int u = d_v[0].second;
		if (distance[u] < INT_MAX - 500 && distance[u] >= 0)
			cout << " " << " from " << previous[u] + 1 << " ----- visited " << u + 1 << " TOTAL DISTANCE " << distance[u] << endl;
		d_v.erase(d_v.begin());

		int v = 0;
		while (v < V) {
			if (g.adj_matrix[u][v] != 0) {
				int alt = distance[u] + g.adj_matrix[u][v];
				if (alt < distance[v]) {
					d_v = modifyQueue(alt, v, d_v);
					distance[v] = alt;
					previous[v] = u;
				}
			}
			v++;
		}
	}
	int o = V - 1;
	while (true) {
		cout << o + 1 << " with distance " << distance[o] << endl;
		o = previous[o];
		if (o == init) {
			cout << o + 1 << " with distance " << distance[o] << endl;
			break;
		}
	}
	return;

};

// FLOYD WARSHAL
void floydWarshal(graph g) {
	// initialization
	int dist[V][V];
	int pred[V][V];
	for (int i = 0; i < V; i++)
		for (int j = 0; j < V; j++) {
			if (i != j) {
				if (g.adj_matrix[i][j] == 0) {
					dist[i][j] = 999;
					pred[i][j] = 999;
				}
				else {
					dist[i][j] = g.adj_matrix[i][j];
					pred[i][j] = i;
				}
			}
			else {
				dist[i][j] = 0;
				pred[i][j] = 999;
			}
		}

	// FLOYD WARSHAL
	for (int h = 0; h < V; h++) {
		for (int i = 0; i < V; i++) {
			for (int j = 0; j < V; j++) {
				if (dist[i][j] > dist[i][h] + dist[h][j]) {
					dist[i][j] = dist[i][h] + dist[h][j];
					pred[i][j] = pred[h][j];
				}
			}
		}
	}

	// print
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++)
			if (dist[i][j] == 999)
				cout << "- ";
			else
				cout << dist[i][j] << " ";
		cout << endl;
	}
}

// BELLMAN-FORD
void bellmanFord(graph g, int init) {

	int previous[V];
	int distance[V];
	for (int i = 0; i < V; i++) {
		previous[i] = NULL;
		distance[i] = 999;
	}
	previous[init] = init;
	distance[init] = 0;

	for (int i = 0; i < V - 1; i++) {
		for (int u = 0; u < V; u++) {
			for (int v = 0; v < V; v++) {
				if (distance[v] > distance[u] + g.adj_matrix[u][v] && g.adj_matrix[u][v] != 0) {
					distance[v] = distance[u] + g.adj_matrix[u][v];
					previous[v] = u;
				}
			}
		}
	}

	int o = V - 1;
	while (true) {
		cout << o + 1 << " with distance " << distance[o] << endl;
		o = previous[o];
		if (o == init) {
			cout << o + 1 << " with distance " << distance[o] << endl;
			break;
		}
	}


}

int main()
{
	graph g;
	cout << "DIJKSTRA " << endl << endl;
	dijkstra(g, 0);
	cout << endl << endl << "FLOYDWARSHAL" << endl << endl;
	floydWarshal(g);
	cout << endl << endl << "BELLMANFORD" << endl << endl;
	bellmanFord(g, 0);
	cout << endl;
	system("pause");

	return 0;
}


