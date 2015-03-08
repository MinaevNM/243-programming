#include <iostream>

using namespace std;

#pragma once

class FS_Machine
{
	int num_of_states;
	char ** matrix;

public:
	FS_Machine( string regexp );
	bool check_string( string s );
};
