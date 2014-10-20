#include <iostream>
#include "Tile.h"

using namespace std;

//default tile is buildable land
Tile::Tile(){
	name = "Scenery";
	symbol = "_";
	buildable = true;
}

Tile::Tile(string n, string s, bool b){
	name = n;
	symbol = s;
	buildable = b;
}

Tile::~Tile(){
	
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

void Tile::printDetails(){
	cout << "\nName: " + getName();
	cout << "\nSymbol: " + getSymbol();
	cout << "\nBuildable: " + isBuildable();
}

bool Tile::isBuildable(){
	return buildable;
}

void Tile::setBuildable(bool b){
	buildable = b;
}