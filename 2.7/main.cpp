#include <iostream>

#pragma warning (disable: 4996) 

using namespace std;

bool walk( bool * was, int v, int * pair, int m, int ** a )
{
	if (was[v])
		return false;
	was[v] = true;
	for (int i = 0; i < m; i++)
	{
		if (!a[v][i])
			continue;
		if (pair[i] == -1 || walk(was, pair[i], pair, m, a))
		{
			pair[i] = v;
			return true;
		}
	}

	return false;
}

void main()
{
	int n, m;
	int ** a;

	freopen("input5.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);

	cin >> n >> m;

	a = new int * [n];

	for (int i = 0; i < n; i++)
		a[i] = new int[m];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> a[i][j];

	bool * was;
	int * pair;

	was = new bool[n];
	pair = new int[m];

	for (int i = 0; i < m; i++)
		pair[i] = -1;

	for (int i = 0; i < n; i++)
	{
			memset(was, false, n * sizeof(bool));
			walk(was, i, pair, m, a);
	}

	int count = 0;
	for (int i = 0; i < m; i++)
		if (pair[i] != -1)
			count++;
	cout << count << endl;
	for (int i = 0; i < m; i++)
		if (pair[i] != -1)
			cout << (pair[i] + 1) << ' ' << (i + 1) << endl;

	for (int i = 0; i < n; i++)
		delete [] a[i];
	delete [] a;
	delete [] was;
	delete [] pair;
}
