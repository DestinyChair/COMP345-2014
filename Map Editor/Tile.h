#pragma once
#include <string>

using std::string;

class Tile{

protected:
	string name;
	string symbol;
	bool buildable;

public:
	Tile();
	Tile(string n, string s, bool b);
	~Tile();

	string getName();
	void setName(string n);
	
	string getSymbol();
	void setSymbol(string s);

	void printDetails();

	bool isBuildable();
	void setBuildable(bool buildable);
};