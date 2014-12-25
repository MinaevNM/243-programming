#include <iostream>
#include <cmath>

#pragma warning(disable: 4996)

using namespace std;

struct point
{
	double x, y;
};

double length( point p1, point p2 )
{
		return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

void main()
{
	int n;

	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);

	cin >> n;

	point * p = new point[n];
	double ** d = new double * [n];

	for (int i = 0; i < n; i++)
		d[i] = new double[n];

	for (int i = 0; i < n; i++)
		cin >> p[i].x >> p[i].y;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			d[i][j] = 0;

	for (int i = 2; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			double min = 1e10;

			for (int k = j + 1; k < i + j; k++)
			{
				double len1, len2;

				len1 = length(p[j], p[k % n]);
				len2 = length(p[k % n], p[(i + j) % n]);

				if (k % n <= j + 1)
					len1 = 0;
				if ((i + j) % n <= k % n + 1)
					len2 = 0;
				
				if (min > d[j][k % n] + d[k % n][(i + j) % n] + len1 + len2)
					min = d[j][k % n] + d[k % n][(i + j) % n] + len1 + len2;
			}

			d[j][(i + j) % n] = min;
		}

	cout << d[0][n - 1] << endl;

	for (int i = 0; i < n; i++)
		delete [] d[i];

	delete [] d;
	delete [] p;
}
