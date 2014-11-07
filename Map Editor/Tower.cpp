#include<iostream>
#include<string>
#include "Tower.h"
#include "Tile.h"
using namespace std;

//default tower 1 dmg, 2 range
Tower::Tower(){
	Tile("Tower", "1", false, 1, 2);
}

Tower::Tower(string s, int d, int r){
	Tile("Tower", s, false, d, r);
}

void Tower::setDmg(int d){
	dmg = d;
}

void Tower::setRange(int r){
	range = r;
}

int Tower::getDmg(){
	return dmg;
}

int Tower::getRange(){
	return range;
}

void Tower::printDetails(){
	Tile::printDetails();
	cout << "\nDamage: " + getDmg();
	cout << "\nRange: " + getRange() << "\n";
}