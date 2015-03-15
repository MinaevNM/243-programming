#include "FS_Machine.h"

#pragma warning(disable: 4996)

FS_Machine::FS_Machine( string regexp )
{
	num_of_states = 4;

	matrix = new set<char> * [num_of_states];
	for (int i = 0; i < num_of_states; i++)
		matrix[i] = new set<char>[num_of_states];
	/*
	matrix[0][1].insert('a');
	matrix[0][1].insert('b');
	matrix[0][2].insert('p');
	matrix[0][3].insert('c');
	matrix[1][1].insert('a');
	matrix[1][1].insert('b');
	matrix[1][3].insert('c');
	matrix[2][3].insert('q'); 
	*/

	matrix[0][1].insert('a');
	matrix[1][3].insert('@');
	matrix[1][2].insert('b');
	matrix[2][3].insert('b');
	matrix[3][3].insert('x');
	//eps_closure();
}

void FS_Machine::eps_closure()
{
	/*
	for (int i = 0; i < num_of_states; i++)
		for (int j = 0; j < num_of_states; j++)
			for (int k = 0; k < num_of_states; k++)
				if (matrix[i][j] == '@' && matrix[j][k] == '@')
					matrix[i][k] = '@';
					*/
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
			if (state == num_of_states - 1)
				return true;
			if (matrix[state][num_of_states - 1].find('@') != matrix[state][num_of_states - 1].end())
				return true;
			return false;				
		}

		char c = seq[cur++];
		bool next_state_found = false;

		for (int i = 0; i < num_of_states; i++)
		{
			if (matrix[state][i].find(c) != matrix[state][i].end())
			{
				state = i;
				next_state_found = true;
				break;
			}
		}

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
