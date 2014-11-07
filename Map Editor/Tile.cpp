#include <iostream>
#include "Tile.h"

using namespace std;

//default tile is buildable land
Tile::Tile(){
	name = "Scenery";
	symbol = "_";
	buildable = true;
	dmg = 0;
	range = 0;
}

Tile::Tile(string n, string s, bool b){
	name = n;
	symbol = s;
	buildable = b;
}


Tile::Tile(string n, string s, bool b, int d, int r){
	name = n;
	symbol = s;
	buildable = b;
	dmg = d;
	range = r;
}

//getter and setter methods
string Tile::getName(){
	return name;
}

void Tile::setName(string n){
	name = n;
}

string Tile::getSymbol(){
	return symbol;
}

void Tile::setSymbol(string s){
	symbol = s;
}

int Tile::getDmg(){
	return dmg;
}

void Tile::setDmg(int d){
	dmg = d;
}

int Tile::getRange(){
	return range;
}

void Tile::setRange(int r){
	range = r;
}

void Tile::printDetails(){
	string buildable;
	if (this->isBuildable()){
		buildable = "true";
	}
	else{
		buildable = "false";
	}
	cout << "\nName: " + getName();
	cout << "\nSymbol: " + getSymbol();
	cout << "\nBuildable: " + buildable;
	cout << "\nDamage: " + getDmg();
	cout << "\nRange: " + getRange() << "\n";
}

bool Tile::isBuildable(){
	return buildable;
}

void Tile::setBuildable(bool b){
	buildable = b;
}