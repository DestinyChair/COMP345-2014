#pragma once
#include <iostream>

using namespace std;

class Character{
public:
	Character();
	string symbol, name, temp;
	int xpos, ypos, money;

	void instructions(), nope(), addTower(), removeTower(), upgradeTower();
	string getTemp();
};
