#include <iostream>
#include <list>

#pragma warning(disable: 4996)

using namespace std;

bool walk( list<pair<int, int>> l, int v, int * table, int s )
{
	switch (table[v])
	{
	case 0:
		table[v] = s;
		for (list<pair<int, int>>::iterator it = l.begin(); it != l.end(); it++)
		{
			if (it->first == v)
				if (!walk(l, it->second, table, 3 - s))
					return false;
			if (it->second == v)
				if (!walk(l, it->first, table, 3 - s))
					return false;
		}
		break;
	case 1:
		if (s == 1)
			return true;
		return false;
	case 2:
		if (s == 2)
			return true;
		return false;
	}
	return true;
}

void main()
{
	int n, m;

	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);

	cin >> n >> m;

	list<pair<int, int>> l;
	int x, y;

	for (int i = 0; i < m; i++)
	{
		cin >> x >> y;
		x--;
		y--;
		l.push_back(pair<int, int>(x, y));
	}

	int * table = new int[n];
	memset(table, 0, n * sizeof(int));

	for (int i = 0; i < n; i++)
		if (!table[i])
			if (!walk(l, i, table, 1))
			{
				cout << "NO";
				delete [] table;
				return;
			}

	cout << "YES" << endl;
	for (int i = 0; i < n; i++)
		if (table[i] == 1)
			cout << i + 1 << ' ';

	delete [] table;
}	