#include "character.h"

#include "eventmanager.h"

/*******Cascading Constructors Destructors*****************/
/****9. Initializer list******************************/
Character::Character(string name) : health(100), stamina(100), currentRoom(nullptr)
{
    this->name  = name; // We need to use "this->" to differentiate between the "name" argument and the "name" from the class.
    //cout << "Character Constructor called" << endl;
}

/*******1. Destructors******/
Character::~Character(){
    //cout << "Character Destructor called" << endl;
    for(auto p : inventoryList){
        delete p;
    }
    inventoryList.clear();
}

void Character::setRoomCount(int x){
    this->roomCount = x;
}

void Character::noOfRoomVisitAttempts()
{
    cout << "\nRooms visit attempts: " << roomCount << endl;
}

string Character::getName()
{
    return name;
}

int Character::getHealth()
{
    return health;
}

int Character::getStamina()
{
    return stamina;
}

Room *Character::getCurrentRoom()
{
    return currentRoom;
}


void Character::setName(string name)
{
    this->name = name;
}

void Character::setHealth(int health)
{
    if (health <= 0) {
        health = 0;
        EventManager::getInstance().trigger("characterDeath", this);
    }

    this->health = health;
}

void Character::setStamina(int stamina)
{
    if (stamina <= 0) {
        stamina = 0;
        EventManager::getInstance().trigger("characterDeath", this);
    }

    this->stamina = stamina;
}

void Character::setCurrentRoom(Room *next)
{
    currentRoom = next;
}

void Character::addItems(item* item){
    inventoryList.push_back(item);
}

bool Character::checkItems(string itemName){
    for(int i = 0; i < (int)inventoryList.size(); i++){
        if(inventoryList[i]->getName() == itemName){
            return true;
        }
    }
    return false;
}

item* Character::removeItemFromList(string itemName){
    for(int i = 0; i < (int)inventoryList.size(); i++){
        if(inventoryList[i]->getName() == itemName){
            inventoryList.erase(inventoryList.begin()+i);
            return inventoryList[i];
        }
    }
    return NULL;
}
