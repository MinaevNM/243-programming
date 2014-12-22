#pragma once

#include <iostream>

using namespace std;

class Node
{
	char c;
	int freq;

	Node * Left;
	Node * Right;

public:
	Node( int _data ) : c(0), freq(_data), Left(NULL), Right(NULL)
	{
	}

	Node( int _data, Node * left, Node * right ) : c(0), freq(_data), Left(left), Right(right)
	{
	}

	Node( char _c, int _freq ) : c(_c), freq(_freq), Left(NULL), Right(NULL)
	{
	}

	pair<char, int> getData()
	{
		return pair<char, int>(c, freq);
	}

	void walk( map<char, string> * codes, string code, int dir )
	{
		if (dir != -1)
			code += dir;
		if (Left == NULL && Right == NULL)
		{
			(*codes)[c] = code;
			return;
		}
		Left->walk(codes, code, '0');
		Right->walk(codes, code, '1');
	}
};

class Tree
{
	Node * Root;

public:
	Tree( int data )
	{
		Root = new Node(data);
	}

	Tree( char c, int freq )
	{
		Root = new Node(c, freq);
	}

	Tree( Tree t1, Tree t2 )
	{
		if (t1.getRootValue().second < t2.getRootValue().second)
			Root = new Node(t1.getRootValue().second + t2.getRootValue().second, t1.getRoot(), t2.getRoot());
		else
			Root = new Node(t1.getRootValue().second + t2.getRootValue().second, t2.getRoot(), t1.getRoot());
		//Root = new Node(t1.getRootValue().second + t2.getRootValue().second, t2.getRoot(), t1.getRoot());
	}

	Node * getRoot()
	{
		return Root;
	}

	pair<char, int> getRootValue()
	{
		if (Root == NULL)
			return pair<char, int>(0, 0);
		return Root->getData();
	}

	map<char, string> * walk()
	{
		map<char, string> * codes = new map<char, string>();

		Root->walk(codes, string(""), -1);
		return codes;
	}
};
