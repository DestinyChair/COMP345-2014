#include "Critter.h"

using namespace std;

Critter::Critter(int hitpoints, int critterId)
{
    this->hitpoints = hitpoints;
    this->critterId = critterId;
}

void Critter::update(int damage)
{
    this->hitpoints = hitpoints - damage;

    if(hitpoints >= 0)
    {
        cout << "Critter #" << critterId << " health is now at " << hitpoints << endl;
    }
}
