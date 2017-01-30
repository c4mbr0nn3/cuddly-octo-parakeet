#include <iostream>
using namespace std;

void printNumbers(int n)
{
	if (n != 0)
	{
		cout << n << endl;
		printNumbers(n - 1);
	}

}

void main()
{
	int n = 19;
	printNumbers(n);

	system("pause");
}