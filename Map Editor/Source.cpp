#include <iostream>
#include <Windows.h>
#include "Map.h"
#include "PathMaker.h"
#include "Character.h"
#include "Tower.h"

using namespace std;

int main(){
	int height, width;
	const int MAXD = 64;
	const int MIND = 4;
	HANDLE inp = GetStdHandle(STD_INPUT_HANDLE);
	DWORD numInp, inpRead = 0;
	bool running = true;
	INPUT_RECORD inpRec;

	GetNumberOfConsoleInputEvents(inp, &numInp);

	//Gets and validates map dimensions
	cout << "\nWhat dimensions would you like your map to be?";
	do{
		cout << "\nHeight: ";
		cin >> height;
		if ((height > MAXD) || (height < MIND)){
			cout << "\nPlease choose a height from " << MIND << "-" << MAXD;
		}
	} while ((height > MAXD) || (height < MIND));
	do{
		cout << "\nWidth: ";
		cin >> width;
		if ((width > MAXD) || (width < MIND)){
			cout << "\nPlease choose a width from " << MIND << "-" << MAXD;
		}
	} while ((width > MAXD) || (width < MIND));

	//pointer to an array of pointers that point to an array of pointers to Tile objects, similar to making a 2D array of tile objects as an object
	//remember that the height and width are +2 for the edges!
	Map* m = new Map(height, width);

	//sets edge tiles
	//top
	for (int i = 0; i < width + 2; i++){
		m->setTile(0, i, "Edge", "*", false);
	}
	//bottom
	for (int i = 0; i < width + 2; i++){
		m->setTile(height + 1, i, "Edge", "*", false);
	}
	//left
	for (int j = 1; j < height + 1; j++){
		m->setTile(j, 0, "Edge", "*", false);
	}
	//right
	for (int j = 1; j < height + 1; j++){
		m->setTile(j, width + 1, "Edge", "*", false);
	}

	PathMaker* PM = new PathMaker();
	PM->instructions();

	m->setTile(PM->ypos, PM->xpos, PM->name, PM->symbol, false);
	m->print();
	
	//reads keyboard input (arrow keys and esc) to generate a path
	//path validation is built in as it is a single direction with no splits
	while (running)
	{
		system("pause>nul");
		ReadConsoleInput(inp, &inpRec, 1, &inpRead);
		switch (inpRec.Event.KeyEvent.wVirtualKeyCode)
		{
		case VK_ESCAPE:
			//quits loop
			running = false;
			break;

		//MOVE LEFT
		case VK_LEFT:
			//bounds
			if (PM->xpos - 1 < 0){
				break;
			}
			//edges
			else if ((PM->xpos - 1 == 0) && (PM->leftEdge)){
				PM->xpos--;
				m->setTile(PM->ypos, PM->xpos, PM->name, PM->symbol, false);
				m->print();
				PM->setDir('A');
				running = false;
				break;
			}
			else if ((PM->ypos==0)||(PM->ypos==m->getHeight()+1)){
				if (PM->leftEdge){
					running = false;
				}
				else{
					m->setTile(PM->ypos, PM->xpos, "Edge", "*", false);
					PM->xpos--;
					m->setTile(PM->ypos, PM->xpos, PM->name, PM->symbol, false);
					m->print();
					PM->setDir('A');
					break;
				}
			}
			//retread path
			else if ((m->getTile(PM->ypos, PM->xpos-1).getSymbol() == "O") && (PM->from('D'))){
				m->setTile(PM->ypos, PM->xpos, "Scenery", "_", true);
				PM->removeDir();
				PM->xpos--;
				m->print();
				break;
			}
			//illegal path crossing
			else if ((m->getTile(PM->ypos, PM->xpos - 1).getSymbol() == "O") && !(PM->from('D'))){
				PM->nope();
				break;
			}
			//normal
			else{
				if (PM->leftEdge == false){
					PM->start = 'E' + PM->ypos;
					PM->leftEdge = true;
				}
				PM->xpos--;
				m->setTile(PM->ypos, PM->xpos, PM->name, PM->symbol, false);
				m->print();
				PM->setDir('A');
				break;
			}

		//MOVE UP
		case VK_UP:
			//bounds
			if (PM->ypos - 1 < 0){
				break;
			}
			//edges
			else if ((PM->ypos - 1 == 0) && (PM->leftEdge)){
				PM->ypos--;
				m->setTile(PM->ypos, PM->xpos, PM->name, PM->symbol, false);
				m->print();
				PM->setDir('W');
				running = false;
				break;
			}
			else if ((PM->xpos == 0) || (PM->xpos == m->getWidth()+1)){
				if (PM->leftEdge){
					running = false;
				}
				else{
					m->setTile(PM->ypos, PM->xpos, "Edge", "*", false);
					PM->ypos--;
					m->setTile(PM->ypos, PM->xpos, PM->name, PM->symbol, false);
					m->print();
					PM->setDir('W');
					break;
				}
			}
			//retread path
			else if ((m->getTile(PM->ypos - 1, PM->xpos).getSymbol() == "O") && (PM->from('S'))){
				m->setTile(PM->ypos, PM->xpos, "Scenery", "_", true);
				PM->removeDir();
				PM->ypos--;
				m->print();
				break;
			}
			//illegal path crossing
			else if ((m->getTile(PM->ypos - 1, PM->xpos - 1).getSymbol() == "O") && !(PM->from('S'))){
				PM->nope();
				break;
			}
			//normal
			else{
				if (PM->leftEdge == false){
					PM->start = 'S' + PM->xpos;
					PM->leftEdge = true;
				}
				PM->ypos--;
				m->setTile(PM->ypos, PM->xpos, PM->name, PM->symbol, false);
				m->print();
				PM->setDir('W');
				break;
			}

		//MOVE RIGHT
		case VK_RIGHT:
			//bounds
			if (PM->xpos - 1 >= m->getWidth()){
				break;
			}
			//edges
			else if ((PM->xpos == m->getWidth()) && (PM->leftEdge)){
				PM->xpos++;
				m->setTile(PM->ypos, PM->xpos, PM->name, PM->symbol, false);
				m->print();
				PM->setDir('D');
				running = false;
				break;
			}
			else if ((PM->ypos == 0) || (PM->ypos == m->getHeight() + 1)){
				if (PM->leftEdge){
					running = false;
				}
				else{
					m->setTile(PM->ypos, PM->xpos, "Edge", "*", false);
					PM->xpos++;
					m->setTile(PM->ypos, PM->xpos, PM->name, PM->symbol, false);
					m->print();
					PM->setDir('D');
					break;
				}
			}
			//retread path
			else if ((m->getTile(PM->ypos, PM->xpos + 1).getSymbol() == "O") && (PM->from('A'))){
				m->setTile(PM->ypos, PM->xpos, "Scenery", "_", true);
				PM->removeDir();
				PM->xpos++;
				m->print();
				break;
			}
			//illegal path crossing
			else if ((m->getTile(PM->ypos, PM->xpos + 1).getSymbol() == "O") && !(PM->from('A'))){
				PM->nope();
				break;
			}
			//normal
			else{
				if (PM->leftEdge == false){
					PM->start = 'W' + PM->ypos;
					PM->leftEdge = true;
				}
				PM->xpos++;
				m->setTile(PM->ypos, PM->xpos, PM->name, PM->symbol, false);
				m->print();
				PM->setDir('D');
				break;
			}

		//MOVE DOWN
		case VK_DOWN:
			//bounds
			if (PM->ypos - 1 >= m->getHeight()){
				break;
			}
			//edges
			else if ((PM->ypos == m->getHeight()) && (PM->leftEdge)){
				PM->ypos++;
				m->setTile(PM->ypos, PM->xpos, PM->name, PM->symbol, false);
				m->print();
				PM->setDir('S');
				running = false;
				break;
			}
			else if ((PM->xpos == 0) || (PM->xpos == m->getWidth() + 1)){
				if (PM->leftEdge){
					running = false;
				}
				else{
					m->setTile(PM->ypos, PM->xpos, "Edge", "*", false);
					PM->ypos++;
					m->setTile(PM->ypos, PM->xpos, PM->name, PM->symbol, false);
					m->print();
					PM->setDir('S');
					break;
				}
			}
			//retread path
			else if ((m->getTile(PM->ypos + 1, PM->xpos).getSymbol() == "O") && (PM->from('W'))){
				m->setTile(PM->ypos, PM->xpos, "Scenery", "_", true);
				PM->removeDir();
				PM->ypos++;
				m->print();
				break;
			}
			//illegal path crossing
			else if ((m->getTile(PM->ypos + 1, PM->xpos).getSymbol() == "O") && !(PM->from('W'))){
				PM->nope();
				break;
			}
			//normal
			else{
				if (PM->leftEdge == false){
					PM->start = 'N' + PM->xpos;
					PM->leftEdge = true;
				}
				PM->ypos++;
				m->setTile(PM->ypos, PM->xpos, PM->name, PM->symbol, false);
				m->print();
				PM->setDir('S');
				break;
			}
		}
	}
	
	cout << "\nYour map is above.\n";

	running = true;

	Character *c = new Character();

	m->setTile(c->ypos, c->xpos, c->name, c->symbol, false);
	m->print();

	//reads keyboard input (arrow keys, esc, F1-F4)
	while (running)
	{
		system("pause>nul");
		ReadConsoleInput(inp, &inpRec, 1, &inpRead);
		switch (inpRec.Event.KeyEvent.wVirtualKeyCode)
		{
		case VK_ESCAPE:
			//quits loop
			running = false;
			break;

			//details
		case VK_F1:
		case VK_NUMPAD0:
			m->setSymbol(c->ypos, c->xpos, c->temp);
			c->temp = m->getTile(c->ypos, c->xpos).getSymbol();
			m->getTile(c->ypos, c->xpos).printDetails();
			m->setSymbol(c->ypos, c->xpos, c->symbol);
			m->print();
			break;

			//buy tower
		case VK_F2:
		case VK_NUMPAD1:
			if (m->getTile(c->ypos, c->xpos).isBuildable()){
				if (c->money - 100 < 0){
					cout << "\nOut of money!";
					break;
				}
				else{
					//Tower should extend Tile, but I can't get it working right now
					m->setTile(c->ypos, c->xpos, 1, 2);
					m->setTile(c->ypos, c->xpos, "Tower", "1", false);
					c->money - 100;
					c->temp = m->getTile(c->ypos, c->xpos).getSymbol();
					m->print();
					break;
				}
			}
			else{
				cout << "\nYou cannot build here.\n";
			}
			break;

			//upgrade tower
		case VK_F3:
		case VK_NUMPAD2:
			if (m->getTile(c->ypos, c->xpos).getName() == "Tower"){
				if (c->money - 100 < 0){
					cout << "\nOut of money!";
					break;
				}
				else{
					//Tower should extend Tile, but I can't get it working right now
					m->setTile(c->ypos, c->xpos, 2, 4);
					m->setTile(c->ypos, c->xpos, "Tower2", "2", false);
					c->money - 100;
					c->temp = m->getTile(c->ypos, c->xpos).getSymbol();
					m->print();
					break;
				}
			}
			else if (m->getTile(c->ypos, c->xpos).getName() == "Tower2"){
				if (c->money - 100 < 0){
					cout << "\nOut of money!";
					break;
				}
				else{
					//Tower should extend Tile, but I can't get it working right now
					m->setTile(c->ypos, c->xpos, 3, 6);
					m->setTile(c->ypos, c->xpos, "Tower3", "3", false);
					c->money - 100;
					c->temp = m->getTile(c->ypos, c->xpos).getSymbol();
					m->print();
					break;
				}
			}
			else{
				cout << "\nNothing to upgrade.\n";
			}
			break;

			//sell tower
		case VK_F4:
		case VK_NUMPAD3:
			if (m->getTile(c->ypos, c->xpos).getName() == "Tower"){
				cout << "\nAre you sure you want to sell this tower? Y/N\n";
				string sell;
				cin >> sell;
				if (sell == "y"){
					c->money + 100;
					m->setTile(c->ypos, c->xpos, "Scenery", "_", true);
					m->setTile(c->ypos, c->xpos, 0, 0);
					c->temp = m->getTile(c->ypos, c->xpos).getSymbol();
					m->getTile(c->ypos, c->xpos).setSymbol("%");
					m->print();
				}
				else{
					break;
				}
			}
			else if (m->getTile(c->ypos, c->xpos).getName() == "Tower2"){
				cout << "\nAre you sure you want to sell this tower? Y/N\n";
				string sell;
				cin >> sell;
				if (sell == "y"){
					c->money + 200;
					m->setTile(c->ypos, c->xpos, "Scenery", "_", true);
					m->setTile(c->ypos, c->xpos, 0, 0);
					c->temp = m->getTile(c->ypos, c->xpos).getSymbol();
					m->getTile(c->ypos, c->xpos).setSymbol("%");
					m->print();
				}
				else{
					break;
				}
			}
			else if (m->getTile(c->ypos, c->xpos).getName() == "Tower3"){
				cout << "\nAre you sure you want to sell this tower? Y/N\n";
				string sell;
				cin >> sell;
				if (sell == "y"){
					c->money + 300;
					m->setTile(c->ypos, c->xpos, "Scenery", "_", true);
					m->setTile(c->ypos, c->xpos, 0, 0);
					c->temp = m->getTile(c->ypos, c->xpos).getSymbol();
					m->getTile(c->ypos, c->xpos).setSymbol("%");
					m->print();
				}
				else{
					break;
				}
			}
			else{
				cout << "\nNothing to sell here.\n";
				break;
			}
			break;

			//MOVE LEFT
		case VK_LEFT:
			//bounds
			if (c->xpos < 1){
				c->nope();
				break;
			}
			else{
				m->setSymbol(c->ypos, c->xpos, c->temp);
				c->xpos--;
				c->temp = m->getTile(c->ypos, c->xpos).getSymbol();
				m->setSymbol(c->ypos, c->xpos, c->symbol);
				m->print();
				break;
			}

			//MOVE RIGHT
		case VK_RIGHT:
			//bounds
			if (c->xpos > m->getWidth()){
				c->nope();
				break;
			}
			else if (c->xpos < m->getWidth() + 1){
				m->setSymbol(c->ypos, c->xpos, c->temp);
				c->xpos++;
				c->temp = m->getTile(c->ypos, c->xpos).getSymbol();
				m->setSymbol(c->ypos, c->xpos, c->symbol);
				m->print();
				break;
			}

			//MOVE UP
		case VK_UP:
			//bounds
			if (c->ypos - 1 < 0){
				c->nope();
				break;
			}
			else{
				m->setSymbol(c->ypos, c->xpos, c->temp);
				c->ypos--;
				c->temp = m->getTile(c->ypos, c->xpos).getSymbol();
				m->setSymbol(c->ypos, c->xpos, c->symbol);
				m->print();
				break;
			}

			//MOVE DOWN
		case VK_DOWN:
			//bounds
			if (c->ypos > m->getHeight()){
				c->nope();
				break;
			}
			else if (c->ypos < m->getHeight() + 1){
				m->setSymbol(c->ypos, c->xpos, c->temp);
				c->ypos++;
				c->temp = m->getTile(c->ypos, c->xpos).getSymbol();
				m->setSymbol(c->ypos, c->xpos, c->symbol);
				m->print();
				break;
			}
		}
	}
	return 0;
}