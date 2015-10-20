#include <queue>
#include <stack>
#include "FS_Machine.h"

#pragma warning(disable: 4996)

FS_Machine::FS_Machine()
{
}

FS_Machine::FS_Machine( char c ) : num_of_states(2)
{
	matrix = new set<char> * [num_of_states];
	for (int i = 0; i < num_of_states; i++)
		matrix[i] = new set<char>[num_of_states];
	matrix[0][1].insert(c);
	final.insert(num_of_states - 1);
}

FS_Machine FS_Machine::Operation( FS_Machine fsm1, FS_Machine fsm2, char op )
{
	FS_Machine f;

	if (op == '&')
	{
		f.num_of_states = fsm1.num_of_states + fsm2.num_of_states;

		f.matrix = new set<char> * [f.num_of_states];
		for (int i = 0; i < f.num_of_states; i++)
			f.matrix[i] = new set<char>[f.num_of_states];

		for (int i = 0; i < fsm1.num_of_states; i++)
			for (int j = 0; j < fsm1.num_of_states; j++)
				f.matrix[i][j] = fsm1.matrix[i][j];

		for (int i = 0; i < fsm2.num_of_states; i++)
			for (int j = 0; j < fsm2.num_of_states; j++)
				f.matrix[fsm1.num_of_states + i][fsm1.num_of_states + j] = fsm2.matrix[i][j];

		f.matrix[fsm1.num_of_states - 1][fsm1.num_of_states].insert('@');
	}
	else if (op == '|')
	{
		f.num_of_states = fsm1.num_of_states + fsm2.num_of_states + 2;

		f.matrix = new set<char> * [f.num_of_states];
		for (int i = 0; i < f.num_of_states; i++)
			f.matrix[i] = new set<char>[f.num_of_states];

		for (int i = 0; i < fsm1.num_of_states; i++)
			for (int j = 0; j < fsm1.num_of_states; j++)
				f.matrix[i + 1][j + 1] = fsm1.matrix[i][j];

		for (int i = 0; i < fsm2.num_of_states; i++)
			for (int j = 0; j < fsm2.num_of_states; j++)
				f.matrix[fsm1.num_of_states + i + 1][fsm1.num_of_states + j + 1] = fsm2.matrix[i][j];

		f.matrix[0][1].insert('@');
		f.matrix[0][fsm1.num_of_states + 1].insert('@');
		f.matrix[fsm1.num_of_states][f.num_of_states - 1].insert('@');
		f.matrix[f.num_of_states - 2][f.num_of_states - 1].insert('@');
	}

	f.final.insert(f.num_of_states - 1);
	return f;
}

FS_Machine FS_Machine::Kleene( FS_Machine fsm )
{
	FS_Machine f;

	f.num_of_states = fsm.num_of_states + 2;

	f.matrix = new set<char> * [f.num_of_states];
	for (int i = 0; i < f.num_of_states; i++)
		f.matrix[i] = new set<char>[f.num_of_states];

	for (int i = 0; i < fsm.num_of_states; i++)
		for (int j = 0; j < fsm.num_of_states; j++)
			f.matrix[i + 1][j + 1] = fsm.matrix[i][j];

	f.matrix[0][1].insert('@');
	f.matrix[f.num_of_states - 2][f.num_of_states - 1].insert('@');
	f.matrix[0][f.num_of_states - 1].insert('@');
	f.matrix[f.num_of_states - 1][0].insert('@');

	f.final.insert(f.num_of_states - 1);
	return f;
}

FS_Machine::FS_Machine( string str )
{
	add_ampersand(str);
	int length = str.size();
	char * regexp = new char[length + 1];
	strcpy(regexp, str.c_str());
	int i = 0;
	stack<char> s;
	stack<FS_Machine> f;
	FS_Machine f1, f2;
	s.push(0);

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
				s.pop();
				f1 = f.top();
				f.pop();
				f2 = f.top();
				f.pop();
				//f.push(FS_Machine::Operation(f2, f1, s.top()));
				f.push(FS_Machine::Operation(f2, f1, '&'));
			}
			s.push('&');
			break;
		case '|':
			if (s.top() == '&' || s.top() == '|')
			{
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

	num_of_states = f.top().num_of_states;
	matrix = new set<char> * [num_of_states];
	for (int i = 0; i < num_of_states; i++)
		matrix[i] = new set<char>[num_of_states];

	copy_matrices(f.top().matrix, matrix, num_of_states);
	
	final.insert(num_of_states - 1);

	delete [] regexp;
}

FS_Machine::~FS_Machine()
{
	/*
	for (int i = 0; i < num_of_states; i++)
		delete [] matrix[i];
	delete [] matrix; */
}

void FS_Machine::eps_closure()
{
	for (int i = 0; i < num_of_states; i++)
		for (int j = 0; j < num_of_states; j++)
			for (int k = 0; k < num_of_states; k++)
				if (matrix[i][j].find('@') != matrix[i][j].end() && matrix[j][k].find('@') != matrix[j][k].end())
					matrix[i][k].insert('@');

	for (int i = 0; i < num_of_states; i++)
		for (set<int>::iterator it = final.begin(); it != final.end(); it++)
			if (matrix[i][*it].find('@') != matrix[i][*it].end())
				final.insert(i);

	// worst loop EVER!
	for (int i = 0; i < num_of_states; i++)
		for (int j = 0; j < num_of_states; j++)
			if (matrix[i][j].find('@') != matrix[i][j].end())
				for (int k = 0; k < num_of_states; k++)
					for (set<char>::iterator it = matrix[j][k].begin(); it != matrix[j][k].end(); it++)
						if (*it != '@')
							matrix[i][k].insert(*it);

	for (int i = 0; i < num_of_states; i++)
		for (int j = 0; j < num_of_states; j++)
			if (matrix[i][j].find('@') != matrix[i][j].end())
				matrix[i][j].erase('@');
}

void FS_Machine::determinate()
{
	queue<set<int>> q;
	vector<set<int>> v;

	set<int> s;
	set<int> ps;
	s.insert(0);
	q.push(s);

	while (!q.empty())
	{
		ps = s;
		s = q.front();
		if (s == ps)
			break;
		q.pop();
		set<int> ns;
		
		matrix[0][1].find('a');
		for (char i = 'a'; i <= 'z'; i++)
			for (set<int>::iterator it = s.begin(); it != s.end(); it++)
				for (int j = 0; j < num_of_states; j++)
					if (matrix[*it][j].size())
						if (matrix[*it][j].find(i) != matrix[*it][j].end())
							ns.insert(j);

		for (char i = 'A'; i <= 'Z'; i++)
			for (set<int>::iterator it = s.begin(); it != s.end(); it++)
				for (int j = 0; j < num_of_states; j++)
					if (matrix[*it][j].find(i) != matrix[*it][j].end())
						ns.insert(j);

		for (char i = '0'; i <= '9'; i++)
			for (set<int>::iterator it = s.begin(); it != s.end(); it++)
				for (int j = 0; j < num_of_states; j++)
					if (matrix[*it][j].find(i) != matrix[*it][j].end())
						ns.insert(j);

		bool in_queue = false;

		for (int i = 0; i < q.size(); i++)
		{
			if (ns == q.front())
			{
				in_queue = true;
				break;
			}
			q.push(q.front());
			q.pop();
		}

		if (!in_queue && ns.size())
		{
			q.push(ns);
			v.push_back(ns);
		}
	}
}

bool FS_Machine::check_string( string s )
{
	int length = s.size();
	char * seq = new char[length + 1];
	strcpy(seq, s.c_str());

	int state = 0;
	int cur = 0;

	while (true)
	{
		if (cur == length)
		{
			delete [] seq;
			if (final.find(state) != final.end())
				return true;
			if (matrix[state][num_of_states - 1].find('@') != matrix[state][num_of_states - 1].end())
				return true;
			return false;				
		}

		char c = seq[cur++];
		bool next_state_found = false;

		if (c != '@')
			for (int i = 0; i < num_of_states; i++)
			{
				if (matrix[state][i].find(c) != matrix[state][i].end())
				{
					state = i;
					next_state_found = true;
					break;
				}
			}
		else
			next_state_found = true;
	
		if (!next_state_found)
		{
			for (int i = 0; i < num_of_states; i++)
			{
				for (int j = 0; j < num_of_states; j++)
					if (matrix[state][i].find('@') != matrix[state][i].end() && matrix[i][j].find(c) != matrix[i][j].end())
					{
						state = j;
						next_state_found = true;
						break;
					}

				if (next_state_found)
					break;
			}

			if (!next_state_found)
			{
				delete [] seq;
				return false;
			}
		}
	}

	delete [] seq;

	return false;
}

void FS_Machine::print_matrix()
{
	for (int i = 0; i < num_of_states; i++)
	{
		for (int j = 0; j < num_of_states; j++)
		{
			if (matrix[i][j].size() == 0)
				cout << 0;
			for (set<char>::iterator it = matrix[i][j].begin(); it != matrix[i][j].end(); it++)
					cout << *it;
			cout << ' ';
		}
		cout << endl;
	}
}

void FS_Machine::print_list()
{
	for (int i = 0; i < num_of_states; i++)
		for (int j = 0; j < num_of_states; j++)
			if (matrix[i][j].size())
			{
				cout << "(" << i << ", " << j << ", ";
				for (set<char>::iterator it = matrix[i][j].begin(); it != matrix[i][j].end(); it++)
					cout << *it;
				cout << ")" << endl;
			}
}

void FS_Machine::print_finals()
{
	cout << "Finals: ";
	for (set<int>::iterator it = final.begin(); it != final.end(); it++)
		cout << *it << ' ';
	cout << endl;
}

bool in_alphabet( char c )
{
	if ((c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A') || (c <= '9' && c >= '0'))
		return true;
	return false;
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

void copy_matrices( set<char> ** src, set<char> ** dest, int n )
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			dest[i][j] = src[i][j];
}
