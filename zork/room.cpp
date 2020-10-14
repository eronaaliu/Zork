#include "room.h"

Room::Room(string name, Game *game) :
    name(name)
{
    this->game = game;
    exits["north"] = nullptr;
    exits["east"]  = nullptr;
    exits["south"] = nullptr;
    exits["west"]  = nullptr;
}

/*******1. Destructors******/
Room::~Room(){
    for(auto p : itemsList){
        delete p;
    }
    itemsList.clear();
}

string Room::getName()
{
    return name;
}

//if scorpion, return !!, if player, return (), if ghoul return {}
string Room::printName(){
    string mapNames = name;

    if(game->getScorpion().getCurrentRoom() == this && game->getGhoul().getCurrentRoom() == this && game->getPlayer().getCurrentRoom() == this){ return "!(" + name + "}";}
    else if(game->getGhoul().getCurrentRoom() == this && game->getScorpion().getCurrentRoom() == this ){ return "!" + name + "}";}

    if(game->getGhoul().getCurrentRoom() == this && game->getPlayer().getCurrentRoom() == this){ return "(" + name + "!";}
    else if(game->getGhoul().getCurrentRoom() == this){ return "!" + name + "!";}

    if(game->getScorpion().getCurrentRoom() == this && game->getPlayer().getCurrentRoom() == this){ return "(" + name + "}";}
    else if(game->getScorpion().getCurrentRoom() == this){ return "{" + name + "}";}

    if(game->getPlayer().getCurrentRoom() == this){ return "(" + name + ")";
    }else{ return "-" + mapNames + "-";
    }
}

void Room::setExits(Room *north, Room *east, Room *south, Room *west)
{
    exits["north"] = north;
    exits["east"]  = east;
    exits["south"] = south;
    exits["west"]  = west;
}

Room *Room::getExit(string direction)
{
    return exits[direction];
}


//add items to list
void Room::addItemsToRoom(item *items){
    itemsList.push_back(items);
}


vector<item*> Room::getItemsInList(){
    return itemsList;
}

item* Room::takeItem(string itemName){
    for(int i = 0; i < (int)itemsList.size(); i++){
        if(itemsList[i]->getName() == itemName){
            itemsList.erase(itemsList.begin()+i);
            return itemsList[i];
        }
    }
    return NULL;
}


string Room::displayItems() {
    string tempString = "Items in room = ";
    int sizeItems = (itemsList.size());
    if (itemsList.size() < 1) {
        tempString = " items in room ";
        cout << itemsList.size();
        }
    else if (itemsList.size() > 0) {
       int x = (0);
        for (int n = sizeItems; n > 0; n--) {
            tempString = tempString + itemsList[x]->getName() + "  " ;
            x++;
            }
        }
    return tempString;
}


