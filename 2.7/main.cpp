#include <iostream>
#include "graph.h"

using namespace std;

void main()
{
	KuhnGraph kg("input4.txt");

	list<pair<int, int>> l = kg.Kuhn();
	
	freopen("output.txt", "wt", stdout);
	cout << l.size() << endl; 
	for (list<pair<int, int>>::iterator it = l.begin(); it != l.end(); it++)
		cout << it->first << ' ' << it->second << endl;
}
