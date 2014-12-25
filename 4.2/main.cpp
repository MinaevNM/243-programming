#include <iostream>
#include <string>

using namespace std;

void main()
{
	char c;
	int state = 0;

	freopen("input.cpp", "rt", stdin);
	//freopen("output.txt", "wt", stdout);

	string s = "";

	while (true)
	{
		if ((c = getchar()) == -1)
		{
			cout << s << endl;
			break;
		}

		switch (state)
		{
		case 0:
			if (c >= 'a' && c <= 'z')
			{
				s = "";
				state = 1;
				s.push_back(c);
			}
			else if (c >= '0' && c <= '9')
			{
				s = "";
				state = 2;
				s.push_back(c);
			}
			else if (c == ';' || c == '<' || c == '=')
			{
				if (c == ';')
					cout << ";		 separator" << endl;
				else if (c == '=')
					cout << "=		 assignment" << endl;
				else 
					state = 3;
			}
			break;
		case 1:
			if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'))
				s.push_back(c);
			else if (c == ';' || c == '<' || c == '=' || c == ' ')
			{
				if (s == "float")
					cout << "float		 type" << endl;
				else if (s == "if")
					cout << "if		 if" << endl;
				else if (s != "")
					cout << s << "		 id"  << endl;
				s = "";
				if (c == ';')
					cout << ";		 separator" << endl;
				else if (c == '=')
					cout << "=		 assignment" << endl;
				state = 0;
			}
			else
				cout << "Error" << endl;
			break;
		case 2:
			if (c >= '1' && c <= '9' || c == '.')
				s.push_back(c);
			else if (c == ';' || c == '<' || c == '=' || c == ' ')
			{
				cout << s << "		 num" << endl;
				s = "";
				state = 0;
			}

			break;
		
		case 3:
			if (c =='=')
			{
				cout << "<=    relation" << endl;
				state = 0;
			}	
			else
			{
			}
			break;
		}
	}
}
