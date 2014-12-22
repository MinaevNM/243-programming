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

double per( point p1, point p2, point p3 )
{
	return length(p1, p2) + length(p2, p3) + length(p3, p1);
}

void main()
{
	int n;

	freopen("input.txt", "rt", stdin);
	//freopen("output.txt", "wt", stdout);

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

	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			d[i][j] = -1e10;

	for (int i = 0; i < n; i++)
		d[i][(i + 1) % n] = length(p[i], p[(i + 1) % n]);
		
	for (int i = 2; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			double min = 1e10;

			for (int k = j; k < i + j; k++)
				if (min < d[j][k] + d[k + 1][(i + j) % n] + per(p[(j - 1 + n) % n], p[k], p[(i + j + n) % n]))
					min = d[j][k] + d[k + 1][(i + j) % n] + per(p[(j - 1 + n) % n], p[k], p[(i + j + n) % n]);

			d[j][(i + j) % n] =  min;
		}
	/*
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
		{
			double min = 1e10;

			for (int k = i; k < j; k++)
				if (min > d[i][k] + d[k + 1][j] + per(p[(i - 1 + n) % n], p[k], p[j]))
					min = d[i][k] + d[k + 1][j] + per(p[(i - 1 + n) % n], p[k], p[j]);

			d[i][j] = min;
		}
		*/
	printf("%lf", d[0][n - 1]);

	for (int i = 0; i < n; i++)
		delete [] d[i];

	delete [] d;
	delete [] p;
}
