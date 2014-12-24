#include <iostream>

using namespace std;

//a-f >= 1
//xy >= 0

void main()
{
	// re = "[a-f]+(xy)*z"

	int n;
	char c;
	
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);

	cin >> n;

	int state = 1;

	for (int i = 0; i < n; i++)
	{
		cin >> c;

		switch (state)
		{
		case 1:
			if (c >= 'a' && c <= 'f')
				state = 2;
			break;
		case 2:
			if (c == 'x')
				state = 3;
			else if (c == 'z')
			{
				cout << "YES";
				return;
			}
			else if (c >= 'a' && c <= 'f')
				;
			else
				state = 1;
			break;
		case 3:
			if (c == 'y' || (c >= 'a' && c <= 'f'))
				state = 2;
			else
				state = 1;
			break;
		}
	}

	cout << "NO";
}
