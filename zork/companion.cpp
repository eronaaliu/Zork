#include "companion.h"

Companion::Companion(string name) : Character(name)
{
    this->name = name;
}
string Companion::getName(){
    return name;
}

