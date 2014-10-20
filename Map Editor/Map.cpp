#include "Map.h"
#include "Tile.h"
#include <iostream>

using namespace std;

Map::Map(){

}

Map::Map(int h, int w){
	height = h;
	width = w;

	//2D: Array of pointers to array of Tile objects
	map = new Tile*[height + 2];
	for (int i = 0; i < height + 2; i++){
		map[i] = new Tile[width + 2];
	}
}

void Map::print(){
	for (int j = 0; j < height + 2; j++){
		for (int i = 0; i < width + 2; i++){
			cout << map[j][i].getSymbol();
		}
		cout << "\n";
	}
}

Tile Map::getTile(int j, int i){
	return map[j][i];
}

void Map::setTile(int j, int i, string n, string s, bool b){
	map[j][i].setName(n);
	map[j][i].setSymbol(s);
	map[j][i].setBuildable(b);
}

void Map::legend(){
	cout << "\n_ = buildable, X = path, * = edge\n";
}

int Map::getMax(){
	return MAXDIMENSIONS;
}

void Map::setWidth(int w){
	width = w;
}

int Map::getWidth(){
	return width;
}

void Map::setHeight(int h){
	height = h;
}

int Map::getHeight(){
	return height;
}