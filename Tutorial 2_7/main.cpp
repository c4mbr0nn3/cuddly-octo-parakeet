#include <iostream>		
#include <random>		// random
#include <time.h>       /* time */
#include <cmath>		// math

using namespace std;

void quickSort(pair<double, double> arr[], int left, int right) {
	int i = left, j = right;
	double tmp;
	double pivot = arr[(left + right) / 2].first;

	while (i <= j) {
		while (arr[i].first < pivot)
			i++;
		while (arr[j].first > pivot)
			j--;
		if (i <= j) {
			tmp = arr[i].first;
			arr[i].first = arr[j].first;
			arr[j].first = tmp;
			i++;
			j--;
		}
	};

	if (left < j)
		quickSort(arr, left, j);
	if (i < right)
		quickSort(arr, i, right);
}

double randNumber(double max)
{
	return (((double)rand()*(max) / (double)RAND_MAX) - max) *(-1);
}

double dist(pair<double, double> p1, pair<double, double> p2)
{
	return sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2));
}

pair<int,int> findMinDist(pair<double, double> array[], int low, int high)
{
	double minDist = numeric_limits<double>::infinity();
	double tempDist;
	pair<int,int> pointIndex;
	for (int i = 0; i < high-1; ++i)
	{
		for (int j = i+1; j < high; ++j)
		{
			tempDist = dist(array[i], array[j]);
			cout << tempDist << endl;
			if (tempDist < minDist)
			{
				minDist = tempDist;
				pointIndex.first = i;
				pointIndex.second = j;
			}
		}
	}
	return pointIndex;
}

pair <int, int> findMinDistDC(pair<double, double> array[],int low, int max)
{
	if (max - low == 2)
	{
		return findMinDist(array, low, max);
	}

	int mid = low + max/ 2;
	pair<double, double> midPoint = array[mid];

	pair <int, int> left = findMinDistDC(array, low, mid);
	pair <int, int> right= findMinDistDC(array, mid + 1, max);

	double dL = dist(array[left.first], array[left.second]);
	double dR = dist(array[right.first], array[right.second]);
	double d;

	if (dL < dR)
	{
		d = dL;
	}
	else
	{
		d = dR;
	}
	pair<double, double> *strip = new pair<double, double>[max - low];
	int j = 0;
	for (int i = 0; i < max - low; ++i)
	{
		if (abs(array[i].first - midPoint.first) < d)
		{
			strip[j] = array[i];
			++j;
		}
	}
	return 
}

void main()
{
	srand(time(NULL));

	int k = 10;
	double max = 50;
	pair<double, double> *points = new pair<double, double>[k];



	for (int i = 0; i < k; ++i)
	{
		points[i].first = randNumber(max);
		points[i].second = randNumber(max);
		//cout << "X_" << i << "\t" << points[i].first << endl;
		//cout << "Y_" << i << "\t" << points[i].second << endl;
	}

	double dist1 = dist(points[2], points[7]);

	cout << "X, Y: " << points[2].first << ", " << points[2].second << endl;
	cout << "X, Y: " << points[7].first << ", " << points[7].second << endl;
	cout << "distance: " << dist1 << endl;

	pair<int, int> mindist = findMinDist(points, k, max);

	quickSort(points, 0, k - 1);


	cout << "Nearest point: " << endl;
	cout << "X1 = " << points[mindist.first].first << " Y1 = " << points[mindist.first].second << endl;
	cout << "X2 = " << points[mindist.second].first << " Y2 = " << points[mindist.second].second << endl;
	cout << dist(points[mindist.first], points[mindist.second]) << endl;

	system("pause");
}