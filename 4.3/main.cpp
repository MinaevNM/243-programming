#include <iostream>
#include <string>

#include "FS_Machine.h"

using namespace std;

#pragma warning(disable: 4996)

void main()
{
	int n;
	string regexp;
	string s;

	freopen("input.cpp", "rt", stdin);
	freopen("output.txt", "wt", stdout);

	cin >> regexp;
	
	FS_Machine * fsm = new FS_Machine(regexp);

	//fsm->print_list();
	fsm->eps_closure();
	cout << endl << "------------------------------" << endl; 
	//fsm->print_list();
	//fsm->print_finals();
	cout << endl << "------------------------------" << endl; 
	fsm->determinate();
	//fsm->print_list();
	//fsm->print_finals();

	cin >> n;

	for (int i = 0; i < n; i++)
	{
		cin >> s;
		cout << (fsm->check_string(s) ? "Yes" : "No") << endl;
	}

	delete fsm;
}
