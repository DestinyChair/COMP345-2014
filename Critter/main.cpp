#include <iostream>
#include "Game.h"
#include "Critter.h"

using namespace std;

int main()
{
    Game towerDefense;

    Critter c1(20, 1);
    Critter c2(30, 2);
    Critter c3(40, 3);
    Critter c4(50, 4);

    towerDefense.attach(&c1);
    towerDefense.attach(&c2);
    towerDefense.attach(&c3);
    towerDefense.attach(&c4);

    cout << "Tower attacks critters with 25 points of damage" << endl;

    towerDefense.damage(25);

    cout << "Tower attacks critters with 10 points of damage" << endl;

    towerDefense.damage(10);

    return 0;
}
