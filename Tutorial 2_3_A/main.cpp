#include <iostream>

// soluzione by ale dio porco

using namespace std;

int power3(int base, int power)
{
	if (power == 0)
	{
		return 1;
	}
	if (power % 2 == 0)
	{
		return (power3(base * base, (power / 2)));
	}
	//
	else
	{
		return base * (power3(base * base, (power / 2)));
	}
}

int main()
{
	cout << power3(2, 21) << endl;

	system("pause");
}