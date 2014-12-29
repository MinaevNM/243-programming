#include <iostream>
#include <list>

using namespace std;

bool edges_compare( const pair<pair<int, int>, int> & p1, const pair<pair<int, int>, int> & p2 )
{
	return (p1.second < p2.second);
}

void main()
{
	int n, m;
	int length = 0;
	
	// edge (v1, v2, c)
	list<pair<pair<int, int>, int>> edges;

	freopen("input.txt", "rt", stdin);                                                                   
	freopen("output.txt", "wt", stdout);

	cin >> n >> m;
	
	for (int i = 0; i < m; i++)
	{
		int v1, v2, c;

		cin >> v1 >> v2 >> c;

		v1--;
		v2--;

		edges.push_back(pair<pair<int, int>, int>(pair<int, int>(v1, v2), c));
	}

	edges.sort(edges_compare);

	int * vertices = new int[n];

	for (int i = 0; i < n; i++)
		vertices[i] = i;

	while (!edges.empty())
	{
		int v1 = edges.front().first.first;
		int v2 = edges.front().first.second;

		if (vertices[v1] != vertices[v2])
		{
			length += edges.front().second;
			
			int tree1 = vertices[v1];
			int tree2 = vertices[v2];

			for (int i = 0; i < n; i++)
				if (vertices[i] == tree2)
					vertices[i] = tree1;
		}
		
		edges.pop_front();
	}

	cout << length;

	delete [] vertices;
} 
