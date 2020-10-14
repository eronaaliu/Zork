#ifndef GAME_H
#define GAME_H

#include<string>
#include<vector>

#include "enemy.h"
#include "room.h"
#include "derived.h"

using namespace std;

class Game
{
public:
    Game();
    ~Game();

    void reset(bool show_update = true);

    void map();
    void hint();
    void info();
    void go(string direction);
    void teleport();
    void take(string itemName);
    void attack(string name);
    void update_screen();

    /******3. Templates *********************/
    template<typename T> void damagePlayer(T damagePlayer){
        player.setHealth(player.getHealth()-damagePlayer);
    }

    /*****Binary Operator Overloading*******/
    void operator+();

    void noOfEnemiems();
    void ghoulDetails();
    void scorpionDetails();
    void roomVisitAttemptIncrement();
    void roamingEnemy();
    void goScorpion();

    void setOver(bool over);
    bool is_over();
    void setCurrentRoom(Room *next);
    void printName();
    void healthStatus();

    string    tempPrint();
    Character &getPlayer();
    Enemy     &getScorpion();
    Enemy     &getGhoul();
    Character* p;
    derived    d;

private:
    Enemy          scorpion;
    Enemy          ghoul;
    Character      player;
    vector<Room *> rooms;
    bool           gameOver;
};
#endif // GAME_H
