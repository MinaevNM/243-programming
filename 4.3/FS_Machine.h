#include <iostream>
#include <set>

using namespace std;

#pragma once

class FS_Machine
{
	int num_of_states;
	set<char> ** matrix;

public:
	void print()
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

	FS_Machine();
	FS_Machine( string regexp );
	FS_Machine( char c );

	static FS_Machine Operation( FS_Machine fsm1, FS_Machine fsm2, char op );
	static FS_Machine Kleene( FS_Machine fsm );

	bool check_string( string s );
	void eps_closure();
};
