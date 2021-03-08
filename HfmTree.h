#pragma once
#ifndef HFMTREE
#define HFMTREE

#include<bits/stdc++.h>
using namespace std;
class HfmTree
{
public:
	HfmTree();
	HfmTree(string, int,int, int, int);
	string getData();
	int getWeight();
	int getTag();
	int getLeft();
	int getRight();
	int getParent();
	string getCharCode();

	void setLeft(int);
	void setRight(int);
	void setParent(int);
	void setTag(int);
	void setCharCode(string);
private:
	string data;
	int weight;
	int left;
	int right;
	int parent;
	string charCode;
	int tag;
};

#endif // !HFMTREE



