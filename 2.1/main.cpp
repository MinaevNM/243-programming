#include <iostream>
#include <queue>
#include <list>

#pragma warning(disable: 4996)

using namespace std;

class vertex
{
public:
	int x, y;
	int xp, yp;
	int length;

	vertex( int _x, int _y, int _length, int _xp, int _yp ) : 
		x(_x), y(_y), length(_length), xp(_xp), yp(_yp)
	{		
	}
};

void main()
{
	int n, x1, x2, y1, y2;

	int m[100][100][2];
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++)
			m[i][j][0] = m[i][j][1] = 0;


	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);

	cin >> n >> x1 >> y1 >> x2 >> y2;

	queue<vertex> q;

	q.push(vertex(x1, y1,0, 0, 0));

	vertex final(0, 0, 0, 0, 0);

	while (true)
	{
		vertex v = q.front();
		q.pop();

		int x = v.x;
		int y = v.y; 

		if (m[x][y][0])
			continue;
		m[x][y][0] = v.xp;
		m[x][y][1] = v.yp;

		if (x == x2 && y == y2)
		{
			final = v;
			break;
		}

		if (x + 2 <= n && y + 1 <= n)
			q.push(vertex(x + 2, y + 1, v.length + 1, x, y));
		if (x + 2 <= n && y - 1 > 0)
			q.push(vertex(x + 2, y - 1, v.length + 1, x, y));
		if (x - 2 > 0 && y + 1 <= n)
			q.push(vertex(x - 2, y + 1, v.length + 1, x, y));
		if (x - 2 > 0 && y - 1 > 0)
			q.push(vertex(x - 2, y - 1, v.length + 1, x, y));
		if (x + 1 <= n && y + 2 <= n)
			q.push(vertex(x + 1, y + 2, v.length + 1, x, y));
		if (x + 1 <= n && y - 2 > 0)
			q.push(vertex(x + 1, y - 2, v.length + 1, x, y));
		if (x - 1 > 0 && y + 2 <= n)
			q.push(vertex(x - 1, y + 2, v.length + 1, x, y));
		if (x - 1 > 0 && y - 2 > 0)
			q.push(vertex(x - 1, y - 2, v.length + 1, x, y));
	}

	cout << final.length << endl;

	int x = x2;
	int y = y2;

	list<pair<int, int>> path;

	while (x != x1 || y != y1)
	{
		path.push_front(pair<int, int>(x, y));
		int xt = m[x][y][0];
		y = m[x][y][1];
		x = xt;
	}
	path.push_front(pair<int, int>(x, y));

	for (list<pair<int, int>>::iterator it = path.begin(); it != path.end(); it++)
		cout << it->first << ' ' << it->second << endl;
}