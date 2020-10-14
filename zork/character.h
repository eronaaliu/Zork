#ifndef CHARACTER_H
#define CHARACTER_H

#include<string>
#include<vector>

#include "item.h"

using namespace std;

// No need to include room since we're only working with pointers.
// This is how we tell the compiler "there will be a room eventually".
// This is called a "forward declaration".

class Room;

class Character
{
public:
    Character(string name);
    ~Character();
    /**********Friend***************/
    friend class Game;

    /*********Static*Dispatch********/
    int     getHealth();
    int     getStamina();
    void    noOfRoomVisitAttempts();
    Room    *getCurrentRoom();

    /*********Virtual functions and polymorphism******/
    virtual void   announcement(){cout << "\nStatus: Uninjured" << endl;}
    virtual string getName();//dynamic bind at run time

    /*********Static*Dispatch***REGULAR FUNCTIONS AT COMPILE TIME***/
    void setRoomCount(int x);
    void setCurrentRoom(Room *next);
    void addItems(item* item);
    bool checkItems(string itemName);

    vector<item*> inventoryList;
    item*         removeItemFromList(string itemName);

    void setName(string name);
    void setHealth(int health);
    void setStamina(int stamina);

    /******Unary operator overloading******************/
    void operator ++(){ ++roomCount;}
    void operator --(){ --stamina;}

    /******Binary operator overloading******************/
    bool operator +(Character& c){ if(currentRoom == c.getCurrentRoom()){ return true; } else { return false; }
}

private:
    string  announcePlayer;
    string  name;
    int     roomCount = 0;
    int     health;
    int     stamina;
    Room    *currentRoom;
};

#endif // CHARACTER_H
