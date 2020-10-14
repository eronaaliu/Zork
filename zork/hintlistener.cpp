#include "hintlistener.h"

#include "game.h"

HintListener::HintListener(Game *game)
{
    this->game = game;
}

void HintListener::run(void *)
{
    game->hint();
}
