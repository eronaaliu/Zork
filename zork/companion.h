#ifndef COMPANION_H
#define COMPANION_H

#include "character.h"


class Companion : public Character
{
public:
    Companion();
    Companion(string name);

    string getName();
private:
    string name;
    int health;
};

#endif // COMPANION_H
