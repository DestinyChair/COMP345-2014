#include <iostream>
#include <Windows.h>
#include "Map.h"
#include "PathMaker.h"

using namespace std;

int main(){
	int height, width;
	const int MAXD = 64;
	const int MIND = 8;
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
	Map* m = new Map(height, width);
	//remember that the height and width are +2 for the edges!

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
	system("pause>nul");
	return 0;
}