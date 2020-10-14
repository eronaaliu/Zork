#include "attacklistener.h"

#include "eventmanager.h"
#include "game.h"

AttackListener::AttackListener(Game* game)
{
    this->game = game;
}

void AttackListener::run(void *)
{
    if(game->getPlayer().getCurrentRoom() == game->getGhoul().getCurrentRoom() && game->getGhoul().getHealth() != 0){
        cout << "You have caused 50 damage with your powerful strike!\n";
        game->getGhoul().setHealth(game->getGhoul().getHealth()-50);
    }else if(game->getPlayer().getCurrentRoom() == game->getScorpion().getCurrentRoom()){
        cout << "You have caused 25 damage with your powerful strike!\n";
        game->getScorpion().setHealth(game->getScorpion().getHealth()-25);
    }
}
