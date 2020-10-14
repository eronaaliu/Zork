#include "item.h"

item::item(std::string name)
{
    this->name = name;
}

std::string item::getName(){
    return name;
}

