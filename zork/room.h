#ifndef ROOM_H
#define ROOM_H

#include "character.h"
#include "game.h"

#include<map>
#include<string>
#include<vector>

class Game;
using namespace std;
/*********Destructor**********/
class Room
{
public:
    Room(string name, Game *game);
    ~Room();

    string getName();
    void   setExits(Room *north, Room *east, Room *south, Room *west);
    Room   *getExit(string direction);
    void   addItemsToRoom(item* item);
    void   removeItemsFromRoom(item *items);
    item*  takeItem(string itemName);
    string displayItems();
    string printName();
    void   operator+();

    vector<item*> itemsList;
    vector<item*> getItemsInList();

private:
    Game  *game;
    string name;

    map<string, Room *> exits;
};

#endif // ROOM_H
