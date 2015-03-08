#include "FS_Machine.h"

#pragma warning(disable: 4996)

FS_Machine::FS_Machine( string regexp )
{
	num_of_states = 11;

	matrix = new char * [num_of_states];
	for (int i = 0; i < num_of_states; i++)
		matrix[i] = new char[num_of_states];

	FILE * f = fopen("matrix.txt", "rt");
	for (int i = 0; i < num_of_states; i++)
	{
		for (int j = 0; j < num_of_states; j++)
			fscanf(f, "%c", &matrix[i][j]);
		fscanf(f, "\n");
	}

	fclose(f);
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
		if (cur == length && state == num_of_states - 1)
		{
			delete [] seq;
			return true;
		}

		char c = seq[cur++];
		bool next_state_found = false;

		for (int i = 0; i < num_of_states; i++)
		{
			if (matrix[state][i] == c)
			{
				state = i;
				next_state_found = true;
				break;
			}
			if (matrix[state][i] == '@')
			{
				for (int j = 0; j < num_of_states; j++)
					if (matrix[i][j] == c)
					{
						state = j;
						next_state_found = true;
						break;
					}

				if (next_state_found)
					break;
			}
		}

		if (!next_state_found)
		{
			delete [] seq;
			return false;
		}
	}

	delete [] seq;

	return false;
}
