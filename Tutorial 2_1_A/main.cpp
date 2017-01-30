#include <iostream>

using namespace std;

int gcd(int a, int n)
{
	int temp;
	if (a < n)
	{
		temp = gcd(n, a);
	}
	else
	{
		temp = a%n;
		if (temp == 0)
		{
			return n;
		}
		else
		{
			temp = gcd(n, temp);
		}
	}
}

int iterativegcd(int a, int n)
{
	int temp;
	if (a<n)
	{
		temp = n%a;
	}
	else
	{
		temp = a%n;
	}
	while (temp!=0)
	{
		int tempN = temp;
		temp = n%temp;
		n = tempN;
	}
	return n;
}

void main()
{
	int number;
	int nummmmero;

	cin >> number;
	cin >> nummmmero;

	int gidiemme=gcd(number, nummmmero);
	int gidimerda = iterativegcd(number, nummmmero);

	cout << "recursive GCD: \t" << gidiemme << endl;
	cout << "iterative GCD: \t" << gidimerda << endl;

	system("pause");
}