#ifndef ITEM_H
#define ITEM_H

#include<iostream>

class item
{
public:
    item(std::string name);
    std::string getName();

private:
    std::string name;
};

#endif // ITEM_H
