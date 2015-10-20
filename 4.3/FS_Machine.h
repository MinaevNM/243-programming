#include <iostream>
#include <set>

using namespace std;

#pragma once

class FS_Machine
{
	int num_of_states;
	set<char> ** matrix;
	set<int> final;

public:
	FS_Machine();
	FS_Machine( string regexp );
	FS_Machine( char c );
	~FS_Machine();

	static FS_Machine Operation( FS_Machine fsm1, FS_Machine fsm2, char op );
	static FS_Machine Kleene( FS_Machine fsm );

	bool check_string( string s );
	void eps_closure();
	void determinate();

	void print_matrix();
	void print_list();
	void print_finals();
};

void copy_matrices( set<char> ** src, set<char> ** dest, int n );
bool in_alphabet( char c );
void add_ampersand( string & s );

