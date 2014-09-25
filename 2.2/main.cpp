#include <iostream>
#include <list>

#pragma warning(disable: 4996)

using namespace std;

void walk( double ** m, int n, int v, int end, double length, 
		   double * dist, list<int> & path, list<int> & best_path )
{
	if (dist[v] == -1 || dist[v] > length)
	{
		dist[v] = length;
		path.push_back(v);
		if (v == end)
		{
			best_path.clear();
			for (list<int>::iterator it = path.begin(); it != path.end(); it++)
				best_path.push_back(*it);
		}

		for (int i = 0; i < n; i++)
			if (i != v && m[v][i] >= 0)
				walk(m, n, i, end, length + m[v][i], dist, path, best_path);
	}
}

void main()
{
	int n, s, f;
	list<int> path;
	list<int> best_path;

	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);

	cin >> n >> s >> f;

	s--;
	f--;

	double ** m = new double *[n];
	double * dist = new double [n];
	
	for (int i = 0; i < n; i++)
		dist[i] = -1;

	for (int i = 0; i < n; i++)
		m[i] = new double[n];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> m[i][j];

	walk(m, n, s, f, 0, dist, path, best_path);
	cout << dist[f] << endl;
	for (list<int>::iterator it = best_path.begin(); it != best_path.end(); it++)
		cout << (*it + 1) << ' ';

	delete [] dist;
	for (int i = 0; i < n; i++)
		delete [] m[i];
	delete [] m;
}