#pragma once
void multiplyTwoStr(char* &num, int numSize)
{
	bool addOneToDec = false;
	for (int i = numSize - 1; i >= 0; i--)
	{
		byte res = (num[i] - '0') + (num[i] - '0');
		if (addOneToDec)
		{
			res++;
			addOneToDec = false;
		}
		if (res >= 10)
		{
			addOneToDec = true;
			res -= 10;
		}
		num[i] = res + '0';
	}
	return;
}
void incStr(char* &num, int numSize)
{
	if (num[numSize - 1] != '9')
	{
		num[numSize - 1]++;
	}
	else {
		int presentScan = numSize - 1;
		while (num[presentScan] == '9')
		{
			num[presentScan] = '0';
			presentScan--;
		}
		num[presentScan]++;
	}
	return;
}