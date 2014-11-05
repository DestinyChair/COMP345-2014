#pragma once
#include <vector>
#include <list>
#include "Critter.h"

class Subject
{
    std::vector<Critter*> list;

    public:
        void attach(Critter *c);
        void detach(Critter *c);
        void notify(int damage);
};
