#include "PathMaker.h"
#include <iostream>

using namespace std;

PathMaker::PathMaker(){
	name = "Pathmaker";
	symbol = "O"; //symbol represents current position
	xpos = 0;
	ypos = 0;
	leftEdge = false;
	start = "";  //stored as NESW and index (N2=top at index 2)
	dir = "";
}

void PathMaker::instructions(){
	cout << "\nMove the 'O' with the arrow keys to build a path.";
	cout << "\nPath starts when you leave the edge and ends when you re-enter it.";
	cout << "\nMonsters follow the path in the order built.\n";
}

void PathMaker::nope(){
	cout << "\nCannot build path in that direction, use your imagination to pretend the";
	cout << "\n'O's are a one directional path with no splits.";
}

bool PathMaker::from(char c){
	return c == dir.back();
}

void PathMaker::removeDir(){
	dir.pop_back();
}

void PathMaker::setDir(char c){
	dir+=c;
}
