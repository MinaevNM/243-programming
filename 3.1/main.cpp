#include <iostream>

#pragma warning(disable: 4996)

using namespace std;

void addShiftsForChar( char c, char * str1n, char * str2n, int n, int * shift )
{
	char * str1 = new char[n];
	char * str2 = new char[n];

	for (int i = 0; i < n; i++)
	{
		if (str1n[i] == c)
			str1[i] = 1;
		else
			str1[i] = 0;
		if (str2n[i] == c)
			str2[i] = 1;
		else
			str2[i] = 0;
	}


	for (int i = 0; i < n / 2; i++)
		swap(str2[i], str2[n - i - 1]);

	char * str3 = new char[2 * n - 1];

	memset(str3, 0, (2 * n - 1) * sizeof(char));
	
	for (int i = 0; i < n; i++)
		if (str2[n - i - 1] == 1)
			for (int j = 0; j < n; j++)
				str3[2 * n - 2 - (i + j)] += str1[n - j - 1];

	shift[0] += (int)str3[n - 1];
	
	for (int i = 0; i < n - 1; i++)
		shift[i + 1] += ((int)str3[i] + (int)str3[i + n]);
		
	delete [] str1;
	delete [] str2;
	delete [] str3;
}

void main()
{
	int n;
	char * str1n;
	char * str2n;

	//freopen("input.txt", "rt", stdin);
	//freopen("output.txt", "wt", stdout);
	
	cin >> n;

	str1n = new char[n + 1];
	str2n = new char[n + 1];

	cin >> str1n;
	cin >> str2n;

	int * shift = new int[n];
	memset(shift, 0, n * sizeof(int));

	addShiftsForChar('A', str1n, str2n, n, shift);
	addShiftsForChar('C', str1n, str2n, n, shift);
	addShiftsForChar('G', str1n, str2n, n, shift);
	addShiftsForChar('T', str1n, str2n, n, shift);

	int max = 0;

	for (int i = 1; i < n; i++)
		if (shift[i] > shift[max])
			max =  i;

	cout << shift[max] << ' ' << max << endl;

	delete [] shift;
	delete [] str1n;
	delete [] str2n;
}
