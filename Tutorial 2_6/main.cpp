#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))
using namespace std;

void quickSort(int arr[], int left, int right) {
	int i = left, j = right;
	int tmp;
	int pivot = arr[(left + right) / 2];

	while (i <= j) {
		while (arr[i] < pivot)
			i++;
		while (arr[j] > pivot)
			j--;
		if (i <= j) {
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i++;
			j--;
		}
	};

	if (left < j)
		quickSort(arr, left, j);
	if (i < right)
		quickSort(arr, i, right);
}

void duplicate(int arr[], int size)
{
	static int arrSize = size;
	quickSort(arr, 0, arrSize-1);

	// print sorted array
	for (int i = 0; i < arrSize; ++i)
	{
		cout << arr[i] << endl;
	}

	int *tempArr = new int[arrSize];
	int j = 0;
	for (int i = 0; i < arrSize; ++i)
	{
		if (arr[i] != arr[i + 1])
		{
			tempArr[j] = arr[i];
			arr[j] = tempArr[j];
			++j;
		}
	}
	for (int i = j; i < arrSize; ++i)
	{
		arr[i] = 0;
	}

	delete[] tempArr;
}

void main()
{
	int random_numbers[10];
	srand((unsigned)time(NULL));
	for (int i = 0; i < 10; i++) {
		random_numbers[i] = rand() % 12;
		cout << random_numbers[i] << endl;
	}
	cout << endl;

	const int size= ARRAY_SIZE(random_numbers);

	duplicate(random_numbers, size);

	cout << endl;

	for (int i = 0; i < size; ++i)
	{
		cout << random_numbers[i] << endl;
	}

	system("pause");
}
