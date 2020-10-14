#include "takelistener.h"

#include "eventmanager.h"
#include "game.h"

TakeListener::TakeListener(Game *game)
{
    this->game = game;
}

void TakeListener::run(void *args_ptr)
{
    if (game->is_over()) {

        return;
    }

    vector<string> *args = (vector<string> *) args_ptr;

    if (args->size() > 1) {
        game->take(args->at(1));
    } else {
        cout << "Must specify an item" << endl;
    }
}
