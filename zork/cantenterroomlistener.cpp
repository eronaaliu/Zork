#include "cantenterroomlistener.h"

#include "eventmanager.h"
#include "game.h"

CantEnterRoomListener::CantEnterRoomListener(Game *game)
{
    this->game = game;
}

void CantEnterRoomListener::run(void *args)//void args takes anything
{
    if (game->is_over()) {
        return;
    }

    Room *room = (Room *) args;

    if (room->getName() == "J") {
        EventManager::getInstance().trigger("victory");
    }
}
