#include "Character.h"
#include "Tile.h"
#include <iostream>

using namespace std;

Character::Character(){
	symbol = "%"; //symbol represents current position
	name = "Character";
	temp = "*";
	xpos = 0;
	ypos = 0;
	money = 1000; //currently arbitrary for testing purposes
}

void Character::instructions(){
	cout << "\nMove the '%' to build towers. Press 'Z' to build a tower.";
	cout << "\nPress 'X' to upgrade a tower. Press 'C' to sell a tower.";
}

void Character::nope(){
	cout << "\nCannot move there.\n";
}

void Character::addTower(){
	
}

void Character::removeTower(){

}

void Character::upgradeTower(){
	
}

string Character::getTemp(){
	return temp;
}