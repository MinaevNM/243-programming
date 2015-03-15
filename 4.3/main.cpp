#include <iostream>
#include <string>
#include <stack>

#include "FS_Machine.h"

using namespace std;

#pragma warning(disable: 4996)

void sorting_station( string str )
{
	int length = str.size();
	char * regexp = new char[length + 1];
	strcpy(regexp, str.c_str());
	int i = 0;
	stack<char> s;

	while (regexp[i])
	{
		if ((regexp[i] <= 'z' && regexp[i] >= 'a') || (regexp[i] <= 'Z' && regexp[i] >= 'A') || (regexp[i] >= '0' && regexp[i] <= '9') || regexp[i] == '@')
			cout << regexp[i];
		else if (regexp[i] == '(')
			s.push(regexp[i]);
		else if (regexp[i] == ')')
		{
			while (s.top() != '(')
			{
				cout << s.top();
				s.pop();
			}
			s.pop();
		}
		i++;
	}

	cout << endl;
}

void main()
{
	int n;
	string regexp;
	string s;

	FS_Machine f1('a');
	FS_Machine f2('b');
	FS_Machine f3('c');
	FS_Machine f4('p');
	FS_Machine f5('q');
	FS_Machine f6;
	FS_Machine f;
	f = FS_Machine::Operation(f1, f2, '|');
	f = FS_Machine::Kleene(f);
	f = FS_Machine::Operation(f, f3, '&');
	f6 = FS_Machine::Operation(f4, f5, '&');
	f = FS_Machine::Operation(f, f6, '|');

	freopen("input.cpp", "rt", stdin);
	freopen("output.txt", "wt", stdout);

	f.print();

	cin >> regexp;

	sorting_station(regexp);

	FS_Machine * fsm = new FS_Machine(regexp);

	cin >> n;

	for (int i = 0; i < n; i++)
	{
		cin >> s;
		cout << (fsm->check_string(s) ? "Yes" : "No") << endl;
	}

	delete fsm;
}
