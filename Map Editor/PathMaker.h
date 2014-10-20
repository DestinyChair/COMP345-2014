#pragma once
#include <iostream>

using namespace std;

class PathMaker{
public:
	PathMaker();
	string name, symbol, dir;
	int xpos, ypos;
	bool leftEdge;

	void instructions(), nope(), removeDir();

	bool from(char c);
	void setDir(char c);
};

