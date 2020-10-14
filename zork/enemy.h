#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"

/**2. Inheritance (including virtual methods) and cascading constructors***/
class Enemy : public Character
{
public:
    Enemy(string name);
    ~Enemy();

    /****Virtual Methods*******/
    void   announcement() override {cout << "\nThere is an Enemy in this room of type: "<< name << " \n";}
    string getName() override; //overriden virtual function from character

    void   setDangerLevel(string dangerLevel);
    string getDangerLevel();

private:
    string dangerLevel;
    string name;
};

#endif // ENEMY_H
