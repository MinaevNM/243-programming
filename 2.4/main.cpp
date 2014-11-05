#include <iostream>
#include <list>

#pragma warning(disable: 4996)

using namespace std;

int minf( int a, int b )
{
	if (a < b)
		return a;
	return b;
}

list<pair<int, int>> edges;

void walk( int v, int prev, bool * was, int * dist, int * min, int ** a, int * m, int length )
{
	was[v] = true;
	dist[v] = min[v] = length;

	for (int i = 0; i < m[v]; i++)
		if (a[v][i] != prev)
		{
			if (was[a[v][i]])
				min[v] = minf(min[v], dist[a[v][i]]);
			else
			{
				walk(a[v][i], v, was, dist, min, a, m, length + 1);
				min[v] = minf(min[v], min[a[v][i]]);
				if (min[a[v][i]] > dist[v])
				{
					bool flag = true;
					for (int j = 0; j < m[v]; j++)
						if (a[v][j] == a[v][i] && j != i)
							flag = false;

					if (flag)
						edges.push_back(pair<int, int>(v, a[v][i]));	
				}
			}
		}
}

int main()
{
	int n;
	int * m;
	int ** a;

	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);

	cin >> n;
	m = new int[n];

	a = new int * [n];

	for (int i = 0; i < n; i++)
	{
		cin >> m[i];
		a[i] = new int[m[i]];
		for (int j = 0; j < m[i]; j++)
			cin >> a[i][j];
	}

	bool * was = new bool[n];
	int * dist = new int[n];
	int * min = new int[n];

	memset(was, false, n * sizeof(bool));
	memset(dist, 0, n * sizeof(int));
	memset(min, 0, n * sizeof(int));

	for (int i = 0; i < n; i++)
		if (!was[i])
			walk(i, -1, was, dist, min, a, m, 0);

	cout << edges.size() << endl;
	for (list<pair<int, int>>::iterator it = edges.begin(); it != edges.end(); it++)
		cout << it->first << ' ' << it->second << endl;

	for (int i = 0; i < n; i++)
		delete [] a[i];
	delete [] a;
	delete [] m;
	delete [] was;
	delete [] dist;
	delete [] min;
}
