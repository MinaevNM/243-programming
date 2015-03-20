#include <iostream>
#include <set>

using namespace std;

#pragma once

class FS_Machine
{
	int num_of_states;
	set<char> ** matrix;

public:
	FS_Machine();
	FS_Machine( string regexp );
	FS_Machine( char c );

	static FS_Machine Operation( FS_Machine fsm1, FS_Machine fsm2, char op );
	static FS_Machine Kleene( FS_Machine fsm );

	bool check_string( string s );
	void eps_closure();

	void print_matrix();
	void print_list();
};
