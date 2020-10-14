#include "damagelistener.h"

#include "eventmanager.h"
#include "game.h"

DamageListener::DamageListener(Game* game)
{
    this->game = game;
}

void DamageListener::run(void *)
{
    if(game->getScorpion().getCurrentRoom() == game->getPlayer().getCurrentRoom()){
        game->damagePlayer(5);
        cout <<"\nYou have been hit, -5 HP" << endl;
    }else if(game->getGhoul().getCurrentRoom() == game->getGhoul().getCurrentRoom()){
        cout <<"\nYou have been hit, -16.6 HP" << endl;
        game->damagePlayer(16.6);
    }else{
        game->damagePlayer(16.6);
    }
}
