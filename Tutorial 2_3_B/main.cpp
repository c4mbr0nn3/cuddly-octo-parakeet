#include <iostream>

using namespace std;

int power3(int base, int power)
{
	if (power == 0)
	{
		return 1;
	}
	else if (power==1)
	{
		return base;
	}
	else
	{
		return base*power3(base, power - 1);
	}
}

int main()
{
	cout << power3(2, 20) << endl;
	system("pause");
}