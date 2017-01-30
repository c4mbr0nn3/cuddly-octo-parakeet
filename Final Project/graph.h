#pragma once
#include"Edge.h"
#include"City.h"
#include<vector>
#include<limits>
#include <chrono>
#include <random>

double calcDist(City one, City two);
vector<City> loadDB();

// custom sorting function: used to sort edge by weights
struct sortWeight
{
	inline bool operator()(edge& A, edge& B) {
		return (A.getWeight() < B.getWeight());
	}
};

class graph
{
public:
	vector<edge> edges;		// edges vector
	int V;					// number of nodes (cities)
	int E;					// number of edges
	vector<City> cities;	// vector of cities

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
		cities = myObject.cities;
	}
	~graph() {}

	void addEdge(City src, City dest, double w) // create an edge and add it to the edges vector
	{
		Node newNode1(src);
		Node newNode2(dest);
		edge newEdge(newNode1, newNode2, w);
		edges.push_back(newEdge);
		++E;
	}
	void build() // build the graph (we choose edge list) loading it from the given .csv file
	{
		cities = loadDB();
		
		V = (int)cities.size();
		
		for (int i = 0; i < V; ++i)
		{
			for (int j = 0; j < V; ++j)
			{
				double d = calcDist(cities[i], cities[j]);
				
				if (d>100)
				{
					addEdge(cities[i], cities[j], d);
				}
			}
		}
	}
	int findFirstEdge(int cityNumber) // output: index of first edge having as start node the city referring to the index "citynumber"
	{
		/*At most 70 outgoing link from a city. By
		our choice we reduce this factor to 65 and then
		we multiply it by the city index. In this way we
		reduce a little bit the work for a linear search.*/
		int index= 65*cityNumber;

		for (int i = index; i < E; ++i) {
			string string_one = edges[i].getStart().getValue().getName();
			string string_two = cities[cityNumber].getName();
			if (string_one.compare(string_two)==0) {
				index = i;
				return index;
			}
		}
		return -1;
	}

	int searchCity(string searchkey) // output: city index (from the list of all the cities) corresponding to "searchkey"
	{
		for (int i = 0; i < V; ++i)
		{
			if (searchkey.compare(cities[i].getName()) == 0)
			{
				return i;
			}
		}
		return -1;
	}

	int minWeight(int citynumber, bool mstSet[]) // output: city index with MIN weight and not in set
	{

		double min = INFINITY;
		int min_index = -1;
		int start = findFirstEdge(citynumber);
		int stop;
		string src = cities[citynumber].getName();
		string end;
		int city_index;

		if (src.compare("VICHY") == 0)  // check condition on the last city of our graph
		{
			stop = E;
		}
		else
		{
			stop = start + 71;
		}

		for (int i = start; i < stop; ++i) {

			end = edges[i].getEnd().getValue().getName();
			city_index = searchCity(end);

			if (edges[i].getStart().getValue().getName().compare(src) != 0) {
				break;
			}
			if (mstSet[city_index] == false && edges[i].getWeight() < min)
			{
				min = edges[i].getWeight();
				min_index = i;
			}
		}
		if (min_index == -1)
		{
			return -1;
		}
		end = edges[min_index].getEnd().getValue().getName();

		return city_index = searchCity(end);
	}

	int maxWeight(int citynumber,bool mstSet[]) // output: city index with MAX weight and not in set
	{

		double max = 0;
		int max_index=-1;
		int start = findFirstEdge(citynumber);
		int stop;
		string src = cities[citynumber].getName();
		string end;
		int city_index;

		if (src.compare("VICHY") == 0) // check condition on the last city of our graph
		{
			stop = E;
		}
		else
		{
			stop = start + 71;
		}

		for (int i = start; i < stop; ++i) {
			
			end = edges[i].getEnd().getValue().getName();
			city_index = searchCity(end);
			
			if (edges[i].getStart().getValue().getName().compare(src) != 0) {
				break;
			}
			if (mstSet[city_index] == false && edges[i].getWeight() > max)
			{
				max = edges[i].getWeight();
				max_index = i;
			}
		}
		if (max_index==-1)
		{
			return -1;
		}
		end = edges[max_index].getEnd().getValue().getName();
		
		return city_index = searchCity(end);
	}

	double pathlength(vector<City> path) // method to calc the length of a given path
	{
		double length = 0;
		for (int i = 0; i < (int)path.size() - 1; ++i) {
			length = length + calcDist(path[i], path[i + 1]);
		}
		return length;
	}

	vector<edge> MST() // PRIM'S ALGORITHM
	{
		vector<edge> tmpMST;			// MST
		vector<string> inserted;		// vector that stores all already inserted node in the MST
		vector<edge> sorted = edges;	// make a copy of our edges vector to sort it

		sort(sorted.begin(), sorted.end(), sortWeight()); // sort the vector using a custom function

		tmpMST.push_back(edges[3238]);										// paris-saint georges
		inserted.push_back(edges[3238].getStart().getValue().getName());	// paris
		inserted.push_back(edges[3238].getEnd().getValue().getName());		// saint georges

		// build MST, stop condition: vector size must be V-1
		while (tmpMST.size()<70)
		{
			// iterate down the sorted vector
			for (int i = 0; i < E; ++i) {
				string startString = sorted[i].getStart().getValue().getName();		// save the name of the edge start node
				string endString= sorted[i].getEnd().getValue().getName();			// save the name of the edge end node

				// initialize two flag value
				int flag_1=0;
				int flag_2=0;

				// look into the already inserted node
				for (int j = 0; j <inserted.size(); ++j)
				{
					if (startString.compare(inserted[j]) == 0)
					{
						flag_1 = 1; // node found in the vector
					}
				}
				if (flag_1 == 1) // the head of current edge is in the inserted list, keep it!
				{
					for (int j = 0; j <inserted.size(); ++j)
					{
						if (endString.compare(inserted[j]) == 0)
						{
							flag_2 = 1; // node found in the vector
						}
					}
					if (flag_2 == 0) // if we do not find the current edge end in the inserted list, keep it and add to MST!
					{
						tmpMST.push_back(sorted[i]); // add current edge to MST
						inserted.push_back(sorted[i].getEnd().getValue().getName()); // add tail to inserted list
						break;
					}
				}
				
			}
		}

		double d = 0;

		// compute total distance of MST
		for (int i = 0; i < tmpMST.size(); ++i) {
			d = d + tmpMST[i].getWeight();
		}

		cout << "MST length: " << d << endl;

		return tmpMST;
	}

	vector<City> localSearchPath() // we use a greedy algorithm
	{
		vector<City> tmpPath;
		bool *pathSet=new bool[V];
		int u = -10; // -10 is never reached by u

		// Initialize all bool to false
		for (int i = 0; i < V; i++) {
			pathSet[i] = false;
		}

		// Always include first 1st node in set.
		tmpPath.push_back(cities[47]); // Paris node is always root
		pathSet[47] = true;

		unsigned seed = chrono::system_clock::now().time_since_epoch().count();

		mt19937 generator(seed);  // mersenne twister (uniform random number) 

		int random= (generator() % (65 - 5 + 1)) + 5; // first index to swap
						 
		// The path will have V vertices
		for (int count = 0; count < V - 1; count++)
		{
			if (count == random) //needed to have a round path with edge distance always greater than 100km
			{
				pathSet[43] = true;
				tmpPath.push_back(cities[43]);
			}
			else
			{
				int city_index = searchCity(tmpPath.back().getName());

				// Pick the maximum edge
				// not yet included in path
				u = maxWeight(city_index, pathSet);

				if (u == -1) { break; }

				// Add the picked node to the path
				pathSet[u] = true;
				tmpPath.push_back(cities[u]);
			}
		}

		if (u == -1)
		{
			int counter = 0;
			while(pathSet[counter]==true)
				{
					counter++;
				}
			tmpPath.push_back(cities[counter]);
		}
		
		tmpPath.push_back(cities[47]); // Last node is always Paris

		double d = pathlength(tmpPath);
		if (d < 0) { tmpPath = localSearchPath(); }

		return tmpPath;
	}

	vector < City> two_opt(int iteration) // 2 opt swap
	{
		vector<City> temp = localSearchPath(); // we choose to start from the same path from Local Search (greedy)
		double d = pathlength(temp);
		double ref_d = pathlength(temp);
		double temp_d;
		City temp_city;

		// obtain a seed from the system clock
		unsigned seed = chrono::system_clock::now().time_since_epoch().count();

		mt19937 generator(seed);  // mersenne twister (uniform random number) 

		for (int i=0; i<iteration; ++i)
		{
			int randomNumber_one = (generator() % (70 - 1 + 1)) + 1; // first index to swap
			int randomNumber_two = (generator() % (70 - 1 + 1)) + 1; // second index to swap

			// swap them
			temp_city = temp[randomNumber_one];
			temp[randomNumber_one] = temp[randomNumber_two];
			temp[randomNumber_two] = temp_city;

			// calculate distance
			temp_d = pathlength(temp);

			/*if greater than before keep the swap and go on.
			if smaller revert the swap and keep going.*/
			if (temp_d > d) { 
				d = temp_d;
			}
			else
			{
				temp_city = temp[randomNumber_one];
				temp[randomNumber_one] = temp[randomNumber_two];
				temp[randomNumber_two] = temp_city;
			}
		}
		cout << "First Path length: " << ref_d << " Km" << endl;
		cout << "2opt length (1000 iteration): " << d <<" Km"<< endl;
		cout << "Improvement over first path: " << (d - ref_d) * 100 / ref_d << "%" << endl;
		return temp;
	}

	// Compute the factorial, we use it in the permutation method
	int fact(int n)
	{
		return (n == 1) ? 1 : n*fact(n - 1);  // recursive function
	}
	// Compute permutations
	vector<vector<int>> printPermutation(vector<int> s)
	{
		int n = (s.size());
		int fc = fact(n);
		vector<vector<int>> permutation; // we store here all the permutations
		int j = 1;
		int m = 0;
		for (int perm_c = 0; perm_c < fc; perm_c++)
		{
			vector<int> perm = s;
			int k = 0;
			while (k != fc / n)
			{
				while (j != n - 1)
				{
					vector<int> temp = perm;
					/*Here we want to add Paris, which is identified by the number 47, to 
					the vector of integers.	Due to fact that we want to start from Paris 
					and then come back to Paris, we add it in the beginning and in the
					end of the vector*/
					int paris_index = 47;
					temp.push_back(paris_index);
					swap(temp[0], temp[n]);
					temp.push_back(paris_index);
					permutation.push_back(temp);
					swap(perm[j], perm[j + 1]);
					k++;
					j++;
				}
				j = 1;
			}
			m++;
			if (m == n)
				break;
			swap(s[0], s[m]);
		}
		//the output of the method is a vector, where its arguments are vectors containing all the possible paths you can take
		return permutation;
	}
	//This method computes the max_distance, taking in a count all the distances between 
	void max_distance(vector<vector<int>> permutation)
	{
		//Define a vector of Nodes
		vector<Node> temp_vec;
		int tmp = 0;
		//Access to Paris, it will be used later
		Node paris = Node(cities[47]);
		//Two four cycles to compute the distance
		for (int i = 0; i < permutation.size(); i++)
		{
			vector<Node> save_vec;
			Node save_cit = Node();
			double distance = 0;
			double d;
			for (int a = 0; a < permutation[i].size() - 1; a++)
			{
				int value1 = permutation[i][a];
				int value2 = permutation[i][a + 1];
				double d = calcDist(cities[value1], cities[value2]);
				distance = distance + d;
				Node temp1 = Node(cities[value1]);
				save_vec.push_back(temp1);
			}
			//The distance is saved in a temp variable, it will be updated if the conditon is satisfied
			if (distance > tmp)
			{
				temp_vec = save_vec;
				tmp = distance;
			}
		}
		//Print the results
		cout << "The random choosen visited cities are:" << endl;
		for (int i = 0; i < temp_vec.size(); ++i)
		{
			cout << temp_vec[i].getValue().getName() << endl;
		}
		cout << "and come back to " << paris.getValue().getName() << endl;
		cout << "The length of the maximum path passing through each city is:" << endl << tmp << " Km" << endl;
	}

	// Brute force algorithm
	void brute_force()
	{	// obtain a seed from the system clock:
		unsigned seed = chrono::system_clock::now().time_since_epoch().count();

		mt19937 generator(seed); // mersenne twister (uniform random number) 

		/* Here we want to choose randomly the four cities 
		which we have to pass through then, the number will 
		be associated to a specific city picked up from a
		vector of cities*/
		int rand1 = (generator() % (70 - 1 + 1)) + 1;
		int rand2 = (generator() % (70 - 1 + 1)) + 1;
		int rand3 = (generator() % (70 - 1 + 1)) + 1;
		int rand4 = (generator() % (70 - 1 + 1)) + 1;

		// Avoid the case which you pass more than one time to Paris (Paris will be the first and the last)
		while (rand1 == 47 || rand2 == 47 || rand3 == 47 || rand4 == 47)
		{
			 rand1 = (generator() % (70 - 1 + 1)) + 1;
			 rand2 = (generator() % (70 - 1 + 1)) + 1;
			 rand3 = (generator() % (70 - 1 + 1)) + 1;
			 rand4 = (generator() % (70 - 1 + 1)) + 1;
		}

		vector<int> random = { rand1, rand2, rand3, rand4 };
		//Method that compute permutations of the random vector
		vector<vector<int>> vector_rand = printPermutation(random);
		//Method that compute the maximum distance
		max_distance(vector_rand);
	}
};

