#pragma once
#include <iostream>
#include <string>
#include "Observer.h"

class Critter: public Observer
{
    public:
        Critter(int hitpoints, int critterId);
        void update(int damage);
    private:
        int hitpoints;
        int critterId;
};
