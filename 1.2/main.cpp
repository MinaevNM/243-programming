#include <iostream> 
#include <queue> 
#include <map> 
#include <string> 
#include <cmath>

#include "tree.h" 

#pragma warning(disable: 4996) 

using namespace std; 

class mycomparison 
{ 
public: 
	mycomparison() 
    { 
	} 
	 
	bool operator() ( Tree & lhs, Tree & rhs ) const 
	{ 
		return (lhs.getRootValue().second > rhs.getRootValue().second); 
	} 
}; 

void main() 
{ 
	freopen("input.txt", "rt", stdin); 
	 
	int num = 0; 
	int diff_letters;
	char c; 
	map<char, int> letters; 
	map<char, int>::iterator it;
	
	while ((c = getchar()) > 0) 
	{ 
		num++; 
		it = letters.find(c); 
		if (it == letters.end()) 
			letters[c] = 1; 
		else 
		{ 
			letters[c]++; 
		} 
	} 

	diff_letters = letters.size();

 	priority_queue<Tree, vector<Tree>, mycomparison> pq; 

	for (it = letters.begin(); it != letters.end(); it++) 
	{ 
		Tree t(it->first, it->second); 
		pq.push(t); 
	} 

	while (pq.size() != 1) 
	{ 
		Tree t1 = pq.top(); 
		pq.pop(); 
		Tree t2 = pq.top(); 
		pq.pop(); 

		Tree t(t1, t2); 
		pq.push(t); 
	} 

	Tree t = pq.top(); 
	map<char, string> * codes = t.walk(); 

	int codelength = 0; 
	for (map<char, string>::iterator it = codes->begin(); it != codes->end(); it++) 
		codelength += it->second.length() * letters[it->first]; 

	cout << "compression coeff: " << (ceil(log((double)diff_letters) / log(2.)) * num / codelength) << endl;  

	for (map<char, string>::iterator it = codes->begin(); it != codes->end(); it++) 
	{ 
		if (it->first == ' ') 
			cout << "space: " << it->second << endl; 
		else 
			cout << it->first << ":     " << it->second << endl; 
	} 
}
