#include <iostream>
using namespace std;
#include "uintn.hpp"

int main(void)
{
	uintN a(0u, 3);
	int b = 5;
	a.num[0] = 30;
	a.num[1] = 0;
	a.num[2] = 0;
	a.num[3] = 0;
	a.num[4] = 0;
	a.showBytes(); cout << endl;
	cout << b << endl;
	uintN c = a - 5;
	c.showBytes(); cout << endl;

	cout << a.ToString() << " - " << b << " = " << c.ToString();

	char* origStr;
	char* binStr;
	for (int i = 0; i < 10000; i++)
	{
		origStr = a.ToString();
		binStr = a.sToBinString('.');
		system("cls");
		cout << origStr << " - " << binStr << endl;
		if (a.num[0] == UBYTE_MAX && a.num[1] == 1)
			a.num[0] = a.num[0] + (1 - 1);
		a++;
	}

	getchar();
	return 0;
}