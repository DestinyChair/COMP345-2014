#include "Subject.h"
#include <algorithm>

using namespace std;

void Subject::attach(Critter *c)
{
    list.push_back(c);
}
void Subject::detach(Critter *c)
{
    list.erase(std::remove(list.begin(), list.end(), c), list.end());
}

void Subject::notify(int damage)
{
    for(vector<Critter*>::const_iterator iter = list.begin(); iter != list.end(); ++iter)
    {
        if(*iter != 0)
        {
            (*iter)->update(damage);
        }
    }

    cout << endl;
}
