#include <iostream> 
#include <string> 

using namespace std; 

void main() 
{ 
	char c; 
 	int state = 0; 
	int cstate = 0;
	freopen("input.cpp", "rt", stdin); 
	freopen("output.txt", "wt", stdout); 

	string s = ""; 
	int line = 1;

	while (true) 
	{ 
		if ((c = getchar()) == -1) 
		{ 
			switch (state)
			{
			case 1:
				if (s == "float") 
					cout << "float		 type" << endl; 
				else if (s == "if") 
					cout << "if		 if" << endl; 
				else if (s != "") 
					cout << s << "		 id"  << endl; 
				break;
			case 2:
				cout << s << endl; 
				break;
			case 3:
				cout << "<		 relation" << endl;
				break;
			}
			
			break; 
		}

		if (c == '\n')
			line++;

		if (cstate)
		{
			state = 0;
			switch (cstate)
			{
			case 1:
				if (c == '/')
					cstate = 3;
				else if (c == '*')
					cstate = 2;
				else
				{
					cout << "Error: unexpected symbol '" << c << "' -- Line " << line  << endl;
					return;
				}
				break;
			case 2:
				if (c == '*')
					cstate = 4;
				break;
			case 3:
				if (c == '\n')
					cstate = 0;
				break;
			case 4:
				if (c == '/')
					cstate = 0;
				break;
			}	

			continue;
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
			else if (c == ';' || c == '<' || c == '=' || c == ' ' || c == '\n') 
			{ 
				if (c == ';') 
					cout << ";		 separator" << endl; 
				else if (c == '=') 
					cout << "=		 assignment" << endl; 
				else if (c == '<')
					state = 3; 
			} 
			else if (c == '/')
			{
				cstate = 1;
				break;
			}
			else
			{
				cout << "Error: unexpected symbol '" << c << "' -- Line " << line << endl;
				return;
			}
			break; 
		case 1: 
			if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) 
				s.push_back(c); 
			else if (c == ';' || c == '<' || c == '=' || c == ' ' || c == '/' || c == '\n') 
			{ 
				if (s == "float") 
					cout << "float		 type" << endl; 
				else if (s == "if") 
					cout << "if		 if" << endl; 
				else if (s != "") 
					cout << s << "		 id"  << endl; 
				s = ""; 
				state = 0; 
				if (c == ';') 
					cout << ";		 separator" << endl; 
				else if (c == '=') 
					cout << "=		 assignment" << endl; 
				else if (c == '<')
					state = 3;		
				else if (c == '/')
				{
					cstate = 1;
					break;
				}
			} 
			else 
			{
				cout << "Error: id should not contain '" << c << "' symbol -- Line" << line << endl; 
				return;
			}
			break; 
		case 2: 
			if (c >= '1' && c <= '9' || c == '.') 
				s.push_back(c); 
			else if (c == ';' || c == '<' || c == '=' || c == ' ' || c == '/' || c == '\n') 
			{ 
				cout << s << "		 num" << endl; 
				s = ""; 
				state = 0; 
				if (c == ';') 
					cout << ";		 separator" << endl; 
				else if (c == '=') 
					cout << "=		 assignment" << endl; 
				else if (c == '<')
					state = 3;	
				else if (c == '/')
				{
					cstate = 1;
					break;
				}
			} 
			else
			{
				cout << "Error: bad suffix on number -- Line " << line << endl;
				return;
			}

			break; 
		 case 3: 
			if (c =='=') 
			{ 
				cout << "<=               relation" << endl; 
				state = 0; 
			}	 
			else 
			{ 
				cout << "<		 relation" << endl;
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
				else if (c == ';' || c == '<' || c == '=' || c == '/' || c == ' ' || c == '\n') 
				{ 
					if (c == ';') 
						cout << ";		 separator" << endl; 
					else if (c == '=') 
						cout << "=		 assignment" << endl; 
					else if (c == '<')
						state = 3; 
					else if (c == '/')
					{
						cstate = 1;
						break;
					}
					else if (c == ' ' || c == '\n')
						state = 0;
				} 
				else
				{
					cout << "Error: unexpected symbol '" << c << "' -- Line " << line << endl;
					return;
				}
			} 
			break; 
		} 
	} 

	if (cstate)
		cout << "Error: comment end not found" << endl;
} 
