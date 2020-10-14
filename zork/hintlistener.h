#ifndef HINTLISTENER_H
#define HINTLISTENER_H

#include "eventlistener.h"

class Game;

// A listener for Hint command
class HintListener : public EventListener
{
public:
    HintListener(Game *game);
    void run(void *args) override;
private:
    Game *game;
};

#endif // HINTLISTENER_H

