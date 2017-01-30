// FinalProj.cpp : definisce il punto di ingresso dell'applicazione console.
//

#include "stdafx.h"
#include <vector>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <utility>
#include<limits>
#include"City.h"
#include"Node.h"
#include"Edge.h"
#include"graph.h"

using namespace std;

#define R 6372.795477598 // earth radius
#define PI 3.141592654

// useful function to clean the console screen
void ClearScreen()
{
	cout << string(100, '\n');
}

// function to print a path on the console
void printPath(vector<City> path) {
	for (int i = 0; i < path.size(); ++i) {
		cout << i + 1 << "\t" << path[i].getName() << endl;
	}
}

// overload of the previous function
void printPath(vector<edge> path) {
	for (int i = 0; i < path.size(); ++i) {
		cout << i + 1 << "\t" << path[i].getStart().getValue().getName()<<" - "<<
			path[i].getEnd().getValue().getName() << endl;
	}
}

// earth distance formula
double calcDist(City one, City two) {
	double d = R*acos(sin(one.getLat()*PI / 180)*sin(two.getLat()*PI / 180) +
		cos(one.getLat()*PI / 180)*cos(two.getLat()*PI / 180)*cos((one.getLong() - two.getLong())*PI / 180));
	if (d < 100) 
	{ 
		return -INFINITY; 
	}
	else
	{
		return d;
	}
}

// load method (.CSV reader)
vector<City> loadDB() {
	string line;
	ifstream in("Cites.csv");
	vector <City> tempVec;
	if (!in) {
	cout << "File not found!" << endl;
	return tempVec;
	}
	getline(in, line);
	while (getline(in, line))
	{
	stringstream linestream(line);
	string cityName;
	double lat;
	double lon;
	for (int col = 0; col < 3; ++col) {
		string val;
		getline(linestream, val, ',');
		if (col == 0)
		{
			cityName = val;
		}
		else if(col==1)
		{
			lat = stod(val);
		}
		else
		{
			lon = stod(val);
		}
	}
	
	City temp(cityName, lat, lon);

	tempVec.push_back(temp);
	}

	return tempVec;
}

int main()
{
	// turn on the program
	bool swOn = true;

	// Initialize value
	graph *grafo = new graph();
	vector<City> local;
	vector<City> opt;
	vector<edge> mst;
	int k;
	
	// User Interface
	while (swOn != false)
	{
		// Initialize values
		char choice1;
		
		ClearScreen();
		cout << "\t*** Welcome in the Travelling Salesman Problem Program ***\n" << endl;
		cout << "[1]\tLoad the graph from Cites.csv\n";
		cout << "[2]\tPerform brute force algorithm to 5 random cities\n";
		cout << "[3]\tPerform 2opt heuristic solution\n";
		cout << "[4]\tPerform Local Search solution (Reversed Prim's Algorithm)\n";
		cout << "[5]\tCompute Minimum Spanning Trees (Prim's Algorithm)\n";
		cout << "[Q]\tExit program :(\n";
		cout << "Enter your choice: ";
		cin >> choice1;
		switch (choice1)
		{
		case '1':
			ClearScreen();
			grafo->build();
			cout << "Graph succesfully loaded from Cites.csv\n\n";
			//printPath(grafo->edges);
			system("pause");
			break;
		case'2':
			ClearScreen();
			grafo->brute_force();
			cout << endl;
			system("pause");
			break;
		case '3':
			ClearScreen();
			opt.clear();
			cout << "How many swap iterations do you want to perform? ";
			cin >> k;
			opt = grafo->two_opt(k);
			cout << endl << endl << "Longest path from Paris to Paris" << endl;
			printPath(opt);
			cout << "You will find distances on top of the list ;-)\n";
			system("pause");
			break;
		case '4':
			ClearScreen();
			local.clear();
			local = grafo->localSearchPath();
			cout << "Path length: " << grafo->pathlength(local) << " Km" << endl;
			cout << endl << "Longest path from Paris to Paris" << endl;
			printPath(local);
			cout << "You will find distances on top of the list ;-)\n";
			system("pause");
			break;
		case '5':
			ClearScreen();
			mst.clear();
			mst = grafo->MST();
			cout << endl << endl << "Minimum Spanning Tree from Paris" << endl;
			printPath(mst);
			cout << "You will find distances on top of the list ;-)\n";
			system("pause");
			break;
		case'Q':
			swOn = false;
			break;
		}
	}
	cout << endl;
	system("pause");
	return 0;
}

