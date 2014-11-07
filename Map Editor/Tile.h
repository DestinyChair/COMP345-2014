#pragma once
#include <string>

using std::string;

class Tile{

protected:
	string name;
	string symbol;
	bool buildable;
	int dmg, range;

public:
	Tile();
	Tile(string n, string s, bool b);
	Tile(string n, string s, bool b, int d, int r);

	string getName();
	void setName(string n);
	
	string getSymbol();
	void setSymbol(string s);

	void setDmg(int d), setRange(int r);
	int getDmg(), getRange();
	void printDetails();

	bool isBuildable();
	void setBuildable(bool buildable);
};