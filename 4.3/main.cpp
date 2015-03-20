#include <iostream>
#include <string>
#include <stack>
#include <queue>

#include "FS_Machine.h"

using namespace std;

#pragma warning(disable: 4996)

bool in_alphabet( char c )
{
	if ((c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A') || (c <= '9' && c >= '0'))
		return true;
	return false;
}

void sorting_station( string str )
{
	int length = str.size();
	char * regexp = new char[length + 1];
	strcpy(regexp, str.c_str());
	int i = 0;
	stack<char> s;
	queue<char> q;
	stack<FS_Machine> f;
	FS_Machine f1, f2;
	s.push(0);

	cout << "SORTING STATION START" << endl;

	while (regexp[i])
	{
		switch (regexp[i])
		{
		case '(':
			s.push(regexp[i]);
			break;
		case ')':
			while (s.top() != '(')
			{
				q.push(s.top());
				if (s.top() == '|' || s.top() == '&')
				{
					f1 = f.top();
					f.pop();
					f2 = f.top();
					f.pop();
					f.push(FS_Machine::Operation(f2, f1, s.top()));
				}

				s.pop();
			}
			s.pop();
			break;
		case '*':
			f1 = f.top();
			f.pop();
			f1 = FS_Machine::Kleene(f1);
			f.push(f1);
			break;
		case '&':
			if (s.top() == '&')
			{
				q.push(s.top());
				s.pop();
				f1 = f.top();
				f.pop();
				f2 = f.top();
				f.pop();
				f.push(FS_Machine::Operation(f2, f1, s.top()));
			}
			s.push('&');
			break;
		case '|':
			if (s.top() == '&' || s.top() == '|')
			{
				q.push(s.top());
				f1 = f.top();
				f.pop();
				f2 = f.top();
				f.pop();
				f.push(FS_Machine::Operation(f2, f1, s.top()));
				s.pop();
			}
			s.push('|');
			break;
		default:
			q.push(regexp[i]);
			f.push(FS_Machine(regexp[i]));
			break;
		}

		i++;
	}

	while (s.top())
	{
		f1 = f.top();
		f.pop();
		f2 = f.top();
		f.pop();
		f.push(FS_Machine::Operation(f2, f1, s.top()));
		s.pop();
	}

	while (!f.empty())
	{
		f.top().print_list();
		f.pop();
		cout << endl << "---------------" << endl;
	}

	cout << "SORTING STATION FINISH" << endl;
}

void add_ampersand( string & s )
{
	for (int i = 0; i < s.size() - 1; i++)
		if ((in_alphabet(s[i]) && in_alphabet(s[i + 1])) || (in_alphabet(s[i]) && s[i + 1] == '(') || (s[i] == ')' && in_alphabet(s[i + 1])) || (s[i] == '*' && (in_alphabet(s[i + 1]) || s[i + 1] == '(')))
		{
			s.insert(i + 1, "&");
			i++;
		}
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

	f.print_matrix();

	cin >> regexp;

	add_ampersand(regexp);

	cout << regexp << endl;

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
