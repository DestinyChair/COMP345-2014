#pragma once
#include "Tile.h"

using namespace std;

class Map{

private:
	int width, height;
	const static int MAXDIMENSIONS = 64;

	Tile** map;

public:
	Map();
	Map(int h, int w);

	Tile getTile(int j, int i);
	void print(), legend(), setSymbol(int j, int i, string s);
	void setTile(int j, int i, string n, string s, bool b), setTile(int j, int i, int d, int r);
	int getWidth(), getHeight(), getMax();
	void setWidth(int w), setHeight(int h);
};