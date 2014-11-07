#pragma once
#include "Tile.h"


class Tower : public Tile{

public:
	Tower();
	Tower(string s, int d, int r);

	int dmg, range;

	void printDetails();
	void setDmg(int d), setRange(int r);
	int getDmg(), getRange();

private:
	void fire();
};